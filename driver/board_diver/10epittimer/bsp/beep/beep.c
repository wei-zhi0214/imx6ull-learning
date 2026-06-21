#include "beep.h"
#include "cc.h"

void beep_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10B0);

    /* GPIO初始化 */
    GPIO5->GDIR |= (1 << 1); // 设置为输出
    GPIO5->DR &= ~(1 << 1); // 初始状态为低电平，蜂鸣器关闭
}

void beep_switch(int status)
{
    if (status)
    {
        GPIO5->DR |= (1 << 1); // 设置为高电平，蜂鸣器开启
    }
    else
    {
        GPIO5->DR &= ~(1 << 1); // 设置为低电平，蜂鸣器关闭
    }
}