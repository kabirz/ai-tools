# 磁盘分区表读取工具

这是一个Python程序，用于读取和分析磁盘的MBR(主引导记录)和GPT(GUID分区表)分区表信息。

## 功能特性

- 支持MBR分区表读取和解析
- 支持GPT分区表读取和解析
- 自动检测分区表类型
- 显示详细的分区信息，包括大小、类型、起始扇区等
- 支持扩展分区和逻辑分区(MBR)
- 解析GPT分区GUID和属性
- 提供命令行界面

## 系统要求

- Python 3.6+
- Linux系统(需要root权限读取磁盘设备)
- 或者对磁盘镜像文件的读取权限

## 安装与使用

### 基本用法

```bash
# 读取磁盘设备的分区表
sudo python3 partition_reader.py /dev/sda

# 读取磁盘镜像文件的分区表
python3 partition_reader.py disk_image.img

# 使用交互式示例脚本
python3 example_usage.py

# 运行测试脚本
python3 test_partition_reader.py
```

### 命令行选项

```
usage: partition_reader.py [-h] [-v] device

磁盘分区表读取工具

positional arguments:
  device    设备路径(如 /dev/sda)

optional arguments:
  -h, --help  show this help message and exit
  -v, --verbose  详细输出
```

### 交互式使用

程序提供了一个交互式示例脚本 `example_usage.py`，可以通过以下方式使用：

```bash
# 交互式模式
python3 example_usage.py

# 直接分析指定磁盘
python3 example_usage.py /dev/sda
```

交互式模式提供以下选项：
1. 列出可用磁盘
2. 分析指定磁盘
3. 分析磁盘镜像文件
4. 退出

## 使用示例

### 示例1：读取MBR分区表

```bash
$ sudo python3 partition_reader.py /dev/sdb
设备: /dev/sdb
分区表类型: MBR
分区数量: 3
--------------------------------------------------------------------------------
分区 1:
  类型: FAT32 LBA
  起始扇区: 2048
  扇区数: 1024000
  大小: 500.00 MB (0.49 GB)
  可引导: 是
  类型字节: 0x0C

分区 2:
  类型: Linux
  起始扇区: 1026048
  扇区数: 20480000
  大小: 10000.00 MB (9.77 GB)
  可引导: 否
  类型字节: 0x83

分区 3:
  类型: Extended
  起始扇区: 21506048
  扇区数: 37830656
  大小: 18457.00 MB (18.03 GB)
  可引导: 否
  类型字节: 0x05
```

### 示例2：读取GPT分区表

```bash
$ sudo python3 partition_reader.py /dev/nvme0n1
设备: /dev/nvme0n1
分区表类型: GPT
分区数量: 4
--------------------------------------------------------------------------------
分区 1:
  类型: EFI System Partition
  起始扇区: 2048
  扇区数: 1024000
  大小: 500.00 MB (0.49 GB)
  名称: EFI System Partition
  GUID: C12A7328F81F11D2BA4B00A0C93EC93B
  属性: System Partition, Legacy BIOS Bootable

分区 2:
  类型: Microsoft Basic Data
  起始扇区: 1026048
  扇区数: 20480000
  大小: 10000.00 MB (9.77 GB)
  名称: Windows
  GUID: EBD0A0A2B9E5443387C068B6B72699C7
  属性: None

分区 3:
  类型: Linux Root x86-64
  起始扇区: 21506048
  扇区数: 20480000
  大小: 10000.00 MB (9.77 GB)
  名称: Linux Root
  GUID: 4F68BCE3E8CD4DB195E9478229A28473
  属性: None

分区 4:
  类型: Linux Swap
  起始扇区: 41986048
  扇区数: 4096000
  大小: 2000.00 MB (1.95 GB)
  名称: Linux Swap
  GUID: 0657FD6DA4AB43C484E50933C84B4F51
  属性: None
```

## 代码结构

### 主要类

- `PartitionEntry`: 分区条目基类
- `MBRPartitionEntry`: MBR分区条目类
- `GPTPartitionEntry`: GPT分区条目类
- `PartitionTableReader`: 分区表读取器类

### 主要方法

- `detect_partition_type()`: 自动检测分区表类型
- `read_mbr_partitions()`: 读取MBR分区表
- `read_gpt_partitions()`: 读取GPT分区表
- `read_extended_partitions()`: 读取扩展分区中的逻辑分区

## 注意事项

1. **权限要求**: 读取物理磁盘设备通常需要root权限或管理员权限。

2. **数据安全**: 此程序只读取数据，不会修改任何磁盘内容，是安全的。

3. **支持格式**: 支持物理磁盘设备(如/dev/sda、/dev/nvme0n1)和磁盘镜像文件。

4. **扇区大小**: 目前默认扇区大小为512字节，这是最常见的标准。

5. **分区类型识别**: 程序内置了常见的分区类型识别表，但对于较新的分区类型可能无法识别。

## 错误处理

程序包含基本的错误处理：

- 设备不存在或无法访问
- 无效的分区表格式
- 损坏的分区表数据
- 权限不足错误

## 文件结构

项目包含以下文件：

- `partition_reader.py` - 主程序文件，包含MBR/GPT分区表读取功能
- `test_partition_reader.py` - 测试脚本，创建虚拟磁盘镜像并测试读取功能
- `example_usage.py` - 交互式示例脚本，提供友好的用户界面
- `README.md` - 项目文档

## 技术细节

### MBR分区表结构

MBR(主引导记录)位于磁盘的第一个扇区(LBA 0)，包含：
- 引导代码(446字节)
- 分区表(64字节，4个分区条目，每个16字节)
- 签名(2字节，0x55AA)

### GPT分区表结构

GPT(GUID分区表)结构：
- 保护MBR(LBA 0)
- GPT头(LBA 1)
- 分区表(LBA 2-33，通常)
- 分区数据区域
- 备份GPT头和分区表(磁盘末尾)

### 支持的分区类型

程序内置了常见分区类型的识别：
- MBR: FAT12/16/32, NTFS, Linux, Linux Swap, Extended等
- GPT: EFI系统分区, Microsoft基本数据, Linux根分区, Linux交换等

## 测试

运行测试脚本验证功能：

```bash
python3 test_partition_reader.py
```

测试脚本会创建虚拟的MBR和GPT磁盘镜像，然后读取并验证分区表信息。

## 扩展功能

可以通过扩展以下功能来增强程序：

- 添加更多分区类型的识别
- 支持不同扇区大小
- 添加图形界面
- 导出分区信息到文件(JSON、XML等格式)
- 分析分区内容(文件系统类型)

## 限制

1. **权限要求**: 读取物理磁盘设备通常需要root权限
2. **扇区大小**: 目前默认扇区大小为512字节
3. **只读操作**: 程序只读取分区表信息，不修改磁盘内容

## 许可证

本项目采用MIT许可证。

## 贡献

欢迎提交问题报告和改进建议。
