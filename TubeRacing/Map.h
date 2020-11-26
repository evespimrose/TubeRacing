#pragma once
#include "Tube.h"
#include "Cube.h"
#include "Lighting.h"
#include "Bullet.h"

class Map
{
private:
	std::vector<Tube> TubeList;
	std::vector<Cube> CubeList;
	std::vector<Lighting> LightingList;

	float tube[1200][3];
	float tubeNormal[1200][3];
	float tubeColor[1200][3];

	GLuint TubeVAO;
	GLuint TubeVBO[3];

	int CubeCounter;

	GLuint CubeVAO;
	GLuint CubeVBO[3];
	GLuint CubeEBO;

	const GLfloat cube[8][3] = {
		{-0.2f, -0.2f, -0.2f}, // 0
		{0.2f, -0.2f, -0.2f},  // 1
		{0.2f, 0.2f, -0.2f},   // 2
		{-0.2f, 0.2f, -0.2f},  // 3

		{-0.2f, -0.2f, 0.2f},  // 4
		{0.2f, -0.2f, 0.2f},   // 5
		{0.2f, 0.2f, 0.2f},    // 6
		{-0.2f, 0.2f, 0.2f}    // 7
	};

	const GLfloat cubeNormal[8][3] = {
		{-1, -1, -1},
		{1, -1, -1},
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, 1},
		{1, -1, 1},
		{1, 1, 1},
		{-1, 1, 1}
	};

	const GLint cubeIndices[12][3] = {
		{1, 0, 2},
		{2, 0, 3},
		{7, 0, 4},
		{3, 0, 7},
		{0, 1, 5},
		{4, 0, 5},
		{7, 4, 6},
		{6, 4, 5},
		{5, 1, 2},
		{5, 2, 6},
		{2, 3, 6},
		{3, 7, 6}
	};

	const GLfloat cubeColor[8][3] = {
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1}
	};

public:
	void Init();
	void Update(float pz);
	void Render(GLuint ShaderProgram);
	bool PlayerCollisionCheck(float pz, float pRotate);
	bool BulletCollisionCheck(std::vector<Bullet>& bList);
};