#include "Map.h"
#include "loadOBJ.h"

void Map::Init()
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	loadOBJ("Tube.obj", vertices, uvs, normals);

	for (int i = 0; i < vertices.size(); ++i)
	{
		tube[i][0] = vertices[i].x;
		tube[i][1] = vertices[i].y;
		tube[i][2] = vertices[i].z;

		Normal[i][0] = normals[i].x;
		Normal[i][1] = normals[i].y;
		Normal[i][2] = normals[i].z;

		Color[i][0] = 0.0f;
		Color[i][1] = 1.0f;
		Color[i][2] = 1.0f;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, 1200 * 3 * sizeof(GLfloat), tube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 1200 * 3 * sizeof(GLfloat), Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 1200 * 3 * sizeof(GLfloat), Normal, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	Tube t[20];

	for (int i = 0; i < 20; ++i)
	{
		t[i].Init(i * 30.0f, VAO);
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
		t.Init(lastzOffset + 30.0f, VAO);
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

}