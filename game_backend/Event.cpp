#include "Event.h"
/*void Event::addAction(Action* action){
	action_list.push_back(action);
}*/
void Event::setEvent(std::string e,std::string button_value,std::map<std::string,retJSON> action_structure){
	eventType=e;
	check_value=button_value;
	action_list=action_structure;
	previous_button_stats=false;
}
/*void Event::setEvent(std::string e,std::string object_id,std::map<std::string,retJSON> action_structure){
	event_type=e;
	subject=GameObjectManager::Instance()->getObject(object_id);
	action_list=action_structure;
	
}*/
void Event::setEvent(std::string e,std::map<std::string,retJSON> event_structure,std::map<std::string,retJSON> action_structure){
	eventType=e;
	event_condition=event_structure;
	action_list=action_structure;
}
bool Event::checkEvent(bool coll_cond){
	
	if(eventType=="KBHit"&&coll_cond==false){
		if(check_value=="W")
			scancode=SDL_SCANCODE_W;
		else if(check_value=="A")
			scancode=SDL_SCANCODE_A;
		else if(check_value=="S")
			scancode=SDL_SCANCODE_S;
		else if(check_value=="D")
			scancode=SDL_SCANCODE_D;
		else if(check_value=="Z")
			scancode=SDL_SCANCODE_Z;
		else if(check_value=="X")
			scancode=SDL_SCANCODE_X;
		else if(check_value=="C")
			scancode=SDL_SCANCODE_C;
		else if(check_value=="F")
			scancode=SDL_SCANCODE_F;
		return InputHandler::Instance()->isKeyDown(scancode);
	}
	else if(eventType=="KBRelease"&&coll_cond==false){
		if(check_value=="W")
			scancode=SDL_SCANCODE_W;
		else if(check_value=="A")
			scancode=SDL_SCANCODE_A;
		else if(check_value=="S")
			scancode=SDL_SCANCODE_S;
		else if(check_value=="D")
			scancode=SDL_SCANCODE_D;
		else if(check_value=="Z")
			scancode=SDL_SCANCODE_Z;
		else if(check_value=="X")
			scancode=SDL_SCANCODE_X;
		else if(check_value=="C")
			scancode=SDL_SCANCODE_C;
		else if(check_value=="F")
			scancode=SDL_SCANCODE_F;
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
	else if(eventType=="COLLISION"&&coll_cond==true&&subject->is_alive==true){
		subject=GameObjectManager::Instance()->getObject(check_value);
		return CollisionManager::Instance()->isColliding(parent->collision_polygon,subject->collision_polygon);
	}
	else if(eventType=="VARIABLE_VALUE_TRIGGER"&&coll_cond==false&&subject->is_alive==true){
		return Parser::Instance()->editorParserExt(event_condition);	
	}
	return false;
}
void Event::handleEvent(bool coll_cond){
	if(checkEvent(coll_cond)){
			Parser::Instance()->editorEval(action_list);
		}
	}
