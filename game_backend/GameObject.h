#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_
#include "Vector2D.h"
#include "SDL.h"
#include <string>
#include "Game.h"
#include <SDL_image.h>
#include <map>
#include <vector>
#include "InputHandler.h"
#include "Model.h"
#include "CollisionPolygon.h"
class Model;
class Event;
class GameObject{
public:
	GameObject(std::string state_id,Model*,float width,float height,Vector2D position);
	GameObject(std::string state_id,Model*,float width,float height,Vector2D position,std::string);
	void update();
	void defaultUpdate();
	void draw();
	void clean();
	void setState(std::string state){
		GameObject::state=state;
	}
	void setVelocity(Vector2D velocity){
		GameObject::velocity=velocity;
	}
	void setPosition(Vector2D position){
		GameObject::position=position;
	}
	std::string getAnimationName(std::string state){
		return state_animation_map[state];
	}
	void add_state_animation_pair(std::string,std::string);
	std::string object_id;
	void addEvent(Event* event);
	bool updated;
	CollisionPolygon *collision_polygon;
private:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	int width;
	int height;
	Model* model;
	std::map <std::string,std::string> state_animation_map;
	std::string state;
	std::vector<Event*> events;
	//std::map <std::string,std::pair<std::vector<std::pair<int,int>>,float>> animations;
	//collision polygon
 
};
#endif