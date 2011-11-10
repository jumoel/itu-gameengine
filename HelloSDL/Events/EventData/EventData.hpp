#ifndef ITUENGINE_EVENTDATA_H
#define ITUENGINE_EVENTDATA_H

#include <Events/EventData/BaseEventData.hpp>

template < typename T >
class EventData : public BaseEventData
{
private:
	EventData();					// disable default construction
	EventData(const EventData &);	// disable copy construction

	const EventType	m_EventType;	//Type of this event.
	T m_Value;

public:
	explicit EventData( T data,  const EventType & eventType, const float timeStamp = 0.0f )
		: BaseEventData(timeStamp)
		, m_EventType(eventType)
	{
		m_Value = data;
	}



	virtual ~EventData() { }

	const T GetValue() { return m_Value; }

	virtual void Serialize(std::ostream &out) const
	{

	};

	virtual const EventType & GetEventType() const
	{
		return m_EventType;
	}

	virtual IEventDataPointer Copy() const
	{
		return IEventDataPointer(new EventData<T>(m_Value, m_EventType, m_TimeStamp));
	}
};

#endif //ITUENGINE_EVENTDATA_H