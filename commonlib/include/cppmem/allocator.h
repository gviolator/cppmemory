#pragma once
#include "interface.h"
#include "membase.h"

#include <memory>
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


Allocator& crtAllocator();
