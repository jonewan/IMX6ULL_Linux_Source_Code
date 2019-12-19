#ifndef _BSP_EXTI_H_
#define _BSP_EXTI_H_ 

#include "imx6u.h"

void exti_init(void);
void gpio1_io18_irqhandler(unsigned int gicciar, void *param);

#endif /* ifndef _BSP_EXTI_H_ */
