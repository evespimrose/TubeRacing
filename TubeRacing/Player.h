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

	//��ġ ���, ȸ�� ���
	glm::mat4 PosMat;
	glm::mat4 RotMat;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

public:
	Player();
	void Move();
};