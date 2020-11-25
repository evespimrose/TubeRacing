#pragma once
#include "fmod.hpp"
#include <windows.h>
#pragma comment(lib,"fmod_vc.lib")

using namespace FMOD;

enum SOUND {
	BACKGROUND_SOUND, 
	ATTACK_SOUND, 
	CRUSH_SOUND,
	COLLAPSE_SOUND
};

class SoundManager {
public:
	static SoundManager* instance;
	static SoundManager* sharedManager();
	void init();
	void loading();
	void play(int _type);
	void stop(int _cNum);
	void ErrorCheck(FMOD_RESULT _r);

private:
	System* pFmod;
	Channel* ch[10];
	Sound* music[10];
	FMOD_RESULT r;
};