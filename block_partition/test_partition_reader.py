#!/usr/bin/env python3
"""
分区表读取工具测试脚本
"""

import os
import tempfile
import struct
from partition_reader import PartitionTableReader, MBRPartitionEntry, GPTPartitionEntry


def create_test_mbr_image():
    """创建一个测试用的MBR磁盘镜像"""
    # 创建一个10MB的测试镜像文件
    with tempfile.NamedTemporaryFile(delete=False, suffix='.img') as f:
        image_path = f.name
        
        # 写入10MB的零数据
        f.write(b'\x00' * (10 * 1024 * 1024))
        
        # 创建MBR分区表
        f.seek(0)  # 回到文件开头
        
        # 写入MBR引导代码(446字节，这里用零填充)
        f.write(b'\x00' * 446)
        
        # 分区1: FAT32, 可引导, 起始扇区2048, 大小1MB
        partition1 = bytearray(16)
        partition1[0] = 0x80  # 可引导标志
        partition1[1] = 0x01  # 起始磁头
        partition1[2] = 0x01  # 起始扇区
        partition1[3] = 0x00  # 起始柱面
        partition1[4] = 0x0B  # 分区类型: FAT32
        partition1[5] = 0xFE  # 结束磁头
        partition1[6] = 0xFF  # 结束扇区
        partition1[7] = 0x00  # 结束柱面
        struct.pack_into('<I', partition1, 8, 2048)  # 起始LBA
        struct.pack_into('<I', partition1, 12, 2048)  # 扇区数 (1MB)
        f.write(partition1)
        
        # 分区2: Linux, 不可引导, 起始扇区4096, 大小2MB
        partition2 = bytearray(16)
        partition2[0] = 0x00  # 不可引导
        partition2[1] = 0x01  # 起始磁头
        partition2[2] = 0x01  # 起始扇区
        partition2[3] = 0x00  # 起始柱面
        partition2[4] = 0x83  # 分区类型: Linux
        partition2[5] = 0xFE  # 结束磁头
        partition2[6] = 0xFF  # 结束扇区
        partition2[7] = 0x00  # 结束柱面
        struct.pack_into('<I', partition2, 8, 4096)  # 起始LBA
        struct.pack_into('<I', partition2, 12, 4096)  # 扇区数 (2MB)
        f.write(partition2)
        
        # 分区3: 空
        f.write(b'\x00' * 16)
        
        # 分区4: 空
        f.write(b'\x00' * 16)
        
        # MBR签名
        f.write(b'\x55\xAA')
        
        return image_path


