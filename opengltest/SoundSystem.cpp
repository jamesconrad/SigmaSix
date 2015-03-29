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
	system->createSound(fp, FMOD_LOOP_NORMAL, NULL, &bg);
	system->playSound(bg, NULL, true, &channel);
	tsl = 0;
	channel->setVolume(0);
	channel->setPaused(false);
	system->update();
}

void SoundSystemClass::PlaySound(soundEffect effect)
{
	system->playSound(soundEffects.at(effect), NULL, false, &effects);
}

void SoundSystemClass::Update(float dTime)
{
	//used for fading in music
	tsl += dTime;
	float tmp = tsl / 3000;
	if (tmp <= 1)
	{
		//using linear interpolation here
		//sound will always start at 0, then increase until it reaches 1
		vol = startvol + tmp * (stopvol - startvol);
		channel->setVolume(vol);
	}
	
	system->update();
}