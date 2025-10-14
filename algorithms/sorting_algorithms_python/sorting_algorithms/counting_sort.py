"""
计数排序 (Counting Sort)

算法原理：
不基于比较的排序算法。统计每个元素出现的次数，然后根据计数信息将元素放到正确的位置。
适用于元素范围不大的整数排序。

时间复杂度：
- 最好情况：O(n + k)，其中k是数据范围
- 平均情况：O(n + k)
- 最坏情况：O(n + k)

空间复杂度：O(n + k) - 需要额外的计数数组和输出数组

稳定性：稳定
"""


def counting_sort(arr):
    """
    计数排序实现（支持负数）
    
    参数：
        arr: 待排序的列表（整数）
        
    返回：
        排序后的列表
    """
    if not arr:
        return arr
    
    # 找到数组中的最大值和最小值
    max_val = max(arr)
    min_val = min(arr)
    
    # 计算数据范围
    range_size = max_val - min_val + 1
    
    # 创建计数数组
    count = [0] * range_size
    
    # 统计每个元素出现的次数
    for num in arr:
        count[num - min_val] += 1
    
    # 修改计数数组，使其存储累计次数
    for i in range(1, range_size):
        count[i] += count[i - 1]
    
    # 创建输出数组
    output = [0] * len(arr)
    
    # 从后向前遍历原数组，保证稳定性
    for i in range(len(arr) - 1, -1, -1):
        num = arr[i]
        index = count[num - min_val] - 1
        output[index] = num
        count[num - min_val] -= 1
    
    # 将排序后的结果复制回原数组
    for i in range(len(arr)):
        arr[i] = output[i]
    
    return arr


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [4, 2, 2, 8, 3, 3, 1],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [-5, -10, 0, -3, 8, 5, -1, 10],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = counting_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
