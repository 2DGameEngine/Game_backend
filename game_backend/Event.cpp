#include "Event.h"
void Event::addAction(Action* action){
	action_list.push_back(action);
}
void Event::setEvent(event_types e,SDL_Scancode scancode){
	event_type=e;
	Event::scancode=scancode;
	previous_button_stats=false;
}
void Event::setEvent(event_types e,std::string object_id){
	event_type=e;

	subject=GameObjectManager::Instance()->getObject(object_id);
	
	
}
void Event::setEvent(event_types e,std::string object_id,std::string variable_name,float variable_value){
	event_type=e;
	subject=GameObjectManager::Instance()->getObject(object_id);
	variable_n=variable_name;
	variable_v=variable_value;
}
bool Event::checkEvent(bool coll_cond){
	
	if(event_type==BUTTON_CLICK&&coll_cond==false){
		return InputHandler::Instance()->isKeyDown(scancode);
	}
	else if(event_type==BUTTON_RELEASE&&coll_cond==false){
		if(InputHandler::Instance()->isKeyDown(scancode)){
			previous_button_stats=true;
			return false;
		}
		else if(!InputHandler::Instance()->isKeyDown(scancode)&&previous_button_stats==true){
			previous_button_stats=false;
			return true;
		}
		return false;
	}
	else if(event_type==COLLISION&&coll_cond==true&&subject->is_alive==true){
		return CollisionManager::Instance()->isColliding(parent->collision_polygon,subject->collision_polygon);
	}
	else if(event_type==VARIABLE_VALUE_TRIGGER&&coll_cond==false&&subject->is_alive==true){
		if(subject->variable_value_map[variable_n].first!=subject->variable_value_map[variable_n].second)
		return subject->isVariableEqual(variable_n,variable_v);
	}
	return false;
}
void Event::handleEvent(bool coll_cond){
	if(checkEvent(coll_cond)){
		for(std::vector<int>::size_type i = 0; i != action_list.size(); i++){ 
			action_list[i]->runAction();
		}
	}
}