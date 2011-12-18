#pragma once
class Profiler
{
public:
	Profiler();
	~Profiler();

	void Begin(const char* name);
	void End(const char* name);

	void WriteToLogFile();

private:


	//List of string, timestamp, level?
};

