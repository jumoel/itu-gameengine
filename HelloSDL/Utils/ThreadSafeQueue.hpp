#ifndef ITUENGINE_THREADSAFEQUEUE_H
#define ITUENGINE_THREADSAFEQUEUE_H

template<typename Data>
class ThreadSafeQueue
{
public:
	void push(Data const& data);
	bool empty() const;
	bool try_pop(Data& popped_value);

private:
	std::queue<Data> the_queue;
	static bool locked = false;
};

#endif //ITUENGINE_THREADSAFEQUEUE_H
