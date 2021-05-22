#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include "format.h"


void Test_1()
{
	assert(format("")=="");
}

void Test_2()
{
	assert(format("1")=="1");
}

void Test_3()
{
	assert(format("{1}", 1, 2)=="2");
}

void Test_4()
{
	assert(format("{0}{0}", "a")=="aa");
}

struct Test
{
};

std::ostream& operator<<(std::ostream& out, const Test&)
{
    out << "test";
    return out;
}

const Test test;

void Test_5()
{
	assert(format("{0}", Test()) == "test");
}

void Test_6()
{
	assert(format("{0}", const_cast<Test&>(test)) == "test");
}

void Test_7()
{
	assert(format("{0}", test) == "test");
}

int main()

{
	Test_1();
	Test_2();
	Test_3();
	Test_4();
	Test_5();
	Test_6();
	Test_7();
	
    	std::cout << "Success!\n";

    	return 0;
}
