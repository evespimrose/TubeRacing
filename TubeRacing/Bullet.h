#pragma once
#include "framework.h"
#include "sound.h"

class Bullet
{
private:
	float specular = 0.8f;
	float diffuse = 0.2f;
	float shininess = 256;

	float rotate;
	GLuint VAO;
	glm::mat4 PosMat;
	float Speed;
	glm::vec3 PosVec;

	LARGE_INTEGER tSecond;
	LARGE_INTEGER tTime;

	float fDeltaTime;

public:
	void Init(glm::vec3 playerPos, GLuint vao, float PlayerSpeed, float Rotate);
	void Render(GLuint ShaderProgram);
	void Move();
	float getzOffset();
	float getRotate();
};