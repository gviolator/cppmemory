#include "pch.h"

#include "poolallocator.h"
#include <cppmem/stopwatch.h>


std::chrono::milliseconds execute(Allocator::Ptr allocator)
{
	const StopWatch sw1;

	constexpr size_t Repeats = 500;

	const std::vector<size_t> allocationSizes({ 64, 128, 256, 512 });
	// const std::vector<size_t> allocationSizes({512});

	const auto t1 = std::chrono::system_clock::now();

	using Ptr = void*;
	std::array<Ptr, 5000> pointers;
	size_t ptri = 0;

	for (size_t z = 0; z < Repeats; ++z)
	{

		ptri = 0;

		for (size_t i = 0; i < 500; ++i)
		{
			for (size_t size : allocationSizes)
			{
				pointers[ptri++] = allocator->alloc(size);
			}
		}

		for (size_t j = 0; j < ptri; ++j)
		{
			allocator->free(pointers[j], std::nullopt);
		}
	}

	// std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t1).count() << " ms\n";
	return sw1.timePassed();
}


int main()
{
	const Allocator::Ptr pool1 = createPoolAllocator({ .concurrent = true });
	const Allocator::Ptr pool2 = createPoolAllocator({ .concurrent = false });
	const Allocator::Ptr crt = crtAllocator();


	const std::chrono::milliseconds t1 = execute(pool1);
	const std::chrono::milliseconds t2 = execute(pool2);
	const std::chrono::milliseconds t3 = execute(crt);

	std::cout << "Pool (concurrent) vs CRT:\n";
	StopWatch::printTimeDiff(t1, t3);

	std::cout << "\nPool (non-concurrent) vs CRT:\n";
	StopWatch::printTimeDiff(t2, t3);

	std::cout << "\nPool (non-concurrent) vs Pool (concurrent):\n";
	StopWatch::printTimeDiff(t2, t1);
	return 0;
}
