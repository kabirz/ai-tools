#pragma once

#include <vector>

namespace sorting {

// 1. 冒泡排序
void bubbleSort(std::vector<int>& arr);

// 2. 选择排序
void selectionSort(std::vector<int>& arr);

// 3. 插入排序
void insertionSort(std::vector<int>& arr);

// 4. 快速排序
void quickSort(std::vector<int>& arr);

// 5. 归并排序
void mergeSort(std::vector<int>& arr);

// 6. 堆排序
void heapSort(std::vector<int>& arr);

// 7. 计数排序
void countingSort(std::vector<int>& arr);

// 8. 基数排序
void radixSort(std::vector<int>& arr);

// 9. 希尔排序
void shellSort(std::vector<int>& arr);

// 10. 桶排序
void bucketSort(std::vector<int>& arr);

// 辅助函数
bool isSorted(const std::vector<int>& arr);

} // namespace sorting