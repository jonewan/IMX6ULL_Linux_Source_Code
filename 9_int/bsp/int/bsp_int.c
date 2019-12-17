#include "bsp_int.h"

/*中断嵌套计数器*/
static unsigned int irq_nesting;

/*中断处理函数表*/
static sys_irq_handle_t irq_table[NUMBER_OF_INT_VECTORS];

/*初始化中断处理函数表*/
void system_irqtable_init(void)
{
	unsigned int i = 0;
	irq_nesting = 0;//中断嵌套计数器清零
	for (i = 0; i < NUMBER_OF_INT_VECTORS; i++){
		irq_table[i].irqhandler = default_irqhandler;
		irq_table[i].user_param = NULL;
	}
}

/*中断初始化函数*/
void int_init(void)
{
	GIC_Init();
	system_irqtable_init();
	/*中断向量偏移设置*/
	__set_VBAR(0x87800000);
}

/*具体的中断处理函数*/
void system_irqhandler(unsigned int gicciar)
{
	uint32_t int_num = gicciar & 0x3ff;

	/*检查中断ID*/
	if ((int_num == 1023) || (int_num >= NUMBER_OF_INT_VECTORS)){
		return;
	}
	irq_nesting++;
	/*根据中断ID号读取中断处理函数并执行*/
	irq_table[int_num].irqhandler(int_num, irq_table[int_num].user_param);
	irq_nesting--;
}
/*注册中断处理函数*/
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *user_param)
{
	irq_table[irq].irqhandler = handler;
	irq_table[irq].user_param = user_param;
}

/*默认中断处理函数*/
void default_irqhandler(unsigned int gicciar, void *user_param)
{
	while(1){
	}
}
