#include "GameObject.h"
bool GameObject::loadSprite(std::string filename){
	SDL_Surface* pTempSurface=IMG_Load(filename.c_str());
	if(pTempSurface)
		std::cout<<"image found\n";
	else{
		std::cout<<IMG_GetError();
		return false;
	}
	texture=SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(),pTempSurface);
	SDL_FreeSurface(pTempSurface);
	return true;
}
bool GameObject::define_animation(std::string animation_name,std::vector<std::pair<int,int>> frame_ids,float speed){
	animations[animation_name]=std::make_pair(frame_ids,speed);
	return true;
}
void GameObject::update(){
	velocity=Vector2D(0,0);
	set_state("stop");
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)){
		set_state("walk_right");
		velocity.setX(1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)){
		set_state("walk_left");
		velocity.setX(-1);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)){
		set_state("walk_right");
		velocity.setY(-5);
	}
	if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)){
		set_state("walk_left");
		velocity.setY(1);
	}
	if(position.getY()>400){
		position.setY(400);
	}
	acceleration.setY(6);
	velocity+=acceleration;
	position+=velocity;
}
void GameObject::draw(){
	SDL_Rect destinationRectangle;
	SDL_Rect sourceRectangle;
	int refresh_rate=100/(animations[state_id].second);
	int frame_number=int((SDL_GetTicks()/refresh_rate) %(animations[state_id].first.size()));
	std::cout<<frame_number;
	sourceRectangle.x = (animations[state_id].first[frame_number].second-1)*width;
	sourceRectangle.y = (animations[state_id].first[frame_number].first-1)*height;
	destinationRectangle.x = position.getX();
	destinationRectangle.y = position.getY();
	destinationRectangle.w = sourceRectangle.w=width;
	destinationRectangle.h = sourceRectangle.h=height;
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),texture,&sourceRectangle,&destinationRectangle,0,0,SDL_FLIP_NONE);
}
GameObject::GameObject(std::string state_id,int width,int height){
		GameObject::state_id=state_id;
		GameObject::position = Vector2D();
		GameObject::velocity = Vector2D(0,0);
		GameObject::acceleration = Vector2D(.01,.01);
		GameObject::width=width;
		GameObject::height=height;
	}