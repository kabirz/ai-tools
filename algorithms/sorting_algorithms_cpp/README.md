# 排序算法实现项目

这是一个使用现代C++实现的10种常用排序算法的项目，包含完整的测试用例和CMake构建系统。

## 实现的排序算法

1. **冒泡排序 (Bubble Sort)** - O(n²) 时间复杂度
2. **选择排序 (Selection Sort)** - O(n²) 时间复杂度
3. **插入排序 (Insertion Sort)** - O(n²) 时间复杂度
4. **快速排序 (Quick Sort)** - O(n log n) 平均时间复杂度
5. **归并排序 (Merge Sort)** - O(n log n) 时间复杂度
6. **堆排序 (Heap Sort)** - O(n log n) 时间复杂度
7. **计数排序 (Counting Sort)** - O(n+k) 时间复杂度，适用于整数
8. **基数排序 (Radix Sort)** - O(d×(n+k)) 时间复杂度，适用于整数
9. **希尔排序 (Shell Sort)** - O(n^1.3) 平均时间复杂度
10. **桶排序 (Bucket Sort)** - O(n+k) 平均时间复杂度

## 项目结构

```
.
├── CMakeLists.txt          # CMake构建配置
├── README.md               # 项目说明
├── include/
│   └── sorting_algorithms.h # 排序算法头文件
├── src/
│   └── sorting_algorithms.cpp # 排序算法实现
├── tests/
│   └── test_sorting.cpp    # GoogleTest测试用例
└── build/                  # 构建目录
```

## 依赖项

- CMake 3.14+
- C++17 兼容的编译器
- GoogleTest 1.17.0+

## 构建和运行

### 1. 安装依赖

在macOS上使用Homebrew：
```bash
brew install cmake googletest
```

在Ubuntu/Debian上：
```bash
sudo apt-get install cmake libgtest-dev
```

### 2. 构建项目

```bash
mkdir build
cd build
cmake ..
make
```

### 3. 运行测试

```bash
./sorting_tests
```

## 测试覆盖

项目包含全面的测试用例：

- **基本功能测试**：验证每种排序算法的正确性
- **边界条件测试**：空数组、单元素数组、重复元素等
- **性能测试**：对比不同算法的执行时间
- **特殊情况测试**：已排序数组、逆序数组、负数等

## 性能对比

基于10,000个随机整数的测试结果（示例）：
- 快速排序：~1595 微秒
- 归并排序：~7286 微秒  
- 堆排序：~2309 微秒

## 算法特点

### 稳定排序
- 冒泡排序、插入排序、归并排序、计数排序、桶排序

### 不稳定排序
- 选择排序、快速排序、堆排序、希尔排序、基数排序

### 原地排序
- 冒泡排序、选择排序、插入排序、快速排序、堆排序、希尔排序

### 非原地排序
- 归并排序、计数排序、基数排序、桶排序

## 使用示例

```cpp
#include "sorting_algorithms.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    // 使用快速排序
    sorting::quickSort(arr);
    
    // 检查是否已排序
    if (sorting::isSorted(arr)) {
        std::cout << "数组已排序！" << std::endl;
    }
    
    return 0;
}
```

## 扩展性

项目设计为易于扩展：
- 可以轻松添加新的排序算法
- 支持不同数据类型的模板实现（当前为int类型）
- 模块化设计便于维护

## 许可证

本项目采用MIT许可证。