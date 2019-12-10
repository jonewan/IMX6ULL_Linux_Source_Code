#include "main.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_clk.h"
#include "bsp_key.h"
#include "bsp_beep.h"

int main(void)
{
	unsigned char led_state = OFF;
	unsigned char beep_state = OFF;
	int key_value = 0;

	imx6u_clk_init();
	clk_enable();
	led_init();
	beep_init();
	key_init();

	led_switch(LED0, led_state);
	beep_switch(beep_state);

	while(1){
		key_value = get_key_value();
		if(key_value == KEY0_VALUE){
			beep_state = !beep_state;
			beep_switch(beep_state);
			led_state = !led_state;
			led_switch(LED0, led_state);
		}
	}
	return 0;
}
