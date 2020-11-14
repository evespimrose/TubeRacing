#pragma once
#include "framework.h"

class Player
{
private:
	//���� ����
	glm::vec3 dirVec;

	//��ġ��
	float xpos;
	float ypos;
	float zpos;

	float dx;
	float dy;
	float dz;

	float acc;
	float dec;

	//��ġ ���, ȸ�� ���, ������ ���
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