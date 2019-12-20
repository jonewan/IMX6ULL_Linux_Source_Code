#ifndef _BSP__KEY_FILTER_H_
#define _BSP__KEY_FILTER_H_

#include "imx6u.h"

void key_filter_init(void);
void gpio1_16_31_irqhandler(unsigned int gicciar, void *param);
/*初始化EPTI1定时器*/
void filter_timer_init(uint32_t value);
/*关闭EPIT1定时器*/
void filter_timer_stop(void);
/*重启EPIT1定时器*/
void filter_timer_restart(uint32_t value);
/*EPIT1定时器中断处理函数*/
void filter_timer_irqhandler(unsigned int gicciar, void *param);

#endif /* ifndef _BSP__KEY_FILTER_H_ */
