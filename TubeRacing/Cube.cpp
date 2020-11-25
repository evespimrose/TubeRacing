#include "Cube.h"


void Cube::Init(float Offset, GLuint vao)
{
	VAO = vao;
	zOffset = Offset;
	PosVec = glm::vec3(0.0f, -3.5f, zOffset);

	PosMat = glm::mat4(1.0f);
	PosMat = glm::translate(PosMat, PosVec);

	rotate = rand() % 360;
	RotMat = glm::mat4(1.0f);

	RotMat = glm::rotate(RotMat, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	PosVec = glm::rotate(PosVec, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Cube::Render(GLuint ShaderProgram)
{
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "modelTransform");
	glm::mat4 TR;
	TR = RotMat * PosMat;

	unsigned int specularLocation = glGetUniformLocation(ShaderProgram, "spec_strength");
	unsigned int diffuseLocation = glGetUniformLocation(ShaderProgram, "diffuse_strength");
	unsigned int shininessLocation = glGetUniformLocation(ShaderProgram, "shininess");

	glUniform1f(specularLocation, specular);
	glUniform1f(diffuseLocation, diffuse);
	glUniform1i(shininessLocation, shininess);


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

float Cube::getzOffset()
{
	return zOffset;
}
float Cube::getRotate()
{
	return rotate;
}
