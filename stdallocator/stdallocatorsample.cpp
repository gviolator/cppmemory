#include "pch.h"
#include <cppmem/allocator.h>

#include <string>
#include <string_view>
#include <memory_resource>

struct Provider1
{
	inline static Allocator::Ptr& allocator()
	{
		return crtAllocator();
	}
};


struct Provider2
{
	inline static Allocator::Ptr& allocator()
	{
		return crtAllocator();
	}
};

template<typename T>
using Allocator1 = StdAllocator<T, Provider1>;

template<typename T>
using Allocator2 = StdAllocator<T, Provider2>;

int main()
{
	using String1 = std::basic_string<char, std::char_traits<char>, Allocator1<char>>;
	using String2 = std::basic_string<char, std::char_traits<char>, Allocator2<char>>;

	String1 str1 = "string1";
	String2 str2 = str1;

	//if (str1 == std::string_view{str2})
	//{

	//}



	return 0;
}

