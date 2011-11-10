#include <Events/EventData/EventData.hpp>

template < typename T >
void EventData<T>::Serialize( std::ostream &out ) const
{

}

template < typename T >
const EventType & EventData<T>::GetEventType() const
{
	return m_EventType;
}

template < typename T >
IEventDataPointer EventData<T>::Copy() const
{
	return IEventDataPointer(new EventData<T>(m_Value, m_EventType, m_TimeStamp));
}

template < typename T >
const T EventData<T>::GetValue()
{
	return m_Value;
}



