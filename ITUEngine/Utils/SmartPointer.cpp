#include <Utils/SmartPointer.hpp>

template <typename T>
SmartPointer<T>::SmartPointer(T* pointer)
{
	_data = pointer;
}

template <typename T>
SmartPointer<T>::~SmartPointer()
{
	delete _data;
}

template <typename T>
T& SmartPointer<T>::operator *()
{
	return *_data;
}

template <typename T>
T* SmartPointer<T>::operator ->()
{
	return _data;
}