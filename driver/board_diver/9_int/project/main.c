#include "main.h"
#include "clk.h"
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "gpio.h"
#include "int.h"

int main(void)
{
    int led_state = 0; // LED状态标志

    int_init(); // 初始化中断系统
    clk_enable(); // 使能时钟
    led_init(); // 初始化LED
    beep_init(); // 初始化蜂鸣器
    key_init(); // 初始化按键
    exti_init(); // 初始化外部中断

    while(1) {
        led_state = !led_state;
        led_switch(LED0, led_state);
        delay(500);
    }
    return 0;
}