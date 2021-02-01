#include "pch.h"
#include <cppmem/pagealloc.h>


int main()
{
	PageAllocator pages(600_Mb);

	std::cout << "Before\n";

	for (size_t i = 0; i < 200; ++i)
	{
		pages.alloc(1_Mb);
	}

	std::cout << "After\n";

	return 0;
}
