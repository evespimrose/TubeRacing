#pragma once

#include "framework.h"

class Tube
{
private:
	float tube[7560][3];
	float Normal[7560][3];
	float Color[7560][3];

	const float specular = 0.5f;
	const float diffuse = 0.5f;
	const float shininess = 32;

	GLuint VAO;
	GLuint VBO[3];

public:
	void Init();
	void Render(GLuint ShaderProgram);
};