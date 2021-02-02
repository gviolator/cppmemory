#pragma once
#include "interface.h"
#include "membase.h"

#include <memory>
#include <memory_resource>
#include <optional>


struct ABSTRACT_TYPE Allocator
{
	using Ptr = std::shared_ptr<Allocator>;


	virtual ~Allocator()
	{}

	virtual void* realloc(void* ptr, size_t size, std::optional<size_t> alignment = std::nullopt) noexcept = 0;

	virtual void free(void* ptr, std::optional<size_t> size) noexcept = 0;


	inline void* alloc(size_t size, std::optional<size_t> alignment = std::nullopt) noexcept
	{
		return this->realloc(nullptr, size, alignment);
	}
};



Allocator::Ptr& crtAllocator();

#pragma region stdlib interoperability

template<typename Expr, typename T>
concept AssignableTo = std::is_assignable_v<T, Expr>;


template<typename T>
concept AllocatorProvider = requires
{
	{T::allocator()} -> AssignableTo<Allocator::Ptr>;
};


/**
* making std allocator
*/
template<typename T, AllocatorProvider AllocProvider>
class StdAllocator
{
public:
	using Provider = AllocProvider;

	using value_type = T;
	using propagate_on_container_move_assignment = std::true_type;

	StdAllocator() noexcept = default;

	template<typename U, typename ... A>
	StdAllocator(const StdAllocator<U, A...>&) noexcept
	{}

	[[nodiscard]] constexpr T* allocate(size_t n)
	{
		void* const ptr = Provider::allocator()->realloc(nullptr, sizeof(T) * n, alignof(T));
		return reinterpret_cast<T*>(ptr);
	}

	void deallocate(T* p, std::size_t n)
	{
		const size_t size = sizeof(T) * n;
		Provider::allocator()->free(reinterpret_cast<void*>(p), size);
	}
};


/**
* making std memory_resource
*/
template<AllocatorProvider AllocProvider>
class MemoryResource : public std::pmr::memory_resource
{
public:
	using Provider = AllocProvider;

private:

	void* do_allocate(size_t size, size_t align) override
	{
		return Provider::allocator()->alloc(size, align);
	}

	void do_deallocate(void* ptr, size_t size, [[maybe_unused]] size_t align) override
	{
		Provider::allocator()->free(ptr, size);
	}

	bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override
	{
		return &static_cast<const std::pmr::memory_resource&>(*this) == &other;
	}
};

#pragma endregion

