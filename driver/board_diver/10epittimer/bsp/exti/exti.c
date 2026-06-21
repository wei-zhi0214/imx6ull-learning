#include "exti.h"
#include "gpio.h"
#include "int.h"
#include "delay.h"
#include "beep.h"

void exti_init(void)
{
    gpio_pin_config_t gpioConfig;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0); // 配置GPIO1_IO18复用为GPIO
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080); // 配置GPIO1_IO18电气属性

    gpioConfig.direction = kGPIO_DigitalInput; // 设置为输入模式
    gpioConfig.outputLogic = 0; // 输出逻辑电平，输入模式下不使用
    gpioConfig.interruptMode = kGPIO_IntFallingEdge; // 下降沿触发中断
    gpio_init(GPIO1, 18, &gpioConfig); // 初始化GPIO1_IO18

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn); // 使能GIC中对应GPIO1_IO18(16-31合并中断)的中断
    gpio_enableint(GPIO1, 18); // 使能GPIO1_IO18的中断
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, gpio1_io18_irqheadnler, NULL); // 注册GPIO1_IO18的中断服务程序
}

void gpio1_io18_irqheadnler(unsigned int gicciar, void* param)
{
    static int beep_status = 0; // 蜂鸣器状态标志

    beep_status = !beep_status; // 切换蜂鸣器状态
    beep_switch(beep_status); // 根据状态切换蜂鸣器

    gpio_clearintflags(GPIO1, 18); // 清除GPIO1_IO18的中断标志
}