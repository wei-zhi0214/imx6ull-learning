#include "delay.h"

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