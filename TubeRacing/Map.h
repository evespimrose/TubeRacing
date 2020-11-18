#pragma once
#include "Tube.h"
#include "Cube.h"

class Map
{
private:
	std::vector<Tube> TubeList;
	std::vector<Cube> CubeList;


public:
	void Init();
	void Update(float pz);
	void Render(GLuint ShaderProgram);
};