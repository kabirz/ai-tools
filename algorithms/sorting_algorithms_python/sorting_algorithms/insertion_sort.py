"""
插入排序 (Insertion Sort)

算法原理：
通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
类似于打扑克牌时整理手牌的过程。

时间复杂度：
- 最好情况：O(n) - 当数组已经有序时
- 平均情况：O(n²)
- 最坏情况：O(n²) - 当数组逆序时

空间复杂度：O(1) - 只需要常数级别的额外空间

稳定性：稳定
"""


def insertion_sort(arr):
    """
    插入排序实现
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    n = len(arr)
    
    # 从第二个元素开始，将每个元素插入到前面已排序的序列中
    for i in range(1, n):
        # 当前要插入的元素
        key = arr[i]
        
        # j 指向已排序序列的最后一个元素
        j = i - 1
        
        # 将大于 key 的元素向后移动一位
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        
        # 将 key 插入到正确的位置
        arr[j + 1] = key
    
    return arr


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [12, 11, 13, 5, 6],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = insertion_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
