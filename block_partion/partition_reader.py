#!/usr/bin/env python3
"""
磁盘分区表读取工具
支持MBR和GPT分区表的读取和分析
"""

import os
import sys
import struct
import argparse
from typing import List, Dict, Optional, Union


class PartitionEntry:
    """分区条目基类"""
    def __init__(self):
        self.start_sector = 0
        self.total_sectors = 0
        self.partition_type = ""
        self.bootable = False
        self.attributes = ""
    
    def get_size_mb(self) -> float:
        """获取分区大小(MB)"""
        return (self.total_sectors * 512) / (1024 * 1024)
    
    def get_size_gb(self) -> float:
        """获取分区大小(GB)"""
        return (self.total_sectors * 512) / (1024 * 1024 * 1024)
    
    def __str__(self) -> str:
        return f"Partition: {self.partition_type}, Start: {self.start_sector}, " \
               f"Size: {self.get_size_mb():.2f} MB, Bootable: {self.bootable}"


class MBRPartitionEntry(PartitionEntry):
    """MBR分区条目"""
    def __init__(self, data: bytes):
        super().__init__()
        self.parse(data)
    
    def parse(self, data: bytes):
        """解析MBR分区条目"""
        if len(data) < 16:
            raise ValueError("MBR分区条目数据长度不足")
        
        # 解析MBR分区条目结构
        self.bootable = (data[0] == 0x80)
        
        # 起始CHS地址(3字节)
        self.start_cylinder = data[3] | ((data[2] & 0xC0) << 2)
        self.start_head = data[1]
        self.start_sector = data[2] & 0x3F
        
        # 分区类型(1字节)
        self.type_byte = data[4]
        self.partition_type = self.get_partition_type_name(self.type_byte)
        
        # 结束CHS地址(3字节)
        self.end_cylinder = data[7] | ((data[6] & 0xC0) << 2)
        self.end_head = data[5]
        self.end_sector = data[6] & 0x3F
        
        # 起始LBA和总扇区数
        self.start_sector_lba = struct.unpack('<I', data[8:12])[0]
        self.total_sectors = struct.unpack('<I', data[12:16])[0]
    
    @staticmethod
    def get_partition_type_name(type_byte: int) -> str:
        """获取分区类型名称"""
        partition_types = {
            0x00: "Empty",
            0x01: "FAT12",
            0x04: "FAT16 <32M",
            0x05: "Extended",
            0x06: "FAT16",
            0x07: "NTFS/exFAT",
            0x0B: "FAT32",
            0x0C: "FAT32 LBA",
            0x0E: "FAT16 LBA",
            0x0F: "Extended LBA",
            0x11: "Hidden FAT12",
            0x14: "Hidden FAT16 <32M",
            0x16: "Hidden FAT16",
            0x1B: "Hidden FAT32",
            0x1C: "Hidden FAT32 LBA",
            0x1E: "Hidden FAT16 LBA",
            0x82: "Linux Swap",
            0x83: "Linux",
            0x85: "Linux Extended",
            0x86: "NTFS Volume Set",
            0x87: "NTFS Volume Set",
            0x8E: "Linux LVM",
            0xA0: "HPFS",
            0xA5: "FreeBSD",
            0xA6: "OpenBSD",
            0xA8: "Mac OS X",
            0xAF: "Mac OS X HFS+",
            0xBE: "Solaris Boot",
            0xBF: "Solaris",
            0xEE: "GPT Protective",
            0xEF: "EFI System Partition",
            0xFD: "Linux RAID",
        }
        return partition_types.get(type_byte, f"Unknown (0x{type_byte:02X})")


