#include "sorting_algorithms.h"

// 冒泡排序
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_int(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
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
        if (min_idx != i) {
            swap_int(&arr[i], &arr[min_idx]);
        }
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
void merge_sort(int arr[], int n) {
    merge_sort_helper(arr, 0, n - 1);
}

void merge_sort_helper(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, left, mid);
        merge_sort_helper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    
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
    
    free(L);
    free(R);
}

// 快速排序
void quick_sort(int arr[], int n) {
    quick_sort_helper(arr, 0, n - 1);
}

void quick_sort_helper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap_int(&arr[i], &arr[j]);
        }
    }
    swap_int(&arr[i + 1], &arr[high]);
    return i + 1;
}

// 堆排序
void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; i--) {
        swap_int(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap_int(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 计数排序
void counting_sort(int arr[], int n) {
    if (n == 0) return;
    
    int max = arr[0];
    int min = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    
    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));
    
    for (int i = 0; i < n; i++) {
        count[arr[i] - min]++;
    }
    
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    
    int* output = (int*)malloc(n * sizeof(int));
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(count);
    free(output);
}

// 桶排序
void bucket_sort(float arr[], int n) {
    if (n == 0) return;
    
    // 找到最大值和最小值
    float max = arr[0];
    float min = arr[0];
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    
    if (max == min) return;
    
    // 创建桶
    int bucket_count = n;
    float** buckets = (float**)malloc(bucket_count * sizeof(float*));
    int* bucket_sizes = (int*)calloc(bucket_count, sizeof(int));
    int* bucket_capacities = (int*)malloc(bucket_count * sizeof(int));
    
    for (int i = 0; i < bucket_count; i++) {
        buckets[i] = (float*)malloc(2 * sizeof(float));
        bucket_capacities[i] = 2;
    }
    
    // 将元素分配到桶中
    for (int i = 0; i < n; i++) {
        int index = (int)((arr[i] - min) / (max - min) * (bucket_count - 1));
        
        if (bucket_sizes[index] == bucket_capacities[index]) {
            bucket_capacities[index] *= 2;
            buckets[index] = (float*)realloc(buckets[index], bucket_capacities[index] * sizeof(float));
        }
        
        buckets[index][bucket_sizes[index]++] = arr[i];
    }
    
    // 对每个桶进行排序（使用插入排序）
    for (int i = 0; i < bucket_count; i++) {
        if (bucket_sizes[i] > 0) {
            for (int j = 1; j < bucket_sizes[i]; j++) {
                float key = buckets[i][j];
                int k = j - 1;
                while (k >= 0 && buckets[i][k] > key) {
                    buckets[i][k + 1] = buckets[i][k];
                    k--;
                }
                buckets[i][k + 1] = key;
            }
        }
    }
    
    // 合并桶
    int index = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    
    free(buckets);
    free(bucket_sizes);
    free(bucket_capacities);
}

// 基数排序
void radix_sort(unsigned int arr[], int n) {
    if (n == 0) return;
    
    // 找到最大数
    unsigned int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    
    // 对每个位数进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort_by_digit(arr, n, exp);
    }
}

void counting_sort_by_digit(unsigned int arr[], int n, int exp) {
    unsigned int* output = (unsigned int*)malloc(n * sizeof(unsigned int));
    int count[10] = {0};
    
    // 统计当前位数的出现次数
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    // 计算累积计数
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // 构建输出数组
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    // 复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
}

// 辅助函数
int* generate_random_array(int size, int min, int max) {
    int* arr = (int*)malloc(size * sizeof(int));
    srand(time(NULL));
    
    for (int i = 0; i < size; i++) {
        arr[i] = min + rand() % (max - min + 1);
    }
    
    return arr;
}

int* generate_sorted_array(int size, bool ascending) {
    int* arr = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    
    if (!ascending) {
        for (int i = 0; i < size / 2; i++) {
            swap_int(&arr[i], &arr[size - 1 - i]);
        }
    }
    
    return arr;
}

bool is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

bool is_sorted_float(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_float_array(float arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_float(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}