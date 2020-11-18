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

	for (int i = 0; i < 12; ++i)
	{
		t[i].Init(i * 50.0f, VAO);
		TubeList.push_back(t[i]);
	}

	Lighting leftLight[10];
	Lighting rightLight[10];

	for (int i = 0; i < 10; ++i)
	{
		leftLight[i].Init(i * 20.0f, -3.5f);
		rightLight[i].Init(i * 20.0f, 3.5f);
		LightingList.push_back(leftLight[i]);
		LightingList.push_back(rightLight[i]);
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
		t.Init(lastzOffset + 50.0f, VAO);
		TubeList.push_back(t);
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