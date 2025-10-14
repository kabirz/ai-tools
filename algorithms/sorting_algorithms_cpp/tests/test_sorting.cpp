#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include "../include/sorting_algorithms.h"

using namespace sorting;

class SortingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 生成测试数据
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(-1000, 1000);
        
        // 小数组测试
        small_array = {5, 2, 8, 1, 9, 3};
        
        // 大数组测试
        large_array.clear();
        for (int i = 0; i < 1000; ++i) {
            large_array.push_back(dis(gen));
        }
        
        // 已排序数组
        sorted_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        // 逆序数组
        reverse_array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
        
        // 重复元素数组
        duplicate_array = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
        
        // 单元素数组
        single_array = {42};
        
        // 空数组
        empty_array = {};
    }
    
    std::vector<int> small_array;
    std::vector<int> large_array;
    std::vector<int> sorted_array;
    std::vector<int> reverse_array;
    std::vector<int> duplicate_array;
    std::vector<int> single_array;
    std::vector<int> empty_array;
};

// 测试辅助函数
TEST_F(SortingTest, IsSortedFunction) {
    EXPECT_TRUE(isSorted(sorted_array));
    EXPECT_FALSE(isSorted(small_array));
    EXPECT_FALSE(isSorted(reverse_array));
    EXPECT_TRUE(isSorted(single_array));
    EXPECT_TRUE(isSorted(empty_array));
}

// 冒泡排序测试
TEST_F(SortingTest, BubbleSort) {
    std::vector<int> test_small = small_array;
    bubbleSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    bubbleSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_sorted = sorted_array;
    bubbleSort(test_sorted);
    EXPECT_TRUE(isSorted(test_sorted));
    
    std::vector<int> test_reverse = reverse_array;
    bubbleSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
    
    std::vector<int> test_duplicate = duplicate_array;
    bubbleSort(test_duplicate);
    EXPECT_TRUE(isSorted(test_duplicate));
    
    std::vector<int> test_single = single_array;
    bubbleSort(test_single);
    EXPECT_TRUE(isSorted(test_single));
    
    std::vector<int> test_empty = empty_array;
    bubbleSort(test_empty);
    EXPECT_TRUE(isSorted(test_empty));
}

// 选择排序测试
TEST_F(SortingTest, SelectionSort) {
    std::vector<int> test_small = small_array;
    selectionSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    selectionSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    selectionSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 插入排序测试
TEST_F(SortingTest, InsertionSort) {
    std::vector<int> test_small = small_array;
    insertionSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    insertionSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    insertionSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 快速排序测试
TEST_F(SortingTest, QuickSort) {
    std::vector<int> test_small = small_array;
    quickSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    quickSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    quickSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 归并排序测试
TEST_F(SortingTest, MergeSort) {
    std::vector<int> test_small = small_array;
    mergeSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    mergeSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    mergeSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 堆排序测试
TEST_F(SortingTest, HeapSort) {
    std::vector<int> test_small = small_array;
    heapSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    heapSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    heapSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 计数排序测试
TEST_F(SortingTest, CountingSort) {
    std::vector<int> test_small = small_array;
    countingSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    countingSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    countingSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 基数排序测试
TEST_F(SortingTest, RadixSort) {
    std::vector<int> test_small = small_array;
    radixSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    radixSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    radixSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 希尔排序测试
TEST_F(SortingTest, ShellSort) {
    std::vector<int> test_small = small_array;
    shellSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    shellSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    shellSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 桶排序测试
TEST_F(SortingTest, BucketSort) {
    std::vector<int> test_small = small_array;
    bucketSort(test_small);
    EXPECT_TRUE(isSorted(test_small));
    
    std::vector<int> test_large = large_array;
    bucketSort(test_large);
    EXPECT_TRUE(isSorted(test_large));
    
    std::vector<int> test_reverse = reverse_array;
    bucketSort(test_reverse);
    EXPECT_TRUE(isSorted(test_reverse));
}

// 性能对比测试
TEST_F(SortingTest, PerformanceComparison) {
    const int size = 10000;
    std::vector<int> test_data(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size);
    
    for (int i = 0; i < size; ++i) {
        test_data[i] = dis(gen);
    }
    
    // 测试快速排序性能
    std::vector<int> quick_data = test_data;
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(quick_data);
    auto end = std::chrono::high_resolution_clock::now();
    auto quick_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_TRUE(isSorted(quick_data));
    
    // 测试归并排序性能
    std::vector<int> merge_data = test_data;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(merge_data);
    end = std::chrono::high_resolution_clock::now();
    auto merge_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_TRUE(isSorted(merge_data));
    
    // 测试堆排序性能
    std::vector<int> heap_data = test_data;
    start = std::chrono::high_resolution_clock::now();
    heapSort(heap_data);
    end = std::chrono::high_resolution_clock::now();
    auto heap_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    EXPECT_TRUE(isSorted(heap_data));
    
    // 输出性能信息（仅用于观察，不作为测试断言）
    std::cout << "QuickSort time: " << quick_duration.count() << " microseconds" << std::endl;
    std::cout << "MergeSort time: " << merge_duration.count() << " microseconds" << std::endl;
    std::cout << "HeapSort time: " << heap_duration.count() << " microseconds" << std::endl;
}

// 边界条件测试
TEST_F(SortingTest, EdgeCases) {
    // 测试所有相同元素
    std::vector<int> same_elements = {5, 5, 5, 5, 5};
    bubbleSort(same_elements);
    EXPECT_TRUE(isSorted(same_elements));
    
    // 测试两个元素
    std::vector<int> two_elements = {2, 1};
    quickSort(two_elements);
    EXPECT_TRUE(isSorted(two_elements));
    
    // 测试负数
    std::vector<int> negative_numbers = {-3, -1, -4, -2, -5};
    mergeSort(negative_numbers);
    EXPECT_TRUE(isSorted(negative_numbers));
    
    // 测试混合正负数
    std::vector<int> mixed_numbers = {3, -1, 4, -2, 0, -5, 2};
    heapSort(mixed_numbers);
    EXPECT_TRUE(isSorted(mixed_numbers));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}