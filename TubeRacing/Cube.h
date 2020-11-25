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
	void Init(GLuint vao, float zOffset);
	float specular = 0.5f;
	float diffuse = 0.5f;
	float shininess = 32;

	glm::mat4 RotMat = glm::mat4(1.0f);
	glm::mat4 PosMat = glm::mat4(1.0f);
public:
	void Init(float Offset, GLuint vao);
	void Render(GLuint ShaderProgram);
	float getzOffset();
};