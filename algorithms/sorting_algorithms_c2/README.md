# 排序算法实现与测试

本项目实现了10种常用的排序算法，并对它们进行了功能和性能测试。

## 目录结构

- `sorting_algorithms.h`: 排序算法函数声明
- `sorting_algorithms.c`: 排序算法实现
- `test_functionality.c`: 功能测试代码
- `test_performance.c`: 性能测试代码
- `test_report.md`: 测试报告
- `Makefile`: 构建文件

## 实现的排序算法

1. 冒泡排序 (Bubble Sort)
2. 选择排序 (Selection Sort)
3. 插入排序 (Insertion Sort)
4. 希尔排序 (Shell Sort)
5. 归并排序 (Merge Sort)
6. 快速排序 (Quick Sort)
7. 堆排序 (Heap Sort)
8. 计数排序 (Counting Sort)
9. 桶排序 (Bucket Sort)
10. 基数排序 (Radix Sort)

## 编译和运行

### 编译

```bash
make
```

### 运行功能测试

```bash
./test_functionality
```

### 运行性能测试

```bash
./test_performance
```

### 清理编译文件

```bash
make clean
```

## 测试报告

详细的测试报告请参见 [test_report.md](test_report.md) 文件。

## 算法复杂度

| 排序算法 | 最好时间复杂度 | 平均时间复杂度 | 最坏时间复杂度 | 空间复杂度 | 稳定性 |
|---------|---------------|---------------|---------------|-----------|-------|
| 冒泡排序 | O(n) | O(n²) | O(n²) | O(1) | 稳定 |
| 选择排序 | O(n²) | O(n²) | O(n²) | O(1) | 不稳定 |
| 插入排序 | O(n) | O(n²) | O(n²) | O(1) | 稳定 |
| 希尔排序 | O(n log n) | O(n^1.3) | O(n²) | O(1) | 不稳定 |
| 归并排序 | O(n log n) | O(n log n) | O(n log n) | O(n) | 稳定 |
| 快速排序 | O(n log n) | O(n log n) | O(n²) | O(log n) | 不稳定 |
| 堆排序 | O(n log n) | O(n log n) | O(n log n) | O(1) | 不稳定 |
| 计数排序 | O(n + k) | O(n + k) | O(n + k) | O(k) | 稳定 |
| 桶排序 | O(n + k) | O(n + k) | O(n²) | O(n + k) | 稳定 |
| 基数排序 | O(n × k) | O(n × k) | O(n × k) | O(n + k) | 稳定 |

注：k 为数据范围或桶的数量

## 许可证

本项目为学习和研究目的而创建，仅供个人使用。