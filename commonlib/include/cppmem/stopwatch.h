#pragma once
#include <chrono>

class StopWatch
{
public:

	static void printTimePassed(const StopWatch&);

	static void printTimeDiff(const std::chrono::milliseconds&, const std::chrono::milliseconds&);


	StopWatch();

	std::chrono::milliseconds timePassed() const;

	size_t ms() const;

private:

	const std::chrono::system_clock::time_point m_timePoint;
};

