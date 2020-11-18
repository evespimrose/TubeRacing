#pragma once

#include "framework.h"

class Tube
{
private:
	float tube[1200][3];
	float Normal[1200][3];
	float Color[1200][3];

	float specular = 0.5f;
	float diffuse = 0.5f;
	float shininess = 32;

	GLuint VAO;
	GLuint VBO[3];

	float zOffset;

public:
	void Init(float Offset);
	void Render(GLuint ShaderProgram);
	float getzOffset();
};