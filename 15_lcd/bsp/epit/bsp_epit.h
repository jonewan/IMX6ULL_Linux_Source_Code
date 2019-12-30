#ifndef _BSP_EPIT_H_
#define _BSP_EPIT_H_

#include "imx6u.h"

void epit1_init(unsigned int frac, unsigned int value);
void epit1_irqhandler(unsigned int gicciar, void *param);

#endif /* ifndef _BSP_EPIT_H_ */
