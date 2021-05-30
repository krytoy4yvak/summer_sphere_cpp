#include "bigint.h"

#include <stdlib.h>

BigInt::BigInt()
        : buf(1)
        , length(1)
        , range_v(1)
{
    values = static_cast<char*>(malloc(1 * sizeof(char)));
    values[0] = 0;
}

BigInt::BigInt(const BigInt& other)
        : buf(other.buf)
        , length(other.length)
        , range_v(other.range_v)
{
    values = static_cast<char*>(malloc(length * sizeof(char)));
    for (size_t i = 0; i < range_v; ++i) 
    {
        values[i] = other.values[i];
    }
}

BigInt::BigInt(BigInt&& other)
        : values(other.values)
        , buf(other.buf)
        , length(other.length)
        , range_v(other.range_v)
{
    other.values = nullptr;
}

BigInt::BigInt(int value)
        : buf(value >= 0 ? 1 : -1)
        , range_v(1)
        , length(1)
{
    init_int(value);
}

BigInt::BigInt(const std::string& str)
{
    init_string(str);
}


BigInt::~BigInt()
{
    if (values != nullptr) {
        free(values);
    }
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (&other == this) {
        return *this;
    }
    buf = other.buf;
    length = other.length;
    range_v = other.range_v;
    char* newvalues = static_cast<char*>(malloc(length * sizeof(char)));
    for (size_t i = 0; i < range_v; ++i) {
        newvalues[i] = other.values[i];
    }
    if (values != nullptr) {
        free(values);
    }
    values = newvalues;
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other)
{
    buf = other.buf;
    length = other.length;
    range_v = other.range_v;
    if (values != nullptr) {
        free(values);
    }
    values = other.values;
    other.values = nullptr;
    return *this;
}

BigInt& BigInt::operator=(int value)
{
    buf = (value >= 0 ? 1 : -1);
    range_v = 1;
    length = 1;
    init_int(value);
    return *this;
}

BigInt& BigInt::operator=(const std::string& str)
{
    init_string(str);
    return *this;
}

BigInt BigInt::operator+(const BigInt& other) const
{
    if (buf == other.buf) {
        return add_bigint(other);
    }
    BigInt tmp = sub_bigint(other);
    tmp.buf *= buf;
    return tmp;
}

BigInt BigInt::operator-(const BigInt& other) const
{
    if (buf != other.buf) {
        return add_bigint(other);
    } else {
        BigInt tmp = sub_bigint(other);
        tmp.buf *= buf;
        return tmp;
    }
}

BigInt BigInt::operator-() const
{
    BigInt res(*this);
    res.buf *= -1;
    return res;
}

BigInt BigInt::operator*(const BigInt& other) const
{
    if ((*this == 0) || other == 0) {
        return BigInt(0);
    }
    BigInt res;
    res.length = range_v + other.range_v;
    res.values = static_cast<char*>(realloc(res.values, res.length * sizeof(char)));
    for (size_t i = 0; i < res.length; ++i) {
        res.values[i] = 0;
    }

    for (size_t j = 0; j < other.range_v; ++j) {
        size_t tmp = 0;
        size_t i = 0;
        for (i = 0; i < range_v; ++i) {
            res.values[j + i] += (other.values[j] * values[i] + tmp);
            tmp = res.values[j + i] / 10;
            res.values[j + i] %= 10;
        }
        while (tmp) {
            res.values[j + i] += tmp;
            tmp = res.values[j + i] / 10;
            res.values[j + i] %= 10;
            ++i;
        }
    }
    size_t j = res.length - 1;
    while (res.values[j] == 0) {
        --j;
    }
    res.range_v = j + 1;
    return res;
}

