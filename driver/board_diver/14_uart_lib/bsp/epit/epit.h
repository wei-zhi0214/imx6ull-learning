#ifndef _EPIT_H
#define _EPIT_H
#include "imx6u.h"

void epit_init(unsigned int frac, unsigned int value);
void epit_irqhandler(unsigned int gicciar, void* param);
#endif 