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
	else if(action_type=="set_velocity_x"){
		ActionTypes::Instance()->setVelocityX(game_object,value);
	}
	else if(action_type=="set_velocity_y"){
		ActionTypes::Instance()->setVelocityY(game_object,value);
	}
	else if(action_type=="play_sound"){
		ActionTypes::Instance()->playSound(string);
	}
	else if(action_type=="delete_object"){
		ActionTypes::Instance()->deleteObject(game_object);
	}
}