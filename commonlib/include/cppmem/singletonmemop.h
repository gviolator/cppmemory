#pragma once
#include "cppmem/diag.h"

#include <new>
#include <type_traits>

template<typename Class_>
struct SingletonMemOp
{
	static void* operator_new(size_t) noexcept
	{
		decltype(auto) state = getSingletonState();
		CHECK(!state.allocated)

		state.allocated = true;
		return &state.storage;
	}

	static void operator_delete(void* ptr, size_t) noexcept
	{
		decltype(auto) state = getSingletonState();
		CHECK(state.allocated)

		state.allocated = false;
	}

private:

	static decltype(auto) getSingletonState() noexcept
	{
		static struct
		{
			// std::aligned_storage_t<sizeof(Class_)> storage;
			alignas(Class_) std::byte storage[sizeof(Class_)];
			bool allocated = false;
		}
		state {};

		return (state);
	};
};

#define SINGLETON_MEMOP(ClassName)\
public:\
	static void* operator new (size_t size) \
	{\
		return SingletonMemOp<ClassName>::operator_new(size);\
	}\
	\
	static void operator delete (void* ptr, size_t size) \
	{\
		SingletonMemOp<ClassName>::operator_delete(ptr, size);\
	}\

