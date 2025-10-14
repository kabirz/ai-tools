"""
桶排序 (Bucket Sort)

算法原理：
将数组元素分配到有限数量的桶中，每个桶内部进行排序（可以使用其他排序算法），
然后按顺序合并所有桶中的元素。

时间复杂度：
- 最好情况：O(n + k)，其中k是桶的数量
- 平均情况：O(n + k)
- 最坏情况：O(n²) - 当所有元素都落入同一个桶时

空间复杂度：O(n + k) - 需要额外的桶空间

稳定性：取决于桶内排序算法是否稳定
"""


def bucket_sort(arr, bucket_count=10):
    """
    桶排序实现
    
    参数：
        arr: 待排序的列表（数值类型）
        bucket_count: 桶的数量
        
    返回：
        排序后的列表
    """
    if not arr or len(arr) <= 1:
        return arr
    
    # 找到数组中的最大值和最小值
    min_val = min(arr)
    max_val = max(arr)
    
    # 如果所有元素相同，直接返回
    if min_val == max_val:
        return arr
    
    # 计算每个桶的范围
    bucket_range = (max_val - min_val) / bucket_count
    
    # 创建桶
    buckets = [[] for _ in range(bucket_count)]
    
    # 将元素分配到各个桶中
    for num in arr:
        # 计算元素应该放入哪个桶
        # 特殊处理最大值，防止索引越界
        if num == max_val:
            index = bucket_count - 1
        else:
            index = int((num - min_val) / bucket_range)
        buckets[index].append(num)
    
    # 对每个桶内的元素进行排序（使用插入排序）
    for bucket in buckets:
        _insertion_sort(bucket)
    
    # 合并所有桶中的元素
    result = []
    for bucket in buckets:
        result.extend(bucket)
    
    # 将结果复制回原数组
    for i in range(len(arr)):
        arr[i] = result[i]
    
    return arr


def _insertion_sort(arr):
    """
    插入排序辅助函数（用于桶内排序）
    
    参数：
        arr: 待排序的列表
    """
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


if __name__ == "__main__":
    # 测试示例
    test_arrays = [
        [0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434],
        [5.5, 2.2, 8.8, 1.1, 9.9],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
        [10, 20, 30, 40, 50],
        [-5, -10, 0, -3, 8, 5, -1, 10],
        []
    ]
    
    for arr in test_arrays:
        print(f"原始数组: {arr}")
        sorted_arr = bucket_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
