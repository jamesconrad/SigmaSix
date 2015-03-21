#ifndef SOUND
#define SOUND

#include <FMOD\fmod.hpp>
#include <vector>

class SoundSystemClass
{
public:
	static SoundSystemClass* instance()
	{
		static SoundSystemClass *instance = new SoundSystemClass();
		return instance;
	}
	void PlaySound(int index);
	void PlayBackground(char* filepath);

private:
	SoundSystemClass();

	FMOD::System *system; //handle to FMOD engine
	FMOD::Sound *bg; //sound that will be loaded and played
	FMOD::Channel *channel;
	std::vector<FMOD::Sound*> sounds;
};

#endif