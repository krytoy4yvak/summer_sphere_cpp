#include <cassert>
#include <iostream>
#include <sstream>
#include "bigint.h"




void Test_1()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "10";
	BigInt result = bint_1 + bint_2;
	assert(result == "1");
}

void Test_2()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "10";
	BigInt result = bint_1 - bint_2;
	assert(result == "-52");
}

void Test_3()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "10";
	bool result = bint_1 < bint_2;
	assert(result == true);
}

void Test_4()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "10";
	bool result = bint_1 > bint_2;
	assert(result == false);
}

void Test_5()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "10";
	bool result = bint_1 <= bint_2;
	assert(result == true);
}

void Test_6()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "-42";
	bool result = bint_1 <= bint_2;
	assert(result == true);
}

void Test_7()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "10";
	bool result = bint_1 >= bint_2;
	assert(result == false);
}

void Test_8()
{
	BigInt bint_1 = "-42";
	BigInt bint_2 = "-42";
	bool result = bint_1 >= bint_2;
	assert(result == true);
}

void Test_9()
{
	BigInt bint_1 = "-42";
	BigInt result = -bint_1;
	assert(result == "42");
}

void Test_10()
{
	std::stringstream stream;
	BigInt bint_1 = "-42";
	std::string result = "0";
	stream << bint_1;
	stream >> result;
	assert(result == "-42");
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
	Test_8();
	Test_9();
	Test_10();
	

    std::cout << "Success!\n";

    return 0;
}
