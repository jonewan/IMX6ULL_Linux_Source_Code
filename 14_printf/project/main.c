#include "main.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_clk.h"
#include "bsp_key.h"
#include "bsp_beep.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "bsp_epit.h"
#include "bsp_key_filter.h"
#include "bsp_uart.h"
#include "stdio.h"

int main(void)
{
	/* uint8_t state = OFF; */
	int a;
	int b;
	int_init();
	imx6u_clk_init();
	clk_enable();
	delay_init();
	uart_init();
	led_init();
	beep_init();
	key_init();

	while(1){
		printf("请输入两个整数,空格隔开:\r\n");
		scanf("%d%d", &a, &b);
		printf("\r\n%d + %d = %d\r\n", a, b, a+b);
	}
	return 0;
}
