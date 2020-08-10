//
// Created by conno on 8/8/2020.
//

#ifndef MATH_MATRIX_CPP
#define MATH_MATRIX_CPP

#include "matrix.h"

// Constructor
template<typename T>
matrix<T>::matrix(unsigned _rows, unsigned _cols, const T& _initial) {
    mat.resize(_rows);
    for (unsigned i=0; i < mat.size(); i++) {
        mat[i].resize(_cols, _initial);
    }
    rows = _rows;
    cols = _cols;
}

template<typename T>
matrix<T>::matrix(unsigned _rows, unsigned _cols, const std::vector<std::vector<T> > &_initial) {
    mat.resize(_rows);
    for (unsigned i=0; i < mat.size(); i++) {
        mat[i].resize(_cols);
        for (unsigned j=0; j < mat[i].size(); j++) {
            mat[i][j] = _initial[i][j];
        }
    }
    rows = _rows;
    cols = _cols;
}

// Copy constructor
template<typename T>
matrix<T>::matrix(const matrix<T>& rhs) {
    mat = rhs.mat;
    rows = rhs.get_rows();
    cols = rhs.get_cols();
}

// Destructor
template<typename T>
matrix<T>::~matrix() = default;

// Assignment operator
template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& rhs) {
    if (&rhs == this)
        return *this;

    unsigned new_rows = rhs.get_rows();
    unsigned new_cols = rhs.get_cols();

    mat.resize(new_rows);
    for (unsigned i = 0; i < mat.size(); i++) {
        mat[i].resize(new_cols);
    }

    for (unsigned i = 0; i < new_rows; i++) {
        for (unsigned j = 0; j < new_cols; j++) {
            mat[i][j] = rhs(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}



// Addition of two matrices
template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &rhs) {
    matrix result(rows, cols, 0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i,j) = this->mat[i][j] + rhs(i,j);
        }
    }

    return result;
}

template<typename T>
matrix<T>& matrix<T>::operator+=(const matrix<T> &rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i=0; i < rows; i++) {
        for (unsigned j=0; j < cols; j++) {
            this->mat[i][j] += rhs(i,j);
        }
    }

    return *this;
}

// Subtraction of matrices
template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &rhs) {
    matrix result(rows, cols, 0);

    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            result(i,j) = this->mat[i][j] - rhs(i,j);
        }
    }

    return result;
}

template<typename T>
matrix<T>& matrix<T>::operator-=(const matrix<T> &rhs) {
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    for (unsigned i=0; i < rows; i++) {
        for (unsigned j=0; j < cols; j++) {
            this->mat[i][j] -= rhs(i,j);
        }
    }

    return *this;
}

// Multiplication
template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &rhs) {
    unsigned rows = this->get_rows();
    unsigned cols = rhs.get_cols();
    matrix result(rows,cols,0.0);

    for (unsigned i=0; i < rows; i++) {
        for (unsigned j=0; j < cols; j++) {
            for (unsigned k=0; k < this->get_cols(); k++) {
                result(i,j) += this->mat[i][k] * rhs(k,j);
            }
        }
    }
    return result;
}

template<typename T>
matrix<T>& matrix<T>::operator*=(const matrix<T> &rhs) {
    matrix result = (*this) * rhs;
    (*this) = result;
    return *this;
}



// Scalar multiplication
template<typename T>
matrix<T> matrix<T>::operator*(const T &rhs) {
    matrix result(rows, cols, 0);

    for (unsigned i=0; i < rows; i++) {
        for (unsigned j=0; j < cols; j++) {
            result(i,j) = this->mat[i][j] * rhs;
        }
    }
    return result;
}

// Transpose
template<typename T>
matrix<T> matrix<T>::transpose() {
    matrix result(cols, rows, 0.0);

    for (unsigned i=0; i < cols; i++) {
        for (unsigned j=0; j < rows; j++) {
            result(i,j) = this->mat[j][i];
        }
    }
    return result;
}

// Row echelon form
template<typename T>
matrix<T> matrix<T>::ref() {
    matrix result = *this;
    for (unsigned i = 0; i < rows; i++) {
        bool nonzero = false;
        for (unsigned k = i; k < rows; k++) {
            if (result.mat[k][i] != 0)
                nonzero = true;
        }
        if (nonzero) {
            result.row_scalar(i, 1 / result.mat[i][i]);
            for (unsigned j = i + 1; j < rows; j++) {
                result.row_add_multiple(j, i, -1 * result.mat[j][i]);
            }
        }
    }
    return result;
}

// Reduced row echelon form
template<typename T>
matrix<T> matrix<T>::rref() {
    matrix result = *this;
    for (unsigned i = 0; i < rows; i++) {
        bool nonzero = false;
        for (unsigned k = i; k < rows; k++) {
            if (result.mat[k][i] != 0)
                nonzero = true;
        }
        if (nonzero) {
            result.row_scalar(i, 1 / result.mat[i][i]);
            for (unsigned j = 0; j < rows; j++) {
                if (i != j)
                    result.row_add_multiple(j, i, -1 * result.mat[j][i]);
            }
        }
    }
    return result;
}

// Multiply row by a scalar
template<typename T>
void matrix<T>::row_scalar(const unsigned &row, const T &scalar) {
    for (unsigned i = 0; i < cols; i++) {
            this->mat[row][i] *= scalar;
    }
}

// Multiply a row by a non-zero number and add result to other row
template<typename T>
void matrix<T>::row_add_multiple(const unsigned int &row1, const unsigned int &row2, const T &scalar) {
    for (unsigned i = 0; i < cols; i++) {
        this->mat[row1][i] += this->mat[row2][i] * scalar;
    }
}

// Access element
template<typename T>
T& matrix<T>::operator()(const unsigned& row, const unsigned& col) {
    return this->mat[row][col];
}

template<typename T>
const T& matrix<T>::operator()(const unsigned int &row, const unsigned int &col) const {
    return this->mat[row][col];
}

// Getters
template<typename T>
unsigned matrix<T>::get_rows() const {
    return this->rows;
}

template<typename T>
unsigned matrix<T>::get_cols() const {
    return this->cols;
}

#endif