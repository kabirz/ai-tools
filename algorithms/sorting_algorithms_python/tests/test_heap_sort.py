"""
测试 Heap Sort 算法
"""

import pytest
from sorting_algorithms.heap_sort import heap_sort


class TestHeapSort:
    """测试 Heap Sort 的各种情况"""
    
    def test_empty_array(self):
        """测试空数组"""
        arr = []
        result = heap_sort(arr)
        assert result == []
    
    def test_single_element(self):
        """测试单元素数组"""
        arr = [42]
        result = heap_sort(arr)
        assert result == [42]
    
    def test_already_sorted(self):
        """测试已排序数组"""
        arr = [1, 2, 3, 4, 5]
        result = heap_sort(arr)
        assert result == [1, 2, 3, 4, 5]
    
    def test_reverse_sorted(self):
        """测试逆序数组"""
        arr = [5, 4, 3, 2, 1]
        result = heap_sort(arr)
        assert result == [1, 2, 3, 4, 5]
    
    def test_duplicates(self):
        """测试包含重复元素的数组"""
        arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3]
        result = heap_sort(arr)
        assert result == [1, 1, 2, 3, 3, 4, 5, 5, 6, 9]
    
    def test_random_array(self):
        """测试随机数组"""
        arr = [64, 34, 25, 12, 22, 11, 90]
        result = heap_sort(arr)
        assert result == [11, 12, 22, 25, 34, 64, 90]
    
    def test_negative_numbers(self):
        """测试包含负数的数组"""
        arr = [-5, -10, 0, -3, 8, 5, -1, 10]
        result = heap_sort(arr)
        assert result == [-10, -5, -3, -1, 0, 5, 8, 10]
    
    def test_all_same(self):
        """测试所有元素相同的数组"""
        arr = [7, 7, 7, 7, 7]
        result = heap_sort(arr)
        assert result == [7, 7, 7, 7, 7]
    
    @pytest.mark.parametrize("test_input,expected", [
        ([3, 2, 1], [1, 2, 3]),
        ([10, -1, 2, 5, 0], [-1, 0, 2, 5, 10]),
        ([100], [100]),
        ([2, 2, 2], [2, 2, 2]),
    ])
    def test_parametrized(self, test_input, expected):
        """参数化测试"""
        result = heap_sort(test_input.copy())
        assert result == expected
    
    def test_maintains_list(self):
        """测试是否修改了原列表（原地排序）"""
        arr = [3, 1, 4, 1, 5]
        original_id = id(arr)
        result = heap_sort(arr)
        # 检查返回的是同一个列表对象
        assert id(result) == original_id
        assert result == [1, 1, 3, 4, 5]
