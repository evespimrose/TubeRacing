#pragma once

#include "framework.h"

class Tube
{
private:
	float tube[1296][3];
	float Normal[1296][3];
	float Color[1296][3];

	GLuint VAO;
	GLuint VBO[3];

public:
	void Init();
	void Render(GLuint ShaderProgram);
};