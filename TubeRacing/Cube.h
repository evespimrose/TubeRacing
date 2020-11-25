#pragma once
#include "framework.h"
#include <glm/gtx/rotate_vector.hpp>

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
	void Init(float Offset, GLuint vao);
	void Render(GLuint ShaderProgram);
	float getzOffset();
	float getRotate():
};