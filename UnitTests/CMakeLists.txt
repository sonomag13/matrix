cmake_minimum_required(VERSION 3.20)

# set the project name and version
project(TestMatrix)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)  # Enforce standard-compliant code

include_directories(
        ../
        /usr/local/include
        /opt/brew/Cellar/glog/0.6.0/include
        /opt/brew/Cellar/gflags/2.2.2/include
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# get ready for the unit test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b75ecf1bed2fcd416b66c86cb6fe79122abf132e.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        TestMatrix
        TestMatrixIndex.cpp
        TestArithmeticOperation.cpp
)

target_link_libraries(
        TestMatrix PRIVATE
        gtest_main
        Eigen3::Eigen
)

include(GoogleTest)
gtest_discover_tests(TestMatrix)