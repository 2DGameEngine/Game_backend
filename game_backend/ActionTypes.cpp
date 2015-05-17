#include "ActionTypes.h"
void ActionTypes::setVelocity(GameObject* game_object,Vector2D velocity_vector){
	game_object->setVelocity(velocity_vector);
}
void ActionTypes::setVelocityX(GameObject* game_object,float x){
	game_object->setVelocityX(x);
}
void ActionTypes::setVelocityY(GameObject* game_object,float y){
	game_object->setVelocityY(y);
}
void ActionTypes::setPosition(GameObject* game_object,Vector2D position_vector){
	game_object->setPosition(position_vector);
}
void ActionTypes::setState(GameObject* game_object,std::string state){
	game_object->setState(state);
}
void ActionTypes::playSound(std::string sound_id){
	SoundManager::Instance()->getSound(sound_id)->play();
}
void ActionTypes::deleteObject(GameObject* game_object){
	game_object->deleteOb();
}
ActionTypes* ActionTypes::s_pInstance=0;