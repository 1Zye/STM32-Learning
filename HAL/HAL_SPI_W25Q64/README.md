# HAL_Template

STM32F103C8T6 / HAL / Keil MDK5 / CubeMX 6.18.1 / STM32Cube FW_F1 V1.8.7。
启动显示 `HAL READY`，主循环为空。HSI 8 MHz、SysTick、SWD 保留，无实验外设初始化。

## 接线与驱动

| OLED | 开发板 |
|---|---|
| SCL | PB8 |
| SDA | PB9 |
| VCC | 3.3V |
| GND | GND |

PB8/PB9 为开漏输出、GPIO_NOPULL，初始输出 SET（释放总线）。必须确认模块已有两路接至 **3.3V** 的有效上拉；没有时可从每路 4.7 kΩ 开始，结合线长、总线电容和波形检查调整。开漏本身不会产生高电平，不能接至 5V 上拉。

保留原完整 HAL OLED 驱动：初始化、清屏、字符、字符串、十进制、有符号数、十六进制、二进制。字库原样保留，显示范围 4 行 × 16 列（128×64、8×16 字符），地址沿用 0x3C。底层增加保守时序等待、应答周期释放 SDA，并以一次 100 ms 上电等待替换空循环。原接口仍不检测 ACK、不支持时钟拉伸；这是现有专用 OLED 驱动，不是通用 I2C 总线驱动。

## 复制创建新工程

1. 关闭模板的 Keil/CubeMX 窗口，将整个 `HAL_Template` 文件夹复制到一个**不存在的新目录**，例如 `D:\Keil_v5\stm32project\MyProject`。不要直接在原模板内增加外设。
2. 先在新目录打开 `HAL_Template.ioc`。在 CubeMX 的 Project Manager 中设置 Project Name 为 `MyProject`；Project Location / 输出目录必须指向新副本，检查最终工程目录确实为 `...\MyProject`，避免重复嵌套或指回模板。使用 Save As 把配置保存为新目录内的 `MyProject.ioc`。
3. 工具链选择 MDK-ARM，保留固件版本 V1.8.7。保留 `Keep User Code when re-generating`，使用复制库文件而非引用外部固件源码；建议关闭 `Delete previously generated files when not re-generated`。本模板未保存原工程的绝对输出路径，但每次改名仍应检查 CubeMX 显示的输出位置。
4. 在 `.ioc` 中按需增加外设。保持 PB8/PB9 的 GPIO_Output / Open Drain / No Pull / 初始 High，以及 SYS 的 Serial Wire。OLED 必须在 GPIO 初始化之后初始化。更改系统时钟后应重新测量软件 I2C 波形。
5. 点击 Generate Code，确认保存的是新目录内的 `.ioc`。`main.c` 中自定义代码只放 USER CODE 区域；不要让生成器管理或替换 `OLED.c`、`OLED.h`、`OLED_Font.h`。
6. 关闭 Keil，在新工程根目录打开 PowerShell，运行以下命令修复/检查自定义 OLED 编译引用（运行前可查看脚本）：

   ```powershell
   powershell -NoProfile -File .\tools\Ensure-OLED.ps1 -ProjectFile .\MDK-ARM\MyProject.uvprojx
   ```

   脚本只修改本副本内指定的 Keil 工程，先创建带时间戳的备份，然后确保 `User OLED` 分组只有一份 OLED 文件引用及 `../Core/Inc` 包含路径。它不会修改 `.ioc`、其他外设或代码。如果系统执行策略禁止脚本，可在 Keil 中手工添加 `Core/Src/OLED.c` 并检查包含路径，无需更改系统策略。
7. 用 Keil 打开新目录生成的 `MDK-ARM\MyProject.uvprojx`，确认 Target、输出文件位置属于新工程，选择本机可用 ARM Compiler 5，执行 Rebuild。首次生成新工程名时也应检查 Debug 使用 ST-LINK、Port=SW、Flash 下载算法适配 STM32F103C8。
8. 新项目正常后再自行整理副本中的旧名称 `.ioc/.uvprojx/.uvoptx`；不要同时维护多个配置文件，也不要删除原模板。脚本遇到多个工程时必须显式指定 `-ProjectFile`。

`User OLED` 为独立用户分组，三个文件存放在工程内部。CubeMX 本次未能实际重新生成，因此暂不能保证所有版本都会自动保留该分组；**每次 Generate Code 后执行第 6 步并 Rebuild**。

## 验证状态（2026-10-13）

- 源工程及外部依赖文件做了 SHA-256 前后比对，未修改。
- 模板与独立复制副本：15 个 C 文件通过 ARM Compiler 6.7 编译为目标文件；检查了所有源文件/包含路径、8 个 OLED 接口、无 USART 业务及引脚一致性。
- 原字库使用合法的平铺数组初始化；编译验证使用 `-Wall -Werror -Wno-missing-braces`，仅关闭该字库的括号风格告警。
- Keil ARMCC 5 实际 Rebuild 已尝试，但编译器/汇编器/链接器在当前执行环境报 DLL 重定位或进程启动失败。**没有成功链接，没有已验证可下载的 AXF/HEX。** 项目仍保留原 ARMCC 5 配置，未改动工具安装和系统设置。
- CubeMX 在安全副本上尝试命令行生成，启动阶段因 Java 首选项注册表访问被拒绝退出；**未完成实际打开/重新生成验证**。配置文本、用户区和路径已静态检查，修复脚本的丢引用恢复已实测。
- 尚未下载到开发板。请在本机正常桌面环境完成 CubeMX Generate + Keil Rebuild，并检查上拉、SWD 下载、冷启动 `HAL READY`、其他显示 API 与 SDA/SCL 波形。

详细情况见 `VALIDATION.md` 和 `validation/` 日志。
