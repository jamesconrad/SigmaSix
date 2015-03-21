#include "SoundSystem.h"

SoundSystemClass::SoundSystemClass()
{
	//init FMOD
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels

	FMOD::Sound *sound;
	system->createSound("assets/sound/plyr_hurt.mp3", FMOD_DEFAULT, NULL, &sound);
	soundEffects.push_back(sound);
	system->createSound("assets/sound/plyr_shoot.mp3", FMOD_DEFAULT, NULL, &sound);

}

void SoundSystemClass::PlayBackground(char* fp)
{
	channel->stop();
	system->createSound(fp, FMOD_LOOP_NORMAL || FMOD_LOWMEM || FMOD_OPENONLY, NULL, &bg);
	system->playSound(bg, NULL, false, &channel);
}

void SoundSystemClass::PlaySound(soundEffect effect)
{
	system->playSound(soundEffects.at(effect), NULL, false, &effects);
}