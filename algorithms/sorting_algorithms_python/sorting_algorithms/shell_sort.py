"""
希尔排序 (Shell Sort)

算法原理：
希尔排序是插入排序的改进版本。它通过将数组分成若干个子序列进行插入排序，
逐步减小间隔（gap），最后间隔为1时就是标准的插入排序。
这样可以让元素更快地移动到其最终位置。

时间复杂度：
- 最好情况：O(n log n)
- 平均情况：取决于间隔序列，通常为 O(n^1.3) 到 O(n^1.5)
- 最坏情况：O(n²)

空间复杂度：O(1) - 只需要常数级别的额外空间

稳定性：不稳定
"""


def shell_sort(arr):
    """
    希尔排序实现
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    n = len(arr)
    
    # 初始间隔设为数组长度的一半，然后逐步减小
    gap = n // 2
    
    # 当间隔大于0时继续排序
    while gap > 0:
        # 对每个间隔进行插入排序
        for i in range(gap, n):
            # 保存当前元素
            temp = arr[i]
            
            # 对间隔为gap的子序列进行插入排序
            j = i
            while j >= gap and arr[j - gap] > temp:
                arr[j] = arr[j - gap]
                j -= gap
            
            # 将temp插入到正确位置
            arr[j] = temp
        
        # 缩小间隔
        gap //= 2
    
    return arr


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [12, 34, 54, 2, 3],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = shell_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
