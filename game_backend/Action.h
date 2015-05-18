#ifndef _ACTION_
#define _ACTION_
#include <string>
#include "ActionTypes.h"
class Action{
public:
	void runAction();
	
	Action(std::string action_type,std::string game_object_id,Vector2D vector){
		Action::action_type=action_type;
		Action::vector=vector;
		Action::game_object_id= game_object_id;
	}
	Action(std::string action_type,std::string game_object_id,float x){
		Action::action_type=action_type;
		value=x;
		Action::game_object_id=game_object_id;
	}
	Action(std::string action_type,std::string game_object_id,int x){
		if(action_type=="change_text_visibility"){
			Action::action_type=action_type;
			Action::text_object_id=game_object_id;
			Action::visible=(x==1);
		}
		Action::action_type=action_type;
		value=x;
		Action::game_object_id=game_object_id;
	}
	Action(std::string action_type,std::string game_object_id,std::string string){
		Action::action_type=action_type;
		Action::string=string;
		Action::game_object_id=game_object_id;
	}
	Action(std::string action_type,std::string string){
		Action::action_type=action_type;
		
		if(action_type=="play_sound"){
			Action::string=string;
			Action::game_object_id="";
		}
		else {
			Action::game_object_id=game_object_id;
			Action::string="";
		}	
	}
	Action(std::string action_type,std::string game_object_id,std::string string,float x){
		Action::action_type=action_type;
		Action::string=string;
		Action::game_object_id=game_object_id;
		value=x;
	}
	/*Action(std::string action_type,std::string text_object_id,bool visible){
		Action::action_type=action_type;
		Action::text_object_id=text_object_id;
		Action::visible=visible;
	}*/
private:
	std::string action_type;
	std::string game_object_id;
	std::string text_object_id;
	Vector2D vector;
	std::string string;
	float value;
	bool visible;
};
#endif