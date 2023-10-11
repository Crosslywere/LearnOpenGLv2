#version 330 core

uniform vec3 viewPos;
uniform samplerCube skybox;
uniform float refractionIndex;

varying vec3 Normal;
varying vec3 FragPos;

void main()
{
	float ratio = 1.0 / clamp(refractionIndex, 1.0, 2.0);
	vec3 I = normalize(FragPos - viewPos);
	vec3 R = refract(I, normalize(Normal), ratio);
	gl_FragColor = vec4(textureCube(skybox, R).rgb, 1.0);
}