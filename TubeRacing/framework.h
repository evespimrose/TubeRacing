#pragma once
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
#define TRUE 1
#define FALSE 0


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