#include <iostream>
#include <cassert>
#include <sstream>

#include "serializer.h"

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    Data(uint64_t a, bool b, uint64_t c)
        : a(a)
        , b(b)
        , c(c)
    {
    }

    template <class S>
    Error serialize(S& serializer) const
    {
        return serializer(a, b, c);
    }
    template <class D>
    Error deserialize(D& deserializer)
    {
        Error error = Error::NoError;
        if ((error = deserializer.load(a)) != Error::NoError) {
            return error;
        }
        if ((error = deserializer.load(b)) != Error::NoError) {
            return error;
        }
        return deserializer.load(c);
    }
};


void Test_1()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);


}

void Test_2()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);

    auto s = std::stringstream("");
    Deserializer d(s);
    assert(d.load(y) == Error::CorruptedArchive);


}

void Test_3()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);

    auto s = std::stringstream("1 text 3");
    Deserializer d(s);
    assert (d.load(y) == Error::CorruptedArchive);


}

void Test_4()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);

    auto s = std::stringstream("9999 1");
    Deserializer d(s);
    assert (d.load(y) == Error::CorruptedArchive);


}

void Test_5()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);

    auto s = std::stringstream("654321 true 7658");
    Deserializer d(s);
    assert (d.load(y) == Error::NoError);

    assert(y.a == 654321);
    assert(y.b == true);
    assert(y.c == 7658);


}

void Test_6()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);
    auto s = std::stringstream("-654321 true 7658");
    Deserializer d(s);
    assert (d.load(y) == Error::CorruptedArchive);
}


void Test_7()
{
    Data x(956, true, 865);
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.save(x);

    Data y { 4321, false, 7656 };
    Deserializer deserializer(stream);
    auto s = std::stringstream("987654321234567898765432 false 876");
    Deserializer d(s);
    assert (d.load(y) == Error::CorruptedArchive);
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