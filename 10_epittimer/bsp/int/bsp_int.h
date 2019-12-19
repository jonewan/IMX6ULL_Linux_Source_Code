#ifndef _BSP_INT_H_
#define _BSP_INT_H_ 

#include "imx6u.h"

/*定义中断处理函数*/
typedef void (*system_irq_handler_t)(unsigned int gicciar, void *param);

/*中断处理函数结构体*/
typedef struct _sys_irq_handle {
	/* data */
	system_irq_handler_t irqhandler;//中断处理函数
	void *user_param;//中断处理函数的参数
}sys_irq_handle_t;

void int_init(void);
void default_irqhandler(unsigned int gicciar, void *user_param);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *user_param);

#endif /* ifndef _BSP_INT_H_ */
