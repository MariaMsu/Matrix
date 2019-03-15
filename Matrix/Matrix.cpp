#include "Matrix.h"

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

const double Matrix::EPS = 0.5;

Matrix::Row::Row(double *row, size_t col_size) : _row(row), _col_number(col_size) {}

double Matrix::Row::operator[](size_t col) const {
    if (col >= _col_number)
        throw std::out_of_range(" line: " + std::to_string(__LINE__));
    return _row[col];
}

double &Matrix::Row::operator[](size_t col) {
    if ((col < 0) || (col >= _col_number))
        throw std::out_of_range(" line: " + std::to_string(__LINE__));
    return _row[col];
}

Matrix::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) {
    //fill memory with 0
    _data = new double[rows * cols * sizeof(double)]{0};
}

Matrix::Matrix(double element) : _rows(1), _cols(1) {
    _data = new double[_rows * _cols * sizeof(double)]{element};
}

Matrix::Matrix(const double *vector, size_t m) : _rows(1), _cols(m) {
    _data = new double[_rows * _cols * sizeof(double)];
    memcpy(_data, vector, m * sizeof(double));
}

Matrix::Matrix(size_t n, const double *vector) : _rows(n), _cols(1) {
    _data = new double[_rows * _cols * sizeof(double)];
    memcpy(_data, vector, n * sizeof(double));
}

Matrix::Matrix(const Row &row) : Matrix(row._row, row._col_number) {}

Matrix::Matrix(const std::string &string) : Matrix(string.c_str()) {}

Matrix::Matrix(const char *string) {
    if ((string[0] != '{') || (string[1] != '{'))
        throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));
    if ((string[strlen(string) - 2] != '}') || (string[strlen(string) - 1] != '}'))
        throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));

    size_t cols = 0;
    size_t rows = 0;

    size_t data_size = 10;
    _data = new double[data_size * sizeof(double)];

    double digit = 0;
    bool integer_part = true;
    int fractional_part_size = 0;
    int negativ = 1;
    size_t digit_in_row = 0;

    for (int i = 2; i < strlen(string) - 2; ++i) {

        if (string[i] == '}') {

            if ((string[++i] == ',') && (string[++i] == '{')) {
                //new digit
                if (fractional_part_size != 0) digit *= pow(0.1, fractional_part_size);
                _data[digit_in_row++ + rows * cols] = negativ * digit;

                digit = 0;
                integer_part = true;
                fractional_part_size = 0;
                negativ = 1;

                if (cols == 0) cols = digit_in_row;
                if (cols != digit_in_row)
                    throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));
                if (++rows * cols > data_size) {
                    //realloc data
                    double *new_data = new double[data_size * 2 * sizeof(double)];
                    memcpy(new_data, _data, data_size);
                    data_size *= 2;
                    delete[] _data;
                    _data = new_data;
                }
                digit_in_row = 0;
            }


        } else if (string[i] == '.') {
            //fractional part
            if (integer_part)
                integer_part = false;
            else
                throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));

        } else if (string[i] == ',') {
            //new digit
            if (fractional_part_size != 0) digit *= pow(0.1, fractional_part_size);
            _data[digit_in_row++ + rows * cols] = negativ * digit;

            digit = 0;
            integer_part = true;
            fractional_part_size = 0;
            negativ = 1;

        } else if (string[i] == '-') {
            if (digit != 0)
                throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));
            negativ = -1;

        } else if (string[i] == '+') {
            if (digit != 0)
                throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));

        } else if (('0' <= string[i]) && (string[i] <= '9')) {
            digit = 10 * digit + (string[i] - '0');
            if (!integer_part) ++fractional_part_size;

        } else throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));

    }

    //last string
    if (fractional_part_size != 0) digit *= pow(0.1, fractional_part_size);
    _data[digit_in_row++ + rows * cols] = negativ * digit;

    if (cols == 0) cols = digit_in_row;
    if (cols != digit_in_row)
        throw std::invalid_argument("Error: invalid syntax line: " + std::to_string(__LINE__));
    if (++rows * cols > data_size) {
        //realloc data
        double *new_data = new double[data_size * 2 * sizeof(double)];
        memcpy(new_data, _data, data_size);
        delete[] _data;
        _data = new_data;
    }

    _rows = rows;
    _cols = cols;
}

