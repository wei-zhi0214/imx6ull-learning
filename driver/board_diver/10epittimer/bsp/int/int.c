#include "int.h"
#include "core_ca7.h"

static unsigned  int irqNesting = 0; // 中断嵌套层数

static sys_irq_handler_t irq_table[NUMBER_OF_INTERRUPTS]; // 中断向量表

void system_irqtable_init(void)
{
    // 这里可以添加中断向量表的初始化代码
    // 例如，设置中断服务程序的地址等
    unsigned int i = 0;

    irqNesting = 0; // 初始化中断嵌套层数
    for(i =0; i < NUMBER_OF_INTERRUPTS; i++)
    {
        // 这里可以将所有中断服务程序指针初始化为默认处理函数
        // 例如：irq_table[i] = default_irq_handler;
        irq_table[i].irqHandler = default_irq_handler; // 这里暂时将所有中断服务程序指针初始化为NULL
        irq_table[i].userParam = NULL;
    }
}

void system_register_irqhandler(unsigned int irqNum, system_irq_handler_t handler, void* param)
{
    irq_table[irqNum].irqHandler = handler; // 注册中断服务程序
    irq_table[irqNum].userParam = param;    // 注册用户参数
}

void int_init(void){
    GIC_Init(); // 初始化GIC
    system_irqtable_init(); // 初始化中断向量表

    //中斷向量中斷向量表offset
    __set_VBAR((uint32_t)0x87800000); // 设置中断向量表地址
}

void system_irq_handler(unsigned int gicciar)
{
    unsigned int irqNum = gicciar & 0x3FF; // 从GICC_IAR寄存器中获取中断号
    if (irqNum < NUMBER_OF_INTERRUPTS) {
        irqNesting++; // 进入中断，嵌套层数加1
        if (irq_table[irqNum].irqHandler) {
            irq_table[irqNum].irqHandler(gicciar, irq_table[irqNum].userParam); // 调用注册的中断服务程序
        }
        irqNesting--; // 退出中断，嵌套层数减1
    }
}

void default_irq_handler(unsigned int gicciar, void* param)
{
    // 这里可以添加默认的中断处理代码
    // 例如，记录未处理的中断信息，或者进入死循环等
    while(1);
}