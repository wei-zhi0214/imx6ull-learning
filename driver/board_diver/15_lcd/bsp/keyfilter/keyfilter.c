#include "keyfilter.h"
#include "gpio.h"
#include "int.h"
#include "beep.h"

void keyfilter_init(void)
{
    gpio_pin_config_t key_config;
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0); // 配置GPIO1_IO18复用为GPIO
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080); // 配置GPIO1_IO18电气属性

    key_config.direction = kGPIO_DigitalInput; // 设置为输入模式
    key_config.interruptMode = kGPIO_IntFallingEdge; // 下降沿触发中断
    gpio_init(GPIO1, 18, &key_config); // 初始化GPIO1_IO18

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn); // 使能GIC中对应GPIO1_IO18(16-31合并中断)的中断
    gpio_enableint(GPIO1, 18); // 使能GPIO1_IO18的中断
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, gpio1_16_31_irqhandler, NULL); // 注册GPIO1_IO18的中断服务程序
    filtertimer_init(66000000 / 100); // 初始化定时器，设置为10ms
}

void filtertimer_init(unsigned int value)
{
    EPIT1->CR = 0; // 先清零控制寄存器，确保EPIT处于复位状态
    EPIT1->CR = (1 << 24) | // CLKSRC=1，选择IPG_CLK作为时钟源
                (0 << 4)  | // PRESCALAR=0，不分频
                (1 << 3)  | // RLD=0，一次性模式，每次按键中断手动重启计时
                (1 << 2)  | // OCIEN=1，使能比较中断
                (1 << 1)  | // ENMOD=1，使能时从LR重新加载计数初值
                (0 << 0);   // EN=0，先不启动，等按键中断触发后才启动

    EPIT1->LR = value; // 设置消抖延时（计数值）
    EPIT1->CMPR = 0; // 计数到0时触发中断

    GIC_EnableIRQ(EPIT1_IRQn); // 使能GIC中对应EPIT1的中断
    system_register_irqhandler(EPIT1_IRQn, filtertimer_irqhandler, NULL); // 注册消抖定时器中断服务程序
}

void filtertimer_stop(void)
{
    EPIT1->CR &= ~(1 << 0); // 停止定时器
}

void filtertimer_restart(unsigned int value)
{
    EPIT1->CR &= ~(1 << 0); // 停止定时器
    EPIT1->LR = value; // 重新加载比较值
    EPIT1->CR |= (1 << 0); // 启动定时器
}

void filtertimer_irqhandler(unsigned int gicciar, void* param)
{
    static unsigned char state = 0;

    if(EPIT1->SR & (1 << 0)) { // 判断是否是EPIT1的中断
        filtertimer_stop(); // 停止定时器
        if(gpio_read(GPIO1, 18) == 0) { // 再次读取按键状态，确认按键确实被按下
            state = !state; // 切换状态
            beep_switch(state); // 根据状态切换蜂鸣器
        }
    }

    EPIT1->SR |= (1 << 0); // 清除定时器中断标志
}

void gpio1_16_31_irqhandler(unsigned int gicciar, void* param)
{
    filtertimer_restart(66000000 / 100); // 重新启动定时器，设置为10ms
    gpio_clearintflags(GPIO1, 18); // 清除GPIO1_IO18的中断标志
}