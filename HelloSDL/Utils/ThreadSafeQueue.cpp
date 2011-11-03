#include <Utils/ThreadSafeQueue.hpp>

void ThreadSafeQueue::push(Data const& data)
{
	//NOTE: Sleep is a WINAPI cmd.
	while(locked) { Sleep( 5 ); }
	locked = true;
	
	the_queue.push(data);
	
	locked = false;
}

bool ThreadSafeQueue::empty() const
{
	//NOTE: Sleep is a WINAPI cmd.
	while(locked) { Sleep( 5 ); }
	locked = true;
	
	auto result = the_queue.empty();

	locked = false;
	return result;
}

bool ThreadSafeQueue::try_pop(Data& popped_value)
{
	//NOTE: Sleep is a WINAPI cmd.
	while(locked) { Sleep( 5 ); }
	locked = true;
	
	if(the_queue.empty())
	{
		return false;
	}

	popped_value=the_queue.front();
	the_queue.pop();

	locked = false;
	
	return true;
}