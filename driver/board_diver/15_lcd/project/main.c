#include "main.h"
#include "clk.h"
#include "led.h"
#include "beep.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
#include "gpio.h"
#include "int.h"
#include "epit.h"
#include "keyfilter.h"
#include "uart.h"
#include "lcd.h"
#include "bsp_lcdapi.h"

unsigned int backclor[10] = {
    LCD_BLUE, LCD_GREEN, LCD_RED, LCD_CYAN, LCD_YELLOW,
    LCD_LIGHTBLUE, LCD_DARKBLUE, LCD_WHITE, LCD_BLACK,
    LCD_ORANGE
};
int main(void)
{
    unsigned int color = 0;
    static unsigned char state = 0;
    unsigned char index = 0;

    int_init();         /* 初始化中断 */
    clk_enable(); // 使能时钟
    delay_init(); // 初始化延迟功能
    led_init(); // 初始化LED
    beep_init(); // 初始化蜂鸣器
    key_init(); // 初始化按键
    keyfilter_init(); // 初始化按键滤波
    uart_init(); // 初始化UART
    lcd_init();         /* 初始化LCD */

    tftlcd_dev.forecolor = LCD_RED;
    tftlcd_dev.backcolor = LCD_WHITE;
    lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPAH IMX6U");
    lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
    lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM&ALIENTEK");
    lcd_show_string(10, 130, 240, 12, 12,(char*)"2026/6/28 13:30");

    while(1) {
        index++;
        lcd_clear(backclor[index]);
        lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPAH IMX6U");
        lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
        lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM&ALIENTEK");
        lcd_show_string(10, 130, 240, 12, 12,(char*)"2019/8/16 1:36");

        if (index == 10)
            index = 0;
        state = !state;
        led_switch(LED0, state);
        delay_ms(1000);
    }

    return 0;
}