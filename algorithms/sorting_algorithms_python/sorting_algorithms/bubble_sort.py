"""
冒泡排序 (Bubble Sort)

算法原理：
重复遍历要排序的数列，每次比较相邻的两个元素，如果它们的顺序错误就交换位置。
遍历数列的工作会重复进行，直到没有元素需要交换，说明数列已经完成排序。

时间复杂度：
- 最好情况：O(n) - 当数组已经有序时
- 平均情况：O(n²)
- 最坏情况：O(n²) - 当数组逆序时

空间复杂度：O(1) - 只需要常数级别的额外空间

稳定性：稳定
"""


def bubble_sort(arr):
    """
    冒泡排序实现
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    n = len(arr)
    
    # 外层循环：需要进行 n-1 轮比较
    for i in range(n - 1):
        # 标记本轮是否发生交换
        swapped = False
        
        # 内层循环：每轮将最大的元素"冒泡"到末尾
        # 每轮后，后面 i 个元素已经有序，无需再比较
        for j in range(n - 1 - i):
            # 如果前一个元素大于后一个元素，交换它们
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        
        # 如果本轮没有发生交换，说明数组已经有序，可以提前结束
        if not swapped:
            break
    
    return arr


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [64, 34, 25, 12, 22, 11, 90],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = bubble_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
