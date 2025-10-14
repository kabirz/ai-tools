#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// 冒泡排序
void bubble_sort(int arr[], int n);

// 选择排序
void selection_sort(int arr[], int n);

// 插入排序
void insertion_sort(int arr[], int n);

// 希尔排序
void shell_sort(int arr[], int n);

// 归并排序
void merge_sort(int arr[], int n);
void merge_sort_helper(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

// 快速排序
void quick_sort(int arr[], int n);
void quick_sort_helper(int arr[], int low, int high);
int partition(int arr[], int low, int high);

// 堆排序
void heap_sort(int arr[], int n);
void heapify(int arr[], int n, int i);

// 计数排序
void counting_sort(int arr[], int n);

// 桶排序
void bucket_sort(float arr[], int n);

// 基数排序
void radix_sort(unsigned int arr[], int n);
void counting_sort_by_digit(unsigned int arr[], int n, int exp);

// 辅助函数
int* generate_random_array(int size, int min, int max);
int* generate_sorted_array(int size, bool ascending);
bool is_sorted(int arr[], int n);
bool is_sorted_float(float arr[], int n);
void print_array(int arr[], int n);
void print_float_array(float arr[], int n);
void swap_int(int* a, int* b);
void swap_float(float* a, float* b);

#endif // SORTING_ALGORITHMS_H