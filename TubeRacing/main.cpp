#include "Player.h"
#include "Map.h"
#include "Sound.h"

using namespace std;

const float length = 0.5;

char* arr;

int GameState = 0;

GLuint vertexShader;
GLuint fragmentShader;

GLuint ShaderProgram;

float ambient = 0.6f;

Player player;
Map m;

float Rotate = 0;

void glutPrint(float x, float y, LPVOID font, string text)
{
	glWindowPos2f(x, y);

	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(font, text[i]);
	}
}

int CalculateFrameRate()
{
	static float framesPerSecond = 0.0f;
	static int fps;
	static float lastTime = 0.0f;
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		fps = (int)framesPerSecond;
		framesPerSecond = 0;
	}

	return fps;
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
	if (GameState == 0)
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 원근 투영
		glUseProgram(ShaderProgram);

		glm::vec3 lc = glm::vec3(0.5f, 0.5f, 0.5f);

		unsigned int LightColorLocation = glGetUniformLocation(ShaderProgram, "lightColor");
		glUniform3fv(LightColorLocation, 1, glm::value_ptr(lc));

		glm::vec3 cp = player.getCamera().getPosition();

		unsigned int viewPosLocation = glGetUniformLocation(ShaderProgram, "viewPos");
		glUniform3fv(viewPosLocation, 1, glm::value_ptr(cp));

		m.Render(ShaderProgram);
		player.Render(ShaderProgram);

		string score = "Score : ";
		score += std::to_string((int)player.getPosition().z);
		glutPrint(850.0f, 980.0f, GLUT_BITMAP_HELVETICA_18, score);

		string speed = "Speed : ";
		speed += std::to_string((int)(player.getSpeed() * 500)) + "km/h";
		glutPrint(0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, speed);

		string life = "Life : ";
		life += std::to_string(player.getLife());
		glutPrint(0.0f, 980.0f, GLUT_BITMAP_HELVETICA_18, life);

		glutSwapBuffers();
	}
	else
	{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glutPrint(420.0f, 550.0f, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
		glutPrint(370.0f, 400.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press R to CONTINUE");

		glutSwapBuffers();
	}
}
GLvoid Timer(int Value)
{
	if (GameState == 1)
	{
		return;
	}

	float pz = player.getPosition().z;

	m.Update(pz);
	player.Update();
	if(m.PlayerCollisionCheck(pz, player.getRotate()))
	{
		if (player.collision())
		{
			GameState = 1;
			glutPostRedisplay();
		}
	}
	std::vector<Bullet> tmpList = player.getBulletList();
	m.BulletCollisionCheck(tmpList);
	player.setBulletList(tmpList);

	string str = "Turbo_Racing   fps:";

	glutSetWindowTitle((str + std::to_string(CalculateFrameRate())).c_str());

	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}


void Reset()
{
	GameState = 0;
	player.Reset();
	m.Reset();

	glutTimerFunc(1, Timer, 0);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	player.Key_Input(key, TRUE);
	switch (key)
	{
	case 'Q':
		exit(0);
		break;
	}

	if (GameState == 1)
	{
		switch (key)
		{
		case 'R':
			Reset();
			break;
		case 'r':
			Reset();
			break;
		}
	}
}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	player.Key_Input(key, FALSE);
}

GLvoid sKeyboard(int key, int x, int y)
{
	player.sKey_Input(key, TRUE);
}
GLvoid sKeyboardUp(int key, int x, int y)
{
	player.sKey_Input(key, FALSE);
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
	glutCreateWindow("Turbo_Racing||      fps:"); // 윈도우 생성 (윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
	glewInit();

	InitShader();

	player.Init();
	m.Init();

	glutTimerFunc(1, Timer, 0);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(sKeyboard);
	glutSpecialUpFunc(sKeyboardUp);
	glutDisplayFunc(drawScene);

	SoundManager::sharedManager()->init();
	SoundManager::sharedManager()->loading();
	SoundManager::sharedManager()->play(BACKGROUND_SOUND);

	glutMainLoop();
}