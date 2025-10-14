use rand::Rng;

/// 冒泡排序
pub fn bubble_sort<T: Ord + Copy>(arr: &mut [T]) {
    let n = arr.len();
    for i in 0..n {
        let mut swapped = false;
        for j in 0..n - i - 1 {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
                swapped = true;
            }
        }
        if !swapped {
            break;
        }
    }
}

/// 选择排序
pub fn selection_sort<T: Ord + Copy>(arr: &mut [T]) {
    let n = arr.len();
    for i in 0..n {
        let mut min_idx = i;
        for j in i + 1..n {
            if arr[j] < arr[min_idx] {
                min_idx = j;
            }
        }
        if min_idx != i {
            arr.swap(i, min_idx);
        }
    }
}

/// 插入排序
pub fn insertion_sort<T: Ord + Copy>(arr: &mut [T]) {
    let n = arr.len();
    for i in 1..n {
        let key = arr[i];
        let mut j = i;
        while j > 0 && arr[j - 1] > key {
            arr[j] = arr[j - 1];
            j -= 1;
        }
        arr[j] = key;
    }
}

/// 希尔排序
pub fn shell_sort<T: Ord + Copy>(arr: &mut [T]) {
    let n = arr.len();
    let mut gap = n / 2;
    
    while gap > 0 {
        for i in gap..n {
            let temp = arr[i];
            let mut j = i;
            while j >= gap && arr[j - gap] > temp {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}

/// 归并排序
pub fn merge_sort<T: Ord + Copy>(arr: &mut [T]) {
    if arr.len() <= 1 {
        return;
    }
    
    let mid = arr.len() / 2;
    merge_sort(&mut arr[..mid]);
    merge_sort(&mut arr[mid..]);
    
    let mut temp = vec![arr[0]; arr.len()];
    let mut i = 0;
    let mut j = mid;
    let mut k = 0;
    
    while i < mid && j < arr.len() {
        if arr[i] <= arr[j] {
            temp[k] = arr[i];
            i += 1;
        } else {
            temp[k] = arr[j];
            j += 1;
        }
        k += 1;
    }
    
    while i < mid {
        temp[k] = arr[i];
        i += 1;
        k += 1;
    }
    
    while j < arr.len() {
        temp[k] = arr[j];
        j += 1;
        k += 1;
    }
    
    arr.copy_from_slice(&temp);
}

/// 快速排序
pub fn quick_sort<T: Ord + Copy>(arr: &mut [T]) {
    if arr.len() <= 1 {
        return;
    }
    
    quick_sort_helper(arr, 0, arr.len() - 1);
}

fn quick_sort_helper<T: Ord + Copy>(arr: &mut [T], low: usize, high: usize) {
    if low < high {
        let pi = partition(arr, low, high);
        
        if pi > 0 {
            quick_sort_helper(arr, low, pi - 1);
        }
        quick_sort_helper(arr, pi + 1, high);
    }
}

fn partition<T: Ord + Copy>(arr: &mut [T], low: usize, high: usize) -> usize {
    let pivot = arr[high];
    let mut i = low;
    
    for j in low..high {
        if arr[j] < pivot {
            arr.swap(i, j);
            i += 1;
        }
    }
    
    arr.swap(i, high);
    i
}

/// 堆排序
pub fn heap_sort<T: Ord + Copy>(arr: &mut [T]) {
    let n = arr.len();
    
    // 构建最大堆
    for i in (0..n / 2).rev() {
        heapify(arr, n, i);
    }
    
    // 逐个提取元素
    for i in (1..n).rev() {
        arr.swap(0, i);
        heapify(arr, i, 0);
    }
}

fn heapify<T: Ord + Copy>(arr: &mut [T], n: usize, i: usize) {
    let mut largest = i;
    let left = 2 * i + 1;
    let right = 2 * i + 2;
    
    if left < n && arr[left] > arr[largest] {
        largest = left;
    }
    
    if right < n && arr[right] > arr[largest] {
        largest = right;
    }
    
    if largest != i {
        arr.swap(i, largest);
        heapify(arr, n, largest);
    }
}

/// 计数排序（仅适用于整数）
pub fn counting_sort(arr: &mut [i32]) {
    if arr.is_empty() {
        return;
    }
    
    let max = *arr.iter().max().unwrap();
    let min = *arr.iter().min().unwrap();
    let range = max - min + 1;
    
    let mut count = vec![0; range as usize];
    
    for &num in arr.iter() {
        count[(num - min) as usize] += 1;
    }
    
    let mut i = 0;
    for (num, &cnt) in count.iter().enumerate() {
        for _ in 0..cnt {
            arr[i] = num as i32 + min;
            i += 1;
        }
    }
}

/// 桶排序（仅适用于浮点数）
pub fn bucket_sort(arr: &mut [f32]) {
    if arr.is_empty() {
        return;
    }
    
    let n = arr.len();
    let max = *arr.iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    let min = *arr.iter().min_by(|a, b| a.partial_cmp(b).unwrap()).unwrap();
    
    if max == min {
        return;
    }
    
    let bucket_count = n;
    let mut buckets: Vec<Vec<f32>> = vec![Vec::new(); bucket_count];
    
    for &value in arr.iter() {
        let index = ((value - min) / (max - min) * (bucket_count - 1) as f32) as usize;
        buckets[index].push(value);
    }
    
    for bucket in &mut buckets {
        insertion_sort_float(bucket);
    }
    
    let mut index = 0;
    for bucket in &buckets {
        for &value in bucket {
            arr[index] = value;
            index += 1;
        }
    }
}

/// 专门用于浮点数的插入排序
fn insertion_sort_float(arr: &mut [f32]) {
    let n = arr.len();
    for i in 1..n {
        let key = arr[i];
        let mut j = i;
        while j > 0 && arr[j - 1] > key {
            arr[j] = arr[j - 1];
            j -= 1;
        }
        arr[j] = key;
    }
}

/// 基数排序（仅适用于正整数）
pub fn radix_sort(arr: &mut [u32]) {
    if arr.is_empty() {
        return;
    }
    
    let max = *arr.iter().max().unwrap();
    let mut exp = 1;
    
    while max / exp > 0 {
        counting_sort_by_digit(arr, exp);
        exp *= 10;
    }
}

fn counting_sort_by_digit(arr: &mut [u32], exp: u32) {
    let n = arr.len();
    let mut output = vec![0; n];
    let mut count = vec![0; 10];
    
    for &num in arr.iter() {
        let digit = (num / exp) % 10;
        count[digit as usize] += 1;
    }
    
    for i in 1..10 {
        count[i] += count[i - 1];
    }
    
    for i in (0..n).rev() {
        let digit = (arr[i] / exp) % 10;
        output[count[digit as usize] - 1] = arr[i];
        count[digit as usize] -= 1;
    }
    
    arr.copy_from_slice(&output);
}

/// 生成随机数组
pub fn generate_random_array(size: usize, min: i32, max: i32) -> Vec<i32> {
    let mut rng = rand::thread_rng();
    (0..size)
        .map(|_| rng.gen_range(min..=max))
        .collect()
}

/// 生成已排序数组
pub fn generate_sorted_array(size: usize, ascending: bool) -> Vec<i32> {
    let mut arr: Vec<i32> = (0..size as i32).collect();
    if !ascending {
        arr.reverse();
    }
    arr
}

/// 生成部分有序数组
pub fn generate_partially_sorted_array(size: usize, sorted_percentage: f32) -> Vec<i32> {
    let mut arr = generate_random_array(size, 1, 1000);
    let sorted_size = (size as f32 * sorted_percentage) as usize;
    
    if sorted_size > 0 {
        let mut sorted_part = arr[..sorted_size].to_vec();
        insertion_sort(&mut sorted_part);
        arr[..sorted_size].copy_from_slice(&sorted_part);
    }
    
    arr
}

/// 检查数组是否已排序
pub fn is_sorted<T: Ord>(arr: &[T]) -> bool {
    arr.windows(2).all(|w| w[0] <= w[1])
}

/// 检查浮点数数组是否已排序
pub fn is_sorted_float(arr: &[f32]) -> bool {
    arr.windows(2).all(|w| w[0] <= w[1])
}