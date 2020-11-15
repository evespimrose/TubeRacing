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
	void ZoomOut(int dz);
	void ZoomIn(int dz);
};