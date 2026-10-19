# HAL_Template 创建与验证报告

日期：2026-10-13（Asia/Shanghai）

## 工程位置与来源

交付工程：`D:\Keil_v5\stm32project\HAL_Template`

源工程：`D:\Keil_v5\stm32project\Hal_Usatr_Send`。目录中只有这一项 HAL `.ioc` 工程；其当前 main.c 有阻塞 UART 接收和 OLED 显示接收字节业务。采用与 `.ioc` 同名、最新的 `MDK-ARM/Hal_Usart_Send.uvprojx`，较旧的中文名工程不作为模板入口。

先完整复制源目录，再修改副本。源目录和实际外部 OLED 依赖共 995 个文件建立 SHA-256 清单，并进行末尾比对。未提交、推送 Git，未修改工具安装、注册表或系统配置。

## 最终结构

```text
HAL_Template/
├── HAL_Template.ioc
├── .mxproject
├── README.md
├── VALIDATION.md
├── Core/
│   ├── Inc/  main.h, OLED.h, OLED_Font.h, stm32f1xx_hal_conf.h, stm32f1xx_it.h
│   └── Src/  main.c, OLED.c, stm32f1xx_hal_msp.c, stm32f1xx_it.c, system_stm32f1xx.c
├── Drivers/  原 HAL / CMSIS 库文件
├── MDK-ARM/
│   ├── HAL_Template.uvprojx
│   ├── HAL_Template.uvoptx
│   ├── startup_stm32f103xb.s
│   └── RTE/, DebugConfig/ 等 Keil 辅助目录（如由工具生成）
├── tools/Ensure-OLED.ps1
└── validation/  编译与生成尝试日志
```

## 修改、保留、移除

- `.ioc` 改名为 HAL_Template，ProjectName / ProjectFileName 同步。删除 USART1 IP、PA9/PA10 分配、USART 参数及初始化排序项；关闭强制 DMA 向量选项。IP 只剩 NVIC/RCC/SYS，GPIO 保留 PB8/PB9。无 I2C 硬件实例、PWM、ADC、SPI、DMA 通道或 RTOS 配置。
- 保留 HSI 8 MHz、AHB/APB 1 分频、FLASH_LATENCY_0、SysTick 和 PA13/PA14 SWD。没有擅自改为 72 MHz。
- 保留 KeepUserCode=true；DeletePrevious=false，固定原 FW_F1 V1.8.7，库为工程内部副本。输出位置未绑定原 USART 目录。
- `main.c` 删除 huart1、MX_USART1_UART_Init 声明/调用/实现、UART 数组和发送接收逻辑、循环延时；USER CODE Includes 内引入 OLED.h，USER CODE 2 显示 HAL READY，while(1) 无业务。保留 CubeMX 标准 WHILE/3 标记布局。
- `stm32f1xx_hal_msp.c` 移除 UART MSP Init/DeInit，保留 HAL_MspInit 和 NOJTAG/SWD。
- `stm32f1xx_hal_conf.h` 禁用 UART、DMA 模块；Keil 移除 HAL UART、DMA 源文件编译引用。HAL 配置中的未启用条件声明、CMSIS 向量表中的 USART/DMA 默认中断名和原厂库文件仍保留，它们不代表启用了外设。未修改任何 HAL 库源文件。
- 清理仅在副本中的旧名称 Keil 工程、历史构建缓存、窗口状态和旧 IOC；新 Keil target/output 均为 HAL_Template。保留原 ST-LINK/SWD 调试配置。
- 实际完整 OLED.c 原位于 `stm32project/OLED.c`，不是源 Core/Src 中只有少数函数的不完整文件。模板使用实际完整版本，OLED.h / 字库同步复制到 Core/Inc。原 font 与模板 font 哈希一致。
- OLED 的字符/字符串/各种数值显示/清屏算法和全部初始化指令保留；只修正 SDA 在 ACK 时释放、保守时序等待与可靠上电等待。底层全部为 HAL，无 SPL 混用。未采用根目录中另一个混用 SPL 的 OLED_HAL.c。
- Keil 源码/包含路径全部解析到模板内部，自定义 OLED 分组只编译一个 OLED.c；保留安装环境的标准 Device Pack 引用。工具安装依赖不属于原工程源码依赖。

