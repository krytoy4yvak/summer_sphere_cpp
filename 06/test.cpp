#include <iostream>
#include <string>
#include <cassert>

#include "format.h"

#define check_err(str, ...) {bool err = false; try {format(str, __VA_ARGS__);} catch(Custom_Exception) {err = true;} assert(err);}




void Test_1()
{
    assert(format("Smile:)", 1, 2) == "Smile:)");
}

void Test_2()
{
    assert(format("{1} November {1} year", 10, 2021) == ("10 November 2021 year"));
}

void Test_3()
{
    assert(format("Help {0} interested {1} this {2} understand your project by {3}", "people", "in", "repository", "adding") == "Help people interested in this repository understand your project by adding");
}

void Test_4()
{
    assert(format("{2}{4}{1}{0}", false, true, 9, 67, "123") == ("912310"));
}

void Test_5()
{
    assert(format("user02076@gmail.com") == ("user02076@gmail.com"));
}

void Test_6()
{
    assert(format("{0}", "{0}") == ("{0}"));
}

void Test_7()
{
    check_err("one two{4r}", 5);
}

void Test_8()
{
    check_err("Something is now{}", 0);
}

void Test_9()
{
    check_err("Teeth}", 2);
}

void Test_10()
{
    check_err("{0}{2345}{1}", 1, "hustle");
}


void Test_11()
{
    check_err("{{0}}", 1);
}

void Test_12()
{
    check_err("This is my toy, {0", "bro");
}

int main()
{
    Test_1();
    //Test_2();
    Test_3();
    Test_4();
    Test_5();
    Test_6();
    Test_7();
    Test_8();
    Test_9();
    Test_10();
    Test_11();
    Test_12();

    std::cout << "TESTS OK" << std::endl;
    return 0;
}