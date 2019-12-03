#include "main.h"

/*
 * Enable clock of peripheral device
 * */
void clk_enable(void)
{
	CCM_CCGR0 = 0xffffffff;
	CCM_CCGR1 = 0xffffffff;
	CCM_CCGR2 = 0xffffffff;
	CCM_CCGR3 = 0xffffffff;
	CCM_CCGR4 = 0xffffffff;
	CCM_CCGR5 = 0xffffffff;
	CCM_CCGR6 = 0xffffffff;
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
	SW_MUX_GPIO1_IO03 = 0x5;//复用为GPIO01-IO03
	SW_PAD_GPIO1_IO03 = 0x10b0;//设置GPIO01-IO03电器属性

	/*GPIO初始化*/
	GPIO1_GDIR = 0X8;//设置为输出
	GPIO1_DR = 0X0;//打开led灯
}

void led_on(void)
{
	GPIO1_DR &= ~(1 << 3);
}

void led_off(void)
{
	GPIO1_DR |= (1 << 3);
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
