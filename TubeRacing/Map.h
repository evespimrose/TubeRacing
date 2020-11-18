#pragma once
#include "Tube.h"
#include "Cube.h"

class Map
{
private:
	std::vector<Tube> TubeList;
	std::vector<Cube> CubeList;

	float tube[1200][3];
	float Normal[1200][3];
	float Color[1200][3];

	GLuint VAO;
	GLuint VBO[3];


public:
	void Init();
	void Update(float pz);
	void Render(GLuint ShaderProgram);
};