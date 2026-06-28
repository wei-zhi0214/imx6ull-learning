#ifndef GPIO_H
#define GPIO_H
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "IMX6.h"
#include "cc.h"

typedef enum _gpio_interrupt_mode{
    kGPIO_NoIntmode = 0x0,        /* 无中断 */
    kGPIO_IntLowLevel = 0x1,     /* 低电平触发 */
    kGPIO_IntHighLevel = 0x2,    /* 高电平触发 */
    kGPIO_IntRisingEdge = 0x3,   /* 上升沿触发 */
    kGPIO_IntFallingEdge = 0x4,  /* 下降沿触发 */
    kGPIO_IntRisingOrFallingEdge = 0x5 /* 上升沿或下降沿触发 */
} gpio_interrupt_mode_t;

typedef enum _gpio_pin_direction{
    kGPIO_DigitalInput = 0x0,    /* 数字输入 */
    kGPIO_DigitalOutput = 0x1    /* 数字输出 */
} gpio_pin_direction_t;

typedef struct _gpio_pin_config
{
    gpio_pin_direction_t direction; /* GPIO引脚方向 */
    uint8_t outputLogic;           /* 输出逻辑电平，0或1 */
    gpio_interrupt_mode_t interruptMode; /* 中断模式 */
} gpio_pin_config_t;

void gpio_init(GPIO_Type *base, uint32_t pin, gpio_pin_config_t *config);
void gpio_write(GPIO_Type *base, uint32_t pin, uint8_t value);
uint8_t gpio_read(GPIO_Type *base, uint32_t pin);
void gpio_intconfig(GPIO_Type *base, uint32_t pin, gpio_interrupt_mode_t interruptMode);
void gpio_enableint(GPIO_Type *base, uint32_t pin);
void gpio_disableint(GPIO_Type *base, uint32_t pin);
void gpio_clearintflags(GPIO_Type *base, uint32_t pin);

#endif