#include "../include/sorting_algorithms.h"
#include <vector>
#include <algorithm>

namespace sorting {

// 1. 冒泡排序
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 2. 选择排序
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
}

// 3. 插入排序
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 4. 快速排序辅助函数
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
}

// 5. 归并排序辅助函数
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSortHelper(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(std::vector<int>& arr) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
}

// 6. 堆排序辅助函数
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 7. 计数排序
void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int max_val = *std::max_element(arr.begin(), arr.end());
    int min_val = *std::min_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;
    
    std::vector<int> count(range, 0);
    std::vector<int> output(arr.size());
    
    for (int num : arr) {
        count[num - min_val]++;
    }
    
    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i] - min_val] - 1] = arr[i];
        count[arr[i] - min_val]--;
    }
    
    arr = output;
}

// 8. 基数排序
void countingSortForRadix(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = {0};
    
    for (int i = 0; i < n; ++i) {
        int digit = abs((arr[i] / exp) % 10);
        count[digit]++;
    }
    
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; --i) {
        int digit = abs((arr[i] / exp) % 10);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    
    arr = output;
}

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    // 分离正数和负数
    std::vector<int> positives, negatives;
    for (int num : arr) {
        if (num >= 0) {
            positives.push_back(num);
        } else {
            negatives.push_back(-num); // 转为正数
        }
    }
    
    // 对正数进行基数排序
    if (!positives.empty()) {
        int max_pos = *std::max_element(positives.begin(), positives.end());
        for (int exp = 1; max_pos / exp > 0; exp *= 10) {
            countingSortForRadix(positives, exp);
        }
    }
    
    // 对负数进行基数排序（先转为正数排序，再反转）
    if (!negatives.empty()) {
        int max_neg = *std::max_element(negatives.begin(), negatives.end());
        for (int exp = 1; max_neg / exp > 0; exp *= 10) {
            countingSortForRadix(negatives, exp);
        }
    }
    
    // 合并结果：负数部分（反转并变回负数）+ 正数部分
    arr.clear();
    for (auto it = negatives.rbegin(); it != negatives.rend(); ++it) {
        arr.push_back(-(*it));
    }
    for (int num : positives) {
        arr.push_back(num);
    }
}

// 9. 希尔排序
void shellSort(std::vector<int>& arr) {
    int n = arr.size();
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 10. 桶排序
void bucketSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int min_val = *std::min_element(arr.begin(), arr.end());
    int max_val = *std::max_element(arr.begin(), arr.end());
    
    int bucket_count = arr.size();
    std::vector<std::vector<int>> buckets(bucket_count);
    
    int range = max_val - min_val;
    if (range == 0) return;
    
    for (int num : arr) {
        int index = (num - min_val) * (bucket_count - 1) / range;
        buckets[index].push_back(num);
    }
    
    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end());
    }
    
    int index = 0;
    for (const auto& bucket : buckets) {
        for (int num : bucket) {
            arr[index++] = num;
        }
    }
}

// 辅助函数
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

} // namespace sorting