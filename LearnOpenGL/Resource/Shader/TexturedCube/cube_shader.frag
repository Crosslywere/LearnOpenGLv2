#version 330 core
in vec2 TexCoords;
uniform sampler2D uTexture2D;
out vec4 FragColor;

void main()
{
	FragColor = texture(uTexture2D, TexCoords);
}