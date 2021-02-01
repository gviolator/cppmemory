#pragma once
#include <memory>


struct Interface1
{
	static std::unique_ptr<Interface1> createDefault();

	virtual ~Interface1() = default;

	virtual void func1() = 0;
};
