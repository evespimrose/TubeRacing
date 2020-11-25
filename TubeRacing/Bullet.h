#pragma once
#include "framework.h"

class Bullet
{
private:
	float specular = 0.8f;
	float diffuse = 0.2f;
	float shininess = 256;

	GLuint VAO;
	glm::mat4 PosMat;
	float Speed;
	glm::vec3 PosVec;

public:
	void Init(glm::vec3 playerPos, GLuint vao, float PlayerSpeed);
	void Render(GLuint ShaderProgram);
	void Move();
	float getzOffset();
};