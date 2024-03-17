// main.cpp to play with matrix

#include <iostream>

#include <array>

#include "Matrix.hpp"
#include "utils.hpp"

int main() {

    const size_t numRow{3};
    const size_t numCol{3};

    auto arr1 = new float[numRow][numCol];
    getIdentityMatrix<float>((float *)(arr1), numRow, numCol);
    printMatrix<float>((float *)arr1, numRow, numCol, "2D array passing by pointer");

    std::array<std::array<float, numCol>, numRow> arr2;
    getIdentityMatrix(arr2);
    printMatrix(arr2, "2D array passing by std::array");

    return EXIT_SUCCESS;
}