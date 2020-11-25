#pragma once
#include "framework.h"
#include <vector>

class Lighting
{
private:
	float posx;
	float posz;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

public:
	void Init(float zOffset, float xOffset);
	void Render(GLuint ShaderProgram, int ind);
	float getzOffset();
};