#ifndef ITUENGINE_LOG_H
#define ITUENGINE_LOG_H

#include <fstream>
#include <iostream>
#include <stdarg.h>

//Simple logger class, for writing strings into a file.

class Log
{
public:
	Log(char* filename);
	~Log();

	void Write(const char* logline, ...);

private:
	std::ofstream m_stream;
};

#endif //ITUENGINE_LOG_H
