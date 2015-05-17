#include "GameObject.h"
#include "Camera.h"
#include "SDL.h"
void Camera::setHeight(float new_height){
	height=new_height;
}
void Camera::setPosition(Vector2D new_position){
	position=new_position;
}
void Camera::setWidth(float new_width){
	width=new_width;
}
void Camera::setType(std::string new_type){
	type=new_type;
}
void Camera::setLinkedObject(std::string new_linkedObject){
	linkedObject=new_linkedObject;
}
Vector2D Camera::getPosition(){
	if(type=="static"){
		return position;
	}
	else if(type=="dynamic"){
		return GameObjectManager::Instance()->getObject(linkedObject)->position;
	}
}
Camera::Camera(float width,float height,Vector2D position,std::string type,std::string linkedObject){
	Camera::width=width;
	Camera::height=height;
	Camera::position=position;
	Camera::type=type;
	Camera::linkedObject=linkedObject;
}
