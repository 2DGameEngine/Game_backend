#include "Sound.h"

void Sound::load(std::string filename){
	if(type=="music"){
		music_object=Mix_LoadMUS(filename.c_str());
	}
	else if(type=="effect"){
		effect_object=Mix_LoadWAV(filename.c_str());
	}
}
Sound::Sound(std::string type){
	Sound::type=type;
}
void Sound::play(){
	if(type=="music"){
		 if( Mix_PlayingMusic() == 0 ){
          Mix_PlayMusic( music_object, -1 );                       
          }
	}
	else if(type=="effect"){
		Mix_PlayChannel( -1, effect_object, 0 );
	}
}