#ifndef _SOUNDMANAGER_
#define _SOUNDMANAGER_
#include "GameObject.h"
#include "Sound.h"
#include <vector>
#include <map>
class SoundManager{
public:
	static SoundManager* Instance(){
		if(s_pInstance==0){
			s_pInstance=new SoundManager();
		}
		return s_pInstance;
	}
	void addSound(Sound*,std::string);
	Sound* getSound(std::string);
private:
	static SoundManager* s_pInstance;
	std::map <std::string,Sound*> id_sound_map;
};
#endif