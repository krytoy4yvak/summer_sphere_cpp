#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include "matrix.h"

void pull_my_matrix(Matrix &matr)
{
    for (size_t i = 0; i < matr.getRows(); ++i)
    {
        for (size_t j = 0; j < matr.getColumns(); ++j)
        {
            matr[i][j] = i + j;
        }
    }
}

void pulling_my_matrix(Matrix &matr, int value)
{
    for (size_t i = 0; i < matr.getRows(); ++i)
    {
        for (size_t j = 0; j < matr.getColumns(); ++j)
        {
            matr[i][j] = value;
        }
    }
}

// Some tests for Matrix class


void Test_1()
{
	Matrix matr(2, 2);
	bool res = false;
	try
	{
	   matr[0][2] = 5;
	}
	catch (const std::out_of_range &e)
	{
	   res = true;
	}
	assert(res==true);

}

void Test_2()
{
	Matrix matr(2, 2);
	bool res = false;
	try
	{
	    matr[10][1] = 5;
	}
	catch (const std::out_of_range &e)
	{
	   res = true;
	}
	assert(res==true);

}

void Test_3()
{
	Matrix matr(2, 2);
	bool res = false;
	try
	{
	    matr[1][1] = 5;
	}
	catch (const std::out_of_range &e)
	{
	   res = true;
	}
	assert(res==false);

}

void Test_4()
{
	Matrix matrix1(2, 3);
	Matrix matrix2(2, 2);
	bool res = false;
	try
	{
	    matrix1 + matrix2;
	}
	catch (const std::logic_error &e)
	{
	   res = true;
	}
	assert(res==true);

}

void Test_5()
{
	Matrix matrix(123, 321);
	assert((matrix.getRows() == 123) && (matrix.getColumns() == 321));

}

void Test_6()
{
	Matrix matrix(2,2);
	matrix[0][0] = 1;
	matrix[0][1] = 2;
	matrix[1][0] = 3;
	matrix[1][1] = 4;

	assert(matrix[0][0] == 1);
	assert(matrix[0][1] == 2);
	assert(matrix[1][0] == 3);
	assert(matrix[1][1] == 4);

}


void Test_7()
{
        Matrix matr1(100, 100);
        Matrix matr2(100, 100);
        pull_my_matrix(matr1);
        pull_my_matrix(matr2);
        assert(matr1 == matr2);
        matr1[40][50] = 45;
        assert(matr1 != matr2);
        matr2[40][50] = 45;
        assert(matr1 == matr2);

}

void Test_8()
{
        Matrix matr1(5, 5);
        Matrix matr2(5, 5);
        pulling_my_matrix(matr1, 7);
        pulling_my_matrix(matr2, 21);
        matr1 *= 3;
        assert(matr1 == matr2);

}


void Test_9()
{
        Matrix matr1(5, 5);
        Matrix matr2(5, 5);
        Matrix matr3(5, 5);

        pulling_my_matrix(matr1, 10);
        pulling_my_matrix(matr2, 15);
        pulling_my_matrix(matr3, 25);
        assert(matr3 == matr1 + matr2);

        matr2 *= -1;
        assert(matr1 == matr3 + matr2);

}


void Test_10()
{
	Matrix matr(1, 1);
	matr[0][0] = -242;
	assert(matr[0][0] == -242);
	

}

void Test_11()
{
	Matrix matr(1, 1);
	assert((matr.getRows() == 1) && (matr.getColumns() == 1));
	

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


    std::cout << "TESTS OK";
    return 0;
}