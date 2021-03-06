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
		BUTTON_RELEASE,
		MOUSE_MOVE,
		COLLISION,
		VARIABLE_VALUE_TRIGGER
	};
class Event{
public:
	void setEvent(event_types,SDL_Scancode);
	void setEvent(event_types,std::string);
	void setEvent(event_types,std::string,std::string,float);
	std::vector<Action*> action_list;
	void addAction(Action*);
	bool checkEvent(bool);
	void handleEvent(bool);
	GameObject* parent;
private:
	event_types event_type;
	SDL_Scancode scancode;
	GameObject* subject;
	std::string variable_n;
	float variable_v;
	bool previous_button_stats;
};
#endif