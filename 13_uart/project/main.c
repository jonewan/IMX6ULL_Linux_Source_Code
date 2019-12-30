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

int main(void)
{
	/* uint8_t state = OFF; */
	unsigned char a;
	int_init();
	imx6u_clk_init();
	clk_enable();
	delay_init();
	uart_init();
	led_init();
	beep_init();
	key_init();

	while(1){
		puts("请输入一个字符:");
		a = getc();
		putc(a);//回显
		puts("\r\n");

		puts("您输入的字符为:");
		putc(a);//回显
		puts("\r\n");
	}
	return 0;
}
