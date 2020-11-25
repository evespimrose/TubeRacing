#pragma once
#include "framework.h"

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
	void Render(GLuint ShaderProgram);
	void setpSpeed(float s);
	void setSpeed(float speed);
	void setRotate(float r);
	void setPosition(glm::vec3 p);
	void setAT();
	glm::vec3 getPosition();
};