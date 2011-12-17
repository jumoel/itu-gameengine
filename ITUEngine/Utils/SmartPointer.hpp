#ifndef ITUENGINE_SMARTPOINTER_HPP
#define ITUENGINE_SMARTPOINTER_HPP

#include <Utils/ReferenceCounter.hpp>


/* Smart Pointer
 * =============
 *
 * Will keep a count of the number of references to an object.
 * When the pointer goes out of scope, the referencecount will
 * be decremented.
 * When the count reaches zero, the data is deleted.
 */
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