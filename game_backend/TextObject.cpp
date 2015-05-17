#include "TextObject.h"
void TextObject::setPosition(Vector2D position){
	TextObject::position=position;
}
void TextObject::setSize(float size){
	TextObject::size=size;
}
void TextObject::setText(std::string text){
	TextObject::text=text;
}