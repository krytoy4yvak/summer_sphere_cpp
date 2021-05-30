#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cassert>

#include "parser.h"

// Make some tests



void Test_1()
{
	TokenParser tp;
	bool start, finish, digit, string;
	start = false;
	finish = false;
	digit = false;
	string = false;

        tp.SetStartCallback([&start] () { start = true; });
        tp.SetDigitTokenCallback([&digit] (int num) { digit = true; });
        tp.SetStringTokenCallback([&string] (const std::string& str) { string = true; });

        tp.ParseString("");
        assert(start && !finish);
        assert(!(digit || string));

}



void Test_2()
{
	TokenParser tp;
	bool start, finish, digit, string;
	start = false;
	finish = false;
	digit = false;
	string = false;

        tp.SetStartCallback([&start] () { start = true; });
        tp.SetDigitTokenCallback([&digit] (int num) { digit = true; });
        tp.SetStringTokenCallback([&string] (const std::string& str) { string = true; });
        tp.SetFinishCallback([&finish] () { finish = true; });

        tp.ParseString("");
        assert(start && finish);
        assert(!(digit || string));

}



void Test_3()
{
	TokenParser tp;
	bool start, finish, digit, string;
	start = false;
	finish = false;
	digit = false;
	string = false;

        tp.SetStartCallback([&start] () { start = true; });
        tp.SetDigitTokenCallback([&digit] (int num) { digit = true; });
        tp.SetStringTokenCallback([&string] (const std::string& str) { string = true; });
        tp.SetFinishCallback([&finish] () { finish = true; });

	tp.ParseString("MyTest3");
	assert(string && !digit);


}


void Test_4()
{
	TokenParser tp;
	bool start, finish, digit, string;
	start = false;
	finish = false;
	digit = false;
	string = false;

        tp.SetStartCallback([&start] () { start = true; });
        tp.SetDigitTokenCallback([&digit] (int num) { digit = true; });
        tp.SetStringTokenCallback([&string] (const std::string& str) { string = true; });
        tp.SetFinishCallback([&finish] () { finish = true; });
        tp.ParseString("Some word");

        tp.ParseString("637573");
        assert(string && digit);


}

void Test_5()
{
	TokenParser tp;
	int num = 0;
	std::string str = "";
	tp.SetDigitTokenCallback([&num] (int value) { num += value; });
	tp.SetStringTokenCallback([&str] (const std::string& string) { str += string; });
	tp.ParseString("765 Test, 235  cases ");
	assert(num == 1000);
	assert(str == "Test,cases");



}


void Test_6()
{
        TokenParser tp;
        int num;

        tp.SetDigitTokenCallback([&num] (int value) { num = 987; });
        tp.ParseString("9876543");
        assert(num == 987);
}

void Test_7()
{
        TokenParser tp;
        int num;

        tp.SetDigitTokenCallback([&num] (int value) { num = -987; });
        tp.ParseString("9876543");
        assert(num == -987);
}


void Test_8()
{
	TokenParser tp;
	std::string str;
	tp.SetStringTokenCallback([&str] (const std::string& string) { str = "Not clear it!"; });
	tp.ParseString("jipehsogfigew");
	assert(str == "Not clear it!");
}


void Test_9()
{
        TokenParser tp;
        std::string str;
        tp.SetStringTokenCallback([&str] (const std::string& string) { str = "Not clear it!"; });
        tp.ParseString("jipehsogfigew");
        tp.SetStringTokenCallback([&str] (const std::string& string) { str = "It`s a trap!"; });
        tp.ParseString("jipehsogfigew");
        assert(str == "It`s a trap!");

}



void Test_10()
{
        TokenParser tp;
        int digitCounter;
        int stringCounter;

        tp.SetStartCallback([&digitCounter, &stringCounter] () { digitCounter = stringCounter = 0; });
        tp.SetDigitTokenCallback([&digitCounter] (int value) { ++digitCounter; });
        tp.SetStringTokenCallback([&stringCounter] (const std::string& str) { ++stringCounter; });

        tp.ParseString("It is the set of 25 error type and 654 minor errors ");
        assert(digitCounter == 2);
        assert(stringCounter == 10);


}


void Test_11()
{
        TokenParser tp;
        int digitCounter;
        int stringCounter;

        tp.SetStartCallback([&digitCounter, &stringCounter] () { digitCounter = stringCounter = 0; });
        tp.SetDigitTokenCallback([&digitCounter] (int value) { ++digitCounter; });
        tp.SetStringTokenCallback([&stringCounter] (const std::string& str) { ++stringCounter; });


        tp.ParseString(
            "Thus, it does not rely on the corruption model probabilities.\n"
            "The Online method assigns tags on-the-fly to each sentence independently and hence runs in O(N)." );
        assert(digitCounter == 0);
        assert(stringCounter == 25);


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
	Test_11();
    
    std::cout << "TESTS OK" << std::endl;
    return 0;
}