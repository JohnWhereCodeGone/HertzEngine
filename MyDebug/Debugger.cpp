#include "Debugger.h"


//awful, doesn't work as intended.

void Debugger::BreakPoint()
{
#if defined(_MSC_VER)
	__debugbreak();
#elif defined(__GNUC__) || defined(__clang__)
	__builtin_trap();
#else
	((void)0); //common way of making macros invalid while remaining syntax-correct.
#endif
}
