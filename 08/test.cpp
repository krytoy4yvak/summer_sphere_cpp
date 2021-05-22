 #include "threadpool.hpp"
 #include <iostream>
 #include <vector>
 #include <sstream>


void Test_1()
{
	ThreadPool pool(8);
	int a = 42;
	auto task1 = [a](int c) { return a*c; };
	auto result = pool.exec(task1,2);
	assert(result.get() == 84);
}


void Test_2()
{
	ThreadPool pool(8);
	int a = 42;
	int b = -10;
	auto task2 = [a, b]() { return a + b; };            
	auto result = pool.exec(task2);
	assert(result.get() == 32);
}

int main()

{
	Test_1();
	Test_2();
	

    std::cout << "Success!\n";

    return 0;
}