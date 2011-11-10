#ifndef ITUENGINE_EMPTYEVENTDATA_H
#define ITUENGINE_EMPTYEVENTDATA_H

#include <Events/EventData/BaseEventData.hpp>

class EmptyEventData : public BaseEventData
{
public:
	explicit EmptyEventData( const EventType & eventType, const float timeStamp = 0.0f );
	virtual ~EmptyEventData() {}

	virtual const EventType & GetEventType() const;	
protected:
	const EventType	m_EventType;	//Type of this event.
};

#endif //ITUENGINE_EMPTYEVENTDATA_H