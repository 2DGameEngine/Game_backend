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
	GameObject(std::string state_id,Model*,float width,float height,float positionX,float positionY,float velocityX,float velocityY,float accelerationX,float accelerationY,bool,bool);
	GameObject(std::string state_id,Model*,float width,float height,float positionX,float positionY,float velocityX,float velocityY,float accelerationX,float accelerationY,std::string,bool,bool);
	void update(bool);
	void defaultUpdate();
	void draw();
	void clean();
	void setState(std::string state){
		GameObject::state=state;
	}
	Vector2D getPosition(){
		return Vector2D(variable_value_map["position_x"].first,variable_value_map["position_y"].first);
	}
	Vector2D getVelocity(){
		return Vector2D(variable_value_map["velocity_x"].first,variable_value_map["velocity_y"].first);
	}
	Vector2D getAcceleration(){
		return Vector2D(variable_value_map["acceleration_x"].first,variable_value_map["acceleration_y"].first);
	}
	void setPosition(Vector2D position){
		variable_value_map["position_x"].first=position.getX();
		variable_value_map["position_y"].first=position.getY();
		collision_polygon->updatePosition(position.getX(),position.getY());
	}
	void setVelocity(Vector2D velocity){
		variable_value_map["velocity_x"].first=velocity.getX();
		variable_value_map["velocity_y"].first=velocity.getY();
	}
	void setAcceleration(Vector2D acceleration){
		variable_value_map["acceleration_x"].first=acceleration.getX();
		variable_value_map["acceleration_y"].first=acceleration.getY();
	}
	/*
	void setVelocity(Vector2D velocity){
		GameObject::velocity=velocity;
	}*/
	void setVelocityX(float x){
		variable_value_map["velocity_x"].first=x;
	}
	void setVelocityY(float y){
		variable_value_map["velocity_y"].first=y;
	}
	/*
	void setPosition(Vector2D position){
		GameObject::position=position;
		collision_polygon->updatePosition(position.getX(),position.getY());
	}*/
	void setPositionX(float new_x){
		variable_value_map["position_x"].first=new_x;
		collision_polygon->updatePosition(new_x,getPosition().getY());
	}
	void setPositionY(float new_y){
		variable_value_map["position_y"].first=new_y;
		collision_polygon->updatePosition(getPosition().getX(),new_y);
	}

	void translateX(float x){
		variable_value_map["position_x"].first+=x;
		collision_polygon->updatePosition(variable_value_map["position_x"].first,getPosition().getY());
	}
	void translateY(float y){
		variable_value_map["position_y"].first+=y;
		collision_polygon->updatePosition(getPosition().getX(),variable_value_map["position_y"].first);
	}
	std::string getAnimationName(std::string state){
		return state_animation_map[state];
	}
	void GameObject::updatePosition();
	void add_state_animation_pair(std::string,std::string);
	void add_variable(std::string,float);
	void change_variable(std::string,float);
	float return_variable_value(std::string);
	std::string object_id;
	void addEvent(Event* event);
	bool updated;
	CollisionPolygon *collision_polygon;
	bool isVariableEqual(std::string,float);
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	void deleteOb();
	float width;
	float height;
	bool rigid;
	bool is_alive;
	bool is_static;
	
	std::map <std::string,std::pair <float,float>> variable_value_map;
private:
	Model* model;
	std::map <std::string,std::string> state_animation_map;
	
	std::string state;
	std::vector<Event*> events;
	//std::map <std::string,std::pair<std::vector<std::pair<int,int>>,float>> animations;
	//collision polygon
 
};
#endif