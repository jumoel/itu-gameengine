#ifndef ITUENGINE_BASEEVENTDATA_H
#define ITUENGINE_BASEEVENTDATA_H

#include <Events/Interfaces/IEventData.hpp>

class BaseEventData : public IEventData
{
public:
	explicit BaseEventData(const float timeStamp = 0.0f ) : m_TimeStamp(timeStamp) { }
	virtual ~BaseEventData() { }

	virtual float GetTimeStamp() const
	{
		return m_TimeStamp;
	}
	
	virtual void Serialize(std::ostream &out) const
	{

	};

	virtual const EventType & GetEventType() const = 0;	
	virtual IEventDataPointer Copy() const = 0;
protected:
	const float m_TimeStamp;
};

#endif //ITUENGINE_BASEEVENTDATA_H