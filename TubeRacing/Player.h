#pragma once
#include "framework.h"

class Player
{
private:
	//방향 벡터
	glm::vec3 dirVec;

	//위치값
	float xpos;
	float ypos;
	float zpos;

	float dx;
	float dy;
	float dz;

	float acc;

	//위치 행렬, 회전 행렬
	glm::mat4 PosMat;
	glm::mat4 RotMat;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

public:
	Player();
	void Move();
};