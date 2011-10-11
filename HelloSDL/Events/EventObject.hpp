#ifndef ITUENGINE_EVENTOBJECT_H
#define ITUENGINE_EVENTOBJECT_H

#define NO_EVENT				0	/* Unused, do not remove ! */

// World Events
#define COLLISION_EVENT			1	/* Collision detected */


// Keyboard Events
#define KEYDOWN_EVENT			2	/* Keys pressed */
#define KEYUP_EVENT				3	/* Keys released */

// Mouse Events
#define MOUSEMOTION_EVENT		4	/* Mouse moved */
#define MOUSEBUTTONDOWN_EVENT	5	/* Mouse button pressed */
#define MOUSEBUTTONUP_EVENT		6	/* Mouse button released */


class EventObject
{
public:
	EventObject(short type);
	~EventObject(void);
	
	short GetType();

protected:
	short type;
};

#endif