#include "Player.h"

void Player::Init()
{
	Left_Keydown = 0;
	Right_Keydown = 0;

	PosMat = glm::mat4(1.0f);
	PosMat = glm::translate(PosMat, glm::vec3(0.0f, -1.0f, 0.0f));

	rad = 0.0f;
	RotMat = glm::mat4(1.0f);

	SclMat = glm::mat4(1.0f);
	SclMat = glm::scale(SclMat, glm::vec3(1.0f, 0.3f, 2.0f));

	dirVec = glm::vec3(0.0f, 0.0f, 1.0f);

	Speed = 1.0f;

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

void Player::Move(int key)
{
	if (key == GLUT_KEY_RIGHT)
	{
		RotMat = glm::rotate(RotMat, glm::radians(-rad), glm::vec3(0.0f, 0.0f, 1.0f));

		rad += 1.5 * Speed;
		if (rad > 360)
		{
			rad -= 360;
		}

		RotMat = glm::rotate(RotMat, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else if (key == GLUT_KEY_LEFT)
	{
		RotMat = glm::rotate(RotMat, glm::radians(-rad), glm::vec3(0.0f, 0.0f, 1.0f));

		rad -= 1.5f * Speed;
		if (rad < 0)
		{
			rad += 360;
		}

		RotMat = glm::rotate(RotMat, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Player::Update()
{
}

void Player::Key_Input(unsigned char key)
{
}

void Player::sKey_Input(int key)
{
	Move(key);
}

void Player::Render(GLuint ShaderProgram)
{
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "modelTransform");

	glm::mat4 TR;
	TR = RotMat * PosMat* SclMat;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

float Player::getSpeed()
{
	return Speed;
}

glm::mat4 Player::getPosition()
{
	return RotMat * PosMat;
}