class GPTPartitionEntry(PartitionEntry):
    """GPT分区条目"""
    def __init__(self, data: bytes):
        super().__init__()
        self.parse(data)
    
    def parse(self, data: bytes):
        """解析GPT分区条目"""
        if len(data) < 128:
            raise ValueError("GPT分区条目数据长度不足")
        
        # 分区类型GUID(16字节)
        self.partition_type_guid = data[0:16]
        
        # 唯一分区GUID(16字节)
        self.unique_partition_guid = data[16:32]
        
        # 起始LBA(8字节)
        self.start_sector_lba = struct.unpack('<Q', data[32:40])[0]
        
        # 结束LBA(8字节)
        self.end_sector_lba = struct.unpack('<Q', data[40:48])[0]
        self.total_sectors = self.end_sector_lba - self.start_sector_lba + 1
        
        # 属性标志(8字节)
        self.attributes_flags = struct.unpack('<Q', data[48:56])[0]
        self.parse_attributes()
        
        # 分区名(72字节，UTF-16LE编码)
        self.name = data[56:128].decode('utf-16le').rstrip('\x00')
        self.partition_type = self.get_gpt_partition_type_name()
    
    def parse_attributes(self):
        """解析GPT分区属性"""
        attrs = []
        if self.attributes_flags & 0x1:
            attrs.append("Required Platform")
        if self.attributes_flags & 0x2:
            attrs.append("EFI Firmware")
        if self.attributes_flags & 0x4:
            attrs.append("Legacy BIOS Bootable")
        if self.attributes_flags & 0x8:
            attrs.append("System Partition")
        if self.attributes_flags & 0x10:
            attrs.append("Read-only")
        if self.attributes_flags & 0x20:
            attrs.append("Hidden")
        if self.attributes_flags & 0x40:
            attrs.append("No Automount")
        if self.attributes_flags & 0x80:
            attrs.append("Shadow Copy")
        
        self.attributes = ", ".join(attrs) if attrs else "None"
    
    def get_gpt_partition_type_name(self) -> str:
        """根据GUID获取GPT分区类型名称"""
        guid = self.partition_type_guid.hex().upper()
        known_types = {
            "00000000000000000000000000000000": "Unused",
            "024DEE4133E711D385E30080C717595D": "System Partition (MBR)",
            "C12A7328F81F11D2BA4B00A0C93EC93B": "EFI System Partition",
            "EBD0A0A2B9E5443387C068B6B72699C7": "Microsoft Basic Data",
            "5808C8AA55E94729A6F498A110D655F5": "Microsoft LDM Metadata",
            "AF9B60A0104343B68FAE859D958A4E5D": "Microsoft LDM Data",
            "DE94BBA406D14440A16A9FD36D00B2C8": "Windows Recovery",
            "E75CAF8FF6244CC8BEEA017E8E3A614F": "IBM General Parallel FS",
            "E3C9E3160B5C499889C9A6F3D9F03A68": "HP-UX Data",
            "E3C9E3160B5C499889C9A6F3D9F06A75": "HP-UX Service",
            "0FC63DAF848347728E793D69D8477DE4": "Linux Filesystem",
            "A19D880F05FC4D3BA006743F0F84911E": "Linux RAID",
            "0657FD6DA4AB43C484E50933C84B4F51": "Linux Swap",
            "E6D6D379F50744C2A23EF338A8B8D834": "Linux LVM",
            "8DA63397000760C974328542094D5A9E": "Linux Reserved",
            "83BD6B9D7F4143C790E56447BFF9C5D6": "FreeBSD Boot",
            "516E7CB56EBC466AB8B0789953357B1E": "FreeBSD Data",
            "516E7CB4E6EC44468485E590966CE13C": "FreeBSD Swap",
            "516E7CB5E6EC44468485E590966CE13C": "FreeBSD UFS",
            "516E7CB8E6EC44468485E590966CE13C": "FreeBSD Vinum",
            "516E7CBAAEC5446EA28E399B5F019D16": "FreeBSD ZFS",
            "48465300000000001122334455667788": "Apple HFS+",
            "7C34571F000011AA991D000000000000": "Apple RAID",
            "7C34571F000011AA991F000000000000": "Apple RAID Offline",
            "7C34571F000011AA991E000000000000": "Apple Boot",
            "7C34571F000011AA9923000000000000": "Apple Label",
            "7C34571F000011AA9921000000000000": "Apple TV Recovery",
            "7C34571F000011AA9922000000000000": "Apple Core Storage",
            "6A82CB451DD24EB88DC796BFE7E1B9D": "Solaris Boot",
            "6A85CF4D1DD24EB88DC796BFE7E1B9D": "Solaris Root",
            "6A87C6F71DD24EB88DC796BFE7E1B9D": "Solaris Swap",
            "6A8B64291DD24EB88DC796BFE7E1B9D": "Solaris Backup",
            "6A898CC41DD24EB88DC796BFE7E1B9D": "Solaris /usr",
            "6A8EF2E91DD24EB88DC796BFE7E1B9D": "Solaris /var",
            "6A90BA391DD24EB88DC796BFE7E1B9D": "Solaris /home",
            "6A9283A51DD24EB88DC796BFE7E1B9D": "Solaris Alternate Sector",
            "6A945A3B1DD24EB88DC796BFE7E1B9D": "Solaris Reserved",
            "6A9630D61DD24EB88DC796BFE7E1B9D": "Solaris Reserved",
            "6A9807671DD24EB88DC796BFE7E1B9D": "Solaris Reserved",
            "6A842CC01DD24EB88DC796BFE7E1B9D": "Solaris Reserved",
            "6A9033D21DD24EB88DC796BFE7E1B9D": "NetBSD Swap",
            "49F48D32B10E4FC497E72AED0B5B5B9D": "NetBSD FFS",
            "49F48D5AB10E4FC497E72AED0B5B5B9D": "NetBSD LFS",
            "49F48D82B10E4FC497E72AED0B5B5B9D": "NetBSD RAID",
            "2BD5E8299A294A7AB3358B5D1A7E7F6D": "Chrome OS Kernel",
            "3CB8E2023B784AC9A79CE1C4F9B874C9": "Chrome OS Root FS",
            "CA3D7E9E326F4FCD9416A615A7B5E0BE": "Chrome OS Reserved",
            "FE3A2A5D4F324C0A91AE404D54A5CE4B": "MidnightBSD Data",
            "85D5E45E237C11D0890E00A0C922FE7D": "MidnightBSD Boot",
            "0322E6965CE711D4881C000A0C91FA7F": "MidnightBSD Swap",
            "4F68BCE3E8CD4DB195E9478229A28473": "Linux Root x86-64",
            "B921B0451DF041C3AF444C6F2800D56C": "Linux /boot x86-64",
            "44479540F29641B29FAE3C8EF630C5E3": "Linux /home x86-64",
            "3B8F842520E041C988B589391896D8A4": "Linux /srv x86-64",
            "734E5AFE2055494E95B4E6676B835B4D": "Linux /var x86-64",
            "8DA63397000760C97C9A667164945499": "Linux /tmp x86-64",
            "4F21B0161CD04D2190DB11E594E5B323": "Linux /usr x86-64",
            "933AC7E12EB44F0198410F53C84F3E6E": "Linux Reserved x86-64",
        }
        return known_types.get(guid, f"Unknown ({guid})")
    
    def __str__(self) -> str:
        return f"GPT Partition: {self.name}, Type: {self.partition_type}, " \
               f"Start: {self.start_sector_lba}, Size: {self.get_size_gb():.2f} GB, " \
               f"Attributes: {self.attributes}"


