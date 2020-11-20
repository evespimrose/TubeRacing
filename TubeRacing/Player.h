#pragma once
#include "Camera.h"

class Player
{
private:
	Camera camera;
    
	glm::vec3 dirVec;

	float rad;

	float specular = 0.8f;
	float diffuse = 0.2f;
	float shininess = 256;

	bool Left_keyDown;
	bool Right_keyDown;

	float posx;
	float posy;
	float posz;

	float Speed;

	float acc;
	float dec;

	glm::vec3 PosVec;

	glm::mat4 PosMat;
	glm::mat4 RotMat;
	glm::mat4 SclMat;

	GLuint VAO;
	GLuint VBO[3];
	GLuint EBO;


	const GLfloat Cube[8][3] = {
		{-0.2f, -0.2f, -0.2f}, // 0
		{0.2f, -0.2f, -0.2f},  // 1
		{0.2f, 0.2f, -0.2f},   // 2
		{-0.2f, 0.2f, -0.2f},  // 3

		{-0.2f, -0.2f, 0.2f},  // 4
		{0.2f, -0.2f, 0.2f},   // 5
		{0.2f, 0.2f, 0.2f},    // 6
		{-0.2f, 0.2f, 0.2f}    // 7
	};

	const GLfloat Normal[8][3] = {
		{-1, -1, -1},
		{1, -1, -1},
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, 1},
		{1, -1, 1},
		{1, 1, 1},
		{-1, 1, 1}
	};

	const GLint Indices[12][3] = {
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

	const GLfloat Color[8][3] = {
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
	void Move();
	void Update();
	void Key_Input(unsigned char key);
	void sKey_Input(int key, bool state);
	void Render(GLuint ShaderProgram);
	float getSpeed();
	glm::vec3 getPosition();
	Camera getCamera();
};