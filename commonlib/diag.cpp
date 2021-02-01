#include "pch.h"
#include "cppmem/diag.h"


void raiseFailure(const char* expression, const char* message)
{
	MessageBoxA(nullptr, expression, "FAILURE", MB_OK | MB_ICONERROR);

	if (IsDebuggerPresent() == TRUE)
	{
		OutputDebugStringA("ASSERT FALURE:");
		OutputDebugStringA(message);
		OutputDebugStringA("\n");
		DebugBreak();
	}

	std::exit(-1);
}
