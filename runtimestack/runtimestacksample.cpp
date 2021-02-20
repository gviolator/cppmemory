#include "pch.h"
#include "tcptable.h"
#include <cppmem/rtstack.h>
#include <cppmem/stopwatch.h>


std::chrono::milliseconds execute()
{
	using String = std::pmr::string;

	const StopWatch sw1;

	for (size_t i = 0; i < 10; ++i)
	{
		rtstack();

		std::pmr::list<String> strings(RtStackGuard::stdMemoryResource());

		for (size_t x = 0; x < 1000; ++x)
		{
			std::basic_stringstream<char, std::char_traits<char>, RtStackStdAllocator<char>> formatter;

			formatter << i << ":LOOOOONG STRING WITH NUMBER (" << x << ")";

			strings.emplace_back(formatter.str());
		}
	}

	return sw1.timePassed();
}



int main()
{
	std::chrono::milliseconds t1;

	{
		rtstack(2_Mb);
		t1 = execute();
	}
	
	const auto t2 = execute();

	StopWatch::printTimeDiff(t1, t2);

	return 0;
}


int main2()
{
	getTcpTableSnapshot([](const TcpEntryHandle* entries, size_t count, void*) noexcept
	{
		for (size_t i = 0; i < count; ++i)
		{
			const TcpTableEntry e(entries[i]);
			std::cout << "local port [" << e.localPort << "] = " << e.state << std::endl;
		}

	}, nullptr);

	return 0;
}
