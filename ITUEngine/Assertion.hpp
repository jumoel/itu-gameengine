#ifndef ITUENGINE_ASSERTION_H
#define ITUENGINE_ASSERTION_H

#include <iostream>

#if ASSERTIONS_ENABLED
	// Some inline assembly that causes a break into the debugger. This will be different on each target CPU
	#define debugBreak() asm { int 3 }

	#define ASSERT(expr) ASSERT_MSG(expr, "")

	#define ASSERT_MSG(expr, msg) \
		if (expr) { } \
		else \
		{ \
		reportAssertionFailure(#expr, #msg, __FILE__, __LINE__); \
			debugBreak(); \
		}
#else
	#define ASSERT_MSG(expr, msg)	// Evaluates to nothing
	#define ASSERT(expr)			// ... same
#endif

inline void reportAssertionFailure(const char *msg1, const char * msg2, const char* file, int line)
{
	std::cerr << "Assertion Failure: " << msg1 << ", " << msg2 << " at " << file << ", line " << line << std::endl;
}

#endif // ITUENGINE_ASSERTION_H