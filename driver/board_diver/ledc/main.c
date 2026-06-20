#include "main.h"

void clk_enable(void)
{
    // 使能GPIO1时钟
    CCM_CCGR1 = 0XFFFFFFFF;
    CCM_CCGR2 = 0XFFFFFFFF;
    CCM_CCGR3 = 0XFFFFFFFF;
    CCM_CCGR4 = 0XFFFFFFFF;
    CCM_CCGR5 = 0XFFFFFFFF;
    CCM_CCGR6 = 0XFFFFFFFF;
}

void led_init(void)
{
    // 配置GPIO1_IO03为输出模式
    SW_MUX_GPIO1_IO03 = 0X5; // 设置复用功能为GPIO
    SW_PAD_GPIO1_IO03 = 0X10B0; // 设置电气属性

    GPIO1_GDIR |= (1 << 3); // 将GPIO1_IO03设置为输出模式
    GPIO1_DR &= ~(1 << 3); // 初始状态为低电平，LED关闭
}

void delay_short(volatile unsigned int count)
{
    while (count--);
}

void delay(volatile unsigned int n)
{
    while (n--)
    {
        delay_short(0x7FF); // 调整这个值以改变延迟时间
    }
}

void led_on(void)
{
    GPIO1_DR |= (1 << 3); // 将GPIO1_IO03设置为高电平，LED点亮
}

void led_off(void)
{
    GPIO1_DR &= ~(1 << 3); // 将GPIO1_IO03设置为低电平，LED熄灭
}

int main(void)
{
    clk_enable(); // 使能时钟
    led_init(); // 初始化LED

    while (1)
    {
        led_on(); // 点亮LED
        delay(1000); // 延迟一段时间
        led_off(); // 熄灭LED
        delay(1000); // 延迟一段时间
    }

    return 0;
}