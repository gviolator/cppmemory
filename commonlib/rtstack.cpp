#include "pch.h"
#include "cppmem/rtstack.h"
#include "cppmem/pagealloc.h"


namespace {

RtStackGuard* currentStack(std::optional<RtStackGuard*> newValue = std::nullopt)
{
	static thread_local RtStackGuard* currentStack__ = nullptr;

	if (newValue)
	{
		RtStackGuard* const prev = currentStack__;
		currentStack__ = *newValue;
		return prev;
	}

	return currentStack__;
}

}


class RtStackAllocator final : public Allocator
{

public:

	RtStackAllocator(const Kilobyte size): m_allocator(size.bytesCount())
	{}

	~RtStackAllocator()
	{
		// std::cout << "max rt size: " << m_allocator.allocatedSize() << std::endl;
	}

	void restore(size_t offset)
	{
		m_offset = offset;
	}

	size_t offset() const
	{
		return m_offset;
	}

private:

	void* realloc(void* prevPtr, size_t size, std::optional<size_t> alignment) noexcept override;

	void free(void* ptr, std::optional<size_t>) noexcept override;


	PageAllocator m_allocator;
	size_t m_offset = 0;
};


void* RtStackAllocator::realloc([[mayb_unused]] void* prevPtr, size_t size, std::optional<size_t> optionalAlignment) noexcept
{
	CHECK(!prevPtr)

	std::byte* topPtr = reinterpret_cast<std::byte*>(m_allocator.base()) + m_offset;

	const size_t alignment = optionalAlignment ? *optionalAlignment : alignof(std::max_align_t);
	CHECK(isPOT(alignment), "Alignment must be power of two")

	const size_t alignedBlockSize = alignedSize(size, alignment);

	// padding = offset from topPtr to make result address aligned.
	const size_t d = reinterpret_cast<ptrdiff_t>(topPtr) % alignment;
	const size_t padding = d == 0 ? 0 : (alignment - d); 

	const size_t allocationSize = alignedBlockSize + padding;

	if (const size_t newOffset = m_offset + allocationSize; newOffset <= m_allocator.allocatedSize())
	{
		m_offset = newOffset;
	}
	else
	{
		topPtr = reinterpret_cast<std::byte*>(m_allocator.alloc(allocationSize));
		CHECK(topPtr, "Runtime dynamic stack is out of memory")
		m_offset = m_allocator.allocatedSize();
	}

	return topPtr + padding;
}

void RtStackAllocator::free([[maybe_unused]] void* ptr, [[maybe_unused]] std::optional<size_t>) noexcept
{ // DEBUG: need to check that ptr belongs to the current runtime stack allocation range.
}

//-----------------------------------------------------------------------------
RtStackGuard::RtStackGuard(): m_prev(currentStack(this))
{
	if (m_prev && m_prev->m_allocator)
	{
		m_allocator = m_prev->m_allocator;
		m_top = dynamic_cast<const RtStackAllocator*>(m_allocator.get())->offset();
	}
}

RtStackGuard::RtStackGuard(Kilobyte size)
	: m_prev(currentStack(this))
	, m_allocator(std::make_shared<RtStackAllocator>(size))
{
}

RtStackGuard::~RtStackGuard()
{
	if (m_allocator)
	{
		dynamic_cast<RtStackAllocator*>(m_allocator.get())->restore(m_top);
	}

	CHECK(currentStack(m_prev) == this);
}


Allocator::Ptr& RtStackGuard::allocator()
{
	auto current = currentStack();
	Allocator::Ptr& allocPtr = (current && current->m_allocator) ? current->m_allocator : crtAllocator();
	CHECK(allocPtr)
	return allocPtr;
}


std::pmr::memory_resource* RtStackGuard::stdMemoryResource()
{
	static MemoryResource<RtStackAllocatorProvider> memResource;

	return &memResource;
}

//-----------------------------------------------------------------------------

//Allocator& rtStack()
//{
//	return RtStackGuard::allocator();
//}

//std::pmr::memory_resource* rtStackMemoryResource()
//{
//	static AllocatorMemoryResource memRes__([]() -> Allocator*
//	{
//		return &RtStackGuard::allocator();
//	});
//
//	return &memRes__;
//}

//RUNTIME_EXPORT Allocator::Ptr rtStackAllocator();
//

