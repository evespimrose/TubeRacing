#include "Bullet.h"

void Bullet::Init(glm::vec3 playerPos, GLuint vao, float PlayerSpeed, float rad)
{
	PosVec = playerPos;
	PosVec.z += 0.5f;

	PosMat = glm::mat4(1.0f);
	PosMat = glm::translate(PosMat, PosVec);

	rotate = rad;
	Speed = PlayerSpeed + 0.3f;
	VAO = vao;
}

void Bullet::Render(GLuint ShaderProgram)
{
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "modelTransform");

	glm::mat4 TR;
	TR = PosMat;
	TR = glm::scale(TR, glm::vec3(0.1f, 0.1f, 0.1f));

	unsigned int specularLocation = glGetUniformLocation(ShaderProgram, "spec_strength");
	unsigned int diffuseLocation = glGetUniformLocation(ShaderProgram, "diffuse_strength");
	unsigned int shininessLocation = glGetUniformLocation(ShaderProgram, "shininess");

	glUniform1f(specularLocation, specular);
	glUniform1f(diffuseLocation, diffuse);
	glUniform1i(shininessLocation, shininess);


	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 144);
}

void Bullet::Move()
{
	PosVec.z += Speed;
	PosMat = glm::translate(PosMat, glm::vec3(0, 0, Speed));
}

float Bullet::getzOffset()
{
	return PosVec.z;
}

float Bullet::getRotate()
{
	return rotate;
}
