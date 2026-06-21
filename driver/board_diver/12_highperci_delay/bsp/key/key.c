#include "key.h"
#include "gpio.h"
#include "delay.h"

void key_init(void)
{
    gpio_pin_config_t gpioConfig;

    // 配置GPIO1_IO00为输入模式
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF080); // 设置电气属性

    gpioConfig.direction = kGPIO_DigitalInput; // 设置为输入模式
    gpioConfig.outputLogic = 0;
    gpioConfig.interruptMode = kGPIO_NoIntmode; // 按键轮询不使用中断
    gpio_init(GPIO1, 18, &gpioConfig); // GPIO1_IO18设置为输入模式
}

int read_key(void)
{
    return gpio_read(GPIO1, 18); // 读取GPIO1_IO18的状态
}

int key_get_value(void)
{
    if (read_key() == 0) // 按键被按下，GPIO输入为低电平
    {
        delay(100); // 消抖延迟
        if (read_key() == 0) // 再次确认按键状态
        {
            return 1; // 按键被按下
        }
    }
    return 0; // 按键未被按下
}