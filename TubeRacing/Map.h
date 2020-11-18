#pragma once
#include "framework.h"
#include "Tube.h"
#include "Cube.h"

class Map
{
private:
	std::vector<Tube> TubeList;
	std::vector<Cube> CubeList;
	float zOffset;


public:
	void Init();
	void Update(float pz);
	void Render(GLuint ShaderProgram);
};