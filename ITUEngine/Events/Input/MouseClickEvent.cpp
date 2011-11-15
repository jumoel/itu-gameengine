#include <Events/Input/MouseClickEvent.hpp>

MouseClickEvent::MouseClickEvent(SDL_MouseButtonEvent *input, short eventtype) : EventObject(eventtype)
{
	this->input = input;
}

MouseClickEvent::~MouseClickEvent(void)
{
}

SDL_MouseButtonEvent* MouseClickEvent::GetInput()
{
	return input;
}

void MouseClickEvent::TestPrint()
{
	// Outputs a test-string to the console of the type:
	// Clicked: <button>, at: <x,y>
	cout << "Clicked: <" << input->button << ">, ";
	cout << "at: <" << input->x << "," << input->y << ">" << endl;
}