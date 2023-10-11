# Learning OpenGL

My adventures learning OpenGL **(Don't ask about version 1)**

Welcome to my repository detailing my adventure into learning graphics programming through _OpenGL_.

This project uses the [premake5](https://premake.github.io) build system.

## Projects

1. **Textured Cube** Created a textured cube by defining vertices with 3D position and texture coordinates.
    The vertex data is sent to the GPU via a vertex buffer object. The vertices are then used on the shader.

    The shader has a uniform for the model-view-projection matrix that multiplies the position data
    in order to transform these coordinates into a normalized device coordinate system relative to the view's frustrum/clip space.

    The texture is applied using the texture coordinates using a sampler2D on the fragment shader of the shader program.
    The fragment is derived by sampling the that texture using the texture coordinate and the 2D texure.

2. **Lighting** Created the following lighting models:
    - **Basic Phong Lighting** This lighting model is a combination of ambient, diffuse and specular lighting.

        Ambient light is the indirect light from a scene. This type of light is simply a multiplication of the ambient value
        and the diffuse color of the object being lit.

        ```glsl
        uniform float ambientAmt;
        uniform vec3 lightColor;
        uniform vec3 objectDiffuse;
        vec3 ambient = ambientAmt * lightColor * objectDiffuse;
        ```

        Diffuse light is the direct light from the light source(s) of a scene. To calculate the diffuse you'd have to
        calculate the light's direction which is the normalized result of the light's position minus the fragment's position.
        Then the dot product of light's direction and the normal gives the amount of light that hits that fragment
        (this is within a range of -1 to 1 so should be clamped from 0 to 1). This value is can then be multiplied by the diffuse color
        and the light color to give the resulting fragment color.

        ```glsl
        in vec3 normal;
        uniform vec3 lightPosition;
        uniform vec3 fragPosition;
        vec3 lightDirection = normalize(lightPosition - fragPosition);
        float diffuseAmt = max(dot(lightDirection, normal), 0.0);
        vec3 diffuse = diffuseAmt * objectDiffuse * lightColor;
        ```

        The specular value is a product of shiny surfaces reflecting light around the normal direction of the surface.
        To calculate the specular light the view direction and the reflection direction is needed. The view direction is calculated similar
        to the light's direction meaning its the view's position minus the fragment's position. The reflection direction is calculated by
        performing a reflect of the inverse light direction about the normal. The amount of specular reflection is then a power of the
        clamped, between 0 and 1, dot product of the reflection direction and the view direction, with a shininess factor.
        The specular amount multiplied by the light's color will then result in the specular value of the fragment.

        ```glsl
        uniform vec3 viewPosition;
        uniform float shininess;
        vec3 viewDirection = normalize(viewPosition - fragPosition);
        vec3 reflectDirection = reflect(-lightDirection, normal);
        float specularAmt = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
        vec3 specular = specularAmt * lightColor;
        ```

        The final fragment color is then the sum of the ambient, diffuse and specular values.

        ```glsl
        vec3 result = ambient + diffuse + specular;
        ```

    - **Sampling Lighting** This lighting model is similar to the _Basic Phong Lighting_ model, but instead of using a flat color,
        uses a texture instead.

        There are two textures to sample from, one for the diffuse color, and another for the specular texture.
        This is a material that has a texture for diffuse, specular, and the float for the shininess.

        ```glsl
        struct Material
        {
            sampler2D diffuse;
            sampler2D specular;
            float shininess;
        };
        ```

        This model also introduces using a struct to encapsulate all of the light's properties as well.

        ```glsl
        struct Light
        {
            vec3 position;

            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };
        ```

        To get the fragment color sample the appropriate texture.

        ```glsl
        in vec2 texCoords;
        vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;
        vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;
        vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;
        ```

    - **Point Light** This lighting model simulate's a light source at a point in space that reduces in intensity with distance.
    To compute the amount of light for a given fragment, the shader needs to take into consideration the light's
    position, constant value, linear value and quadratic value.

        The constant, linear and quadratic values define a curve for the light to attenuate according to. The way to calculate attenuation is:

        ```glsl
        float dist = distance(light.position, fragPosition);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
        ```

        This attenuation value can then be used to modify the final output fragment color.

        ```glsl
        vec3 result = ambient + attenuation * (diffuse + specular);
        ```

    - **Spot Light _(Flash light)_** This lighting model simulates a light coming from a point going in a particular direction and all the while creating a circle with its cross section, in other words a flash light.

        This is done by creating an additional variables in the light's `struct`. These values are a as follows:

        ```glsl
        struct Light
        {
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;

            vec3 position;
            vec3 direction;

            // For attenuation of the light source
            float constant;
            float linear;
            float quadratic;

            float outerCutoff;
            float innerCutoff;
        };
        ```

        The inner and outer cutoff values are the cosines of the angles that define the inner and outer radius respectively.
        The outer cutoff is where the light nolonger has any effect, or in other words the outermost edge of the light's casted circle.
        The inner cutoff on the other hand is the inner circle where light is at its most intense. From the inner circle to the outer circle
        the intensity of the light drops from a 1 to a 0. So in order to determine the area where the light would affect the following calculation is done:

        ```glsl
        vec3 lightDirection = normalize(light.position - fragPosition);
        float theta = dot(lightDirection, normalize(-light.direction));
        if (theta > light.outerCutoff)
        {
            // Perform light calculation
        }
        else
        {
            // Return nothing (or ambient for a little light in the scene)
        }
        ```

        With this the light will only cast a circle.

        But this isn't enough to simulate the light. To make it more like a spot/flash light its intensity would have to be reduced the farther away from the inner cutoff it goes.
        The intensity reduction is achieved by the following calculation:

        ```glsl
        float epsilon = light.innerCutoff - light.outerCutoff;
        float intensity = clamp((theta - light.innerCutoff) / epsilon, 0.0, 1.0);
        ```

        This intensity can then be multiplied by the final result to get the final fragment color.

    - **Multiple Light Sources** This simply combines all other lighting models ie. Spot, Point and Directional lights.
        All the lights in the scene are calculated for each surface.
        The light sources are then attenuated based on their position and strength (quadratic and linear values) except for the directional light which has a global presense. There are a total of 6 light sources. That is 1 directional light, 4 point lights, and 1 spot light.
        The spot light is tied to the camera's position and front direction so it acts as a flash light.

3. **Cubemaps** Created a cubemap as a skybox. A cubemap is a type of texture. This texture has 6 images attached to itself.
    These being:

    - `GL_TEXTURE_CUBE_MAP_POSITIVE_X`
    - `GL_TEXTURE_CUBE_MAP_NEGATIVE_X`
    - `GL_TEXTURE_CUBE_MAP_POSITIVE_Y`
    - `GL_TEXTURE_CUBE_MAP_NEGATIVE_Y`
    - `GL_TEXTURE_CUBE_MAP_POSITIVE_Z`
    - `GL_TEXTURE_CUBE_MAP_NEGATIVE_Z`

    These textures are all combined into on singular texture being the cubemap. The texture is rendered onto a cube that uses its vertex positions to sample the texture.
    The cubemap's texture is sampled by using a 3D coordinate of it cube drawn to get its fragment color.

## Backends

1. **Framebuffers** A framebuffer is a buffer on the gpu that will be written to on every frame drawn if bound. Framebuffers can store color data, depth data, stencile data
    or a combination of these. In the `Window` class a framebuffer is used to capture the color data. This data is stored on an empty texture on the GPU.
    To then render the output image for the cureent frame, the texture is rendered onto a quad that spans the screen using a simple shader.
