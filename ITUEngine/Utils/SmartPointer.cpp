#include <Utils/SmartPointer.hpp>

template <typename T>
SmartPointer<T>::SmartPointer(T* pointer) : _data(pointer), _references(0)
{
	_references = new ReferenceCounter();
	_references->AddReference();
}

template <typename T>
SmartPointer<T>::SmartPointer() : _data(0), _references(0)
{
	_references = new ReferenceCounter();
	_references->AddReference();
}


// Copy constructur.
// Add a reference
template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& sp) : _data(sp._data), _references(sp._references)
{
	_references->AddReference();
}

template <typename T>
SmartPointer<T>::~SmartPointer()
{
	// Only delete the data if no one is still using it.
	if (_references->Release() == 0)
	{
		delete _data;
		delete _references;
	}
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


// Assigment operator
template <typename T>
SmartPointer<T>& SmartPointer<T>::operator =(const SmartPointer<T>& sp)
{
	// Don't do self assignment
	if (this != *sp)
	{
		// Decrement the old reference count and delete if necessary
		if (_references->Release() == 0)
		{
			delete _data;
			delete _references;
		}

		_data = sp._data;
		_references = sp._references;

		_references->AddReference();
	}

	return *this;
}