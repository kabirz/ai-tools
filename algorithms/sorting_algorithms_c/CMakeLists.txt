cmake_minimum_required(VERSION 3.10)
project(SortingAlgorithms C)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

# 添加排序算法库
add_library(sorting_algorithms STATIC sorting_algorithms.c)

# 添加测试程序
add_executable(test_sorting test_sorting.c)
target_link_libraries(test_sorting sorting_algorithms)

# 添加性能测试程序
add_executable(performance_test_simple performance_test_simple.c)
target_link_libraries(performance_test_simple sorting_algorithms)

# 添加自定义目标
add_custom_target(test
    COMMAND test_sorting
    DEPENDS test_sorting
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "运行单元测试"
)

add_custom_target(performance
    COMMAND performance_test_simple
    DEPENDS performance_test_simple
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "运行性能测试"
)

# 设置输出目录
set_target_properties(test_sorting PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_target_properties(performance_test_simple PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)