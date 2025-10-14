"""
快速排序 (Quick Sort)

算法原理：
通过选择一个"基准"元素，将数组分为两个子数组：
- 小于基准的元素放在左边
- 大于基准的元素放在右边
然后递归地对左右子数组进行快速排序。

时间复杂度：
- 最好情况：O(n log n) - 每次分区都均匀
- 平均情况：O(n log n)
- 最坏情况：O(n²) - 当数组已排序或逆序，每次只能分出一个元素

空间复杂度：O(log n) - 递归调用栈的深度

稳定性：不稳定
"""


def quick_sort(arr):
    """
    快速排序实现（主函数）
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    _quick_sort_helper(arr, 0, len(arr) - 1)
    return arr


def _quick_sort_helper(arr, low, high):
    """
    快速排序的递归辅助函数
    
    参数：
        arr: 待排序的列表
        low: 起始索引
        high: 结束索引
    """
    if low < high:
        # 获取分区点的索引
        pivot_index = _partition(arr, low, high)
        
        # 递归排序左半部分
        _quick_sort_helper(arr, low, pivot_index - 1)
        
        # 递归排序右半部分
        _quick_sort_helper(arr, pivot_index + 1, high)


def _partition(arr, low, high):
    """
    分区函数：选择基准元素，将数组分为两部分
    
    参数：
        arr: 待排序的列表
        low: 起始索引
        high: 结束索引
        
    返回：
        基准元素最终的位置索引
    """
    # 选择最后一个元素作为基准
    pivot = arr[high]
    
    # i 指向小于基准的区域的最后一个元素
    i = low - 1
    
    # 遍历 [low, high-1] 范围
    for j in range(low, high):
        # 如果当前元素小于等于基准
        if arr[j] <= pivot:
            i += 1
            # 将当前元素交换到小于基准的区域
            arr[i], arr[j] = arr[j], arr[i]
    
    # 将基准元素放到正确的位置
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    
    return i + 1


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [10, 7, 8, 9, 1, 5],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = quick_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
