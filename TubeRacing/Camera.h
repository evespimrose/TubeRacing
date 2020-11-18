#pragma once
#include "framework.h"
#include <glm/gtx/rotate_vector.hpp>

class Camera
{
private:
	float posx;
	float posy;
	float posz;

	float pSpeed;

	float rotate;

	glm::vec3 AT;

public:
	Camera();
	void Render(GLuint ShaderProgram);
	void ZoomOut(int dz);
	void ZoomIn(int dz);
	void setpSpeed(float s);
	void setSpeed(float speed);
	void setRotate(float r);
	void setPosition(glm::vec3 p);
	void setAT();
};