Matrix::~Matrix() {
    delete[]_data;
}

const Matrix::Row Matrix::operator[](size_t row) const {
    if ((row < 0) || (row >= _rows))
        throw std::out_of_range("line: " + std::to_string(__LINE__));
    return Row(_data + row * _cols, _cols);
}

Matrix::Row Matrix::operator[](size_t row) {
    if ((row < 0) || (row >= _rows))
        throw std::out_of_range("line: " + std::to_string(__LINE__));
    return Row(_data + row * _cols, _cols);
}

bool Matrix::operator==(const Matrix &other) const {
    if ((_cols != other._cols) || (_rows != other._rows))
        throw std::out_of_range("line: " + std::to_string(__LINE__));

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            if (other[i][j] - (*this)[i][j] > EPS)
                return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix &other) const {
    return !(this == &other);
}

Matrix &Matrix::operator*=(double multiplier) {
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            _data[i * _cols + j] *= multiplier;
    return *this;
}

size_t Matrix::rows() const {
    return _rows;
}

size_t Matrix::columns() const {
    return _cols;
}

Matrix Matrix::diagonal(const double *vals, size_t n) {
    Matrix m(n, n);
    for (int i = 0; i < n; ++i) {
        m[i][i] = vals[i];
    }
    return m;
}

Matrix Matrix::identity(size_t n) {
    Matrix m(n, n);
    for (int i = 0; i < n; ++i) {
        m[i][i] = 1;
    }
    return m;
}

void Matrix::set(int i, int j, double val) {
    _data[i * _cols + j] = val;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m) {
    out << '{';
    for (int i = 0; i < m._rows - 1; ++i) {
        out << '{';
        for (int j = 0; j < m._cols - 1; ++j) {
            out << m[i][j] << ',';
        }
        out << m[i][m._cols - 1];
        out << '}' << ',';
    }

    out << '{';
    for (int j = 0; j < m._cols - 1; ++j) {
        out << m[m._rows - 1][j] << ',';
    }
    out << m[m._rows - 1][m._cols - 1];
    out << '}' << '}';
    return out;
}

Matrix Matrix::operator-() const {
    Matrix new_matrix(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            new_matrix[i][j] = -(*this)[i][j];
        }
    }
    return new_matrix;
}

Matrix Matrix::operator+(const Matrix &other) const {
    if ((_cols != other._cols) || (_rows != other._rows))
        throw std::out_of_range(" line: " + std::to_string(__LINE__));

    Matrix new_matrix(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            new_matrix[i][j] = (*this)[i][j] + other[i][j];
        }
    }
    return new_matrix;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if ((_cols != other._cols) || (_rows != other._rows))
        throw std::out_of_range(" line: " + std::to_string(__LINE__));

    Matrix new_matrix(_rows, _cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            new_matrix[i][j] = (*this)[i][j] - other[i][j];
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (_cols != other._rows)
        throw std::out_of_range(" line: " + std::to_string(__LINE__));

    Matrix new_matrix(_rows, other._cols);
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < other._cols; ++j) {
            for (int k = 0; k < _cols; ++k) {
                //the new matrix was fill with 0
                new_matrix[i][j] += (*this)[i][k] * other[k][j];
            }
        }
    }

    return new_matrix;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    *this = *this * other;
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    *this = *this - other;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    *this = *this + other;
    return *this;
}

Matrix &Matrix::operator=(const Matrix &m) {
    double *_new_data = new double[m._rows * m._cols * sizeof(double)];
    delete _data;
    _data = _new_data;
    memcpy(_data, m._data, m._rows * m._cols * sizeof(double));
    _cols = m._cols;
    _rows = m._rows;
    return *this;
}







