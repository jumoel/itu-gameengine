#include "MouseMoveEvent.h"
#include "SDL_events.h"

MouseMoveEvent::MouseMoveEvent(SDL_MouseMotionEvent *input) : EventObject(type)
{

}


MouseMoveEvent::~MouseMoveEvent(void)
{
}
