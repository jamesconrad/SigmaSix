#ifndef SOUND
#define SOUND

#include <FMOD\fmod.hpp>
#include <vector>

enum soundEffect
{
	PLAYER_SHOOT = 0,
	PLAYER_HURT = 1
};

class SoundSystemClass
{
public:
	static SoundSystemClass* instance()
	{
		static SoundSystemClass *instance = new SoundSystemClass();
		return instance;
	}
	void PlaySound(soundEffect);
	void PlayBackground(char* filepath);

private:
	SoundSystemClass();

	FMOD::System *system; //handle to FMOD engine
	FMOD::Sound *bg; //sound that will be loaded and played
	FMOD::Channel *channel;
	FMOD::Channel *effects;
	std::vector<FMOD::Sound*> soundEffects;
};

#endif