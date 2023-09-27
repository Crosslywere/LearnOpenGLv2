#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;

	float constant;
	float linear;
	float quadratic;

	float innerCutoff;
	float outerCutoff;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
uniform Material uMaterial;
uniform DirectionalLight uDirectionalLight;
uniform PointLight uPointLight[4];
uniform SpotLight uSpotLight;
uniform vec3 uViewPos;
out vec4 FragColor;

vec3 calculateDirectionalLight(in DirectionalLight light, in vec3 normal, in float shininess)
{
	vec3 ambient = light.ambient * texture(uMaterial.diffuse, TexCoords).rgb;

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * light.diffuse * texture(uMaterial.diffuse, TexCoords).rgb;

	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
	vec3 specular = spec * light.specular * texture(uMaterial.specular, TexCoords).rgb;

	vec3 result = ambient + diffuse + specular;
	return result;
}

vec3 calculatePointLight(in PointLight light, in vec3 normal, in float shininess)
{
	vec3 ambient = light.ambient * texture(uMaterial.diffuse, TexCoords).rgb;

	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * light.diffuse * texture(uMaterial.diffuse, TexCoords).rgb;

	vec3 viewDir = normalize(uViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
	vec3 specular = spec * light.specular * texture(uMaterial.specular, TexCoords).rgb;

	float dist = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	vec3 result = ambient + diffuse + specular;
	return attenuation * result;
}

vec3 calculateSpotLight(in SpotLight light, in vec3 normal, in float shininess)
{
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	if (theta > light.outerCutoff)
	{
		vec3 ambient = light.ambient * texture(uMaterial.diffuse, TexCoords).rgb;
		
		float diff = max(dot(lightDir, normal), 0.0);
		vec3 diffuse = diff * light.diffuse * texture(uMaterial.diffuse, TexCoords).rgb;

		vec3 viewDir = normalize(uViewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);
		vec3 specular = spec * light.specular * texture(uMaterial.specular, TexCoords).rgb;

		float dist = distance(light.position, FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
		
		float epsilon = light.innerCutoff - light.outerCutoff;
		float intensity = clamp((theta - light.innerCutoff) / epsilon, 0.0, 1.0);

		return intensity * attenuation * (ambient + diffuse + specular);
	}
	return vec3(0.0);
}

void main()
{
	vec3 normal = normalize(Normal);
	vec3 result = calculateDirectionalLight(uDirectionalLight, normal, uMaterial.shininess);
	for (int i = 0; i < 4; i++)
	{
		result += calculatePointLight(uPointLight[i], normal, uMaterial.shininess);
	}
	result += calculateSpotLight(uSpotLight, normal, uMaterial.shininess);
	FragColor = vec4(result, 1.0);
}