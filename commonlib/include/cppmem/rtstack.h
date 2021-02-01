#pragma once

#include <cppmem/allocator.h>


class RtStackGuard
{
public:

	static Allocator& allocator();


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


// Allocator& rtStack();
