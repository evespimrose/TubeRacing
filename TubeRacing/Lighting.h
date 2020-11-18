#pragma once
#include "framework.h"


class Lighting
{
private:
	float xpos;
	float zpos;

	float constant = 1.0f;
	float linear = 0.09f;
	float quadric = 0.032f;

public:
	void Init(float zOffset, float xOffset);
};