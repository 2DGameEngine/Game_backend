#ifndef _TEXTOBJECT_
#define _TEXTOBJECT_
#include "Vector2D.h"
#include <string>
#include <map>
#include <vector>
#include "SDL_ttf.h"
#include "SDL.h"
#include "Game.h"
class TextObject{
public:
	TextObject(Vector2D position, std::string id, std::string text, std::string font_file, float size, float color_red, float color_green, float color_blue);
	TextObject(Vector2D position, std::string id, std::string text, std::string font_file, float size);
	Vector2D position;
	std::string id;
	std::string text;
	std::string font_file;
	float color_red;
	float color_green;
	float color_blue;
	float size;
	bool visible;
	void setPosition(Vector2D position);
	void setText(std::string text);
	void setSize(float size);
	bool TextObject::load_texture();
	void draw();
private:
	SDL_Texture* texture;
	int width_of_frame;
	int height_of_frame;
};
#endif