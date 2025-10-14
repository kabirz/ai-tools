# 排序算法集合

一个包含10种常见排序算法的Python实现，附带完整的测试用例和性能比较工具。

## 📋 项目简介

本项目实现了计算机科学中最常用的10种排序算法，每个算法都有：
- ✅ 详细的中文注释和文档
- ✅ 完整的单元测试（使用pytest）
- ✅ 时间和空间复杂度分析
- ✅ 独立的模块文件，便于学习和使用

## 🎯 包含的算法

### 1. 冒泡排序 (Bubble Sort)
- **文件**: `sorting_algorithms/bubble_sort.py`
- **特点**: 简单直观，相邻元素两两比较
- **适用场景**: 小规模数据，教学演示

### 2. 选择排序 (Selection Sort)
- **文件**: `sorting_algorithms/selection_sort.py`
- **特点**: 每次选择最小元素放到已排序序列末尾
- **适用场景**: 数据规模较小，交换次数少

### 3. 插入排序 (Insertion Sort)
- **文件**: `sorting_algorithms/insertion_sort.py`
- **特点**: 像整理扑克牌一样，逐个插入到正确位置
- **适用场景**: 小规模或近乎有序的数据

### 4. 快速排序 (Quick Sort)
- **文件**: `sorting_algorithms/quick_sort.py`
- **特点**: 分治法，选择基准元素进行分区
- **适用场景**: 通用场景，平均性能优秀

### 5. 归并排序 (Merge Sort)
- **文件**: `sorting_algorithms/merge_sort.py`
- **特点**: 分治法，稳定排序，性能稳定
- **适用场景**: 需要稳定排序，大规模数据

### 6. 堆排序 (Heap Sort)
- **文件**: `sorting_algorithms/heap_sort.py`
- **特点**: 利用堆数据结构，空间效率高
- **适用场景**: 空间受限，需要O(n log n)保证

### 7. 希尔排序 (Shell Sort)
- **文件**: `sorting_algorithms/shell_sort.py`
- **特点**: 插入排序的改进版，使用间隔序列
- **适用场景**: 中等规模数据

### 8. 计数排序 (Counting Sort)
- **文件**: `sorting_algorithms/counting_sort.py`
- **特点**: 非比较排序，适用于整数，支持负数
- **适用场景**: 整数排序，数据范围不大

### 9. 基数排序 (Radix Sort)
- **文件**: `sorting_algorithms/radix_sort.py`
- **特点**: 按位排序，支持负数
- **适用场景**: 整数或固定长度字符串

### 10. 桶排序 (Bucket Sort)
- **文件**: `sorting_algorithms/bucket_sort.py`
- **特点**: 将数据分配到多个桶中分别排序
- **适用场景**: 数据分布均匀时效率高

## 📊 复杂度对比表

| 算法 | 最好时间 | 平均时间 | 最坏时间 | 空间复杂度 | 稳定性 |
|------|----------|----------|----------|------------|--------|
| 冒泡排序 | O(n) | O(n²) | O(n²) | O(1) | ✓ |
| 选择排序 | O(n²) | O(n²) | O(n²) | O(1) | ✗ |
| 插入排序 | O(n) | O(n²) | O(n²) | O(1) | ✓ |
| 快速排序 | O(n log n) | O(n log n) | O(n²) | O(log n) | ✗ |
| 归并排序 | O(n log n) | O(n log n) | O(n log n) | O(n) | ✓ |
| 堆排序 | O(n log n) | O(n log n) | O(n log n) | O(1) | ✗ |
| 希尔排序 | O(n log n) | O(n^1.3) | O(n²) | O(1) | ✗ |
| 计数排序 | O(n+k) | O(n+k) | O(n+k) | O(n+k) | ✓ |
| 基数排序 | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | ✓ |
| 桶排序 | O(n+k) | O(n+k) | O(n²) | O(n+k) | ✓* |

*稳定性取决于桶内排序算法

## 🚀 安装与使用

### 前置要求

- Python 3.7+
- pytest（用于运行测试）

### 克隆项目

```bash
cd /Users/zhp/code/linux/ai/test2
```

### 安装依赖

```bash
pip install pytest
```

## 💻 使用方法

### 1. 列出所有算法

```bash
python3 main.py --list
```

