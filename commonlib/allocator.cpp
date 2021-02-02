#include "pch.h"
#include <cppmem/allocator.h>
#include <cppmem/singletonmemop.h>


class CrtAllocator final : public Allocator
{
public:
	SINGLETON_MEMOP(CrtAllocator)

	void* realloc(void* prevPtr, size_t size, std::optional<size_t> optionalAlignment) noexcept override
	{
		const size_t alignment = optionalAlignment ? *optionalAlignment : sizeof(std::max_align_t);

		CHECK(isPOT(alignment))

		return ::_aligned_realloc(prevPtr, size, alignment);
	}
	/**
	*/
	void free(void* ptr, std::optional<size_t>) noexcept override
	{
		::_aligned_free(ptr);
	}
};

Allocator::Ptr& crtAllocator()
{
	static Allocator::Ptr allocator(new CrtAllocator());
	// static Allocator::Ptr allocator = std::make_shared<CrtAllocator>();

		//
	return allocator;
}
