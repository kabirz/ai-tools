#include "sorting_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 1000

// 打印数组
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 验证数组是否已排序
int is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// 生成随机数组
void generate_random_array(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

// 复制数组
void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    int original_array[ARRAY_SIZE];
    int test_array[ARRAY_SIZE];
    
    // 生成随机数组
    generate_random_array(original_array, ARRAY_SIZE);
    
    printf("功能测试开始...\n");
    
    // 测试冒泡排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    bubble_sort(test_array, ARRAY_SIZE);
    printf("冒泡排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试选择排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    selection_sort(test_array, ARRAY_SIZE);
    printf("选择排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试插入排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    insertion_sort(test_array, ARRAY_SIZE);
    printf("插入排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试希尔排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    shell_sort(test_array, ARRAY_SIZE);
    printf("希尔排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试归并排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    merge_sort(test_array, 0, ARRAY_SIZE - 1);
    printf("归并排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试快速排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    quick_sort(test_array, 0, ARRAY_SIZE - 1);
    printf("快速排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试堆排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    heap_sort(test_array, ARRAY_SIZE);
    printf("堆排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试计数排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    counting_sort(test_array, ARRAY_SIZE, 10000);
    printf("计数排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试桶排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    bucket_sort(test_array, ARRAY_SIZE, 10);
    printf("桶排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    // 测试基数排序
    copy_array(original_array, test_array, ARRAY_SIZE);
    radix_sort(test_array, ARRAY_SIZE);
    printf("基数排序: %s\n", is_sorted(test_array, ARRAY_SIZE) ? "通过" : "失败");
    
    printf("功能测试完成。\n");
    
    return 0;
}