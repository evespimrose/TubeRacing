#include "Lighting.h"

void Lighting::Init(float zOffset, float xOffset)
{
	posx = xOffset;
	posz = zOffset;
}


float Lighting::getzOffset()
{
	return posz;
}

void Lighting::Render(GLuint ShaderProgram, int ind)
{
	std::string str;

	str = "pointLights[" + std::to_string(ind) + "]";

	std::string tmp = ".position";
	glm::vec3 p = glm::vec3(posx, 0, posz);
	glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(p));

	p = glm::vec3(1.0f, 1.0f, 1.0f);

	tmp = ".ambient";
	glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(p));

	tmp = ".diffuse";
	glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(p));

	tmp = ".specular";
	glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(p));

	tmp = ".constant";
	glUniform1f(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), constant);

	tmp = ".linear";
	glUniform1f(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), linear);

	tmp = ".quadratic";
	glUniform1f(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), quadratic);
}