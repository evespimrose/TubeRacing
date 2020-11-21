#pragma once
#include "framework.h"

class Cube
{
private:
	GLuint VAO;
	float zOffset;
	float rotate;
public:
	void Init(GLuint vao);
	void Render(GLuint ShaderProgram);
};