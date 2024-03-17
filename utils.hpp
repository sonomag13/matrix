//
// Created by lgao23 on 3/14/24.
//

#pragma once

#include <cassert>
#include <iostream>

template<class T>
void printMatrix(T* arr, size_t numRow, size_t numCol, const std::string & note) {

    std::cout << note << '\n';

    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            std::cout << arr[rowIdx * numCol + colIdx] << ' ';
        }
        std::cout << '\n';
    }

}

template<class T>
void getIdentityMatrix(T* arr, size_t numRow, size_t numCol) {
    // make arr an identity matrix

    assert(numRow == numCol);
    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            size_t idx = rowIdx * numCol + colIdx;
            if (rowIdx == colIdx) {
                arr[idx] = static_cast<T>(1.0);
            }
            else {
                arr[idx] = static_cast<T>(0.0);
            }
        }
    }

}

template<class T, size_t numRow, size_t numCol>
void getIdentityMatrix(std::array<std::array<T, numCol>, numRow> & mat) {

    assert(numRow == numCol);
    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            if (rowIdx == colIdx) {
                mat[rowIdx][colIdx] = static_cast<T>(1.0);
            }
            else {
                mat[rowIdx][colIdx] = static_cast<T>(0.0);
            }
        }
    }

}

template<class T, size_t numRow, size_t numCol>
void printMatrix(const std::array<std::array<T, numCol>, numRow> & mat, const std::string & note) {

    assert(numRow == numCol);
    std::cout << note << '\n';
    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            std::cout << mat[rowIdx][colIdx] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << '\n';
}