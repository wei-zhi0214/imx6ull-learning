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
#include "uart.h"

int main(void)
{
    int_init();         /* 初始化中断 */
    clk_enable(); // 使能时钟
    delay_init(); // 初始化延迟功能
    led_init(); // 初始化LED
    beep_init(); // 初始化蜂鸣器
    key_init(); // 初始化按键
    keyfilter_init(); // 初始化按键滤波
    uart_init(); // 初始化UART


    while(1) {
        puts("enter one char:\n");
        char c = getc(); // 获取输入的字符
        putc(c); // 输出获取的字符
        puts("\r\n");

        //display the character on the LED
        puts("display the character on the LED:\n");
        putc(c); // 输出获取的字符
        puts("\r\n");
    }

    return 0;
}