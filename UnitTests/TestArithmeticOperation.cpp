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

    std::array<std::array<float, numCol>, numRow> array1;
    std::array<std::array<float, numCol>, numRow> array2;
    std::array<std::array<float, numCol>, numRow> arraySum;
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

    Matrix<float, numRow1, numCol1> mat1(array1);
    Matrix<float, numRow2, numCol2> mat2(array2);
    auto mat3 = mat1.mul<float, numRow2, numCol2>(mat2);
}