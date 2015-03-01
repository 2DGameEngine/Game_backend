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
bool GameObject::define_animation(std::string animation_name,std::vector<int> frame_ids){
	animations[animation_name]=frame_ids;
	return true;
}
void GameObject::update(){
	//velocity+=acceleration;
	//position+=velocity;
}
void GameObject::draw(){
	SDL_Rect destinationRectangle;
	SDL_Rect sourceRectangle;
	int frame_number=int((SDL_GetTicks()/100) %(animations[state_id].size()));
	std::cout<<frame_number;
	sourceRectangle.x = (animations[state_id][frame_number]-1)*width;
	sourceRectangle.y = 0;
	destinationRectangle.x = position.getX();
	destinationRectangle.y = position.getY();
	destinationRectangle.w = sourceRectangle.w=width;
	destinationRectangle.h = sourceRectangle.h=height;
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),texture,&sourceRectangle,&destinationRectangle,0,0,SDL_FLIP_NONE);
}
GameObject::GameObject(std::string state_id,int width,int height){
		GameObject::state_id=state_id;
		GameObject::position = Vector2D();
		GameObject::velocity = Vector2D();
		GameObject::acceleration = Vector2D();
		GameObject::width=width;
		GameObject::height=height;
	}