#ifndef __INT_H
#define __INT_H
#include "imx6u.h"

#define NUMBER_OF_INTERRUPTS 160 // GIC支持的最大中断号(PMU_IRQ2_IRQn = 159)+1

typedef void (*system_irq_handler_t)(unsigned int gicciar, void* param);

typedef struct _sys_irq_handler
{
    system_irq_handler_t irqHandler; // 中断服务程序指针
    void* userParam; // 用户参数
} sys_irq_handler_t;

void int_init(void);
void system_register_irqhandler(unsigned int irqNum, system_irq_handler_t handler, void* param);
void default_irq_handler(unsigned int gicciar, void* param);

#endif