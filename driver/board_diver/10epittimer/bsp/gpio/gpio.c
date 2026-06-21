#include "gpio.h"

void gpio_init(GPIO_Type *base, uint32_t pin, gpio_pin_config_t* config)
{
    if(config->direction == kGPIO_DigitalInput) // 输入
    {
        base->GDIR &= ~(1 << pin); // 设置为输入模式
    }
    else // 输出
    {
        base->GDIR |= (1 << pin); // 设置为输出模式
        gpio_write(base, pin, config->outputLogic); // 初始化输出为指定电平
    }
    gpio_intconfig(base, pin, config->interruptMode); // 配置中断模式
}

void gpio_write(GPIO_Type *base, uint32_t pin, uint8_t value)
{
    if(value)
    {
        base->DR |= (1 << pin); // 设置为高电平
    }
    else
    {
        base->DR &= ~(1 << pin); // 设置为低电平
    }
}

uint8_t gpio_read(GPIO_Type *base, uint32_t pin)
{
    return (base->DR >> pin) & 0x1; // 读取输入状态
}

void gpio_enableint(GPIO_Type *base, uint32_t pin)
{
    // 这里可以添加使能GPIO中断的代码，具体实现取决于硬件平台
    base->IMR |= (1 << pin); // 使能指定引脚的中断
}

void gpio_disableint(GPIO_Type *base, uint32_t pin)
{
    // 这里可以添加禁用GPIO中断的代码，具体实现取决于硬件平台
    base->IMR &= ~(1 << pin); // 禁用指定引脚的中断
}

void gpio_clearintflags(GPIO_Type *base, uint32_t pin)
{
    // 这里可以添加清除GPIO中断标志的代码，具体实现取决于硬件平台
    base->ISR |= (1 << pin); // 清除指定引脚的中断标志
}

void gpio_intconfig(GPIO_Type *base, uint32_t pin, gpio_interrupt_mode_t interruptMode)
{
    volatile uint32_t* icr;
    uint32_t icrShift;
    uint32_t icrValue;

    if(interruptMode == kGPIO_IntRisingOrFallingEdge)
    {
        base->EDGE_SEL |= (1 << pin); // 任意边沿触发，由EDGE_SEL决定，忽略ICR
        return;
    }
    base->EDGE_SEL &= ~(1 << pin); // 使用ICR寄存器配置中断触发方式

    icrShift = pin;
    if(pin < 16)
    {
        icr = &base->ICR1; // ICR1配置0-15引脚
    }
    else
    {
        icr = &base->ICR2; // ICR2配置16-31引脚
        icrShift -= 16;
    }

    // ICR每个引脚占2位：00=低电平 01=高电平 10=上升沿 11=下降沿
    switch(interruptMode)
    {
        case kGPIO_IntLowLevel:
            icrValue = 0x0; // 低电平触发
            break;
        case kGPIO_IntHighLevel:
            icrValue = 0x1; // 高电平触发
            break;
        case kGPIO_IntRisingEdge:
            icrValue = 0x2; // 上升沿触发
            break;
        case kGPIO_IntFallingEdge:
            icrValue = 0x3; // 下降沿触发
            break;
        case kGPIO_NoIntmode:
        default:
            icrValue = 0x0;
            break;
    }
    *icr = (*icr & ~(0x3 << (icrShift * 2))) | (icrValue << (icrShift * 2));
}