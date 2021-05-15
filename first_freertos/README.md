# 移植freertos到stm32f103上
 设置为STM32F103RC,keil版本为5.14.0.0，操作系统为win10
## 这是已经成功移植的代码，需要注意的是里面有与硬件相关的管脚，使用时需要注意修改
## 如LED_Init()中，管脚为PA8，PD2管脚
## USART_Config()中，PA9、PA10分别为TX1和RX1
