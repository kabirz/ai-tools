cmake_minimum_required(VERSION 3.14)
project(SortingAlgorithms)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含目录
include_directories(include)

# 查找GoogleTest
find_package(GTest REQUIRED)

# 创建排序算法库
add_library(sorting_lib STATIC src/sorting_algorithms.cpp)

# 创建测试可执行文件
add_executable(sorting_tests tests/test_sorting.cpp)

# 链接库
target_link_libraries(sorting_tests 
    sorting_lib 
    GTest::gtest 
    GTest::gtest_main
)

# 启用测试
enable_testing()

# 添加测试
add_test(NAME AllSortingTests COMMAND sorting_tests)