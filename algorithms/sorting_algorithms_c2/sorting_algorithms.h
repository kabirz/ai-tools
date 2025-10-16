#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void shell_sort(int arr[], int n);
void merge_sort(int arr[], int l, int r);
void quick_sort(int arr[], int low, int high);
void heap_sort(int arr[], int n);
void counting_sort(int arr[], int n, int max_val);
void bucket_sort(int arr[], int n, int bucket_count);
void radix_sort(int arr[], int n);

#endif // SORTING_ALGORITHMS_H