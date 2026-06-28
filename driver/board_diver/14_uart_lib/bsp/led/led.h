#ifndef LED_H
#define LED_H
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "IMX6.h"

#define LED0 0

void led_init(void);
void led_on(void);
void led_off(void);
void led_switch(int led, int status);

#endif