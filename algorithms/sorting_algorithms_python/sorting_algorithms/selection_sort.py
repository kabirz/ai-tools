"""
选择排序 (Selection Sort)

算法原理：
首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置。
然后，再从剩余未排序元素中继续寻找最小（大）元素，放到已排序序列的末尾。
重复这个过程，直到所有元素均排序完毕。

时间复杂度：
- 最好情况：O(n²)
- 平均情况：O(n²)
- 最坏情况：O(n²)

空间复杂度：O(1) - 只需要常数级别的额外空间

稳定性：不稳定（相同元素的相对位置可能改变）
"""


def selection_sort(arr):
    """
    选择排序实现
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    n = len(arr)
    
    # 外层循环：确定第 i 个位置的元素
    for i in range(n - 1):
        # 假设当前位置 i 是未排序部分的最小值
        min_idx = i
        
        # 内层循环：在未排序部分找到真正的最小值
        for j in range(i + 1, n):
            if arr[j] < arr[min_idx]:
                min_idx = j
        
        # 将找到的最小值与第 i 个位置交换
        # 只有当最小值不在当前位置时才交换
        if min_idx != i:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
    
    return arr


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [64, 25, 12, 22, 11],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = selection_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
