#include "bsp_exti.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_delay.h"
#include "bsp_beep.h"

void exti_init(void) 
{
	GPIO_PIN_CONFIG key_config;

	/*复用为GPIO1_IO18*/
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
	/*设置为输入*/
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

	key_config.direction =  KGPIO_DIGITAL_INPUT;
	key_config.interrupt_mode = KGPIO_INT_FALLINGEDGE;
	gpio_init(GPIO1, 18, &key_config);

	GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, gpio1_io18_irqhandler, NULL);
	gpio_pin_int_enable(GPIO1, 18);
}

/*中断处理函数*/
void gpio1_io18_irqhandler(unsigned int gicciar, void *param)
{
	static uint8_t state = 0;

	delay(10);//用来做简易的按键消抖，实际中禁止在中断中使用延时函数
	if (gpio_pin_get_logic(GPIO1, 18) == 0){
		state = !state;
		beep_switch(state);
	}
	/*清除中断标志位*/
	gpio_pin_intflag_clear(GPIO1, 18);
}
