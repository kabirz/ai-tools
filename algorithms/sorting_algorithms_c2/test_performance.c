#include "sorting_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SMALL_SIZE 1000
#define MEDIUM_SIZE 10000
#define LARGE_SIZE 100000

// 生成随机数组
void generate_random_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

// 复制数组
void copy_array(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// 测试排序算法性能
double test_sort_performance(void (*sort_func)(int[], int), int arr[], int n) {
    int* test_array = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_array, n);
    
    clock_t start = clock();
    sort_func(test_array, n);
    clock_t end = clock();
    
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(test_array);
    return cpu_time_used;
}

// 测试归并排序性能
double test_merge_sort_performance(int arr[], int n) {
    int* test_array = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_array, n);
    
    clock_t start = clock();
    merge_sort(test_array, 0, n - 1);
    clock_t end = clock();
    
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(test_array);
    return cpu_time_used;
}

// 测试快速排序性能
double test_quick_sort_performance(int arr[], int n) {
    int* test_array = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_array, n);
    
    clock_t start = clock();
    quick_sort(test_array, 0, n - 1);
    clock_t end = clock();
    
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(test_array);
    return cpu_time_used;
}

// 测试计数排序性能
double test_counting_sort_performance(int arr[], int n) {
    int* test_array = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_array, n);
    
    clock_t start = clock();
    counting_sort(test_array, n, 100000);
    clock_t end = clock();
    
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(test_array);
    return cpu_time_used;
}

// 测试桶排序性能
double test_bucket_sort_performance(int arr[], int n) {
    int* test_array = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_array, n);
    
    clock_t start = clock();
    bucket_sort(test_array, n, 10);
    clock_t end = clock();
    
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(test_array);
    return cpu_time_used;
}

// 测试基数排序性能
double test_radix_sort_performance(int arr[], int n) {
    int* test_array = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_array, n);
    
    clock_t start = clock();
    radix_sort(test_array, n);
    clock_t end = clock();
    
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    free(test_array);
    return cpu_time_used;
}

int main() {
    srand(time(NULL));
    
    int* small_array = (int*)malloc(SMALL_SIZE * sizeof(int));
    int* medium_array = (int*)malloc(MEDIUM_SIZE * sizeof(int));
    int* large_array = (int*)malloc(LARGE_SIZE * sizeof(int));
    
    // 生成测试数据
    generate_random_array(small_array, SMALL_SIZE);
    generate_random_array(medium_array, MEDIUM_SIZE);
    generate_random_array(large_array, LARGE_SIZE);
    
    printf("性能测试开始...\n");
    printf("测试数据规模: %d, %d, %d\n", SMALL_SIZE, MEDIUM_SIZE, LARGE_SIZE);
    printf("\n");
    
    // 测试各种排序算法
    printf("冒泡排序:\n");
    printf("小规模数据: %f 秒\n", test_sort_performance(bubble_sort, small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_sort_performance(bubble_sort, medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_sort_performance(bubble_sort, large_array, LARGE_SIZE));
    printf("\n");
    
    printf("选择排序:\n");
    printf("小规模数据: %f 秒\n", test_sort_performance(selection_sort, small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_sort_performance(selection_sort, medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_sort_performance(selection_sort, large_array, LARGE_SIZE));
    printf("\n");
    
    printf("插入排序:\n");
    printf("小规模数据: %f 秒\n", test_sort_performance(insertion_sort, small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_sort_performance(insertion_sort, medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_sort_performance(insertion_sort, large_array, LARGE_SIZE));
    printf("\n");
    
    printf("希尔排序:\n");
    printf("小规模数据: %f 秒\n", test_sort_performance(shell_sort, small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_sort_performance(shell_sort, medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_sort_performance(shell_sort, large_array, LARGE_SIZE));
    printf("\n");
    
    printf("归并排序:\n");
    printf("小规模数据: %f 秒\n", test_merge_sort_performance(small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_merge_sort_performance(medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_merge_sort_performance(large_array, LARGE_SIZE));
    printf("\n");
    
    printf("快速排序:\n");
    printf("小规模数据: %f 秒\n", test_quick_sort_performance(small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_quick_sort_performance(medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_quick_sort_performance(large_array, LARGE_SIZE));
    printf("\n");
    
    printf("堆排序:\n");
    printf("小规模数据: %f 秒\n", test_sort_performance(heap_sort, small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_sort_performance(heap_sort, medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_sort_performance(heap_sort, large_array, LARGE_SIZE));
    printf("\n");
    
    printf("计数排序:\n");
    printf("小规模数据: %f 秒\n", test_counting_sort_performance(small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_counting_sort_performance(medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_counting_sort_performance(large_array, LARGE_SIZE));
    printf("\n");
    
    printf("桶排序:\n");
    printf("小规模数据: %f 秒\n", test_bucket_sort_performance(small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_bucket_sort_performance(medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_bucket_sort_performance(large_array, LARGE_SIZE));
    printf("\n");
    
    printf("基数排序:\n");
    printf("小规模数据: %f 秒\n", test_radix_sort_performance(small_array, SMALL_SIZE));
    printf("中等规模数据: %f 秒\n", test_radix_sort_performance(medium_array, MEDIUM_SIZE));
    printf("大规模数据: %f 秒\n", test_radix_sort_performance(large_array, LARGE_SIZE));
    printf("\n");
    
    printf("性能测试完成。\n");
    
    free(small_array);
    free(medium_array);
    free(large_array);
    
    return 0;
}