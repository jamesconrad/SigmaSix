#include "SoundSystem.h"

SoundSystemClass::SoundSystemClass()
{
	//init FMOD
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

void SoundSystemClass::PlayBackground(char* fp)
{
	system->createSound(fp, FMOD_LOOP_NORMAL, NULL, &bg);
	system->playSound(bg, NULL, false, &channel);
}

void PlaySound(char* fp)
{
}