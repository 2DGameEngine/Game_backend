#ifndef _SOUND_
#define _SOUND_
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
class Sound{
private:
	std::string filename;
	std::string type;
	Mix_Music *music_object;
	Mix_Chunk *effect_object;
public:
	void load(std::string);
	Sound(std::string);
	void play();

};
#endif