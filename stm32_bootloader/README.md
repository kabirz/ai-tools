# STM32F407 Bootloader (UART + CAN)

该示例为 STM32F407xG 器件实现了一个 32 KiB 内的自定义 bootloader，使用 STM32 LL 库，并支持通过 UART 与 CAN 总线更新应用固件。

## 特性
- Bootloader 固件分区：`0x0800_0000` ~ `0x0800_7FFF`（32 KiB）。
- 应用固件默认入口地址：`0x0800_8000`。
- 采用 CMake + GCC/Clang 交叉编译，上电后自动初始化系统时钟到 168 MHz。
- 支持通过 UART (USART3, 115200 8N1) 与 CAN (500 kbps, StdID 0x321/0x322) 进行固件更新。
- 自定义协议：固定前导字节 `0x55`，支持 `PING/INFO/ERASE/WRITE/VERIFY/EXECUTE/RESET` 等命令。

## 快速开始
1. 安装 `arm-none-eabi-gcc` 工具链，并提供相应的 `toolchain.cmake`（可简单参照下方示例）。
2. 配置 LL 库和 CMSIS 头文件搜索路径（默认假设使用 STM32CubeF4 包）。
3. 构建：
   ```sh
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/path/to/arm-gcc-toolchain.cmake
   cmake --build build
   ```
4. 生成的 `bootloader.bin`/`bootloader.hex` 位于 `build/` 目录，可直接烧录到 `0x0800_0000`。

### toolchain.cmake 示例
```cmake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(ARM_TOOLCHAIN_PREFIX arm-none-eabi)

set(CMAKE_C_COMPILER ${ARM_TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_ASM_COMPILER ${ARM_TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${ARM_TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_SIZE ${ARM_TOOLCHAIN_PREFIX}-size)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

## 传输协议概要
每个数据帧使用如下格式（小端）：

| 字段 | 长度 | 描述 |
| ---- | ---- | ---- |
| Preamble | 1 | 固定 `0x55` |
| Cmd | 1 | 命令字 |
| Length | 2 | Payload 长度（<= 256） |
| Address/Status | 4 | 写入时为目标地址，响应时为状态码 |
| Payload | N | 数据内容 |
| CRC32 | 4 | 对 Payload 计算的 CRC-32 (Poly 0xEDB88320) |

常用命令：
- `PING`：连通性测试，payload 为空，返回 `"PONG"`。
- `INFO`：返回 bootloader 版本、应用入口、最大固件大小及可用传输通道。
- `ERASE`：payload[0:4] 为要擦除的字节长度，`Address` 指向起始地址。
- `WRITE`：payload 为写入的数据块，`Address` 为写入起始地址，需要按 4B 对齐。
- `VERIFY`：payload 为 `[length(uint32_t), expected_crc(uint32_t)]`。
- `EXECUTE`：写入成功后请求跳转到应用程序。
- `RESET`：请求系统复位。

## 硬件连接
- UART：默认使用 `USART3`，引脚 `PD8 (TX) / PD9 (RX)`，波特率 115200。
- CAN：默认使用 `CAN1`，引脚 `PB9 (TX) / PB8 (RX)`，经典 CAN 500 kbps，标准帧 `0x321`（Host→Device），`0x322`（Device→Host）。
  需要外接 CAN 收发器并提供合适的终端电阻。

## 后续集成建议
- 根据项目需求调整保持 bootloader 的按键/条件检测逻辑（默认读取 `PA0`）。
- 将协议扩展到分包校验、版本回滚等高级特性，或对接 PC 侧工具。
- 在量产前建议启用写保护、读保护、双备份等安全相关机制。

> ⚠️ 注意：示例工程未随附 STM32 官方库文件，请从 STM32CubeF4 包中获取对应的 CMSIS 与 LL 头文件，并更新 `CMakeLists.txt` 中的包含路径。