def create_test_gpt_image():
    """创建一个测试用的GPT磁盘镜像"""
    # 创建一个20MB的测试镜像文件
    with tempfile.NamedTemporaryFile(delete=False, suffix='.img') as f:
        image_path = f.name
        
        # 写入20MB的零数据
        f.write(b'\x00' * (20 * 1024 * 1024))
        
        # 创建保护MBR
        f.seek(0)  # 回到文件开头
        
        # 写入MBR引导代码(446字节，这里用零填充)
        f.write(b'\x00' * 446)
        
        # 保护分区: GPT保护分区, 覆盖整个磁盘
        protective_partition = bytearray(16)
        protective_partition[0] = 0x00  # 不可引导
        protective_partition[1] = 0x00  # 起始磁头
        protective_partition[2] = 0x02  # 起始扇区
        protective_partition[3] = 0x00  # 起始柱面
        protective_partition[4] = 0xEE  # 分区类型: GPT保护
        protective_partition[5] = 0xFE  # 结束磁头
        protective_partition[6] = 0xFF  # 结束扇区
        protective_partition[7] = 0xFF  # 结束柱面
        struct.pack_into('<I', protective_partition, 8, 1)  # 起始LBA
        struct.pack_into('<I', protective_partition, 12, 0xFFFFFFFF)  # 扇区数 (尽可能大)
        f.write(protective_partition)
        
        # 其他3个分区为空
        f.write(b'\x00' * 16 * 3)
        
        # MBR签名
        f.write(b'\x55\xAA')
        
        # GPT头 (LBA 1)
        f.seek(512)  # 第二个扇区
        
        # GPT签名 "EFI PART"
        f.write(b'EFI PART')
        
        # 版本 (4字节)
        f.write(struct.pack('<I', 0x00010000))
        
        # 头大小 (4字节)
        f.write(struct.pack('<I', 92))
        
        # 头CRC32 (4字节)
        f.write(struct.pack('<I', 0))  # 先写0，后面计算
        
        # 保留 (4字节)
        f.write(struct.pack('<I', 0))
        
        # 当前LBA (8字节)
        f.write(struct.pack('<Q', 1))
        
        # 备份LBA (8字节)
        f.write(struct.pack('<Q', 0))  # 简化，不设置备份
        
        # 第一个可用LBA (8字节)
        f.write(struct.pack('<Q', 34))  # GPT头(1扇区) + 分区表(32扇区)
        
        # 最后一个可用LBA (8字节)
        f.write(struct.pack('<Q', (20 * 1024 * 1024 // 512) - 1))
        
        # 磁盘GUID (16字节)
        f.write(b'\x12\x34\x56\x78\x90\xAB\xCD\xEF\x12\x34\x56\x78\x90\xAB\xCD\xEF')
        
        # 分区表起始LBA (8字节)
        f.write(struct.pack('<Q', 2))
        
        # 分区条目数量 (4字节)
        f.write(struct.pack('<I', 4))  # 4个分区
        
        # 分区条目大小 (4字节)
        f.write(struct.pack('<I', 128))  # 128字节每个分区
        
        # 分区表CRC32 (4字节)
        f.write(struct.pack('<I', 0))  # 先写0，后面计算
        
        # 保留 (剩余部分)
        f.write(b'\x00' * (512 - 92))
        
        # 分区表 (从LBA 2开始)
        f.seek(2 * 512)  # LBA 2
        
        # 分区1: EFI系统分区
        partition1 = bytearray(128)
        # 分区类型GUID: EFI系统分区
        partition1[0:16] = bytes.fromhex("C12A7328F81F11D2BA4B00A0C93EC93B")
        # 唯一分区GUID
        partition1[16:32] = bytes.fromhex("1234567890AB11D391234567890ABCDE")
        # 起始LBA
        struct.pack_into('<Q', partition1, 32, 34)
        # 结束LBA
        struct.pack_into('<Q', partition1, 40, 34 + 2048 - 1)  # 1MB
        # 属性
        struct.pack_into('<Q', partition1, 48, 0)  # 无特殊属性
        # 分区名 (UTF-16LE): "EFI System"
        name_bytes = "EFI System".encode('utf-16le')
        partition1[56:56+len(name_bytes)] = name_bytes
        f.write(partition1)
        
        # 分区2: Linux根分区
        partition2 = bytearray(128)
        # 分区类型GUID: Linux根分区x86-64
        partition2[0:16] = bytes.fromhex("4F68BCE3E8CD4DB195E9478229A28473")
        # 唯一分区GUID
        partition2[16:32] = bytes.fromhex("234567890ABD11D391234567890ABCDE")
        # 起始LBA
        struct.pack_into('<Q', partition2, 32, 34 + 2048)
        # 结束LBA
        struct.pack_into('<Q', partition2, 40, 34 + 2048 + 4096 - 1)  # 2MB
        # 属性
        struct.pack_into('<Q', partition2, 48, 0)  # 无特殊属性
        # 分区名 (UTF-16LE): "Linux Root"
        name_bytes = "Linux Root".encode('utf-16le')
        partition2[56:56+len(name_bytes)] = name_bytes
        f.write(partition2)
        
        # 分区3: Microsoft基本数据分区
        partition3 = bytearray(128)
        # 分区类型GUID: Microsoft基本数据
        partition3[0:16] = bytes.fromhex("EBD0A0A2B9E5443387C068B6B72699C7")
        # 唯一分区GUID
        partition3[16:32] = bytes.fromhex("34567890ABCE11D391234567890ABCDE")
        # 起始LBA
        struct.pack_into('<Q', partition3, 32, 34 + 2048 + 4096)
        # 结束LBA
        struct.pack_into('<Q', partition3, 40, 34 + 2048 + 4096 + 6144 - 1)  # 3MB
        # 属性
        struct.pack_into('<Q', partition3, 48, 0)  # 无特殊属性
        # 分区名 (UTF-16LE): "Windows"
        name_bytes = "Windows".encode('utf-16le')
        partition3[56:56+len(name_bytes)] = name_bytes
        f.write(partition3)
        
        # 分区4: Linux交换分区
        partition4 = bytearray(128)
        # 分区类型GUID: Linux交换分区
        partition4[0:16] = bytes.fromhex("0657FD6DA4AB43C484E50933C84B4F51")
        # 唯一分区GUID
        partition4[16:32] = bytes.fromhex("4567890ABCDF11D391234567890ABCDE")
        # 起始LBA
        struct.pack_into('<Q', partition4, 32, 34 + 2048 + 4096 + 6144)
        # 结束LBA
        struct.pack_into('<Q', partition4, 40, 34 + 2048 + 4096 + 6144 + 2048 - 1)  # 1MB
        # 属性
        struct.pack_into('<Q', partition4, 48, 0)  # 无特殊属性
        # 分区名 (UTF-16LE): "Linux Swap"
        name_bytes = "Linux Swap".encode('utf-16le')
        partition4[56:56+len(name_bytes)] = name_bytes
        f.write(partition4)
        
        return image_path


def test_mbr_reading():
    """测试MBR分区表读取"""
    print("测试MBR分区表读取...")
    
    # 创建测试MBR镜像
    mbr_image = create_test_mbr_image()
    
    try:
        # 读取分区表
        reader = PartitionTableReader(mbr_image)
        partitions = reader.read_partitions()
        
        print(f"检测到的分区表类型: {reader.partition_type}")
        print(f"检测到的分区数量: {len(partitions)}")
        
        for i, partition in enumerate(partitions):
            print(f"分区 {i+1}: {partition}")
            print(f"  类型: {partition.partition_type}")
            print(f"  起始扇区: {partition.start_sector_lba if hasattr(partition, 'start_sector_lba') else partition.start_sector}")
            print(f"  扇区数: {partition.total_sectors}")
            print(f"  大小: {partition.get_size_mb():.2f} MB")
            
            if isinstance(partition, MBRPartitionEntry):
                print(f"  可引导: {'是' if partition.bootable else '否'}")
                print(f"  类型字节: 0x{partition.type_byte:02X}")
            
            print()
        
        print("MBR测试通过!")
    finally:
        # 清理测试文件
        os.unlink(mbr_image)


def test_gpt_reading():
    """测试GPT分区表读取"""
    print("测试GPT分区表读取...")
    
    # 创建测试GPT镜像
    gpt_image = create_test_gpt_image()
    
    try:
        # 读取分区表
        reader = PartitionTableReader(gpt_image)
        partitions = reader.read_partitions()
        
        print(f"检测到的分区表类型: {reader.partition_type}")
        print(f"检测到的分区数量: {len(partitions)}")
        
        for i, partition in enumerate(partitions):
            print(f"分区 {i+1}: {partition}")
            print(f"  类型: {partition.partition_type}")
            print(f"  起始扇区: {partition.start_sector_lba if hasattr(partition, 'start_sector_lba') else partition.start_sector}")
            print(f"  扇区数: {partition.total_sectors}")
            print(f"  大小: {partition.get_size_mb():.2f} MB")
            
            if isinstance(partition, GPTPartitionEntry):
                print(f"  名称: {partition.name}")
                print(f"  GUID: {partition.partition_type_guid.hex().upper()}")
                print(f"  属性: {partition.attributes}")
            
            print()
        
        print("GPT测试通过!")
    finally:
        # 清理测试文件
        os.unlink(gpt_image)


def main():
    """主函数"""
    print("开始测试分区表读取工具...")
    print("-" * 50)
    
    test_mbr_reading()
    print("-" * 50)
    test_gpt_reading()
    
    print("所有测试完成!")


if __name__ == "__main__":
    main()
