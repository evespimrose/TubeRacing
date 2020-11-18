#pragma once
#include "framework.h"

class Tube
{
private:
	float zOffset;
	float VAO;

	float specular = 0.5f;
	float diffuse = 0.5f;
	float shininess = 32;

public:
	void Init(float Offset, GLuint vao);
	void Render(GLuint ShaderProgram);
	float getzOffset();
};