#include "Action.h"
void Action::runAction(){
	if(game_object!=NULL)
		game_object->updated=true;
	if(action_type=="set_velocity"){
		ActionTypes::Instance()->setVelocity(game_object,vector);
	}
	else if(action_type=="set_position"){
		ActionTypes::Instance()->setPosition(game_object,vector);
	}
	else if(action_type=="set_state"){
		ActionTypes::Instance()->setState(game_object,string);
	}
	else if(action_type=="play_sound"){
		ActionTypes::Instance()->playSound(string);
	}
}