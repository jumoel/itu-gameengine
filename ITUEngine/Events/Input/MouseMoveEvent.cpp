#include <Events/Input/MouseMoveEvent.hpp>

MouseMoveEvent::MouseMoveEvent(SDL_MouseMotionEvent *input, short eventtype) : EventObject(eventtype)
{
	this->input = input;
}

MouseMoveEvent::~MouseMoveEvent(void)
{
}

SDL_MouseMotionEvent* MouseMoveEvent::GetInput()
{
	return input;
}

void MouseMoveEvent::TestPrint()
{
	// Outputs a test-string to the console of the type:
	// Moved: <x,y>, relative: <xrel,yrel>
	cout << "Moved: <" << input->x << "," << input->y << ">, ";
	cout << "relative: <" << input->xrel << "," << input->yrel << ">" << endl;
}