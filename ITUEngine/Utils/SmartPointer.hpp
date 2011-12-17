#ifndef ITUENGINE_SMARTPOINTER_HPP
#define ITUENGINE_SMARTPOINTER_HPP

#include <Utils/ReferenceCounter.hpp>

template <typename T> class SmartPointer
{
private:
	T *_data;
	ReferenceCounter *_references;

public:
	SmartPointer(const SmartPointer<T>& sp);
	SmartPointer(T* pointer);
	SmartPointer();

	~SmartPointer();

	T& operator *();
	T* operator ->();
	SmartPointer<T>& operator =(const SmartPointer<T>& sp);

};

#endif ITUENGINE_SMARTPOINTER_HPP