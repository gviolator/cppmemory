#pragma once
#include <cppmem/allocator.h>
#include <cppmem/preprocessor.h>

class RtStackGuard
{
public:

	static Allocator::Ptr& allocator();

	static std::pmr::memory_resource* stdMemoryResource();


	RtStackGuard();

	RtStackGuard(Kilobyte size);

	~RtStackGuard();

	RtStackGuard(const RtStackGuard&) = delete;

	RtStackGuard& operator = (const RtStackGuard&) = delete;


private:

	RtStackGuard* const m_prev = nullptr;
	Allocator::Ptr m_allocator;
	size_t m_top = 0;
};


struct RtStackAllocatorProvider
{
	static Allocator::Ptr& allocator()
	{
		return RtStackGuard::allocator();
	}
};


template<typename T>
using RtStackStdAllocator = StdAllocator<T, RtStackAllocatorProvider>;





#define rtstack(...) const RtStackGuard ANONYMOUS_VARIABLE_NAME(rtStack__) {__VA_ARGS__}
