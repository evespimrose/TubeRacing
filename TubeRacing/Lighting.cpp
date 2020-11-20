#include "Lighting.h"
#include "string"

void Lighting::Init(float zOffset, float xOffset)
{
	posx = xOffset;
	posz = zOffset;

}
void Lighting::Render(GLuint ShaderProgram)
{
	std::string str;

	for (int i = 0; i < 20; ++i)
	{
		str = "PointLights[" + std::to_string(i) + "]";

		std::string tmp = ".position";
		glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(glm::vec3(posx, 0, posz)));

		tmp = ".ambient";
		glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

		tmp = ".diffuse";
		glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(glm::vec3(posx, 0, posz)));

		tmp = ".specular";
		glUniform3fv(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1, glm::value_ptr(glm::vec3(posx, 0, posz)));

		tmp = ".constant";
		glUniform1f(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 1.0f);

		tmp = "linear";
		glUniform1f(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 0.09f);

		tmp = "quadratic";
		glUniform1f(glGetUniformLocation(ShaderProgram, (str + tmp).c_str()), 0.032f);
	}

}