#include <Events/EventData/EmptyEventData.hpp>

EmptyEventData::EmptyEventData( const EventType & eventType, const float timeStamp /*= 0.0f */ )
	: m_EventType ( eventType )
	, BaseEventData ( timeStamp )
{

}

const EventType & EmptyEventData::GetEventType() const
{
	return m_EventType;
}
