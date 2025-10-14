"""
基数排序 (Radix Sort)

算法原理：
按照位数进行排序，从最低位开始，依次对每一位进行稳定排序（通常使用计数排序）。
适用于整数或字符串排序。

时间复杂度：
- 最好情况：O(d * (n + k))，其中d是位数，k是基数（通常为10）
- 平均情况：O(d * (n + k))
- 最坏情况：O(d * (n + k))

空间复杂度：O(n + k) - 需要额外的空间来存储中间结果

稳定性：稳定
"""


def radix_sort(arr):
    """
    基数排序实现（支持负数）
    
    参数：
        arr: 待排序的列表（整数）
        
    返回：
        排序后的列表
    """
    if not arr:
        return arr
    
    # 将负数和非负数分开处理
    negative = [x for x in arr if x < 0]
    non_negative = [x for x in arr if x >= 0]
    
    # 对负数的绝对值进行基数排序，然后反转
    if negative:
        negative = [-x for x in negative]
        _radix_sort_helper(negative)
        negative = [-x for x in reversed(negative)]
    
    # 对非负数进行基数排序
    if non_negative:
        _radix_sort_helper(non_negative)
    
    # 合并结果
    result = negative + non_negative
    
    # 将结果复制回原数组
    for i in range(len(arr)):
        arr[i] = result[i]
    
    return arr


def _radix_sort_helper(arr):
    """
    基数排序辅助函数（仅处理非负整数）
    
    参数：
        arr: 待排序的非负整数列表
    """
    if not arr:
        return
    
    # 找到最大值以确定位数
    max_val = max(arr)
    
    # 从个位开始，对每一位进行计数排序
    exp = 1
    while max_val // exp > 0:
        _counting_sort_by_digit(arr, exp)
        exp *= 10


def _counting_sort_by_digit(arr, exp):
    """
    按照指定位数进行计数排序
    
    参数：
        arr: 待排序的列表
        exp: 当前位数（1表示个位，10表示十位，以此类推）
    """
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    
    # 统计每个数字在当前位上的出现次数
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1
    
    # 修改计数数组，使其存储累计次数
    for i in range(1, 10):
        count[i] += count[i - 1]
    
    # 从后向前构建输出数组，保证稳定性
    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1
    
    # 将排序后的结果复制回原数组
    for i in range(n):
        arr[i] = output[i]


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [170, 45, 75, 90, 802, 24, 2, 66],
        [5, 2, 8, 1, 9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [-5, -10, 0, -3, 8, 5, -1, 10],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = radix_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
