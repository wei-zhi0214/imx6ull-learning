#include "uart.h"
#include "gpio.h"
#include <stdarg.h>

void uart_io_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0); /*复用为UART1_TX */
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0); /*复用为UART1_RX */
   
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10b0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10b0);
}

/* 关闭UART */
void uart_disable(UART_Type *base)
{
    base->UCR1 &= ~ (1 << 0);
}
/* 打开UART */
void uart_enable(UART_Type *base)
{
    base->UCR1 |= (1 << 0);
}
/* 复位UART */
void uart_softreset(UART_Type *base)
{
    base->UCR2 &= ~(1 << 0);
    while((base->UCR2 & 0X1) == 0);
}

void uart_init(void)
{
    uart_io_init();
    uart_disable(UART1);
    uart_softreset(UART1);


    UART1->UCR1 = 0; /* 关闭UART1 */
    UART1->UCR1 &= ~(1 << 14); /* 关闭UART1自動波特律校验 */
    UART1->UCR2 |= (1 << 1) | (1 << 2) | (1 << 5) | (1 << 14); /*始能tx,rx,數據長度8,ignore rts pin*/
    UART1->UCR3 |= (1 << 2);

    /* 设置波特率为115200 */
    UART1->UFCR &= ~ (7 << 7);  /* 对RFDIV进行清零 */
    UART1->UFCR = 5 << 7;       /* 1分频，uart_clk=80MHz */
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

    uart_enable(UART1);
}

void putc(unsigned char c)
{
    while(!(UART1->USR2 & (1 << 3))); /* 等待发送缓冲区为空 */
    UART1->UTXD = c; /* 发送数据 */
}

unsigned char getc(void)
{
    while(!(UART1->USR2 & (1 << 0))); /* 等待接收缓冲区有数据 */
    return UART1->URXD; /* 返回接收到的数据 */
}

void puts(char *str)
{
    while(*str)
    {
        putc(*str++);
    }
}

void raise(int sig)
{
    /* 这里可以实现信号处理逻辑 */
}