#pragma once
#include "framework.h"

class Camera
{
private:
	float posx;
	float posy;
	float posz;

	float pSpeed;

	glm::vec3 AT;

public:
	Camera();
	void Render(GLuint ShaderProgram);
	void setpSpeed(float s);
};