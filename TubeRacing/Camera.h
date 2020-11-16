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
	void ZoomOut(int dz);
	void ZoomIn(int dz);
	void setpSpeed(float s);
	void setSpeed(float speed);
};