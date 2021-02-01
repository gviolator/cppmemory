#include "pch.h"
#include "myclass.h"



int main()
{
	Interface1* const c = new MyClass();

	c->func1();

	delete c;


	return 0;
}
