#pragma once
#include "framework.h"

class Bullet
{
private:
	GLuint VA0;
	glm::mat4 PosMat;

public:
	void Init(glm::vec3 playerPos, GLuint vao);
	void Render();
};