### 2. 运行单个算法

```bash
# 使用快速排序对随机数组排序
python3 main.py --algo quick

# 使用冒泡排序对50个元素排序
python3 main.py --algo bubble --size 50

# 对自定义数组排序
python3 main.py --algo merge --custom 5 2 8 1 9
```

### 3. 比较所有算法性能

```bash
# 默认20个元素
python3 main.py --all

# 比较1000个元素的性能
python3 main.py --all --size 1000

# 显示排序前后的数组
python3 main.py --all --show-array
```

### 4. 在Python代码中使用

```python
from sorting_algorithms import quick_sort, merge_sort

# 使用快速排序
arr = [64, 34, 25, 12, 22, 11, 90]
sorted_arr = quick_sort(arr)
print(sorted_arr)  # [11, 12, 22, 25, 34, 64, 90]

# 使用归并排序
arr2 = [5, 2, 8, 1, 9]
sorted_arr2 = merge_sort(arr2)
print(sorted_arr2)  # [1, 2, 5, 8, 9]
```

## 🧪 运行测试

### 运行所有测试

```bash
pytest tests/
```

### 运行特定算法的测试

```bash
pytest tests/test_quick_sort.py
```

### 显示详细输出

```bash
pytest tests/ -v
```

### 查看测试覆盖率

```bash
pytest tests/ --cov=sorting_algorithms
```

## 📁 项目结构

```
test2/
├── sorting_algorithms/          # 排序算法包
│   ├── __init__.py             # 包初始化文件
│   ├── bubble_sort.py          # 冒泡排序
│   ├── selection_sort.py       # 选择排序
│   ├── insertion_sort.py       # 插入排序
│   ├── quick_sort.py           # 快速排序
│   ├── merge_sort.py           # 归并排序
│   ├── heap_sort.py            # 堆排序
│   ├── shell_sort.py           # 希尔排序
│   ├── counting_sort.py        # 计数排序
│   ├── radix_sort.py           # 基数排序
│   └── bucket_sort.py          # 桶排序
├── tests/                       # 测试文件夹
│   ├── __init__.py
│   ├── conftest.py             # pytest配置
│   ├── test_bubble_sort.py     # 冒泡排序测试
│   ├── test_selection_sort.py  # 选择排序测试
│   ├── test_insertion_sort.py  # 插入排序测试
│   ├── test_quick_sort.py      # 快速排序测试
│   ├── test_merge_sort.py      # 归并排序测试
│   ├── test_heap_sort.py       # 堆排序测试
│   ├── test_shell_sort.py      # 希尔排序测试
│   ├── test_counting_sort.py   # 计数排序测试
│   ├── test_radix_sort.py      # 基数排序测试
│   └── test_bucket_sort.py     # 桶排序测试
├── main.py                      # 主程序（命令行工具）
└── README.md                    # 项目文档
```

## 📝 示例输出

### 单个算法运行示例

```
============================================================
算法: 快速排序 (quick)
============================================================
排序前: [64, 34, 25, 12, 22, 11, 90]
排序后: [11, 12, 22, 25, 34, 64, 90]
执行时间: 0.0234 毫秒
排序正确性: ✓ 通过
```

### 所有算法比较示例

```
============================================================
比较所有排序算法
============================================================
数组大小: 1000

排名    算法            英文名          时间(ms)    状态
------------------------------------------------------------
1      快速排序        quick           0.8456      ✓
2      归并排序        merge           1.2341      ✓
3      堆排序          heap            1.5678      ✓
4      希尔排序        shell           2.3421      ✓
5      插入排序        insertion       12.4567     ✓
6      选择排序        selection       18.7654     ✓
7      冒泡排序        bubble          25.3456     ✓
8      计数排序        counting        0.5432      ✓
9      基数排序        radix           1.1234      ✓
10     桶排序          bucket          1.4567      ✓
```

## 🎓 学习建议

1. **初学者**: 从冒泡、选择、插入排序开始
2. **进阶**: 学习快速、归并、堆排序的分治思想
3. **高级**: 了解计数、基数、桶排序的特殊应用场景

## 🤝 贡献

欢迎提交问题和改进建议！

## 📄 许可证

本项目仅用于学习和教学目的。

## 👨‍💻 作者

Created with ❤️ for learning sorting algorithms
