#ifndef ITUENGINE_PROFILER_H
#define ITUENGINE_PROFILER_H

#include <utility>
#include <map>
#include <vector>
#include <stdint.h>
#include <Utils/Log.hpp>

class Profiler
{
public:
	Profiler();
	~Profiler();

	void Begin(const char* name);
	void End(const char* name);

private:
	typedef const char* ProfileKey;
	typedef uint32_t ProfileTimestamp;
	typedef uint32_t DeltaTime;

	typedef std::vector<DeltaTime> ProfileTimeList;

	typedef std::map<ProfileKey, ProfileTimestamp> ProfileMap;
	typedef std::pair<ProfileKey, ProfileTimestamp> ProfileSet;

	typedef std::map<ProfileKey, ProfileTimeList> ProfileHistoricMap;
	typedef std::pair<ProfileKey, ProfileTimeList> ProfileHistoricSet;

	typedef std::map<ProfileKey, Log> ProfileLogMap;
	//typedef std::pair<ProfileKey, *Log> ProfileLogSet;

	void WriteToLogFiles();

	int m_WriteToLogCounter;
	
	ProfileMap m_ProfileMap;
	ProfileLogMap m_ProfileLogMap;
	ProfileHistoricMap m_ProfileHistoricMap;

};

#endif //ITUENGINE_PROFILER_H