bool BigInt::operator==(const BigInt& other) const
{
    if (range_v != other.range_v) return false;
    if ((range_v == 1) && (values[0] == 0) && (other.values[0] == 0)) return true;
    if (buf != other.buf) return false;
    for (size_t i = 0; i < range_v; ++i) {
        if (values[i] != other.values[i]) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
    return !(*this == other);
}


bool BigInt::operator>(const BigInt& other) const
{
    if (*this == other) return false;
    if (buf != other.buf) return buf > other.buf;
    bool greater = abs_greater(other);
    return (buf == 1 ? greater : !greater);
}

bool BigInt::operator>=(const BigInt& other) const
{
    if (*this == other) return true;
    if (buf != other.buf) return buf > other.buf;
    bool greater = abs_greater(other);
    return (buf == 1 ? greater : !greater);
}

bool BigInt::operator<(const BigInt& other) const
{
    return !(*this >= other);
}

bool BigInt::operator<=(const BigInt& other) const
{
    return !(*this > other);
}

std::ostream& operator<<(std::ostream& os, const BigInt& bigint)
{
    if (bigint.buf == -1) {
        os << '-';
    }
    size_t i = bigint.range_v - 1;
    do
    {
        os << static_cast<int>(bigint.values[i]);
    }
    while (i-- > 0);
    return os;
}

void BigInt::init_zero()
{
    range_v = length = buf = 1;
    char* newvalues = static_cast<char*>(malloc(sizeof(char)));
    newvalues[0] = 0;
    if (values != nullptr) {
        free(values);
    }
    values = newvalues;
}

void BigInt::init_int(int value)
{
    char* newvalues;
    if (value == 0) {
        init_zero();
        return;
    }
    value *= buf;
    int tmp = value;
    while (tmp / 10 != 0)
    {
        ++range_v;
        ++length;
        tmp /= 10;
    }
    newvalues = static_cast<char*>(malloc(length * sizeof(char)));
    for (size_t i = 0; i < range_v; ++i) {
        newvalues[i] = value % 10;
        value /= 10;
    }
    if (values != nullptr) {
        free(values);
    }
    values = newvalues;
}

void BigInt::init_string(const std::string& str)
{
    char* newvalues;
    if (str.size() == 0) {
        init_zero();
        return;
    }
    buf = (str[0] == '-' ? -1 : 1);
    size_t forward_zeros = 0;
    for (size_t i = (buf == 1 ? 0 : 1); i < str.size(); ++i) {
        if (str[i] == '0') {
            ++forward_zeros;
        } else {
            break;
        }
    }

    if (buf == 1) {
        if (str.size() - forward_zeros == 0) {
            init_zero();
            return;
        }
        range_v = length = str.size() - forward_zeros;
        newvalues =  static_cast<char*>(malloc(length * sizeof(char)));
        for (size_t i = 0; i < str.size() - forward_zeros; ++i) {
            newvalues[i] = str[str.size() - 1 - i] - '0';
        }
    } else {
        if (str.size() - 1 - forward_zeros == 0) {
            init_zero();
            return;
        }
        range_v = length = str.size() - 1 - forward_zeros;
        newvalues =  static_cast<char*>(malloc(length * sizeof(char)));
        for (size_t i = 0; i < str.size() - 1 - forward_zeros; ++i) {
            newvalues[i] = str[str.size() - 1 - i] - '0';
        }
    }


    if (values != nullptr) {
        free(values);
    }
    values = newvalues;
}

BigInt BigInt::add_bigint(const BigInt& other) const
{
    const BigInt* greater;
    const BigInt* less;
    if (range_v >= other.range_v) {
        greater = this;
        less = &other;
    } else {
        greater = &other;
        less = this;
    }
    BigInt value = *greater;
    int transfer = 0;
    if ((greater->range_v == less->range_v) && (greater->length == greater->range_v)) {
        value.values = static_cast<char*>(realloc(value.values, (value.length + 1) * sizeof(char)));
        value.values[value.length] = 0;
        value.length += 1;
    }
    for (size_t i = 0; i < less->range_v; ++i) {
        char tmp = greater->values[i] + less->values[i];
        tmp += transfer;
        if (tmp >= 10) {
            transfer = 1;
        } else {
            transfer = 0;
        }
        value.values[i] = tmp % 10;
    }
    return value;
}

bool BigInt::abs_greater(const BigInt& other) const
{
    if (range_v != other.range_v) {
        return range_v > other.range_v;
    }
    size_t i = range_v - 1;
    do {
        if (values[i] != other.values[i]) {
            return values[i] > other.values[i];
        }
    } while (i-- > 0);
    return false;
}

BigInt BigInt::sub_bigint(const BigInt& other) const
{
    const BigInt* greater;
    const BigInt* less;
    if (abs_greater(other)) {
        greater = this;
        less = &other;
    } else {
        greater = &other;
        less = this;
    }
    BigInt value = *greater;
    for (size_t i = 0; i < less->range_v; ++i) {
        if (value.values[i] < less->values[i]) {
            size_t j = i + 1;
            while (value.values[j] == 0) ++j;
            value.values[j] -= 1;
            value.values[i] += 10;
        }
        value.values[i] -= less->values[i];
    }
    size_t i = value.range_v - 1;
    do {
        if (value.values[i] == 0) {
            value.range_v -= 1;
        } else {
            break;
        }
    } while (i-- > 1);
    value.buf = greater == this ? 1 : -1;
    return value;
}