#ifndef TASK8_2_MATRIX_H
#define TASK8_2_MATRIX_H

#include <cstddef>
#include <iostream>


class Matrix {
private:

    static const double EPS;

    size_t _rows;
    size_t _cols;
    double *_data;

    //класс нужен, чтоб реализовать операцию [][]
    class Row {
    public:
        double *_row;
        size_t _col_number;

        explicit Row(double *row, size_t col_size);

        double operator[](size_t col) const;

        double &operator[](size_t col);
    };

public:
    // matrix m*n
    Matrix(size_t rows, size_t cols);

    // matrix 1*1 with given element
    Matrix(double element);

    // matrix-string with size m
    Matrix(const double *vector, size_t m);

    // matrix-column with size m
    Matrix(size_t n, const double *vector);

    // matrix from string representation
    Matrix(const char *string);
    Matrix(const std::string& string);

    // matrix from Row
    Matrix(const Row &row);

    static Matrix diagonal(const double *vals, size_t n);

    static Matrix identity(size_t n);

    ~Matrix();

    const Row operator[](size_t row) const;

    Row operator[](size_t row);

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &other) const;

    Matrix operator-() const;

    Matrix operator + (const Matrix &other) const;

    Matrix operator - (const Matrix &other) const;

    Matrix operator * (const Matrix &other) const;

    Matrix &operator*=(double multiplier);

    Matrix &operator*=(const Matrix &other);

    Matrix &operator-=(const Matrix &other);

    Matrix &operator+=(const Matrix &other);

    Matrix &operator=(const Matrix& m);

    size_t rows() const;

    size_t columns() const;

    void set(int i, int j, double val);

    friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
};


#endif //TASK8_2_MATRIX_H