class PartitionTableReader:
    """分区表读取器"""
    
    def __init__(self, device_path: str):
        self.device_path = device_path
        self.sector_size = 512
        self.partition_type = None
        self.partitions: List[PartitionEntry] = []
    
    def read_sector(self, sector: int, count: int = 1) -> bytes:
        """读取指定的扇区"""
        with open(self.device_path, 'rb') as f:
            f.seek(sector * self.sector_size)
            return f.read(count * self.sector_size)
    
    def detect_partition_type(self) -> str:
        """检测分区表类型"""
        # 读取第一个扇区(MBR区域)
        first_sector = self.read_sector(0)
        
        # 检查MBR签名
        if len(first_sector) >= 512 and first_sector[510] == 0x55 and first_sector[511] == 0xAA:
            # 检查是否是GPT保护MBR
            mbr_partitions = []
            for i in range(4):
                offset = 446 + i * 16
                partition_data = first_sector[offset:offset+16]
                if partition_data[4] == 0xEE:  # GPT保护分区类型
                    return "GPT"
                mbr_partitions.append(partition_data)
            
            # 检查是否有有效的MBR分区
            for partition_data in mbr_partitions:
                if partition_data[4] != 0x00:  # 非空分区
                    return "MBR"
        
        return "Unknown"
    
    def read_mbr_partitions(self) -> List[MBRPartitionEntry]:
        """读取MBR分区表"""
        partitions = []
        first_sector = self.read_sector(0)
        
        # MBR分区表从偏移446开始，每个分区条目16字节，共4个分区
        for i in range(4):
            offset = 446 + i * 16
            partition_data = first_sector[offset:offset+16]
            
            # 跳过空分区
            if partition_data[4] == 0x00:
                continue
            
            try:
                partition = MBRPartitionEntry(partition_data)
                partitions.append(partition)
            except Exception as e:
                print(f"无法解析MBR分区 {i}: {e}")
        
        # 检查扩展分区
        extended_start = None
        for partition in partitions:
            if partition.type_byte in [0x05, 0x0F]:  # 扩展分区类型
                extended_start = partition.start_sector_lba
                break
        
        if extended_start:
            self.read_extended_partitions(extended_start, partitions)
        
        return partitions
    
    def read_extended_partitions(self, extended_start: int, partitions: List[MBRPartitionEntry]):
        """读取扩展分区中的逻辑分区"""
        current_extended = extended_start
        
        while True:
            extended_sector = self.read_sector(current_extended)
            
            # 读取扩展分区中的第一个逻辑分区
            first_partition_data = extended_sector[446:462]
            if first_partition_data[4] == 0x00:  # 空分区
                break
            
            try:
                # 调整逻辑分区的起始扇区
                adjusted_data = bytearray(first_partition_data)
                start_lba = struct.unpack('<I', first_partition_data[8:12])[0]
                adjusted_start = current_extended + start_lba
                struct.pack_into('<I', adjusted_data, 8, adjusted_start)
                
                logical_partition = MBRPartitionEntry(bytes(adjusted_data))
                partitions.append(logical_partition)
            except Exception as e:
                print(f"无法解析逻辑分区: {e}")
            
            # 检查是否有下一个扩展分区
            second_partition_data = extended_sector[462:478]
            if second_partition_data[4] == 0x00:  # 没有下一个扩展分区
                break
            
            next_extended_lba = struct.unpack('<I', second_partition_data[8:12])[0]
            current_extended = extended_start + next_extended_lba
    
    def read_gpt_partitions(self) -> List[GPTPartitionEntry]:
        """读取GPT分区表"""
        partitions = []
        
        # 读取GPT头(通常在LBA 1)
        gpt_header_sector = self.read_sector(1)
        
        # 解析GPT头
        if len(gpt_header_sector) < 92:
            raise ValueError("GPT头数据长度不足")
        
        # 验证GPT签名("EFI PART")
        signature = gpt_header_sector[0:8]
        if signature != b'EFI PART':
            raise ValueError("无效的GPT签名")
        
        # 获取分区表起始LBA和分区条目数量
        partition_entry_lba = struct.unpack('<Q', gpt_header_sector[72:80])[0]
        num_partition_entries = struct.unpack('<I', gpt_header_sector[80:84])[0]
        partition_entry_size = struct.unpack('<I', gpt_header_sector[84:88])[0]
        
        # 读取分区表
        partition_table_size = num_partition_entries * partition_entry_size
        partition_table_sectors = (partition_table_size + 511) // 512
        
        partition_table_data = b''
        for i in range(partition_table_sectors):
            sector_data = self.read_sector(partition_entry_lba + i)
            partition_table_data += sector_data
        
        # 解析分区条目
        for i in range(num_partition_entries):
            offset = i * partition_entry_size
            partition_data = partition_table_data[offset:offset+partition_entry_size]
            
            # 检查是否是空分区(全0)
            if all(b == 0 for b in partition_data):
                continue
            
            try:
                partition = GPTPartitionEntry(partition_data)
                partitions.append(partition)
            except Exception as e:
                print(f"无法解析GPT分区 {i}: {e}")
        
        return partitions
    
    def read_partitions(self) -> List[PartitionEntry]:
        """读取分区表"""
        if not os.path.exists(self.device_path):
            raise FileNotFoundError(f"设备不存在: {self.device_path}")
        
        if not os.access(self.device_path, os.R_OK):
            raise PermissionError(f"无权限读取设备: {self.device_path}")
        
        self.partition_type = self.detect_partition_type()
        
        if self.partition_type == "MBR":
            partitions = self.read_mbr_partitions()
        elif self.partition_type == "GPT":
            partitions = self.read_gpt_partitions()
        else:
            raise ValueError("未知的分区表类型")
        
        self.partitions = partitions
        return partitions
    
    def print_partition_info(self):
        """打印分区信息"""
        print(f"设备: {self.device_path}")
        print(f"分区表类型: {self.partition_type}")
        print(f"分区数量: {len(self.partitions)}")
        print("-" * 80)
        
        for i, partition in enumerate(self.partitions):
            print(f"分区 {i+1}:")
            print(f"  类型: {partition.partition_type}")
            print(f"  起始扇区: {partition.start_sector_lba if hasattr(partition, 'start_sector_lba') else partition.start_sector}")
            print(f"  扇区数: {partition.total_sectors}")
            print(f"  大小: {partition.get_size_mb():.2f} MB ({partition.get_size_gb():.2f} GB)")
            
            if isinstance(partition, MBRPartitionEntry):
                print(f"  可引导: {'是' if partition.bootable else '否'}")
                print(f"  类型字节: 0x{partition.type_byte:02X}")
            elif isinstance(partition, GPTPartitionEntry):
                print(f"  名称: {partition.name}")
                print(f"  GUID: {partition.partition_type_guid.hex().upper()}")
                print(f"  属性: {partition.attributes}")
            
            print()


def main():
    """主函数"""
    parser = argparse.ArgumentParser(description="磁盘分区表读取工具")
    parser.add_argument("device", help="设备路径(如 /dev/sda)")
    parser.add_argument("-v", "--verbose", action="store_true", help="详细输出")
    
    args = parser.parse_args()
    
    try:
        reader = PartitionTableReader(args.device)
        partitions = reader.read_partitions()
        reader.print_partition_info()
    except Exception as e:
        print(f"错误: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()