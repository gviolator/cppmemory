#pragma once
#include "cppmem/diag.h"

#include <new>
#include <type_traits>

template<typename Class_>
struct SingletonMemOp
{


	static void* operator_new(size_t size) noexcept
	{
		decltype(auto) state = getSingletonState();
		CHECK(!state.allocated)
		CHECK(sizeof(Class_) >= size)

		state.allocated = true;
		return &state.storage;
	}

	static void operator_delete(void* ptr, size_t) noexcept
	{
		decltype(auto) state = getSingletonState();
		CHECK(state.allocated)
		CHECK(ptr == &state.storage)

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


#pragma region stdlib helper
template<typename T>
struct SingletonStdAllocator
{
	using value_type = T;

	SingletonStdAllocator() = default;

	template<typename U>
	SingletonStdAllocator(const SingletonStdAllocator<U>& ) noexcept
	{};

	T* allocate(size_t n, const void* hint = 0)
	{
		void* const ptr = SingletonMemOp<T>::operator_new(sizeof(T) * n);

		return reinterpret_cast<T*>(ptr);
	}

	void deallocate(T* ptr, size_t n)
	{
		SingletonMemOp<T>::operator_delete(ptr, sizeof(T) * n);
	}
};
#pragma endregion


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

