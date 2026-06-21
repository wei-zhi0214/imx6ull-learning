#include "main.h"
#include "clk.h"
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "gpio.h"
#include "int.h"
#include "epit.h"

int main(void)
{
    int_init(); // 初始化中断系统
    clk_enable(); // 使能时钟
    led_init(); // 初始化LED
    beep_init(); // 初始化蜂鸣器
    key_init(); // 初始化按键
    exti_init(); // 初始化外部中断
    epit_init(0, 66000000 / 2); // 初始化EPIT，分频系数为0，比较值为66000000（1秒）

    while(1) {
        delay(500);
    }
    return 0;
}