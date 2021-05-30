#include <iostream>
#include <cassert>

#include "bigint.h"



void Test_1()
{
        BigInt a("98765");
        BigInt b("9876");
        assert(!(a == b));
}

void Test_2()
{
        BigInt a("98765");
        BigInt b("9876");
        assert(a != b);
}

void Test_3()
{
        BigInt a("98765");
        BigInt b("9876");
        assert(!(a < b));
}

void Test_4()
{
        BigInt a("98765");
        BigInt b("9876");
        assert(!(a <= b));
}

void Test_5()
{
        BigInt a("98765");
        BigInt b("9876");
        assert(a > b);
}

void Test_6()
{
        BigInt a("98765");
        BigInt b("9876");
        assert(a >= b);
}


void Test_7()
{
        BigInt a("-98765");
        BigInt b("9876");
        assert(!(a == b));
}

void Test_8()
{
        BigInt a("-98765");
        BigInt b("9876");
        assert(a != b);
}

void Test_9()
{
        BigInt a("-98765");
        BigInt b("9876");
        assert(a < b);

}

void Test_10()
{
        BigInt a("-98765");
        BigInt b("9876");
        assert(a <= b);
}

void Test_11()
{
        BigInt a("-98765");
        BigInt b("9876");
        assert(!(a > b));
}

void Test_12()
{
        BigInt a("-98765");
        BigInt b("9876");
        assert(!(a >= b));
}


void Test_13()
{
        BigInt a("98765");
        BigInt b("-9876");
        assert(!(a == b));

}

void Test_14()
{
        BigInt a("98765");
        BigInt b("-9876");
        assert(a != b);

}

void Test_15()
{
        BigInt a("98765");
        BigInt b("-9876");
        assert(a > b);

}

void Test_16()
{
        BigInt a("98765");
        BigInt b("-9876");
        assert(a >= b);

}

void Test_17()
{
        BigInt a("98765");
        BigInt b("-9876");
        assert(!(a < b));

}

void Test_18()
{
        BigInt a("98765");
        BigInt b("-9876");
        assert(!(a <= b));

}


void Test_19()
{
        BigInt a("98765");
        BigInt b("98765");
        assert(b == a);
}

void Test_20()
{
        BigInt a("98765");
        BigInt b("98765");
        assert(!(b != a));
}

void Test_21()
{
        BigInt a("98765");
        BigInt b("98765");
        assert(!(a > b));
}

void Test_22()
{
        BigInt a("98765");
        BigInt b("98765");
        assert(a >= b);
}

void Test_23()
{
        BigInt a("98765");
        BigInt b("98765");
        assert(!(a < b));
}

void Test_24()
{
        BigInt a("98765");
        BigInt b("98765");
        assert(a <= b);
}


void Test_25()
{
        BigInt a("-98765");
        BigInt b("-98765");
        assert(b == a);
}


void Test_26()
{
        BigInt a("-98765");
        BigInt b("-98765");
        assert(!(b != a));
}

void Test_27()
{
        BigInt a("-98765");
        BigInt b("-98765");
        assert(!(a > b));
}

void Test_28()
{
        BigInt a("-98765");
        BigInt b("-98765");
        assert(a >= b);
}

void Test_29()
{
        BigInt a("-98765");
        BigInt b("-98765");
        assert(!(a < b));
}

void Test_30()
{
        BigInt a("-98765");
        BigInt b("-98765");
        assert(a <= b);
}


void Test_31()
{
        BigInt a;
        assert(a == 0);
}

void Test_32()
{
        BigInt a("98765");
        assert(a == 98765);
}

void Test_33()
{
        BigInt a("-98765");
        assert(a == -98765);
}

void Test_34()
{
        BigInt a(98765);
        assert(a == 98765);
}

void Test_35()
{
        BigInt a(-98765);
        assert(a == -98765);
}

void Test_36()
{
        BigInt a(BigInt(98765));
        assert(a == 98765);
}

void Test_37()
{
        BigInt a(BigInt(98765));
        BigInt b(a);
        assert(b == 98765);
}

void Test_38()
{
        BigInt a("00000098");
        assert(a == 98);
}

void Test_39()
{
        BigInt a("0000000");
        assert(a == 0);
}

void Test_40()
{
        BigInt a("-0000000");
        assert(a == 0);
}

void Test_41()
{
        BigInt a;
        a = 98;
        assert(a == 98);
}

void Test_42()
{
        BigInt a;
        a = "98";
        assert(a == 98);
}

void Test_43()
{
        BigInt a;
        BigInt b;
        a = 98;
        b = a;
        assert(b == 98);
}

void Test_44()
{
        BigInt a;
        a = BigInt(98);
        assert(a == 98);
}

void Test_45()
{
        BigInt a = 21;
        BigInt b = 10;
        assert(a + b == 31);
}

void Test_46()
{
        BigInt a = 21;
        BigInt b = 10;
        assert(a - b == 11);
}

void Test_47()
{
        BigInt a = 21;
        BigInt b = 10;
        assert(b + a == 31);
}

void Test_48()
{
        BigInt a = 21;
        BigInt b = 10;
        assert(b - a == -11);
}

void Test_49()
{
        BigInt a = -10;
        BigInt b = 30;
        assert(a + b == 20);
}

void Test_50()
{
        BigInt a = -10;
        BigInt b = 30;
        assert(a - b == -40);
}

void Test_51()
{
        BigInt a = -10;
        BigInt b = 30;
        assert(b + a == 20);
}

void Test_52()
{
        BigInt a = -10;
        BigInt b = 30;
        assert(b + a == 20);
}

void Test_53()
{
        BigInt a = -10;
        BigInt b = 30;
        assert(b - a == 40);
}


void Test_54()
{
        BigInt a = -87;
        assert(-a == 87);
        assert(-(-a) == -87);

}

void Test_55()
{
        BigInt a = 3000;
        BigInt b = 3000;
        assert(a - b == 0);
}

void Test_56()
{
        BigInt a = 3000;
        BigInt b = 3000;
        assert(a + b == 6000);
}

void Test_57()
{
        BigInt a("56473892093485765748933948");
        BigInt b("893849304984934857849309485");
        assert(a * b == BigInt("50479149197556459529886293691097915538883166674896780"));
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
    Test_12();
    Test_13();
    Test_14();
    Test_15();
    Test_16();
    Test_17();
    Test_18();
    Test_19();
    Test_20();
    Test_21();
    Test_22();
    Test_23();
    Test_24();
    Test_25();
    Test_26();
    Test_27();
    Test_28();
    Test_29();
    Test_30();
    Test_31();
    Test_32();
    Test_33();
    Test_34();
    Test_35();
    Test_36();
    Test_37();
    Test_38();
    Test_39();
    Test_40();
    Test_41();
    Test_42();
    Test_43();
    Test_44();
    Test_45();
    Test_46();
    Test_47();
    Test_48();
    Test_49();
    Test_50();
    Test_51();
    Test_52();
    Test_53();
    Test_54();
    Test_55();
    Test_56();
    Test_57();
    std::cout << "TESTS OK" << std::endl;
    return 0;
}