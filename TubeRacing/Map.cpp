#include "Map.h"
#include "loadOBJ.h"

void Map::Init()
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	loadOBJ("Tube.obj", vertices, uvs, normals);

	CubeCounter = 1;

	for (int i = 0; i < vertices.size(); ++i)
	{
		tube[i][0] = vertices[i].x;
		tube[i][1] = vertices[i].y;
		tube[i][2] = vertices[i].z;

		tubeNormal[i][0] = normals[i].x;
		tubeNormal[i][1] = normals[i].y;
		tubeNormal[i][2] = normals[i].z;

		tubeColor[i][0] = 0.0f;
		tubeColor[i][1] = 1.0f;
		tubeColor[i][2] = 1.0f;
	}

	glGenVertexArrays(1, &TubeVAO);
	glBindVertexArray(TubeVAO);
	glGenBuffers(3, TubeVBO);

	glBindBuffer(GL_ARRAY_BUFFER, TubeVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 1200 * 3 * sizeof(GLfloat), tube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, TubeVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 1200 * 3 * sizeof(GLfloat), tubeColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, TubeVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 1200 * 3 * sizeof(GLfloat), tubeNormal, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &CubeVAO);
	glBindVertexArray(CubeVAO);
	glGenBuffers(3, CubeVBO);
	glGenBuffers(1, &CubeEBO);

	glBindBuffer(GL_ARRAY_BUFFER, CubeVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, CubeVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cubeColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, CubeVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), cubeNormal, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), cubeIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

	Tube t[20];

	for (int i = 0; i < 20; ++i)
	{
		t[i].Init(i * 30.0f, TubeVAO);
		TubeList.push_back(t[i]);
	}

	Lighting leftLight[15];
	Lighting rightLight[15];

	for (int i = 0; i < 15; ++i)
	{
		leftLight[i].Init(i * 15.0f, -3.5f);
		rightLight[i].Init(i * 15.0f, 3.5f);
		LightingList.push_back(leftLight[i]);
		LightingList.push_back(rightLight[i]);
	}
}

void Map::Update(float pz)
{
	std::vector<Tube>::iterator Titer = TubeList.begin();
	if (Titer->getzOffset() + 50.0f < pz)
	{
		TubeList.erase(Titer);
		Titer = TubeList.end() - 1;
		float lastzOffset = Titer->getzOffset();

		Tube t;
		t.Init(lastzOffset + 30.0f, TubeVAO);
		TubeList.push_back(t);
	}

	std::vector<Lighting>::iterator Liter = LightingList.begin();
	if (Liter->getzOffset() + 50.0f < pz)
	{
		Liter = LightingList.erase(Liter);
		Liter = LightingList.erase(Liter);

		Liter = LightingList.end() - 1;
		float lastzOffset = Liter->getzOffset();

		Lighting l;
		l.Init(lastzOffset + 15.0f, -3.5f);
		LightingList.push_back(l);

		Lighting r;
		r.Init(lastzOffset + 15.0f, 3.5f);
		LightingList.push_back(r);
	}

	if (!CubeList.empty())
	{
		std::vector<Cube>::iterator Citer = CubeList.begin();
		if (Citer->getzOffset() + 50.0f < pz)
		{
			CubeList.erase(Citer);
			Citer = CubeList.end() - 1;
		}
	}

	while ((int)pz % 100 == 0 && pz > 100.0f)
	{
		if (CubeCounter > 0)
		{
			CubeCounter--;
			Cube c;

			c.Init(pz + 300.0f + rand() % 100, CubeVAO);
			CubeList.push_back(c);
		}
		else if (CubeCounter == 0)
		{
 			CubeCounter = 1 + pz / 1000;
			if (CubeCounter > 10)
			{
				CubeCounter = 10;
			}
			break;
		}
	}
}

bool Map::PlayerCollisionCheck(float pz, float pRotate)
{
	std::vector<Cube>::iterator Citer = CubeList.begin();
	for (; Citer != CubeList.end(); ++Citer)
	{
		float cz = Citer->getzOffset();
		float cRotate = Citer->getRotate();
		if (cz < pz + 0.5f && cz > pz - 0.5f && cRotate > pRotate - 10 && cRotate < pRotate + 10)
		{
			CubeList.erase(Citer);
			return true;
		}
	}
	return false;
}

void Map::BulletCollisionCheck(std::vector<Bullet>& bList)
{
	std::vector<Bullet>::iterator iter = bList.begin();

	for (; iter != bList.end();)
	{
		bool isCollision = 0;
		std::vector<Cube>::iterator Citer = CubeList.begin();
		for (; Citer != CubeList.end();)
		{
			float bz = iter->getzOffset();
			float bRad = iter->getRotate();
			float cRad = Citer->getRotate();

			float cz = Citer->getzOffset();
			if (bz > cz - 0.2f && bz < cz + 0.2f && bRad < cRad + 3.0f && bRad > cRad - 3.0f)
			{
				isCollision = 1;
				CubeList.erase(Citer);
				break;
			}
			else
			{
				Citer++;
			}
		}
		if (isCollision)
		{
			iter = bList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void Map::Render(GLuint ShaderProgram)
{
	int ind = 0;
	std::vector<Lighting>::iterator Liter = LightingList.begin();
	for (; Liter != LightingList.end(); ++Liter)
	{
		Liter->Render(ShaderProgram, ind);
		ind++;
	}

	std::vector<Tube>::iterator Titer = TubeList.begin();
	for (; Titer != TubeList.end(); ++Titer)
	{
		Titer->Render(ShaderProgram);
	}

	std::vector<Cube>::iterator Citer = CubeList.begin();
	for (; Citer != CubeList.end(); ++Citer)
	{
		Citer->Render(ShaderProgram);
	}
}