#ifndef ITUENGINE_IEVENTDATA_H
#define ITUENGINE_IEVENTDATA_H

#include <Utils/StringUtils.hpp>

typedef hash EventType;

class IEventData;
typedef std::shared_ptr<IEventData> IEventDataPointer;

class IEventData
{
public:
	virtual const EventType & GetEventType() const = 0;
	virtual float GetTimeStamp() const = 0;
	virtual void Serialize(std::ostream &out) const = 0;

	virtual IEventDataPointer Copy() const = 0;
};

#endif //ITUENGINE_IEVENTDATA_H

