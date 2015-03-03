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
class GameObject{
public:
	GameObject(std::string state_id,Model*,int width,int height);
	void update();
	void draw();
	void clean();
	void setState(std::string state){
		GameObject::state=state;
	}
	std::string getAnimationName(std::string state){
		return state_animation_map[state];
	}
	void add_state_animation_pair(std::string,std::string);
private:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	int width;
	int height;
	Model* model;
	std::map <std::string,std::string> state_animation_map;
	std::string state;
	//std::map <std::string,std::pair<std::vector<std::pair<int,int>>,float>> animations;
	//collision polygon
 
};
#endif