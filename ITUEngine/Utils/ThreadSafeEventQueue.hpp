#ifndef ITUENGINE_THREADSAFEEVENTQUEUE_H
#define ITUENGINE_THREADSAFEEVENTQUEUE_H

#include <Events/Interfaces/IEventData.hpp>
#include <queue>

class ThreadSafeEventQueue
{
public:
	void push(IEventDataPointer const& data);
	bool empty() const;
	bool try_pop(IEventDataPointer& popped_value);

private:
	std::queue<IEventDataPointer> the_queue;

	static bool Locked();
	static void Lock();
	static void Unlock();

	static bool locked;
};

#endif //ITUENGINE_THREADSAFEEVENTQUEUE_H
