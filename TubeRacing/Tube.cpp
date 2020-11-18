#include "Tube.h"

void Tube::Init(float Offset, GLuint vao)
{
	zOffset = Offset;
	VAO = vao;
}

void Tube::Render(GLuint ShaderProgram)
{
	glBindVertexArray(VAO);

	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "modelTransform");

	glm::mat4 TR = glm::mat4(1.0f);
	TR = glm::translate(TR, glm::vec3(0.0f, 0.0f, zOffset));

	unsigned int specularLocation = glGetUniformLocation(ShaderProgram, "spec_strength");
	unsigned int diffuseLocation = glGetUniformLocation(ShaderProgram, "diffuse_strength");
	unsigned int shininessLocation = glGetUniformLocation(ShaderProgram, "shininess");

	glUniformMatrix4fv(specularLocation, 1, GL_FALSE, &specular);
	glUniformMatrix4fv(diffuseLocation, 1, GL_FALSE, &diffuse);
	glUniformMatrix4fv(shininessLocation, 1, GL_FALSE, &shininess);

	TR = glm::scale(TR, glm::vec3(2.5f, 2.5f, 2.5f));
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 1200);
}

float Tube::getzOffset()
{
	return zOffset;
}
