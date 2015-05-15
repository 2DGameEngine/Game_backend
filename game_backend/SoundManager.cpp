#include "SoundManager.h"
void SoundManager::addSound(Sound* sound,std::string sound_id){
	id_sound_map[sound_id]=sound;
}
Sound* SoundManager::getSound(std::string sound_id){
	return id_sound_map[sound_id];
}
SoundManager* SoundManager::s_pInstance=0;