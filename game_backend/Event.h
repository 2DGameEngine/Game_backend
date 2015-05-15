#ifndef _EVENT_
#define _EVENT_
#include <SDL.h>
#include "Action.h"
#include "InputHandler.h"
#include "CollisionManager.h"
#include <string>
class Action;
enum event_types{
		BUTTON_CLICK,
		MOUSE_MOVE,
		VARIABLE_VALUE,
		COLLISION
	};
class Event{
public:
	void setEvent(event_types,SDL_Scancode);
	void setEvent(event_types,std::string);
	std::vector<Action*> action_list;
	void addAction(Action*);
	bool checkEvent();
	void handleEvent();
	GameObject* parent;
private:
	event_types event_type;
	SDL_Scancode scancode;
	GameObject* subject;

};
#endif