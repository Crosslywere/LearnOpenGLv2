#version 330 core

uniform vec3 viewPos;
uniform samplerCube skybox;

varying vec3 Normal;
varying vec3 FragPos;

void main()
{
	vec3 I = normalize(FragPos - viewPos);
	vec3 R = reflect(I, normalize(Normal));
	gl_FragColor = vec4(textureCube(skybox, R).rgb, 1.0);
}