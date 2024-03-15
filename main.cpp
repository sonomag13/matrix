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
    // printMatrix<float>((float *)arr1, numRow, numCol);

    std::array<std::array<float, numCol>, numRow> arr2;
    getIdentityMatrix(arr2);
    // printMatrix(arr2);

    Matrix<float, numRow, numCol> mat1(arr2);
    mat1.printMatrix();

    Matrix<float, numRow, numCol> mat2;
    mat2.printMatrix();

    mat2 = mat1;
    mat2.printMatrix();

    Matrix<float, numRow, numCol> mat3(std::move(mat2));
    std::cout <<"After moving\n";
    std::cout << "mat3 = \n";
    mat3.printMatrix();
    std::cout << "mat2 = \n";
    mat2.printMatrix();


    Matrix<float, numRow, numCol> mat4;
    mat4 = Matrix<float, numRow, numCol>(arr2);
    std::cout << "mat4 = \n";
    mat4.printMatrix();

    /* Do not even compile
        Matrix<int, numRow, numCol> mat3;
        mat3 = mat2;
    */

    return EXIT_SUCCESS;
}