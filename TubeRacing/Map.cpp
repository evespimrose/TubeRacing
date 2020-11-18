#include "Map.h"

void Map::Init()
{
	Tube t[10];

	for (int i = 0; i < 10; ++i)
	{
		t[i].Init(-i * 10.0f);
		TubeList.push_back(t[i]);
	}
}

void Map::Update(float pz)
{
	float lastzOffset;
	std::vector<Tube>::iterator iter = TubeList.begin();
	if (iter->getzOffset() + 100.0f < pz)
	{
		TubeList.erase(iter);
		iter = TubeList.end() - 1;
		lastzOffset = iter->getzOffset();
		Tube t;
		t.Init(lastzOffset - 100.0f);
	}

}

void Map::Render(GLuint ShaderProgram)
{
	std::vector<Tube>::iterator iter = TubeList.begin();
	for (; iter != TubeList.end(); ++iter)
	{
		iter->Render(ShaderProgram);
	}
}