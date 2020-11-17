#pragma once
#include "framework.h"
#include "Tube.h"
#include "Cube.h"

class Map
{
private:
	std::vector<Tube> TubeList;
	std::vector<Cube> CubeList;

public:
	void Init();
	void Update();

};