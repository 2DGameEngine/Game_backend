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
void TextObject::setVisible(bool visible){
	TextObject::visible=visible;
}
std::string TextObject::getId(){
	return id;
}
TextObject::TextObject(Vector2D position, std::string id, std::string text, std::string font_file, float size, float color_red, float color_green, float color_blue){
	TextObject::position=position;
	TextObject::id=id;
	TextObject::text=text;
	TextObject::size=size;
	TextObject::font_file=font_file;
	TextObject::color_green=color_green;
	TextObject::color_red=color_red;
	TextObject::color_blue=color_blue;
	TextObject::visible=true;
}
TextObject::TextObject(Vector2D position, std::string id, std::string text, std::string font_file, float size){
	TextObject::position=position;
	TextObject::id=id;
	TextObject::text=text;
	TextObject::font_file=font_file;
	TextObject::size=size;
	TextObject::color_green=0;
	TextObject::color_red=0;
	TextObject::color_blue=0;
	TextObject::visible=true;
}
bool TextObject::load_texture(){
	TTF_Font* tempFont = TTF_OpenFont(font_file.c_str(),size);
	SDL_Color textColor = {color_red,color_green,color_blue};
	SDL_Surface* tempSurface=TTF_RenderText_Solid(tempFont,text.c_str(),textColor);
	width_of_frame = tempSurface->w;
	height_of_frame = tempSurface->h;
	texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(),tempSurface);
	SDL_FreeSurface(tempSurface);
	return true;
}
void TextObject::draw(){
	TextObject::load_texture();
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	sourceRectangle.x=0;
	sourceRectangle.y=0;
	sourceRectangle.w=width_of_frame;
	sourceRectangle.h=height_of_frame;
	destinationRectangle.x=position.getX();
	destinationRectangle.y=position.getY();
	destinationRectangle.w=width_of_frame;
	destinationRectangle.h=height_of_frame;
	SDL_RenderCopyEx(TheGame::Instance()->getRenderer(),texture,&sourceRectangle,&destinationRectangle,0,0,SDL_FLIP_NONE);
}