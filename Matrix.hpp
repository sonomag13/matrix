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
};