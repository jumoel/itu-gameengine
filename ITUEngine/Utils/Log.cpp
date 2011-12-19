#include <Utils/Log.hpp>
#include <stdio.h>


Log::Log(char* filename) 
{
	m_stream.open(filename);
}

Log::~Log()
{
	m_stream.close();
}

void Log::Write(const char* logline, ...)
{
	va_list argList;
	char cbuffer[1024];
	va_start(argList, logline);
	vsnprintf(cbuffer, 1024, logline, argList);
	va_end(argList);
	m_stream << cbuffer << std::endl;
}