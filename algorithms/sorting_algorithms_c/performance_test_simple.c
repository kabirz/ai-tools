#include "sorting_algorithms.h"
#include <sys/time.h>

// 获取当前时间（毫秒）
double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

// 测试排序算法性能
void test_sort_performance(const char* name, void (*sort_func)(int[], int), int* arr, int n) {
    int* test_arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        test_arr[i] = arr[i];
    }
    
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
        test_sort_performance("计数排序", counting_sort, random_arr, size);
        
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
    
    return 0;
}