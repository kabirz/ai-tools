#include "sorting_algorithms.h"
#include <sys/time.h>
#include <string.h>

// 获取当前时间（毫秒）
double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

// 测试排序算法性能
void test_sort_performance(const char* name, void (*sort_func)(int[], int), int* arr, int n) {
    int* test_arr = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_arr, n);
    
    double start_time = get_time_ms();
    sort_func(test_arr, n);
    double end_time = get_time_ms();
    
    printf("  %s: %.3f ms\n", name, end_time - start_time);
    
    free(test_arr);
}

// 测试计数排序性能（单独处理，因为它是非比较排序）
void test_counting_sort_performance(const char* name, void (*sort_func)(int[], int), int* arr, int n) {
    int* test_arr = (int*)malloc(n * sizeof(int));
    copy_array(arr, test_arr, n);
    
    double start_time = get_time_ms();
    sort_func(test_arr, n);
    double end_time = get_time_ms();
    
    printf("  %s: %.3f ms\n", name, end_time - start_time);
    
    free(test_arr);
}

int main() {
    printf("排序算法性能测试\n");
    printf("==================\n");
    
    int sizes[] = {1000, 5000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        printf("\n数组大小: %d\n", size);
        printf("------------\n");
        
        // 随机数组测试
        int* random_arr = generate_random_array(size, 1, 10000);
        
        printf("随机数组:\n");
        test_sort_performance("冒泡排序", bubble_sort, random_arr, size);
        test_sort_performance("选择排序", selection_sort, random_arr, size);
        test_sort_performance("插入排序", insertion_sort, random_arr, size);
        test_sort_performance("希尔排序", shell_sort, random_arr, size);
        test_sort_performance("归并排序", merge_sort, random_arr, size);
        test_sort_performance("快速排序", quick_sort, random_arr, size);
        test_sort_performance("堆排序", heap_sort, random_arr, size);
        test_counting_sort_performance("计数排序", counting_sort, random_arr, size);
        
        // 已排序数组测试
        int* sorted_arr = generate_sorted_array(size, true);
        
        printf("已排序数组:\n");
        test_sort_performance("冒泡排序", bubble_sort, sorted_arr, size);
        test_sort_performance("插入排序", insertion_sort, sorted_arr, size);
        
        // 逆序数组测试
        int* reverse_arr = generate_sorted_array(size, false);
        
        printf("逆序数组:\n");
        test_sort_performance("冒泡排序", bubble_sort, reverse_arr, size);
        test_sort_performance("快速排序", quick_sort, reverse_arr, size);
        
        free(random_arr);
        free(sorted_arr);
        free(reverse_arr);
    }
    
    // 测试桶排序（浮点数）
    printf("\n桶排序测试（浮点数）\n");
    printf("------------------\n");
    
    float bucket_sizes[] = {1000, 5000, 10000};
    int num_bucket_sizes = sizeof(bucket_sizes) / sizeof(bucket_sizes[0]);
    
    for (int i = 0; i < num_bucket_sizes; i++) {
        int size = bucket_sizes[i];
        printf("\n数组大小: %d\n", size);
        printf("------------\n");
        
        // 生成随机浮点数数组
        float* random_float_arr = (float*)malloc(size * sizeof(float));
        srand(time(NULL));
        for (int j = 0; j < size; j++) {
            random_float_arr[j] = (float)rand() / RAND_MAX * 100.0f;
        }
        
        printf("随机数组:\n");
        float* test_arr = (float*)malloc(size * sizeof(float));
        copy_float_array(random_float_arr, test_arr, size);
        
        double start_time = get_time_ms();
        bucket_sort(test_arr, size);
        double end_time = get_time_ms();
        
        printf("  桶排序: %.3f ms\n", end_time - start_time);
        
        free(random_float_arr);
        free(test_arr);
    }
    
    // 测试基数排序（无符号整数）
    printf("\n基数排序测试（无符号整数）\n");
    printf("------------------------\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        printf("\n数组大小: %d\n", size);
        printf("------------\n");
        
        // 生成随机无符号整数数组
        unsigned int* random_uint_arr = (unsigned int*)malloc(size * sizeof(unsigned int));
        srand(time(NULL));
        for (int j = 0; j < size; j++) {
            random_uint_arr[j] = rand() % 10000;
        }
        
        printf("随机数组:\n");
        unsigned int* test_arr = (unsigned int*)malloc(size * sizeof(unsigned int));
        memcpy(test_arr, random_uint_arr, size * sizeof(unsigned int));
        
        double start_time = get_time_ms();
        radix_sort(test_arr, size);
        double end_time = get_time_ms();
        
        printf("  基数排序: %.3f ms\n", end_time - start_time);
        
        free(random_uint_arr);
        free(test_arr);
    }
    
    return 0;
}