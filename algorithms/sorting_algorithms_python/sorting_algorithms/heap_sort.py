"""
堆排序 (Heap Sort)

算法原理：
利用堆这种数据结构进行排序：
1. 将待排序数组构建成一个最大堆
2. 将堆顶元素（最大值）与末尾元素交换
3. 将剩余元素重新调整为最大堆
4. 重复步骤2-3，直到所有元素排序完成

时间复杂度：
- 最好情况：O(n log n)
- 平均情况：O(n log n)
- 最坏情况：O(n log n)

空间复杂度：O(1) - 只需要常数级别的额外空间

稳定性：不稳定
"""


def heap_sort(arr):
    """
    堆排序实现
    
    参数：
        arr: 待排序的列表
        
    返回：
        排序后的列表（原地排序）
    """
    if not arr:
        return arr
    
    n = len(arr)
    
    # 构建最大堆
    # 从最后一个非叶子节点开始，自底向上调整
    for i in range(n // 2 - 1, -1, -1):
        _heapify(arr, n, i)
    
    # 一个个从堆中取出元素
    for i in range(n - 1, 0, -1):
        # 将当前最大值（堆顶）移到数组末尾
        arr[0], arr[i] = arr[i], arr[0]
        
        # 对剩余元素重新调整为最大堆
        _heapify(arr, i, 0)
    
    return arr


def _heapify(arr, n, i):
    """
    调整堆，使以 i 为根的子树满足最大堆的性质
    
    参数：
        arr: 待调整的列表
        n: 堆的大小
        i: 当前节点的索引
    """
    largest = i  # 初始化最大值为根节点
    left = 2 * i + 1  # 左子节点
    right = 2 * i + 2  # 右子节点
    
    # 如果左子节点存在且大于根节点
    if left < n and arr[left] > arr[largest]:
        largest = left
    
    # 如果右子节点存在且大于当前最大值
    if right < n and arr[right] > arr[largest]:
        largest = right
    
    # 如果最大值不是根节点
    if largest != i:
        # 交换根节点和最大值
        arr[i], arr[largest] = arr[largest], arr[i]
        
        # 递归调整受影响的子树
        _heapify(arr, n, largest)


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
        sorted_arr = heap_sort(arr.copy())
        print(f"排序后: {sorted_arr}\n")
