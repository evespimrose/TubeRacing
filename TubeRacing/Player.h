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
	float dec;

	//위치 행렬, 회전 행렬, 스케일 행렬
	glm::mat4 PosMat;
	glm::mat4 RotMat;
	glm::mat4 SclMat;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

public:
	Player();
	void Move();
	void Update();
	void Key_Input(unsigned char key);
	void sKey_Input(int key);
	void InitBuffer();
};