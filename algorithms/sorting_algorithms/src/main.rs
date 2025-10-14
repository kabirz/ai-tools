use std::time::Instant;

fn main() {
    println!("排序算法性能测试");
    println!("==================");
    
    let sizes = vec![1000, 5000, 10000];
    
    for &size in &sizes {
        println!("\n数组大小: {}", size);
        println!("------------");
        
        // 随机数组测试
        let mut random_arr = generate_random_array(size, 1, 10000);
        let mut arr_copy = random_arr.clone();
        
        println!("随机数组:");
        test_sort("冒泡排序", &mut random_arr, bubble_sort);
        test_sort("选择排序", &mut arr_copy, selection_sort);
        
        random_arr = generate_random_array(size, 1, 10000);
        arr_copy = random_arr.clone();
        test_sort("插入排序", &mut random_arr, insertion_sort);
        test_sort("希尔排序", &mut arr_copy, shell_sort);
        
        random_arr = generate_random_array(size, 1, 10000);
        arr_copy = random_arr.clone();
        test_sort("归并排序", &mut random_arr, merge_sort);
        test_sort("快速排序", &mut arr_copy, quick_sort);
        
        random_arr = generate_random_array(size, 1, 10000);
        arr_copy = random_arr.clone();
        test_sort("堆排序", &mut random_arr, heap_sort);
        test_sort("计数排序", &mut arr_copy, counting_sort);
        
        // 已排序数组测试
        let mut sorted_arr = generate_sorted_array(size, true);
        let mut arr_copy = sorted_arr.clone();
        
        println!("已排序数组:");
        test_sort("冒泡排序", &mut sorted_arr, bubble_sort);
        test_sort("插入排序", &mut arr_copy, insertion_sort);
        
        // 逆序数组测试
        let mut reverse_arr = generate_sorted_array(size, false);
        let mut arr_copy = reverse_arr.clone();
        
        println!("逆序数组:");
        test_sort("冒泡排序", &mut reverse_arr, bubble_sort);
        test_sort("快速排序", &mut arr_copy, quick_sort);
    }
}

fn test_sort<T: Copy, F>(name: &str, arr: &mut [T], sort_fn: F)
where
    F: FnOnce(&mut [T]),
{
    let start = Instant::now();
    sort_fn(arr);
    let duration = start.elapsed();
    
    println!("  {}: {:?}", name, duration);
}

// 复制lib.rs中的排序算法实现到main.rs中
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