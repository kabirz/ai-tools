#!/usr/bin/env python3
"""
分区表读取工具使用示例
"""

import os
import sys
from partition_reader import PartitionTableReader


def list_available_disks():
    """列出可用的磁盘设备"""
    disks = []
    
    # 常见的磁盘设备路径
    disk_paths = [
        '/dev/sda', '/dev/sdb', '/dev/sdc', '/dev/sdd', '/dev/sde',
        '/dev/nvme0n1', '/dev/nvme1n1', '/dev/nvme2n1',
        '/dev/hda', '/dev/hdb', '/dev/hdc',
        '/dev/vda', '/dev/vdb', '/dev/vdc'
    ]
    
    for disk_path in disk_paths:
        if os.path.exists(disk_path) and os.access(disk_path, os.R_OK):
            disks.append(disk_path)
    
    return disks


def analyze_disk(disk_path):
    """分析指定磁盘的分区表"""
    print(f"正在分析磁盘: {disk_path}")
    print("=" * 60)
    
    try:
        reader = PartitionTableReader(disk_path)
        partitions = reader.read_partitions()
        
        print(f"分区表类型: {reader.partition_type}")
        print(f"分区数量: {len(partitions)}")
        print()
        
        # 计算总大小
        total_size_mb = sum(p.get_size_mb() for p in partitions)
        total_size_gb = sum(p.get_size_gb() for p in partitions)
        
        print(f"总分区大小: {total_size_mb:.2f} MB ({total_size_gb:.2f} GB)")
        print()
        
        # 显示分区详情
        for i, partition in enumerate(partitions):
            print(f"分区 {i+1}:")
            print(f"  类型: {partition.partition_type}")
            print(f"  起始扇区: {partition.start_sector_lba if hasattr(partition, 'start_sector_lba') else partition.start_sector}")
            print(f"  扇区数: {partition.total_sectors}")
            print(f"  大小: {partition.get_size_mb():.2f} MB ({partition.get_size_gb():.2f} GB)")
            
            if hasattr(partition, 'bootable'):
                print(f"  可引导: {'是' if partition.bootable else '否'}")
            
            if hasattr(partition, 'name'):
                print(f"  名称: {partition.name}")
            
            if hasattr(partition, 'attributes') and partition.attributes:
                print(f"  属性: {partition.attributes}")
            
            print()
        
        return True
    except Exception as e:
        print(f"错误: {e}")
        return False


def interactive_mode():
    """交互模式"""
    print("磁盘分区表分析工具 - 交互模式")
    print("=" * 40)
    
    while True:
        print("\n请选择操作:")
        print("1. 列出可用磁盘")
        print("2. 分析指定磁盘")
        print("3. 分析磁盘镜像文件")
        print("4. 退出")
        
        choice = input("\n请输入选项 (1-4): ").strip()
        
        if choice == '1':
            print("\n正在扫描可用磁盘...")
            disks = list_available_disks()
            
            if disks:
                print("\n可用磁盘:")
                for i, disk in enumerate(disks, 1):
                    print(f"  {i}. {disk}")
            else:
                print("\n未找到可用的磁盘设备。")
                print("可能需要root权限才能访问磁盘设备。")
        
        elif choice == '2':
            disk_path = input("\n请输入磁盘路径 (如 /dev/sda): ").strip()
            if disk_path:
                analyze_disk(disk_path)
            else:
                print("无效的磁盘路径。")
        
        elif choice == '3':
            image_path = input("\n请输入磁盘镜像文件路径: ").strip()
            if image_path and os.path.exists(image_path):
                analyze_disk(image_path)
            else:
                print("文件不存在或无法访问。")
        
        elif choice == '4':
            print("退出程序。")
            break
        
        else:
            print("无效的选项，请重新输入。")


def main():
    """主函数"""
    if len(sys.argv) > 1:
        # 命令行模式
        disk_path = sys.argv[1]
        if os.path.exists(disk_path):
            success = analyze_disk(disk_path)
            sys.exit(0 if success else 1)
        else:
            print(f"错误: 设备或文件不存在: {disk_path}")
            sys.exit(1)
    else:
        # 交互模式
        interactive_mode()


if __name__ == "__main__":
    main()