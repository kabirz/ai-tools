"""
Pytest 配置文件
定义通用的测试数据和fixture
"""

import pytest


# 通用测试数据集
@pytest.fixture
def test_data_basic():
    """基础测试数据集"""
    return {
        'empty': [],
        'single': [42],
        'sorted': [1, 2, 3, 4, 5],
        'reverse': [5, 4, 3, 2, 1],
        'duplicates': [3, 1, 4, 1, 5, 9, 2, 6, 5, 3],
        'random': [64, 34, 25, 12, 22, 11, 90],
        'with_negatives': [-5, -10, 0, -3, 8, 5, -1, 10],
        'all_same': [7, 7, 7, 7, 7],
    }


@pytest.fixture
def expected_results():
    """期望的排序结果"""
    return {
        'empty': [],
        'single': [42],
        'sorted': [1, 2, 3, 4, 5],
        'reverse': [1, 2, 3, 4, 5],
        'duplicates': [1, 1, 2, 3, 3, 4, 5, 5, 6, 9],
        'random': [11, 12, 22, 25, 34, 64, 90],
        'with_negatives': [-10, -5, -3, -1, 0, 5, 8, 10],
        'all_same': [7, 7, 7, 7, 7],
    }
