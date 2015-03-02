#include <SDL.h>
enum event_type{
		BUTTON_CLICK,
		MOUSE_MOVE,
		VARIABLE_VALUE
	}
class Event{
	void setEvent(event_type,SDL_Scancode);

};