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

    int a, b;
    int c = 100;
    printf("%d的十六进制为:%#x\r\n", c, c);
    while(1) {
        printf("请输入两个整数，使用空格隔开:");
        scanf("%d %d", &a, &b);
        printf("\r\n 数据%d+%d=%d\r\n", a, b, a+b);
    }

    return 0;
}