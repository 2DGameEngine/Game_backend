#ifndef _CAMERA_
#define _CAMERA_
#include "SDL.h"
class Camera{
public:
	Camera(float width,float height,Vector2D position,std::string type,std::string linkedObject,Vector2D offset);
	float width;
	float height;
	Vector2D position;
	Vector2D offset;
	std::string type;
	std::string linkedObject;
	void setWidth(float new_width);
	void setHeight(float new_height);
	void setPosition(Vector2D new_postion);
	void setType(std::string new_type);
	void setLinkedObject(std::string new_linkedObject);
	Vector2D getPosition();
};
#endif