#version 330 core

in vec3 Color;

uniform vec3 uColor;

void main()
{
	gl_FragColor = vec4(Color * uColor, 1.0);
}