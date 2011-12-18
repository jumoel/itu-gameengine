#include <Utils/Profiler.hpp>
#include <Abstractions/Time.hpp>
#include <Assertion.hpp>
#include <string>
#include <utility>

void Profiler::StartUp()
{
	m_WriteToLogCounter = 0;
}

void Profiler::ShutDown()
{
	WriteToLogFiles();
	m_ProfileMap.clear();
	m_ProfileHistoricMap.clear();
	m_ProfileLogMap.clear();
}

void Profiler::Begin(const char* name)
{
	ProfileTimestamp now = Time::GetCurrentMS();

	//Try to find name in our profile map.
	auto profileMapIterator = m_ProfileMap.find(name);
	if(profileMapIterator == m_ProfileMap.end())
	{
		//If it's not found, create it.
		m_ProfileMap.insert(  std::make_pair(name, now) );
		profileMapIterator = m_ProfileMap.find(name);

		ASSERT_MSG(profileMapIterator != m_ProfileMap.end(), "This should not happen");
	}
	else
	{
		//If it's found replace the timestamp.
		profileMapIterator->second = now;
	}
}

void Profiler::End(const char* name)
{
	ProfileTimestamp now = Time::GetCurrentMS();

	//Try to find name in our profile map.
	auto profileMapIterator = m_ProfileMap.find(name);
	if(profileMapIterator != m_ProfileMap.end())
	{
		//If it's found get the start time.
		ProfileTimestamp start = profileMapIterator->second;
		DeltaTime delta = now - start;

		//Try to find name in our historic profile map.
		auto historicMapIterator = m_ProfileHistoricMap.find(name);
		if(historicMapIterator == m_ProfileHistoricMap.end())
		{
			m_ProfileHistoricMap.insert( ProfileHistoricSet(name, ProfileTimeList()) );
			historicMapIterator = m_ProfileHistoricMap.find(name);

			if(historicMapIterator == m_ProfileHistoricMap.end())
			{
				ASSERT_MSG(false, "This should not happen");
			}
			else
			{
				historicMapIterator->second.push_back(delta);
			}
		}
		else
		{
			historicMapIterator->second.push_back(delta);
		}
	}
	else
	{
		//If it's not found, Something failed.
		ASSERT_MSG(false, "Tried to end a profiling task, that has not been started.");
	}

	m_WriteToLogCounter++;

	if(m_WriteToLogCounter == 1000)
	{
		WriteToLogFiles();

		m_WriteToLogCounter = 0;
	}
}

void Profiler::WriteToLogFiles()
{
	ProfileTimestamp now = Time::GetCurrentMS();

	auto historicMapIterator = m_ProfileHistoricMap.begin();
	for(historicMapIterator; historicMapIterator != m_ProfileHistoricMap.end(); historicMapIterator++)
	{
		ProfileKey key = historicMapIterator->first;
		ProfileTimeList list = historicMapIterator->second;

		auto logMapIterator = m_ProfileLogMap.find((const char*)key);
		if(logMapIterator == m_ProfileLogMap.end())
		{
			char filestring[255];
			sprintf_s(filestring,"%s%d%s", key, now, ".log");

			//insert
			m_ProfileLogMap.insert( std::make_pair( key, filestring));
			logMapIterator = m_ProfileLogMap.find((const char*)key);
			if(logMapIterator == m_ProfileLogMap.end())
			{
				ASSERT_MSG(false, "This should not happen");
			}
			else
			{
				logMapIterator->second.Write(key);

				auto listIterator = list.begin();
				for(listIterator; listIterator != list.end(); listIterator++)
				{
					logMapIterator->second.Write("%d,", (*listIterator));
				}
			}
		}
		else
		{
			auto listIterator = list.begin();
			for(listIterator; listIterator != list.end(); listIterator++)
			{	
				logMapIterator->second.Write("%d,", (*listIterator));
			}
		}

		historicMapIterator->second.clear();
	}
}