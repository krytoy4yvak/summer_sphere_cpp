#include <iostream>
#include <cassert>

#include "allocator.h"


void Test_1()
{
	Allocator all;
        assert(all.alloc(1) == nullptr);
        all.reset();
        assert(all.alloc(1) == nullptr);

}

void Test_2()
{
	Allocator all;
        all.makeAllocator(100);

        char* ptr1 = all.alloc(50);
        assert(ptr1 != nullptr);

}

void Test_3()
{
        Allocator all;
        all.makeAllocator(100);

        char* ptr1 = all.alloc(50);
        assert(ptr1 != nullptr);

        char* ptr2 = all.alloc(50);
        assert(ptr2 != nullptr);

}

void Test_4()
{
        Allocator all;
        all.makeAllocator(100);

        char* ptr1 = all.alloc(50);
        assert(ptr1 != nullptr);

        char* ptr2 = all.alloc(50);
        assert(ptr2 != nullptr);

        char* ptr3 = all.alloc(2);
        assert(ptr3 == nullptr);

}

void Test_5()
{
        Allocator all;
        all.makeAllocator(100);

        char* ptr1 = all.alloc(50);
        assert(ptr1 != nullptr);

        char* ptr2 = all.alloc(50);
        assert(ptr2 != nullptr);

        char* ptr3 = all.alloc(2);
        assert(ptr3 == nullptr);

        all.reset();
        ptr3 = all.alloc(10);
        assert(ptr1 == ptr3);

}


void Test_6() 
{
	Allocator all;
        all.makeAllocator(26);
        char* ptr = all.alloc(26);
        for (char c = 'a'; c <= 'z'; ++c) {
            ptr[c - 'a'] = c;
        }
        all.reset();
        ptr = all.alloc(26);
        for (char c = 'a'; c <= 'z'; ++c) {
            assert(ptr[c - 'a'] == c);
        }

}

void Test_7() 
{
	Allocator all;
	all.reset();
	char* ptr1 = all.alloc(100);
	char* ptr2 = all.alloc(1);
	assert (ptr2 != nullptr);
	ptr1 = all.alloc(101);
	assert(ptr1 != nullptr);

}

int main()
{

	Test_1();
	Test_2();
	Test_3();
	Test_4();
	Test_5();
	Test_6()	;
	Test_7();

	std::cout << "Success!\n";

	return 0;
}