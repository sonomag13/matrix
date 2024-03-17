/**
 * Matrix.hpp -- a class of matrix calculation
 */

#pragma once

#include <array>
#include <cassert>

template<class T, size_t numRow, size_t numCol>
class Matrix {
public:
    Matrix() {

        std::cout << "Empty matrix is constructed" << '\n';
    }

    Matrix(const std::array<std::array<T, numCol>, numRow> & array): _data(array) {

        std::cout << "Matrix is constructed with input array" << '\n';
    }

    ~Matrix() {

        std::cout << "Matrix is destructed" << '\n';
    }

    T& operator()(size_t rowIdx, size_t colIdx) {
        // index return the reference of a value; used to modify the value

        return _data[rowIdx][colIdx];
    }

    T operator()(size_t rowIdx, size_t colIdx) const {
        // index return a copy of a value; used to get the value

        return _data[rowIdx][colIdx];
    }

    T at(size_t rowIdx, size_t colIdx) const {
        // safe way to get a value

        try {
            return _data.at(rowIdx).at(colIdx);
        }
        catch(std::out_of_range & err) {
            throw(err);
        }
    }

    T& at(size_t rowIdx, size_t colIdx) {
        // safe way to modify a value

        try{
            return _data.at(rowIdx).at(colIdx);
        }
        catch(std::out_of_range & err) {
            throw(err);
        }
    }

    Matrix(const Matrix & otherMatrix) {

        if (this == &otherMatrix) {
            return;
        }

        std::cout << "Copy constructor is invoked" << '\n';
        _data = otherMatrix.data;
    }

    Matrix & operator=(const Matrix & otherMatrix) {

        if (this != &otherMatrix) {
            _data = otherMatrix._data;
            assert(&_data != &otherMatrix._data);
            std::cout << "Copy assignment is invoked" << '\n';
        }

        return *this;
    }

    Matrix (Matrix && otherMatrix) noexcept {

        std::cout << "Move constructor is invoked" << '\n';
        swap(_data, otherMatrix._data);
    }

    Matrix & operator=(Matrix && otherMatrix) noexcept {

        std::cout << "Move assignment is invoked" << '\n';
        swap(_data, otherMatrix._data);

        return *this;
    }

    Matrix operator+(const Matrix & otherMatrix) {

        try{
            assert(_hasSameShape(otherMatrix));
        }
        catch(std::exception & err) {

            throw(std::invalid_argument("Error: shape of matrices do not match; cannot add"));
        }

        Matrix<T, numRow, numCol> outputMat;

        for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
            for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
                outputMat(rowIdx, colIdx) = _data[rowIdx][colIdx] + otherMatrix(rowIdx, colIdx);
            }
        }

        return outputMat;
    }

    template<class T2, size_t numRow2, size_t numCol2>
    Matrix mul(const Matrix<T2, numRow2, numCol2> & other) {

        try{
           assert(numCol == other._data.size());
        }
        catch(std::exception & err) {

            throw(std::invalid_argument("Error: shape of matrices do not match; cannot multiply"));
        }

        Matrix<T, numRow, numCol2> outputMat;

        return outputMat;
    }

    void printMatrix() {

        for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
            for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
                std::cout << _data[rowIdx][colIdx] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    std::array<std::array<T, numCol>, numRow> _data;

    bool _inBoundary(size_t rowIdx, size_t colIdx) {

        return 0 <= rowIdx && rowIdx < numRow && 0 <= colIdx && colIdx < numCol;
    }

    bool _hasSameShape(const Matrix & otherMatrix) {

        return numRow == otherMatrix._data.size() && numCol == otherMatrix._data.at(0).size();
    }

    void _calcProd(const Matrix & otherMatrix, size_t rowIdx, size_t colIdx, Matrix & outputMatrix) {

        T val{0};
        for (size_t k = 0; k < numCol; ++k) {
            val += _data[rowIdx][k] * otherMatrix(k, colIdx);
        }

        outputMatrix(rowIdx, colIdx) = val;
    }
};