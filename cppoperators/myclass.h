#pragma once
#include "interface1.h"

class MyClass : public Interface1
{
public:
	static void* operator new (size_t);

	static void operator delete (void*, size_t);

	MyClass();

	~MyClass();

	void func1() override;

private:


};
