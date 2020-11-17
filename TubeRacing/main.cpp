#include "Player.h"
#include "Tube.h"

using namespace std;

const float length = 0.5;

char* arr;

GLuint vertexShader;
GLuint fragmentShader;

GLuint ShaderProgram;

float ambient = 0.6f;

Player player;

float Rotate = 0;

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
	GLchar* fragmentShaderSource = filetobuf("Fragment0.glsl");;

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

void InitShader()
{
	make_vertexShaders();
	make_fragmentShaders();

	//-- shader Program
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(ShaderProgram);
}

GLvoid drawScene()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 원근 투영
	glUseProgram(ShaderProgram);

	glm::vec3 lp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 lc = glm::vec3(1.0f, 1.0f, 1.0f);

	unsigned int LightPosLocation = glGetUniformLocation(ShaderProgram, "lightPos");
	glUniformMatrix4fv(LightPosLocation, 1, GL_FALSE, glm::value_ptr(lp));

	unsigned int LightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
	glUniformMatrix4fv(LightColorLocation, 1, GL_FALSE, glm::value_ptr(lc));

	player.Render(ShaderProgram);
	t.Render(ShaderProgram);


	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	player.Key_Input(key);
	switch (key)
	{
	case 'Q':
		exit(0);
		break;
	}
}

GLvoid sKeyboard(int key, int x, int y)
{
	player.sKey_Input(key, TRUE);
}
GLvoid sKeyboardUp(int key, int x, int y)
{
	player.sKey_Input(key, FALSE);
}

GLvoid Timer(int Value)
{
	player.Update();
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

	player.Init();

	glutTimerFunc(1, Timer, 0);
	glutSpecialFunc(sKeyboard);
	glutKeyboardFunc(Keyboard);
	glutSpecialUpFunc(sKeyboardUp);
	glutDisplayFunc(drawScene);
	glutMainLoop();
}