#include "pch.h"
#include "myclass.h"



void* MyClass::operator new (size_t size, std::align_val_t)
{
	std::cout << "Request to allocate: (" << size << ") bytes\n";
	return _aligned_malloc(size, alignof(MyClass));
}

void MyClass::operator delete (void* ptr, size_t)
{
	std::cout << "Free\n";
	_aligned_free(ptr);
}

MyClass::MyClass()
{}

MyClass::~MyClass()
{}

void MyClass::func1()
{
	std::cout << "MyClass::func1()\n";
}

//-----------------------------------------------------------------------------
std::unique_ptr<Interface1> Interface1::createDefault()
{
	return std::make_unique<MyClass>();
}
