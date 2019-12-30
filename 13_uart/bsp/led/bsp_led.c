#include "bsp_led.h"
#include "cc.h"

/*
 * Initialize the led
 * */
void led_init(void)
{
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10b0);

	/*GPIO初始化*/
	GPIO1->GDIR = 0X8;
	/* GPIO1->DR &= ~(1 << 3);//默认打开LED */
	GPIO1->DR |= (1 << 3);//默认关闭LED
}

void led_switch(int led, int status)
{
	switch(led){
		case LED0:
			if (status == ON)
				GPIO1->DR &= ~(1 << 3);
			else
				GPIO1->DR |= (1 << 3);
		break;
	}

}
