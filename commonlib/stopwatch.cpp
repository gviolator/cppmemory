#include "pch.h"
#include <cppmem/stopwatch.h>

#include <chrono>


	using namespace std::chrono;


StopWatch::StopWatch(): m_timePoint(system_clock::now())
{}

milliseconds StopWatch::timePassed() const
{
	return duration_cast<milliseconds>(system_clock::now() - m_timePoint);
}

size_t StopWatch::ms() const
{
	return this->timePassed().count();
}


void StopWatch::printTimePassed(const StopWatch& sw)
{
	std::cout << sw.timePassed().count() << " ms\n";
}

void StopWatch::printTimeDiff(const std::chrono::milliseconds& base, const std::chrono::milliseconds& comparer)
{
	const size_t c1 = base.count();
	const size_t c2 = comparer.count();

	double diff = 0;
	const char* mark = "+";
	if (c2 > c1)
	{
		const auto p = static_cast<double>(c1) / 100;
		diff = (c2 - c1) / p;
	}
	else
	{
		mark = "-";
		const auto p = static_cast<double>(c2) / 100;
		diff = (c1 - c2) / p;
	}


	std::cout << "(" << c1 << ")ms (" << c2 << ")ms, diff:" << mark << diff << "%\n";
}
