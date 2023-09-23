#version 330 core

in vec3 Normal;
in vec3 FragPos;
uniform vec3 uObjectColor;
uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;
uniform float uShininess;
out vec4 FragColor;

void main()
{
	vec3 ambient = 0.1 * uObjectColor * uLightColor;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(uLightPos - FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = uLightColor * diff * uObjectColor;

	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShininess);
	vec3 specular = spec * uLightColor;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0);
}