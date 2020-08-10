//
// Created by conno on 8/8/2020.
//

#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include <vector>

template <typename T> class matrix {
private:
    std::vector<std::vector<T> > mat;
    unsigned rows;
    unsigned cols;

public:
    // Constructors
    matrix(unsigned _rows, unsigned _cols, const T& _initial);
    matrix(unsigned _rows, unsigned _cols, const std::vector<std::vector<T> >& _initial );

    // Copy constructor
    matrix(const matrix<T>& rhs);

    // Destructor
    virtual ~matrix();

    matrix<T>& operator=(const matrix<T>& rhs);

    // Matrix math operations
    matrix<T> operator+(const matrix<T>& rhs);
    matrix<T>& operator+=(const matrix<T>& rhs);
    matrix<T> operator-(const matrix<T>& rhs);
    matrix<T>& operator-=(const matrix<T>& rhs);
    matrix<T> operator*(const matrix<T>& rhs);
    matrix<T>& operator*=(const matrix<T>& rhs);

    // Scalar math
    matrix<T> operator*(const T& rhs);

    // Matrix operations
    matrix<T> transpose();
    void ref();
    void rref();


    // Elementary row operations
    void row_scalar(const unsigned& row, const T& scalar);
    void row_add_multiple(const unsigned &row1, const unsigned &row2, const T& scalar);

    // Access elements
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;

    // Getters
    unsigned get_rows() const;
    unsigned get_cols() const;

};

#include "matrix.cpp"

#endif //MATH_MATRIX_H
