#pragma once

#include <iostream>
#include <cstddef>
#include <stdexcept>

class Row
{
public:
    Row() = delete;
    Row(size_t size);
    ~Row();

    int &operator[](size_t ind);
    int operator[](size_t ind) const;

private:
    int *buf;
    size_t size_;
};

class Matrix
{
public:
    Matrix(size_t rows, size_t columns);
    ~Matrix();

    Row &operator[](size_t row);
    const Row& operator[](size_t row) const;

    size_t getRows() const;
    size_t getColumns() const;

    Matrix& operator*=(int value);
    Matrix operator+(const Matrix &other) const;
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

private:
    size_t rows_;
    size_t columns_;
    Row *values;
};