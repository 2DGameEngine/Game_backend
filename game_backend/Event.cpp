#include "Event.h"
void Event::addAction(Action* action){
	action_list.push_back(action);
}
void Event::setEvent(event_types e,SDL_Scancode scancode){
	event_type=e;
	Event::scancode=scancode;
}
void Event::setEvent(event_types e,std::string object_id){
	event_type=e;

	subject=GameObjectManager::Instance()->getObject(object_id);
	
	
}
bool Event::checkEvent(bool coll_cond){
	
	if(event_type==BUTTON_CLICK&&coll_cond==false){
		return InputHandler::Instance()->isKeyDown(scancode);
	}
	else if(event_type==COLLISION&&coll_cond==true&&subject->is_alive==true){
		std::cout<<CollisionManager::Instance()->isColliding(parent->collision_polygon,subject->collision_polygon);
		return CollisionManager::Instance()->isColliding(parent->collision_polygon,subject->collision_polygon);
	}
	return false;
}
void Event::handleEvent(bool coll_cond){
	if(checkEvent(coll_cond)){
		for(std::vector<int>::size_type i = 0; i != action_list.size(); i++){ 
			action_list[i]->runAction();
		}
		std::cout<<"a";
	}
}