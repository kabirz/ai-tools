use sorting_algorithms::*;

#[test]
fn test_bubble_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    bubble_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_selection_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    selection_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_insertion_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    insertion_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_shell_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    shell_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_merge_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    merge_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_quick_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    quick_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_heap_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    heap_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_counting_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    counting_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_bucket_sort() {
    let mut arr = vec![0.64, 0.34, 0.25, 0.12, 0.22, 0.11, 0.90];
    bucket_sort(&mut arr);
    assert!(is_sorted_float(&arr));
    assert_eq!(arr, vec![0.11, 0.12, 0.22, 0.25, 0.34, 0.64, 0.90]);
}

#[test]
fn test_radix_sort() {
    let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
    radix_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, vec![11, 12, 22, 25, 34, 64, 90]);
}

#[test]
fn test_empty_array() {
    let mut empty_arr: Vec<i32> = vec![];
    bubble_sort(&mut empty_arr);
    assert!(is_sorted(&empty_arr));
    assert_eq!(empty_arr, vec![]);
    
    let mut empty_arr: Vec<i32> = vec![];
    quick_sort(&mut empty_arr);
    assert!(is_sorted(&empty_arr));
    assert_eq!(empty_arr, vec![]);
}

#[test]
fn test_single_element() {
    let mut single_arr = vec![42];
    bubble_sort(&mut single_arr);
    assert!(is_sorted(&single_arr));
    assert_eq!(single_arr, vec![42]);
    
    let mut single_arr = vec![42];
    quick_sort(&mut single_arr);
    assert!(is_sorted(&single_arr));
    assert_eq!(single_arr, vec![42]);
}

#[test]
fn test_already_sorted() {
    let mut sorted_arr = vec![1, 2, 3, 4, 5, 6, 7];
    bubble_sort(&mut sorted_arr);
    assert!(is_sorted(&sorted_arr));
    assert_eq!(sorted_arr, vec![1, 2, 3, 4, 5, 6, 7]);
    
    let mut sorted_arr = vec![1, 2, 3, 4, 5, 6, 7];
    quick_sort(&mut sorted_arr);
    assert!(is_sorted(&sorted_arr));
    assert_eq!(sorted_arr, vec![1, 2, 3, 4, 5, 6, 7]);
}

#[test]
fn test_reverse_sorted() {
    let mut reverse_arr = vec![7, 6, 5, 4, 3, 2, 1];
    bubble_sort(&mut reverse_arr);
    assert!(is_sorted(&reverse_arr));
    assert_eq!(reverse_arr, vec![1, 2, 3, 4, 5, 6, 7]);
    
    let mut reverse_arr = vec![7, 6, 5, 4, 3, 2, 1];
    quick_sort(&mut reverse_arr);
    assert!(is_sorted(&reverse_arr));
    assert_eq!(reverse_arr, vec![1, 2, 3, 4, 5, 6, 7]);
}

#[test]
fn test_duplicate_elements() {
    let mut dup_arr = vec![5, 2, 8, 2, 9, 5, 6];
    bubble_sort(&mut dup_arr);
    assert!(is_sorted(&dup_arr));
    assert_eq!(dup_arr, vec![2, 2, 5, 5, 6, 8, 9]);
    
    let mut dup_arr = vec![5, 2, 8, 2, 9, 5, 6];
    quick_sort(&mut dup_arr);
    assert!(is_sorted(&dup_arr));
    assert_eq!(dup_arr, vec![2, 2, 5, 5, 6, 8, 9]);
}

#[test]
fn test_random_arrays() {
    for i in 0..10 {
        let size = (i * 10 + 5) % 100 + 1;
        let mut arr = generate_random_array(size, -1000, 1000);
        let mut expected = arr.clone();
        expected.sort();
        
        bubble_sort(&mut arr);
        assert!(is_sorted(&arr));
        assert_eq!(arr, expected);
    }
}

#[test]
fn test_large_array() {
    let mut arr = generate_random_array(1000, 1, 10000);
    let mut expected = arr.clone();
    expected.sort();
    
    quick_sort(&mut arr);
    assert!(is_sorted(&arr));
    assert_eq!(arr, expected);
}