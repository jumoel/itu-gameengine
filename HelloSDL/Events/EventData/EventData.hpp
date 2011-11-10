#ifndef ITUENGINE_EVENTDATA_H
#define ITUENGINE_EVENTDATA_H

#include <Events/EventData/BaseEventData.hpp>

template < typename T >
class EventData : BaseEventData
{
public:
	explicit EventData( T data,  const EventType & eventType, const float timeStamp = 0.0f )
		: BaseEventData(timeStamp)
		, m_EventType(eventType)
	{
		m_Value = data;
	}

	virtual ~EventData() { }

	virtual void Serialize(std::ostream &out) const;

	virtual const EventType & GetEventType() const;	
	virtual IEventDataPointer Copy() const;

	const T GetValue();
	
private:
	EventData();					// disable default construction
	EventData(const EventData &);	// disable copy construction

	const EventType	m_EventType;	//Type of this event.
	T m_Value;
};

#endif //ITUENGINE_EVENTDATA_H