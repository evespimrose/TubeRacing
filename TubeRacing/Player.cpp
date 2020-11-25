#include "Player.h"

void Player::Init()
{
	Left_keyDown = 0;
	Right_keyDown = 0;

	PosVec = glm::vec3(0.0f, -3.5f, 0.0f);

	PosMat = glm::mat4(1.0f);
	PosMat = glm::translate(PosMat, PosVec);

	rad = 0.0f;
	RotMat = glm::mat4(1.0f);

	SclMat = glm::mat4(1.0f);
	SclMat = glm::scale(SclMat, glm::vec3(1.0f, 0.3f, 2.0f));

	dirVec = glm::vec3(0.0f, 0.0f, 1.0f);

	Speed = 0.0f;

	acc = 0.00005f;
	dec = 1.0f;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	loadOBJ("Shphere.obj", vertices, uvs, normals);

	for (int i = 0; i < vertices.size(); ++i)
	{
		Sphere[i][0] = vertices[i].x;
		Sphere[i][1] = vertices[i].y;
		Sphere[i][2] = vertices[i].z;

		SphereNormal[i][0] = normals[i].x;
		SphereNormal[i][1] = normals[i].y;
		SphereNormal[i][2] = normals[i].z;

		SphereColor[i][0] = 0.0f;
		SphereColor[i][1] = 1.0f;
		SphereColor[i][2] = 1.0f;
	}

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

	if (Left_keyDown)
	{
		RotMat = glm::rotate(RotMat, glm::radians(-rad), glm::vec3(0.0f, 0.0f, 1.0f));
		PosVec = glm::rotate(PosVec, glm::radians(-rad), glm::vec3(0.0f, 0.0f, 1.0f));

		rad += 2.0f * Speed;
		if (rad > 360)
		{
			rad -= 360;
		}

		RotMat = glm::rotate(RotMat, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
		PosVec = glm::rotate(PosVec, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	if (Right_keyDown)
	{
		RotMat = glm::rotate(RotMat, glm::radians(-rad), glm::vec3(0.0f, 0.0f, 1.0f));
		PosVec = glm::rotate(PosVec, glm::radians(-rad), glm::vec3(0.0f, 0.0f, 1.0f));

		rad -= 2.0f * Speed;
		if (rad < 0)
		{
			rad += 360;
		}

		RotMat = glm::rotate(RotMat, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
		PosVec = glm::rotate(PosVec, glm::radians(rad), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Player::Update()
{
	Move();
	camera.setPosition(PosVec);
	camera.setRotate(rad);
	camera.setpSpeed(Speed);
	camera.setAT();

	if (Speed < 1.5)
	{
		Speed += acc;
	}

	PosVec.z += Speed;
	PosMat = glm::translate(PosMat, glm::vec3(0.0f, 0.0f, Speed));
}

void Player::Key_Input(unsigned char key)
{
}

void Player::sKey_Input(int key, bool state)
{
	if (key == GLUT_KEY_RIGHT)
	{
		if(state)
			Right_keyDown = 1;

		else
			Right_keyDown = 0;
	}

	if (key == GLUT_KEY_LEFT)
	{
		if (state)
			Left_keyDown = 1;

		else
			Left_keyDown = 0;
	}
}

void Player::Render(GLuint ShaderProgram)
{
	camera.Render(ShaderProgram);
	
	unsigned int modelLocation = glGetUniformLocation(ShaderProgram, "modelTransform");

	glm::mat4 TR;
	TR = RotMat * PosMat * SclMat;

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

float Player::getSpeed()
{
	return Speed;
}

glm::vec3 Player::getPosition()
{
	return PosVec;
}

Camera Player::getCamera()
{
	return camera;
}
