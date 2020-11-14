#include <fstream>
#include <iostream>
#include <string>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <glm.hpp>
#include <ext.hpp>
#include <gtc/matrix_transform.hpp>

#include <time.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

const float length = 0.5;

char* arr;

GLuint vertexShader;
GLuint fragmentShader;

GLuint ShaderProgram;

bool LightRotOn = 0;

float CameraX = 0;
float CameraZ = 0;
float CameraRotate = 0;

float MoonRotate = 0;

float ambient = 0.6;


GLfloat Cube[8][3] = {
	{-0.2f, -0.2f, -0.2f}, // 0
	{0.2f, -0.2f, -0.2f},  // 1
	{0.2f, 0.2f, -0.2f},   // 2
	{-0.2f, 0.2f, -0.2f},  // 3

	{-0.2f, -0.2f, 0.2f},  // 4
	{0.2f, -0.2f, 0.2f},   // 5
	{0.2f, 0.2f, 0.2f},    // 6
	{-0.2f, 0.2f, 0.2f}    // 7
};

GLfloat CubeNormal[8][3] = {
	{-1, -1, -1},
	{1, -1, -1},
	{1, 1, -1},
	{-1, 1, -1},
	{-1, -1, 1},
	{1, -1, 1},
	{1, 1, 1},
	{-1, 1, 1}
};

GLint CubeIndices[12][3] = {
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

GLfloat CubeColor[8][3] = {
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1},
	{0, 0, 1}
};
GLfloat CubeColorA[8][4] = {
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5},
	{0, 0, 1, 0.5}
};

float Rotate = 0;
void ReadObj(FILE* objFile, glm::vec4*& ObjVert, glm::vec4*& objNormal, glm::vec4*& ObjElementVec, int& Index, int& NormalIndex, int& ElementIndex)
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;
	int NormalNum = 0;
	while (!feof(objFile))
	{
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'v' && count[1] == 'n' && count[2] == '\0')
			NormalNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // 배열 초기화
	}

	//--- 2. 메모리 할당
	ObjVert = (glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	objNormal = (glm::vec4*)malloc(sizeof(glm::vec4) * NormalNum);
	ObjElementVec = (glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);

	rewind(objFile);

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
	while (!feof(objFile))
	{
		char bind[100];
		fscanf(objFile, "%s", bind);

		if (bind[0] == 'v' && bind[1] == '\0')
		{
			fscanf(objFile, "%f %f %f",
				&ObjVert[Index].x, &ObjVert[Index].y, &ObjVert[Index].z);

			Index++;
		}

		if (bind[0] == 'v' && bind[1] == 'n' && bind[2] == '\0')
		{
			fscanf(objFile, "%f %f %f",
				&objNormal[NormalIndex].x, &objNormal[NormalIndex].y, &objNormal[NormalIndex].z);

			NormalIndex++;
		}

		else if (bind[0] == 'f' && bind[1] == '\0')
		{
			fscanf(objFile, "%f %f %f",
				&ObjElementVec[ElementIndex].x, &ObjElementVec[ElementIndex].y, &ObjElementVec[ElementIndex].z);

			ElementIndex++;
		}
	}
}



void convertXY(int w, int h, int x, int y, float& ox, float& oy)
{
	ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}


GLchar* filetobuf(const char* filename)
{
	string tmp;
	string Source;
	ifstream readFile;

	readFile.open(filename);

	readFile.seekg(0, ios::end);
	Source.reserve(readFile.tellg());
	readFile.seekg(0, ios::beg);

	Source.assign((istreambuf_iterator<char>(readFile)), istreambuf_iterator<char>());

	arr = new char[Source.length() + 2];

	strcpy_s(arr, Source.length() + 1, Source.c_str());

	arr[Source.length() + 1] = '\0';

	return arr;
}

void make_vertexShaders()
{
	GLchar* vertexShaderSource = filetobuf("Vertex.glsl");

	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	delete[] arr;

	GLint result;
	GLchar errorLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void make_fragmentShaders()
{
	GLchar* fragmentShaderSource = filetobuf("Fragment.glsl");;

	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	delete[] arr;

	GLint result;
	GLchar errorLog[512];

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		return;
	}
}

void InitBuffer()
{
	
}

void InitShader()
{
	make_vertexShaders();
	make_fragmentShaders();

	//-- shader Program
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);

	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(ShaderProgram);
}

GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 원근 투영
	glUseProgram(ShaderProgram);
	glm::mat4 Projection = glm::mat4(1.0f);
	Projection = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f);
	unsigned int ProjectionLocation = glGetUniformLocation(ShaderProgram, "projectionTransform");;
	glUniformMatrix4fv(ProjectionLocation, 1, GL_FALSE, &Projection[0][0]);

	// 카메라 초기화
	glm::vec3 cameraPos = glm::vec3(CameraX, 2.0f, 8.0f + CameraZ);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	view = glm::rotate(view, glm::radians(CameraRotate), glm::vec3(0.0f, 1.0f, 0.0f));

	unsigned int viewLocation = glGetUniformLocation(ShaderProgram, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//조명 값 전달
	int lightPosLocation = glGetUniformLocation(ShaderProgram, "lightPos");
	glUniform3f(lightPosLocation, 0, 0, 0);

	int lightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniform3f(lightColorLocation, 1, 1, 1);

	int viewPosLocation = glGetUniformLocation(ShaderProgram, "viewPos");
	glUniform3f(viewPosLocation, CameraX, 2.0f, 3.0f + CameraZ);

	int AmbientLocation = glGetUniformLocation(ShaderProgram, "ambientLight");
	glUniform1f(AmbientLocation, ambient);


	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'Q':
		exit(0);
		break;
	}
}

GLvoid Timer(int Value)
{
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	srand((unsigned int)time(NULL));

	GLint width = 1000;
	GLint height = 1000;

	//--- 윈도우 생성하기
	glutInit(&argc, argv);// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(width, height); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성 (윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
	glewInit();

	InitShader();
	InitBuffer();

	glutTimerFunc(1, Timer, 0);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutMainLoop();
}