#pragma once

#define KEYBOARD_EVENT		0
#define MOUSE_CLICK_EVENT	1
#define MOUSE_MOVE_EVENT	2
#define COLLISION_EVENT		3

class EventObject
{
public:
	EventObject(short type);
	~EventObject(void);
	
	short GetType();

protected:
	short type;
};

