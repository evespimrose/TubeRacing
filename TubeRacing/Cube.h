#pragma once
#include "framework.h"

class Cube
{
private:
	GLuint VAO;
	float zOffset;
	float rotate;

	float specular = 0.8f;
	float diffuse = 0.2f;
	float shininess = 256;

	glm::mat4 PosMat;
	glm::mat4 RotMat;
	glm::vec3 PosVec;

public:
	void Init(GLuint vao, float zOffset);
	void Render(GLuint ShaderProgram);
	float getzOffset();
};