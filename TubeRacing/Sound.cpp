#include "Sound.h"

SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::sharedManager()
{
	if (instance == NULL) instance = new SoundManager;
	return instance;
}

void SoundManager::init()
{
	r = System_Create(&pFmod);
	r = pFmod->init(100, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::loading()
{
	r = pFmod->createSound("sound/sound01.mp3", FMOD_LOOP_NORMAL, NULL, &music[BACKGROUND_SOUND]);
	r = pFmod->createSound("sound/sound02.mp3", FMOD_LOOP_NORMAL, NULL, &music[DRIVE_SOUND]);
	r = pFmod->createSound("sound/sound03.mp3", FMOD_DEFAULT, NULL, &music[ATTACK_SOUND]);
	r = pFmod->createSound("sound/sound04.mp3", FMOD_DEFAULT, NULL, &music[OVER_SOUND]);
	r = pFmod->createSound("sound/sound05.mp3", FMOD_DEFAULT, NULL, &music[CRUSH_SOUND]);
}

void SoundManager::play(int _type)
{
	pFmod->update();
	r = pFmod->playSound(music[_type],NULL, false, &ch[_type]);
}

void SoundManager::stop(int _cNum)
{
	ch[_cNum]->stop();
}