#ifndef _BSP_DELAY_H_
#define _BSP_DELAY_H_ 

#include "imx6u.h"

void delay_init(void);
void gpt1_irqhandler(unsigned int gicciar, void *param);
/*微秒级延时*/
void delay_us(uint32_t us);
/*毫秒级延时*/
void delay_ms(uint32_t ms);
void delay_short(volatile unsigned int n);
void delay(volatile unsigned int n);

#endif /* ifndef _BSP_DELAY_H_ */
