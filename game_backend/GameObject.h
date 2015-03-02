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
class GameObject{
public:
	GameObject(std::string state_id,int width,int height);
	std::string state_id;
	bool loadSprite(std::string filename);
	bool define_animation(std::string animation_name,std::vector<std::pair<int,int>>,float speed);
	void update();
	void draw();
	void clean();
	void set_state(std::string state_id){
		GameObject::state_id=state_id;
	}
private:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	int width;
	int height;
	SDL_Texture* texture;
	std::map <std::string,std::pair<std::vector<std::pair<int,int>>,float>> animations;
	//collision polygon
 
};
#endif