# Learning OpenGL

My adventures learning OpenGL **(Don't ask about version 1)**

Welcome to my repository detailing my adventure into learning graphics programming through _OpenGL_.

This project uses the [premake5](https://premake.github.io) build system.

## Projects

1. **Textured Cube** Created a textured cube by defining vertices with 3D position and texture coordinates.
    The vertex data is sent to the GPU via a vertex buffer object. The vertices are then used on the shader.

    The shader has a uniform for the model-view-projection matrix `uniform mat4 uMVP` that multiplies the position data
    in order to transform these coordinates into a normalized device coordinate system relative to the view's frustrum/clip space.

    The texture is applied using the texture coordinates using a sampler2D on the fragment shader of the shader program.
    The fragment is derived by sampling the that texture using the texture coordinate and the 2D texure.

2. **Lighting** Created the following lighting models:
    - **Basic Phong Lighting** This lighting model is a combination of ambient, diffuse and specular lighting.

        Ambient light is the indirect light from a scene. This type of light is simply a multiplication of the ambient value
        and the diffuse color of the object being lit.

        ```glsl
        float ambientAmt;
        vec3 lightColor;
        vec3 objectDiffuse;
        vec3 ambient = ambientAmt * lightColor * objectDiffuse;
        ```

        Diffuse light is the direct light from the light source(s) of a scene. To calculate the diffuse you'd have to
        calculate the light's direction, the normalized the light's position minus the fragment's position.
        Then the dot product of light's direction and the normal gives the amount of light that hits that fragment
        (this is within a range of -1 to 1 so should be clamped from 0 to 1). This value is can then be multiplied by the diffuse color
        and the light color to give the resulting fragment color.

        ```glsl
        vec3 normal;
        vec3 lightPosition;
        vec3 fragPosition;
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
        vec3 viewPosition;
        float shininess;
        vec3 viewDirection = normalize(viewPosition - fragPosition);
        vec3 reflectDirection = reflect(-lightDirection, normal);
        float specularAmt = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
        vec3 specular = specularAmt * lightColor;
        ```

        The final fragment color is then the sum of the ambient, diffuse and specular values.

        ```glsl
        vec3 result = ambient + diffuse + specular;
        ```
