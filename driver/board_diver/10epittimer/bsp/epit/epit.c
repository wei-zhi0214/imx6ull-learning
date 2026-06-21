#include "epit.h"
#include "int.h"
#include "led.h"

void epit_init(unsigned int frac, unsigned int value)
{
    
    EPIT1->CR = 0; // 先清零控制寄存器，确保EPIT处于复位状态
    /* 2. 配置EPIT工作模式 */
    EPIT1->CR = (1 << 24) | // CLKSRC=1，选择IPG_CLK作为时钟源
                (frac << 4) | // PRESCALAR，设置分频系数
                (1 << 3) | // RLD=1，计数到0后自动从LR重新加载（循环模式）
                (1 << 2) | // OCIEN=1，使能比较中断
                (1 << 1) | // ENMOD=1，使能时从LR重新加载计数初值（否则会从复位后的0xFFFFFFFF开始数，第一次要等很久才会中断）
                (0 << 0); // EN=0，先不启动，等LR/CMPR配置好再启动

    /* 3. 设置比较值 */
    EPIT1->LR = value; // 设置比较值，单位为时钟周期数
    EPIT1->CMPR = 0; // 设置比较寄存器为0，表示每次计数到LR时触发中断

    /* 4. 配置中断 */
    GIC_EnableIRQ(EPIT1_IRQn); // 使能GIC中对应EPIT的中断
    system_register_irqhandler(EPIT1_IRQn, epit_irqhandler, NULL); // 注册EPIT中断服务程序

    /* 5. 启动EPIT */
    EPIT1->CR |= (1 << 0); // 启动计数器
}

void epit_irqhandler(unsigned int gicciar, void* param)
{
    static int led_state = 0; // LED状态标志

    led_state = !led_state; // 切换LED状态
    led_switch(LED0, led_state); // 根据状态切换LED

    EPIT1->SR |= (1 << 0); // 清除EPIT的中断标志
}