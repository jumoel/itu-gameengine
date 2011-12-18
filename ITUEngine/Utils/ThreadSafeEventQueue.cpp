#include <Utils/ThreadSafeEventQueue.hpp>
#include <windows.h>

bool ThreadSafeEventQueue::locked = false;

//NOTE: This queue is not ThreadSafe...

void ThreadSafeEventQueue::push(IEventDataPointer const& data)
{
	//NOTE: Sleep is a WINAPI cmd.
	//while(Locked()) { Sleep( 5 ); }
	//Lock();
	
	the_queue.push(data);
	
	//Unlock();
}

bool ThreadSafeEventQueue::empty() const
{
	//NOTE: Sleep is a WINAPI cmd.
	//while(Locked()) { Sleep( 5 ); }
	//Lock();
	
	auto result = the_queue.empty();

	//Unlock();
	return result;
}

bool ThreadSafeEventQueue::try_pop(IEventDataPointer& popped_value)
{
	//NOTE: Sleep is a WINAPI cmd.
	//while(Locked()) { Sleep( 5 ); }
	//Lock();

	if(the_queue.empty())
	{
		return false;
	}

	popped_value=the_queue.front();
	the_queue.pop();

	//Unlock();
	return true;
}

bool ThreadSafeEventQueue::Locked()
{
	return ThreadSafeEventQueue::locked;
}

void ThreadSafeEventQueue::Lock()
{
	ThreadSafeEventQueue::locked = true;
}

void ThreadSafeEventQueue::Unlock()
{
	ThreadSafeEventQueue::locked = false;
}