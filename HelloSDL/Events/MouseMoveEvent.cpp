#include "MouseMoveEvent.h"
#include "SDL_events.h"

MouseMoveEvent::MouseMoveEvent(SDL_MouseMotionEvent *input, short eventtype) : EventObject(eventtype)
{

}


MouseMoveEvent::~MouseMoveEvent(void)
{
}
