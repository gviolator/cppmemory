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

	const auto p = static_cast<double>(c1) / 100;
	const auto diff = (c2 - c1) / p;

	std::cout << "(" << c1 << ")ms (" << c2 << ")ms, diff:" << diff << "%\n";
}
