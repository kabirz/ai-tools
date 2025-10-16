#include "sorting_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 冒泡排序
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 选择排序
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// 插入排序
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 希尔排序
void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 归并排序
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 快速排序
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 堆排序
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
        
    if (right < n && arr[right] > arr[largest])
        largest = right;
        
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
        
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// 计数排序
void counting_sort(int arr[], int n, int max_val) {
    int* count = (int*)calloc(max_val + 1, sizeof(int));
    int* output = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++)
        count[arr[i]]++;
        
    for (int i = 1; i <= max_val; i++)
        count[i] += count[i - 1];
        
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
        
    free(count);
    free(output);
}

// 桶排序
void bucket_sort(int arr[], int n, int bucket_count) {
    int max_val = arr[0], min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
        if (arr[i] < min_val) min_val = arr[i];
    }
    
    int range = max_val - min_val + 1;
    int bucket_size = (range / bucket_count) + 1;
    
    int** buckets = (int**)malloc(bucket_count * sizeof(int*));
    int* bucket_sizes = (int*)calloc(bucket_count, sizeof(int));
    int* bucket_capacities = (int*)malloc(bucket_count * sizeof(int));
    
    for (int i = 0; i < bucket_count; i++) {
        bucket_capacities[i] = bucket_size;
        buckets[i] = (int*)malloc(bucket_size * sizeof(int));
    }
    
    for (int i = 0; i < n; i++) {
        int bucket_index = (arr[i] - min_val) / bucket_size;
        if (bucket_index >= bucket_count) bucket_index = bucket_count - 1;
        
        if (bucket_sizes[bucket_index] >= bucket_capacities[bucket_index]) {
            bucket_capacities[bucket_index] *= 2;
            buckets[bucket_index] = (int*)realloc(buckets[bucket_index], 
                                                bucket_capacities[bucket_index] * sizeof(int));
        }
        
        buckets[bucket_index][bucket_sizes[bucket_index]++] = arr[i];
    }
    
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        if (bucket_sizes[i] > 0) {
            insertion_sort(buckets[i], bucket_sizes[i]);
            for (int j = 0; j < bucket_sizes[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
    }
    
    for (int i = 0; i < bucket_count; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucket_sizes);
    free(bucket_capacities);
}

// 基数排序
int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void counting_sort_for_radix(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
}

void radix_sort(int arr[], int n) {
    int max = get_max(arr, n);
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort_for_radix(arr, n, exp);
    }
}