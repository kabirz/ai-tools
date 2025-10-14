#include "sorting_algorithms.h"
#include <assert.h>

// 测试函数声明
void test_bubble_sort();
void test_selection_sort();
void test_insertion_sort();
void test_shell_sort();
void test_merge_sort();
void test_quick_sort();
void test_heap_sort();
void test_counting_sort();
void test_bucket_sort();
void test_radix_sort();
void test_edge_cases();

// 辅助函数
bool arrays_equal(int arr1[], int arr2[], int n);
bool float_arrays_equal(float arr1[], float arr2[], int n);
void copy_array(int src[], int dest[], int n);
void copy_float_array(float src[], float dest[], int n);

int main() {
    printf("运行排序算法测试...\n");
    
    test_bubble_sort();
    test_selection_sort();
    test_insertion_sort();
    test_shell_sort();
    test_merge_sort();
    test_quick_sort();
    test_heap_sort();
    test_counting_sort();
    test_bucket_sort();
    test_radix_sort();
    test_edge_cases();
    
    printf("所有测试通过!\n");
    return 0;
}

void test_bubble_sort() {
    printf("测试冒泡排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    bubble_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("冒泡排序测试通过!\n");
}

void test_selection_sort() {
    printf("测试选择排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    selection_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("选择排序测试通过!\n");
}

void test_insertion_sort() {
    printf("测试插入排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    insertion_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("插入排序测试通过!\n");
}

void test_shell_sort() {
    printf("测试希尔排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    shell_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("希尔排序测试通过!\n");
}

void test_merge_sort() {
    printf("测试归并排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    merge_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("归并排序测试通过!\n");
}

void test_quick_sort() {
    printf("测试快速排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    quick_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("快速排序测试通过!\n");
}

void test_heap_sort() {
    printf("测试堆排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    heap_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("堆排序测试通过!\n");
}

void test_counting_sort() {
    printf("测试计数排序...\n");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    counting_sort(arr, n);
    assert(arrays_equal(arr, expected, n));
    assert(is_sorted(arr, n));
    
    printf("计数排序测试通过!\n");
}

void test_bucket_sort() {
    printf("测试桶排序...\n");
    
    float arr[] = {0.64f, 0.34f, 0.25f, 0.12f, 0.22f, 0.11f, 0.90f};
    float expected[] = {0.11f, 0.12f, 0.22f, 0.25f, 0.34f, 0.64f, 0.90f};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    bucket_sort(arr, n);
    assert(float_arrays_equal(arr, expected, n));
    assert(is_sorted_float(arr, n));
    
    printf("桶排序测试通过!\n");
}

void test_radix_sort() {
    printf("测试基数排序...\n");
    
    unsigned int arr[] = {64, 34, 25, 12, 22, 11, 90};
    unsigned int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    radix_sort(arr, n);
    assert(arrays_equal((int*)arr, (int*)expected, n));
    assert(is_sorted((int*)arr, n));
    
    printf("基数排序测试通过!\n");
}

void test_edge_cases() {
    printf("测试边界情况...\n");
    
    // 空数组
    int empty_arr[] = {};
    bubble_sort(empty_arr, 0);
    assert(is_sorted(empty_arr, 0));
    
    // 单元素数组
    int single_arr[] = {42};
    bubble_sort(single_arr, 1);
    assert(is_sorted(single_arr, 1));
    assert(single_arr[0] == 42);
    
    // 已排序数组
    int sorted_arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    bubble_sort(sorted_arr, n);
    assert(is_sorted(sorted_arr, n));
    
    // 逆序数组
    int reverse_arr[] = {5, 4, 3, 2, 1};
    bubble_sort(reverse_arr, n);
    assert(is_sorted(reverse_arr, n));
    
    // 重复元素数组
    int dup_arr[] = {5, 2, 8, 2, 9, 5, 6};
    bubble_sort(dup_arr, n);
    assert(is_sorted(dup_arr, n));
    
    printf("边界情况测试通过!\n");
}

// 辅助函数实现
bool arrays_equal(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

bool float_arrays_equal(float arr1[], float arr2[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void copy_float_array(float src[], float dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}