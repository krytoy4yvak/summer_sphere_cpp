#include "matrix.h"

Row::Row(size_t size)
    : size_(size)
{
    buf = new int[size];
}

Row::~Row()
{
    delete[] buf;
}

int &Row::operator[](size_t ind)
{
    if (ind >= size_)
    {
        throw std::out_of_range("");
    }
    return buf[ind];
}

int Row::operator[](size_t ind) const
{
    if (ind >= size_)
    {
        throw std::out_of_range("");
    }
    return buf[ind];
}

Matrix::Matrix(size_t rows, size_t columns)
    : rows_(rows), columns_(columns)
{
    values = static_cast<Row *>(malloc(rows * sizeof(Row)));
    for (size_t i = 0; i < rows_; ++i)
    {
        new (values + i) Row(columns_);
    }
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < rows_; ++i)
    {
        values[i].~Row();
    }
    free(values);
}

Row &Matrix::operator[](size_t row)
{
    if (row >= rows_)
    {
        throw std::out_of_range("");
    }
    return values[row];
}

const Row& Matrix::operator[](size_t row) const
{
    if (row >= rows_)
    {
        throw std::out_of_range("");
    }
    return values[row];
}

size_t Matrix::getRows() const
{
    return rows_;
}

size_t Matrix::getColumns() const
{
    return columns_;
}

Matrix& Matrix::operator*=(int value)
{
    for (size_t i = 0; i < rows_; ++i)
    {
        for (size_t j = 0; j < columns_; ++j)
        {
            values[i][j] *= value;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if ((columns_ != other.columns_) || (rows_ != other.rows_))
    {
        throw std::logic_error("Sum of matrix with different sizes");
    }
    Matrix matrix(rows_, columns_);
    for (size_t i = 0; i < rows_; ++i)
    {
        for (size_t j = 0; j < columns_; ++j)
        {
            matrix.values[i][j] = values[i][j] + other.values[i][j];
        }
    }
    return matrix;
}

bool Matrix::operator==(const Matrix &other) const
{
    for (size_t i = 0; i < rows_; ++i)
    {
        for (size_t j = 0; j < columns_; ++j)
        {
            if (values[i][j] != other.values[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    os << "[";
    for (size_t i = 0; i < matrix.rows_; ++i)
    {
        os << "[";
        for (size_t j = 0; j < matrix.columns_; ++j)
        {
            os << matrix.values[i][j];
            if (j < matrix.columns_ - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        if (i < matrix.rows_ - 1)
        {
            os << std::endl;
        }
    }
    os << "]";
}