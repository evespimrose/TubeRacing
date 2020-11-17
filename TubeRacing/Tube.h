#pragma once

#include "framework.h"

class Tube
{
private:
	float tube[1200][3];
	float Normal[1200][3];
	float Color[1200][3];

	const float specular = 0.5f;
	const float diffuse = 0.5f;
	const float shininess = 32;

	GLuint VAO;
	GLuint VBO[3];

public:
	void Init();
	void Render(GLuint ShaderProgram);
};