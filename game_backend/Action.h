#ifndef _ACTION_
#define _ACTION_
#include <string>
#include "ActionTypes.h"
class Action{
public:
	void runAction();
	
	Action(std::string action_type,GameObject* game_object,Vector2D vector){
		Action::action_type=action_type;
		Action::vector=vector;
		Action::game_object=game_object;
	}
	Action(std::string action_type,GameObject* game_object,float x){
		Action::action_type=action_type;
		value=x;
		Action::game_object=game_object;
	}
	Action(std::string action_type,GameObject* game_object,std::string string){
		Action::action_type=action_type;
		Action::string=string;
		Action::game_object=game_object;
	}
	Action(std::string action_type,std::string string){
		Action::action_type=action_type;
		Action::string=string;
		Action::game_object=NULL;
	}
private:
	std::string action_type;
	GameObject* game_object;
	Vector2D vector;
	std::string string;
	float value;
};
#endif