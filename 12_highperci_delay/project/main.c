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

int main(void)
{
	uint8_t state = OFF;
	int_init();
	imx6u_clk_init();
	clk_enable();
	delay_init();
	led_init();
	beep_init();
	key_init();

	while(1){
		state = !state;
		led_switch(LED0, state);
		delay_ms(500);
	}
	return 0;
}
