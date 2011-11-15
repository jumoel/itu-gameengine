#include <Events/Input/KeyPressedEvent.hpp>

KeyPressedEvent::KeyPressedEvent(SDL_KeyboardEvent *input, short eventtype) : EventObject(eventtype)
{
	this->input = input;
}

KeyPressedEvent::~KeyPressedEvent(void)
{
}

SDL_KeyboardEvent* KeyPressedEvent::GetInput()
{
	return input;
}

void KeyPressedEvent::TestPrint()
{
	// Outputs a test-string to the console of the type:
	// Keyboard: <keysym.sym>, with action: <type>
	cout << "Keyboard: <" << input->keysym.sym << ">, ";
	cout << "with action: <" << input->type << ">" << endl;
}