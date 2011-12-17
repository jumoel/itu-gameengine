#ifndef ITUENGINE_SMARTPOINTER_HPP
#define ITUENGINE_SMARTPOINTER_HPP

template <typename T> class SmartPointer
{
private:
	T* _data;

public:
	SmartPointer(T* pointer);
	~SmartPointer();

	T& operator *();
	T* operator ->();

}

#endif ITUENGINE_SMARTPOINTER_HPP