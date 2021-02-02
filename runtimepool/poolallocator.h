#pragma once
#include <cppmem/allocator.h>


struct PoolAllocatorConfig
{
	static constexpr size_t DefaultGranularity = 64;
	static constexpr size_t DefaultBlockMinSize = 32;
	static constexpr size_t DefaultBlockMaxSize = 1024;

	const bool concurrent = true;
	const size_t granularity = DefaultGranularity;
	const size_t blockMinSize = DefaultBlockMinSize;
	const size_t blockMaxSize = DefaultBlockMaxSize;
};


Allocator::Ptr createPoolAllocator(PoolAllocatorConfig = {});
