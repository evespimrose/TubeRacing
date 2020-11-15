#include "Player.h"

void Player::Init()
{
	PosMat = glm::mat4(1.0f);
	RotMat = glm::mat4(1.0f);

	SclMat = glm::mat4(1.0f);
	SclMat = glm::scale(SclMat, glm::vec3(1.0f, 0.3f, 2.0f));

	dirVec = glm::vec3(0.0f, 0.0f, 1.0f);

	dx = 0;
	dy = 0;
	dz = 0;

	posx = 0;
	posy = 0;
	posz = 0;

	acc = 0;
	dec = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), Cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), Normal, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), Indices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);
}

void Player::Move()
{
}

void Player::Update()
{
}

void Player::Key_Input(unsigned char key)
{
}

void Player::sKey_Input(int key)
{
}

void Player::Render(GLuint ShaderProgram)
{
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "modelTransform");

	glm::mat4 TR;
	TR = SclMat * RotMat * PosMat;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

glm::vec3 Player::getSpeed()
{
	return glm::vec3(dx, dy, dz);
}

glm::vec3 Player::getPosition()
{
	return glm::vec3(posx, posy, posz);
}
