#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec4 ObjectColor;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
	float lightIntense = 0.7;

	vec3 resultColor = (lightColor + vec3(ObjectColor)) * lightIntense;

	float ambientLight = 0.3;

	vec3 ambient;
	ambient = ambientLight * resultColor;

	vec3 normalVector = normalize (Normal);

	vec3 lightDir;
	lightDir = normalize (lightPos - FragPos);

	float diffuseStrength = 0.5;

	float diffuseLight;
	diffuseLight = max (dot(normalVector, lightDir), 0.0);

	vec3 diffuse;
	diffuse = diffuseLight * resultColor * diffuseStrength;

	int shininess = 32;

	vec3 viewDir;
	viewDir = normalize (viewPos - FragPos);

	vec3 reflectDir;
	reflectDir = reflect (-lightDir, normalVector);

	float spec_strength = 0.5;

	float specularLight;
	specularLight = max (dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, shininess);

	vec3 specular;
	specular = spec_strength * specularLight * vec3(0.9, 0.9, 0.9);

	vec3 result;
	result = (ambient + diffuse + specular) * resultColor;
	FragColor = vec4 (result, ObjectColor.a);
}
