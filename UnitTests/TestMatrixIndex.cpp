/**
 * Unit test of matrix construction and access
 */

#include <array>
#include <gtest/gtest.h>
#include <iostream>
#include <random>

#include "../Matrix.hpp"
#include "../utils.hpp"

TEST(TestMatrix, TestConstructor) {

    const size_t numRow{100};
    const size_t numCol{100};

    // uniform random float number generator
    std::random_device rd;
    std::mt19937 generator(rd());
    float minVal{-100.0f};
    float maxVal{+100.0f};
    std::uniform_real_distribution<float> distRealNum(minVal, maxVal);

    // first give value to array
    std::array<std::array<float, numCol>, numRow> array;
    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            array.at(rowIdx).at(colIdx) = distRealNum(generator);
        }
    }

    // build matrix with random numbers array
    Matrix<float, numRow, numCol> randomFloatMat(array);

    // test the matrix and array have the save value
    for (size_t rowIdx = 0; rowIdx < numRow; ++rowIdx) {
        for (size_t colIdx = 0; colIdx < numCol; ++colIdx) {
            EXPECT_FLOAT_EQ(array.at(rowIdx).at(colIdx), randomFloatMat.at(rowIdx, colIdx));
        }
    }

}

TEST(TestMatrix, TestOverloadingPrenthesis) {

    const size_t numRow{3};
    const size_t numCol{3};

    std::array<std::array<float, numCol>, numRow> array;
    getIdentityMatrix<float, numRow, numCol>(array);
    Matrix<float, numRow, numCol> identityMat(array);

    size_t rowIdx{0};
    size_t colIdx{0};

    // read a value from matrix
    float val2Read = identityMat(rowIdx, colIdx);
    EXPECT_FLOAT_EQ(val2Read, 1.0f);

    // write a value to matrix
    float val2Write = 100.0;
    identityMat(rowIdx, colIdx) = val2Write;
    EXPECT_FLOAT_EQ(identityMat(rowIdx, colIdx), val2Write);

    // write to an invalid index
    size_t invalidRowIdx = numRow;
    try {
        identityMat.at(invalidRowIdx, colIdx) = val2Write;
        FAIL();
    }
    catch(std::out_of_range & err) {
        std::cout << "Error: " << err.what() << '\n';
    }

    try {
        val2Read = identityMat.at(invalidRowIdx, colIdx);
        FAIL();
    }
    catch(std::out_of_range & err) {
        std::cout << "Error: " << err.what() << '\n';
    }

}