## 验证结果及边界

| 项目 | 结果 |
|---|---|
| 8 个公开 OLED 声明对应唯一定义 | 通过 |
| 完整初始化指令、PB8/PB9、开漏/无内部上拉/初值高、GPIO 先初始化 | 静态检查通过 |
| 无 UART 实验调用、变量、初始化、MSP 配置 | 通过 |
| Keil 源文件存在、无外部工程路径、无重复 C 文件、OLED 入目标 | 通过 |
| 模板 15 个 C 文件 ARM Compiler 6.7 实际编译 | 通过，生成 .o；非完整链接 |
| 跨目录 IndependentCopy 副本 15 个 C 文件编译 | 通过，生成 .o；非完整链接 |
| 模拟丢失 OLED 分组后运行 Ensure-OLED.ps1 | 恢复成功，随后 C 编译通过 |
| Keil ARMCC 5 完整 Rebuild | 首次工具进程启动失败，后续限时尝试超时停止；未生成有效固件 |
| ARM Compiler 6 汇编器/链接器备选 | 同样出现 DLL 重定位启动错误；项目恢复原 ARMCC 5 配置 |
| CubeMX 副本重新生成 | 已尝试，Java 首选项注册表 Access denied 导致启动退出；未执行生成 |
| `.ioc` 实际 GUI 打开、增加外设后重新生成 | 未验证，需在正常桌面环境执行 |
| 完整链接无未定义符号 | 未验证；不能用 C 编译替代链接 |
| 开发板 OLED、上拉、时序、SWD 下载 | 未验证 |

C 编译使用 `-Wall -Werror -Wno-missing-braces`；最后一项仅针对原样保留的字库平铺数组初始化风格，不屏蔽未声明函数/类型错误。Keil 启动失败日志不能被解读为工程源码已编译失败或已编译成功。

测试副本位于本次 Codex 工作区 `work/IndependentCopy`；CubeMX 测试位于 `work/CopyTest`，都没有使用模板或源 USART 目录作为生成目标。源码路径解析全部位于各自副本，但由于工具环境限制，没有完成“改名 + 新增外设 + 实际再生成 + 完整链接”的闭环。

## 上板及后续必要检查

1. 在正常桌面 CubeMX 打开副本 IOC，核对名称/最终输出目录后 Generate Code；执行 README 的 OLED 引用修复步骤，在 Keil Rebuild 至无编译/链接错误。
2. 确认 PB8/PB9 各自有到 3.3V 的物理上拉。可从 4.7 kΩ 开始评估，需考虑模块已有电阻、线长/电容和上升时间；本次无法远程确定板上是否装有电阻。
3. ST-LINK 选 SWD，检查下载及冷启动 HAL READY。逐项调用 Clear/ShowChar/ShowString/ShowNum/ShowSignedNum/ShowHexNum/ShowBinNum，确认布局、边界和字库符合期望。
4. 有逻辑分析仪时检查空闲 SDA/SCL 高电平、ACK 周期 SDA 释放、上升时间及实际时钟。当前旧式 OLED API 不反馈 ACK，不处理时钟拉伸；编译不代表实物通信成功。

参考：ST [CubeMX CLI 文档](https://dev.st.com/stm32cube-docs/stm32cubemx/6.18.0/en/docs/markup/CubeMX_CLI.html)，NXP [I2C 总线规范 UM10204](https://cache.nxp.com/docs/en/user-guide/UM10204.pdf)。总线应答阶段释放 SDA、依靠上拉形成高电平的依据见后者。

