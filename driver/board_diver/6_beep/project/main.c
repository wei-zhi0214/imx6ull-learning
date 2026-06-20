#include "main.h"
#include "clk.h"
#include "led.h"
#include "beep.h"
#include "delay.h"

int main(void)
{
    clk_enable(); // 使能时钟
    led_init(); // 初始化LED
    beep_init(); // 初始化蜂鸣器

    while (1)
    {
        led_on(); // 点亮LED
        beep_switch(1); // 打开蜂鸣器
        delay(1000); // 延迟一段时间

        led_off(); // 熄灭LED
        beep_switch(0); // 关闭蜂鸣器
        delay(1000); // 延迟一段时间
    }

    return 0;
}