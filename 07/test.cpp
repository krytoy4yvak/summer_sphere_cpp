#include <iostream>
#include <vector>
#include <cassert>

#include "vector.h"

template<typename T1, typename T2>
void assert_equals(const T1& lhs, const T2& rhs) {
    assert (lhs.size() == rhs.size());

    for (size_t i = 0; i < lhs.size(); ++i) {
        assert(lhs[i] == rhs[i]);
    }
}




void Test_1()
{
        Vector<int> my_vec = {8, 6, 8};
        std::vector<int> vec = {8, 6, 8};
        assert(!my_vec.empty());
        assert_equals(my_vec, vec);

}

void Test_2()
{
        Vector<int> my_vec = {8, 6, 8};
        std::vector<int> vec = {8, 6, 8};
        my_vec.pop_back(); vec.pop_back();
        my_vec.push_back(4); vec.push_back(4);
        assert_equals(my_vec, vec);

}

void Test_3()
{
        Vector<int> my_vec = {8, 6, 8};
        std::vector<int> vec = {8, 6, 8};
        my_vec.clear(); vec.clear();
        assert(my_vec.size() == vec.size());
        assert(my_vec.empty());

}

void Test_4()
{
        Vector<int> my_vec = {8, 6, 8};
        std::vector<int> vec = {8, 6, 8};
        my_vec.push_back(1); vec.push_back(1);
        my_vec.push_back(1); vec.push_back(1);
        my_vec.emplace_back(1); vec.emplace_back(1);
        assert(my_vec.size() == vec.size());

}

void Test_5()
{
        Vector<int> my_vec = {8, 6, 8};
        std::vector<int> vec = {8, 6, 8};
        my_vec.push_back(1); vec.push_back(1);
        my_vec.push_back(1); vec.push_back(1);
        my_vec.emplace_back(1); vec.emplace_back(1);
        assert(my_vec.size() == vec.size());

}

void Test_6()
{
        Vector<int> my_vec = {8, 6, 8};
        std::vector<int> vec = {8, 6, 8};

        my_vec.clear(); vec.clear();

        my_vec.push_back(1); vec.push_back(1);
        my_vec.push_back(1); vec.push_back(1);
        my_vec.emplace_back(1); vec.emplace_back(1);

        {
            int counter = 0;
            for (auto it = my_vec.begin(); it != my_vec.end(); ++it, ++counter) {
                assert(*it == 1);
            }
            assert(counter == 3);
        }

}

void Test_7()
{
        Vector<int> vec1 = {8, 6, 8};
        Vector<int> vec2 = {7, 7, 7};
        assert_equals(vec1, Vector<int>{8, 6, 8});
        vec1 = vec2;
        assert_equals(vec1, vec2);

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
    std::cout << "TESTS OK" << std::endl;
    return 0;
}