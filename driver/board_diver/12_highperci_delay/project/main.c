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
#include "keyfilter.h"

int main(void)
{
    unsigned int led_state = 0; // LED状态标志

    int_init();         /* 初始化中断 */
    clk_enable(); // 使能时钟
    delay_init(); // 初始化延迟功能
    led_init(); // 初始化LED
    beep_init(); // 初始化蜂鸣器
    key_init(); // 初始化按键
    keyfilter_init(); // 初始化按键滤波

    while(1) {
        led_state = !led_state; // 切换LED状态
        led_switch(LED0, led_state); // 根据状态切换LED
        delay_us(2000); // 延迟2000微秒
    }
    return 0;
}