"""
归并排序 (Merge Sort)

算法原理：
采用分治法的典型应用：
1. 分解：将数组分成两半
2. 解决：递归地对两半进行排序
3. 合并：将两个已排序的子数组合并成一个有序数组

时间复杂度：
- 最好情况：O(n log n)
- 平均情况：O(n log n)
- 最坏情况：O(n log n)

空间复杂度：O(n) - 需要额外的数组空间来合并

稳定性：稳定
"""


def merge_sort(arr):
    """
    归并排序实现（主函数）
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    _merge_sort_helper(arr, 0, len(arr) - 1)
    return arr


def _merge_sort_helper(arr, left, right):
    """
    归并排序的递归辅助函数
    
    参数：
        arr: 待排序的列表
        left: 起始索引
        right: 结束索引
    """
    if left < right:
        # 找到中间点，避免溢出
        mid = left + (right - left) // 2
        
        # 递归排序左半部分
        _merge_sort_helper(arr, left, mid)
        
        # 递归排序右半部分
        _merge_sort_helper(arr, mid + 1, right)
        
        # 合并两个已排序的部分
        _merge(arr, left, mid, right)


def _merge(arr, left, mid, right):
    """
    合并两个已排序的子数组
    
    参数：
        arr: 待排序的列表
        left: 左子数组的起始索引
        mid: 左子数组的结束索引
        right: 右子数组的结束索引
    """
    # 创建临时数组来存储左右两部分
    left_part = arr[left:mid + 1]
    right_part = arr[mid + 1:right + 1]
    
    # 初始化三个指针
    i = 0  # 左子数组的索引
    j = 0  # 右子数组的索引
    k = left  # 合并后数组的索引
    
    # 比较左右子数组的元素，将较小的放入原数组
    while i < len(left_part) and j < len(right_part):
        if left_part[i] <= right_part[j]:
            arr[k] = left_part[i]
            i += 1
        else:
            arr[k] = right_part[j]
            j += 1
        k += 1
    
    # 将左子数组剩余的元素复制到原数组
    while i < len(left_part):
        arr[k] = left_part[i]
        i += 1
        k += 1
    
    # 将右子数组剩余的元素复制到原数组
    while j < len(right_part):
        arr[k] = right_part[j]
        j += 1
        k += 1


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [12, 11, 13, 5, 6, 7],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = merge_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
