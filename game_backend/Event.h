#ifndef _EVENT_
#define _EVENT_
#include <SDL.h>
#include "Action.h"
#include "InputHandler.h"
#include "CollisionManager.h"
#include "FileManager.h"
#include "Parser.h"
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
	void setEvent(std::string,std::string,std::map<std::string,retJSON>);
	void setEvent(std::string,std::map<std::string,retJSON>,std::map<std::string,retJSON>);
	//std::vector<Action*> action_list;
	void addAction(Action*);
	bool checkEvent(bool);
	void handleEvent(bool);
	GameObject* parent;
private:
	std::string eventType;
	std::string check_value;
	std::map<std::string,retJSON> event_condition;
	std::map<std::string,retJSON> action_list;
	SDL_Scancode scancode;
	GameObject* subject;
	std::string variable_n;
	float variable_v;
	bool previous_button_stats;
};
#endif