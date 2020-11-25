#include "Sound.h"
#include "fmod_errors.h"

SoundManager* SoundManager::sharedManager()
{
	if (instance == NULL) instance = new SoundManager;
	return instance;
}

void SoundManager::init()
{
	r = System_Create(&pFmod);
	ErrorCheck(r);
	r = pFmod->init(100, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(r);
}

void SoundManager::loading()
{
	r = pFmod->createSound("sound01.mp3", FMOD_LOOP_NORMAL, NULL, &music[BACKGROUND_SOUND]);
	ErrorCheck(r);
	r = pFmod->createSound("sound02.mp3", FMOD_DEFAULT, NULL, &music[DRIVE_SOUND]);
	ErrorCheck(r);
	r = pFmod->createSound("sound03.mp3", FMOD_DEFAULT, NULL, &music[ATTACK_SOUND]);
	ErrorCheck(r);
}

void SoundManager::play(int _type)
{
	pFmod->update();
	r = pFmod->playSound(music[_type],NULL, false, &ch[_type]);
	ErrorCheck(r);
}

void SoundManager::stop(int _cNum)
{
	ch[_cNum]->stop();
}

void SoundManager::ErrorCheck(FMOD_RESULT _r)
{
	if (r != FMOD_OK)
	{
		TCHAR szStr[256] = { 0 };
		MultiByteToWideChar(CP_ACP, NULL, FMOD_ErrorString(r), -1, szStr, 256);
		MessageBox(NULL, szStr, "SoundError", MB_OK);
	}
}