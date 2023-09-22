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
