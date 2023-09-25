#version 330 core
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;

	float constant;
	float linear;
	float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
uniform Material uMaterial;
uniform Light uLight;
uniform vec3 uViewPos;
out vec4 FragColor;

void main()
{
	vec3 ambient = uLight.ambient * texture(uMaterial.diffuse, TexCoords).rgb;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(uLight.position - FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * uLight.diffuse * texture(uMaterial.diffuse, TexCoords).rgb;

	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), uMaterial.shininess);
	vec3 specular = spec * uLight.specular * texture(uMaterial.specular, TexCoords).rgb;

	float dist = distance(uLight.position, FragPos);
	float attenuation = 1.0 / (uLight.constant + uLight.linear * dist + uLight.quadratic * (dist * dist));

	vec3 result = ambient + attenuation * (diffuse + specular);
	FragColor = vec4(result, 1.0);
}