//
// Created by lgao23 on 3/17/24.
//

/**
 * Unit test of matrix construction and access
 */

#include <array>
#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <iostream>
#include <random>

#include "../Matrix.hpp"
#include "../utils.hpp"

template<class T, size_t numRow, size_t numCol>
void getEigenMatrixAndArray(std::uniform_real_distribution<T> dist,
                            std::mt19937 gen,
                            std::array<std::array<T, numCol>, numRow> & array,
                            Eigen::MatrixXf & eigenMat) {

    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            float val{dist(gen)};
            array[rowIdx][colIdx] = val;
            eigenMat(rowIdx, colIdx) = val;
        }
    }

}

TEST(TestMatrix, TestMatrixAddition) {
    // test add two matrices

    const size_t numRow{100};
    const size_t numCol{100};

    // uniform random float number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    float minVal{-100.0f};
    float maxVal{+100.0f};
    std::uniform_real_distribution<float> distRealNum(minVal, maxVal);

    std::array<std::array<float, numCol>, numRow> array1{};
    std::array<std::array<float, numCol>, numRow> array2{};
    std::array<std::array<float, numCol>, numRow> arraySum{};
    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            float val1{distRealNum(generator)};
            float val2{distRealNum(generator)};
            array1.at(rowIdx).at(colIdx) = val1;
            array2.at(rowIdx).at(colIdx) = val2;
            arraySum.at(rowIdx).at(colIdx) = val1 + val2;
        }
    }

    Matrix<float, numRow, numCol> mat1(array1);
    Matrix<float, numRow, numCol> mat2(array2);
    Matrix<float, numRow, numCol> matSum = mat1 + mat2;

    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            EXPECT_FLOAT_EQ(arraySum.at(rowIdx).at(colIdx), matSum.at(rowIdx, colIdx));
        }
    }
}

TEST(TestMatrix, TestMatrixMultiplication) {
    // test add two matrices

    // uniform random float number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    float minVal{-100.0f};
    float maxVal{+100.0f};
    std::uniform_real_distribution<float> distRealNum(minVal, maxVal);

    const size_t numRow1{4};
    const size_t numCol1{4};
    std::array<std::array<float, numCol1>, numRow1> array1{};
    Eigen::MatrixXf eigenMat1(numRow1, numCol1);
    getEigenMatrixAndArray<float, numRow1, numCol1>(distRealNum, generator, array1, eigenMat1);

    const size_t numRow2{numCol1};
    const size_t numCol2{2};
    std::array<std::array<float, numCol2>, numRow2> array2{};
    Eigen::MatrixXf eigenMat2(numRow2, numCol2);
    getEigenMatrixAndArray<float, numRow2, numCol2>(distRealNum, generator, array2, eigenMat2);

    Eigen::MatrixXf eigenMatProduct(numRow1, numCol2);
    eigenMatProduct = eigenMat1 * eigenMat2;

    std::cout << "product by Eigen:\n" << eigenMatProduct << '\n';

    Matrix<float, numRow1, numCol1> mat1(array1);
    Matrix<float, numRow2, numCol2> mat2(array2);
    Matrix<float, numRow1, numCol2> mat3{mat1 * mat2};

    std::cout << "product by Matrix:\n";
    mat3.printMatrix();

    for (size_t rowIdx = 0; rowIdx < numRow1; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol2; ++colIdx) {
            EXPECT_FLOAT_EQ(mat3(rowIdx, colIdx), eigenMatProduct(rowIdx, colIdx));
        }
    }

    const size_t numRow3{numCol1 + 1}; // invalid row number
    const size_t numCol3{2};
    std::array<std::array<float, numCol3>, numRow3> wrongArray{};
    Eigen::MatrixXf wrongEigenMat(numRow3, numCol3);
    getEigenMatrixAndArray<float, numRow3, numCol3>(distRealNum, generator, wrongArray, wrongEigenMat);
    Matrix mat4(wrongArray);

    try {
        Matrix<float, numRow1, numCol3> mat5{mat1 * mat4};
    }
    catch(std::exception & err) {
        std::cout << err.what() << '\n';
    }
}

TEST(TestMatrix, TestIdentityMatrixMultiplication) {
    // test multiplication of a vector with identity matrix

    const size_t numRow{3};
    const size_t numCol{3};

    std::array<std::array<int, numCol>, numRow> array{};
    getIdentityMatrix<int, numRow, numCol>(array);
    Matrix<int, numRow, numCol> identityMat(array);

    // uniform random float number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    int minVal{-100};
    int maxVal{+100};
    std::uniform_int_distribution<int> distRealNum(minVal, maxVal);

    std::array<std::array<int, 1>, numRow> array1D{};
    Matrix<int, numRow, 1> vec1(array1D);

    Matrix<int, numRow, 1> vec2{identityMat * vec1};

    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        EXPECT_FLOAT_EQ(vec1(rowIdx, 0), vec2(rowIdx, 0));
    }

}