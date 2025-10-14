# 排序算法集合

这是一个用 Rust 实现的排序算法集合，包含了 10 种常见的排序算法，并提供了完整的测试案例和性能比较。

## 包含的排序算法

1. **冒泡排序 (Bubble Sort)**
   - 时间复杂度: O(n²)
   - 空间复杂度: O(1)
   - 稳定排序

2. **选择排序 (Selection Sort)**
   - 时间复杂度: O(n²)
   - 空间复杂度: O(1)
   - 不稳定排序

3. **插入排序 (Insertion Sort)**
   - 时间复杂度: O(n²)
   - 空间复杂度: O(1)
   - 稳定排序

4. **希尔排序 (Shell Sort)**
   - 时间复杂度: O(n log² n)
   - 空间复杂度: O(1)
   - 不稳定排序

5. **归并排序 (Merge Sort)**
   - 时间复杂度: O(n log n)
   - 空间复杂度: O(n)
   - 稳定排序

6. **快速排序 (Quick Sort)**
   - 时间复杂度: O(n log n)
   - 空间复杂度: O(log n)
   - 不稳定排序

7. **堆排序 (Heap Sort)**
   - 时间复杂度: O(n log n)
   - 空间复杂度: O(1)
   - 不稳定排序

8. **计数排序 (Counting Sort)**
   - 时间复杂度: O(n + k)
   - 空间复杂度: O(k)
   - 稳定排序
   - 仅适用于整数

9. **桶排序 (Bucket Sort)**
   - 时间复杂度: O(n + k)
   - 空间复杂度: O(n + k)
   - 稳定排序
   - 仅适用于浮点数

10. **基数排序 (Radix Sort)**
    - 时间复杂度: O(d × (n + k))
    - 空间复杂度: O(n + k)
    - 稳定排序
    - 仅适用于正整数

## 项目结构

```
sorting_algorithms/
├── Cargo.toml          # 项目配置文件
├── src/
│   ├── lib.rs          # 排序算法实现
│   └── main.rs         # 性能测试程序
└── tests/
    └── sorting_tests.rs # 单元测试
```

## 如何使用

### 作为库使用

在你的 `Cargo.toml` 中添加：

```toml
[dependencies]
sorting_algorithms = { path = "path/to/sorting_algorithms" }
```

然后在你的代码中使用：

```rust
use sorting_algorithms::*;

let mut arr = vec![64, 34, 25, 12, 22, 11, 90];
bubble_sort(&mut arr);
assert!(is_sorted(&arr));
```

### 运行性能测试

```bash
cd sorting_algorithms
cargo run --release
```

这将运行所有排序算法在不同大小和类型的数组上的性能测试。

### 运行单元测试

```bash
cd sorting_algorithms
cargo test
```

这将运行所有单元测试，验证每个排序算法的正确性。

## 测试案例

项目包含全面的测试案例，包括：

- 基本功能测试
- 空数组测试
- 单元素数组测试
- 已排序数组测试
- 逆序数组测试
- 包含重复元素的数组测试
- 随机数组测试
- 大型数组测试

## 性能比较

运行 `cargo run --release` 可以看到不同排序算法在各种情况下的性能表现。测试包括：

- 随机数组
- 已排序数组
- 逆序数组

## 依赖项

- `rand = "0.8"` - 用于生成随机测试数据

## 贡献

欢迎提交 Issue 和 Pull Request 来改进这个项目！

## 许可证

MIT License