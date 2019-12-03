#include "imx6u.h"

/*
 * Enable clock of peripheral device
 * */
void clk_enable(void)
{
	CCM->CCM_CCGR0 = 0xffffffff;
	CCM->CCM_CCGR1 = 0xffffffff;
	CCM->CCM_CCGR2 = 0xffffffff;
	CCM->CCM_CCGR3 = 0xffffffff;
	CCM->CCM_CCGR4 = 0xffffffff;
	CCM->CCM_CCGR5 = 0xffffffff;
	CCM->CCM_CCGR6 = 0xffffffff;
}

/*
 * Delay function
 * */
void delay_short(volatile unsigned int n)
{
	while(n--)
		;
}

void delay(volatile unsigned int n)
{
	while(n--){
		delay_short(0x7ff);
	}
}

/*
 * Initialize the led
 * */
void led_init(void)
{
	IOMUX_SW_MUX->GPIO1_IO03 = 0x5;
	IOMUX_SW_PAD->GPIO1_IO03 = 0x10b0;

	/*GPIO初始化*/
	GPIO1->GDIR = 0X8;
	GPIO1->DR &= ~(1 << 3);
}

void led_on(void)
{
	GPIO1->DR &= ~(1 << 3);
}

void led_off(void)
{
	GPIO1->DR |= (1 << 3);
}

int main(void)
{
	clk_enable();
	led_init();
	while(1){
		led_on();
		delay(500);
		led_off();
		delay(500);
	}
	return 0;
}
