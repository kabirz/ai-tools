#!/usr/bin/env python3
"""
排序算法演示程序
支持运行和比较各种排序算法的性能
"""

import argparse
import time
import random
from sorting_algorithms import (
    bubble_sort, selection_sort, insertion_sort,
    quick_sort, merge_sort, heap_sort,
    shell_sort, counting_sort, radix_sort, bucket_sort
)


# 可用的排序算法
ALGORITHMS = {
    'bubble': ('冒泡排序', bubble_sort),
    'selection': ('选择排序', selection_sort),
    'insertion': ('插入排序', insertion_sort),
    'quick': ('快速排序', quick_sort),
    'merge': ('归并排序', merge_sort),
    'heap': ('堆排序', heap_sort),
    'shell': ('希尔排序', shell_sort),
    'counting': ('计数排序', counting_sort),
    'radix': ('基数排序', radix_sort),
    'bucket': ('桶排序', bucket_sort),
}


def generate_random_array(size=20, min_val=-50, max_val=100):
    """生成随机数组"""
    return [random.randint(min_val, max_val) for _ in range(size)]


def measure_time(sort_func, arr):
    """测量排序算法的执行时间"""
    start_time = time.perf_counter()
    result = sort_func(arr.copy())
    end_time = time.perf_counter()
    elapsed_time = (end_time - start_time) * 1000  # 转换为毫秒
    return result, elapsed_time


def run_single_algorithm(algo_name, arr, show_array=True):
    """运行单个排序算法"""
    if algo_name not in ALGORITHMS:
        print(f"错误：未知的算法 '{algo_name}'")
        return
    
    name_cn, sort_func = ALGORITHMS[algo_name]
    
    print(f"\n{'='*60}")
    print(f"算法: {name_cn} ({algo_name})")
    print(f"{'='*60}")
    
    if show_array:
        print(f"排序前: {arr}")
    
    sorted_arr, elapsed = measure_time(sort_func, arr)
    
    if show_array:
        print(f"排序后: {sorted_arr}")
    
    print(f"执行时间: {elapsed:.4f} 毫秒")
    
    # 验证排序是否正确
    is_sorted = all(sorted_arr[i] <= sorted_arr[i+1] for i in range(len(sorted_arr)-1))
    print(f"排序正确性: {'✓ 通过' if is_sorted else '✗ 失败'}")


def run_all_algorithms(arr, show_array=False):
    """运行所有排序算法并比较性能"""
    print(f"\n{'='*60}")
    print(f"比较所有排序算法")
    print(f"{'='*60}")
    print(f"数组大小: {len(arr)}")
    
    if show_array and len(arr) <= 20:
        print(f"原始数组: {arr}")
    
    results = []
    
    for algo_name in sorted(ALGORITHMS.keys()):
        name_cn, sort_func = ALGORITHMS[algo_name]
        
        try:
            sorted_arr, elapsed = measure_time(sort_func, arr)
            is_sorted = all(sorted_arr[i] <= sorted_arr[i+1] for i in range(len(sorted_arr)-1))
            results.append((name_cn, algo_name, elapsed, is_sorted))
        except Exception as e:
            results.append((name_cn, algo_name, -1, False))
            print(f"警告: {name_cn} 执行出错: {e}")
    
    # 按执行时间排序
    results.sort(key=lambda x: x[2] if x[2] >= 0 else float('inf'))
    
    print(f"\n{'排名':<6}{'算法':<15}{'英文名':<15}{'时间(ms)':<12}{'状态'}")
    print('-' * 60)
    
    for i, (name_cn, algo_name, elapsed, is_sorted) in enumerate(results, 1):
        if elapsed >= 0:
            time_str = f"{elapsed:.4f}"
        else:
            time_str = "错误"
        
        status = '✓' if is_sorted else '✗'
        print(f"{i:<6}{name_cn:<15}{algo_name:<15}{time_str:<12}{status}")


def list_algorithms():
    """列出所有可用的排序算法"""
    print("\n可用的排序算法：")
    print(f"{'序号':<6}{'英文名':<15}{'中文名':<15}")
    print('-' * 40)
    
    for i, (algo_name, (name_cn, _)) in enumerate(sorted(ALGORITHMS.items()), 1):
        print(f"{i:<6}{algo_name:<15}{name_cn:<15}")
    
    print(f"\n共 {len(ALGORITHMS)} 种算法")


def main():
    parser = argparse.ArgumentParser(
        description='排序算法演示和性能比较工具',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
示例:
  %(prog)s --list                    # 列出所有算法
  %(prog)s --algo quick              # 运行快速排序
  %(prog)s --algo bubble --size 50   # 对50个元素进行冒泡排序
  %(prog)s --all                     # 比较所有算法
  %(prog)s --all --size 1000         # 用1000个元素比较所有算法
  %(prog)s --custom 5 2 8 1 9        # 对自定义数组排序
        """
    )
    
    parser.add_argument('--list', '-l', action='store_true',
                        help='列出所有可用的排序算法')
    
    parser.add_argument('--algo', '-a', choices=list(ALGORITHMS.keys()),
                        help='选择要运行的排序算法')
    
    parser.add_argument('--all', action='store_true',
                        help='运行所有算法并比较性能')
    
    parser.add_argument('--size', '-s', type=int, default=20,
                        help='生成随机数组的大小（默认: 20）')
    
    parser.add_argument('--custom', '-c', nargs='+', type=int,
                        help='使用自定义数组（空格分隔的整数）')
    
    parser.add_argument('--show-array', action='store_true',
                        help='显示排序前后的数组（仅在 --all 模式下有效）')
    
    args = parser.parse_args()
    
    # 列出所有算法
    if args.list:
        list_algorithms()
        return
    
    # 准备测试数组
    if args.custom:
        test_array = args.custom
    else:
        test_array = generate_random_array(args.size)
    
    # 运行单个算法
    if args.algo:
        run_single_algorithm(args.algo, test_array, show_array=True)
    
    # 运行所有算法
    elif args.all:
        run_all_algorithms(test_array, show_array=args.show_array)
    
    # 默认：显示帮助信息
    else:
        parser.print_help()
        print("\n提示: 使用 --list 查看所有可用算法")


if __name__ == '__main__':
    main()
