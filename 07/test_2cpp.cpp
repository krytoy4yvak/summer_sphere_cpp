#include <iomanip>
#include <iostream>
#include <vector>

#include "vector.h"


void Test_1()
{
	vector<int> vec = {1,2,3};
	//vec.resize(6, 42);
	//vector<int> answer = {1,2,3,42,42,42};
	//assert(vec == answer);
}

int main()

{
	Test_1();
	
    	std::cout << "Success!\n";

    	return 0;
}




