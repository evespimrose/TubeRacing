#pragma once
#include "framework.h"

class Camera
{
private:
	float posx;
	float posy;
	float posz;

	glm::vec3 AT;

public:
	void Render(GLuint ShaderProgram);
	void Fast(int speed);
};