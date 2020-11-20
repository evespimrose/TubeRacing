#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 ObjectColor;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightColor;

uniform int shininess;
uniform float diffuse_strength;
uniform float spec_strength;


struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLights[20];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0) * diffuse_strength;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess) * spec_strength;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // 결과들을 결합
    vec3 ambient  = light.ambient * diffuse_strength;
    vec3 diffuse  = light.diffuse * diff;
    vec3 specular = light.specular * spec;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

void main()
{
	float lightIntense = 0.7;

	vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < 20; i++)
    {
        result += CalcPointLight(pointLights[i], normalize(Normal), FragPos, normalize(viewPos - FragPos)) * ObjectColor;
    }

	FragColor = vec4 (result, 1.0);
}
