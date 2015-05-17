#ifndef _TEXTOBJECT_
#define _TEXTOBJECT_
#include "Vector2D.h"
#include <string>
#include <map>
#include <vector>
class TextObject{
public:
	Vector2D position;
	std::string id;
	std::string text;
	float size;
	void setPosition(Vector2D position);
	void setText(std::string text);
	void setSize(float size);
};
#endif