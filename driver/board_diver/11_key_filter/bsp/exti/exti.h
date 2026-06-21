#ifndef _EXTI_H
#define _EXTI_H
#include "imx6u.h"

void exti_init(void);
void gpio1_io18_irqheadnler(unsigned int gicciar, void* param);
#endif