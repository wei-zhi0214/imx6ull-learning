#include "delay.h"

void delay_init(void)
{
    GPT1->CR = 0; // 先清零控制寄存器，确保GPT1处于复位状态
    GPT1->CR = (1 << 9) | // FRR=1，自由运行模式，计数到0xFFFFFFFF才回卷，不受比较影响
               (1 << 6) | // CLKSRC=1，选择IPG_CLK作为时钟源（GPT的CLKSRC在[8:6]，不是EPIT那样的bit24）
               (1 << 1);  // ENMOD=1，使能时计数器从0开始计数
    GPT1->PR = 66 - 1; // GPT的分频在独立的PR寄存器：66MHz/66=1MHz，即每次计数代表1us
    GPT1->CR |= (1 << 0); // 启动GPT1，让它从开机后持续自由计数
}

void delay_us(volatile unsigned int us)
{
    unsigned int old, now;
    unsigned int cnt = 0;

    old = GPT1->CNT;
    while (cnt < us) {
        now = GPT1->CNT;
        if (now != old) {
            if (now > old) {
                cnt += now - old;
            } else { // 计数器从0xFFFFFFFF回卷到0
                cnt += (0xFFFFFFFF - old) + now;
            }
            old = now;
        }
    }
}

void delay_ms(volatile unsigned int ms)
{
    int i = 0;
    for (i = 0; i < ms; i++) {
        delay_us(1000); // 每次调用delay_us实现1ms的延迟
    }
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