#ifndef DELAY_H
#define DELAY_H

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "IMX6.h"

void delay_init(void);
void delay_us(volatile unsigned int us);
void delay_ms(volatile unsigned int ms);
void delay_short(volatile unsigned int count);
void delay(volatile unsigned int n);
#endif