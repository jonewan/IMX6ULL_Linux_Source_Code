#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

/*
 * Initialize the led
 * */
#define LED0	0

void led_init(void);
void led_switch(int led, int status);


#endif /* ifndef _BSP_LED_H_*/
