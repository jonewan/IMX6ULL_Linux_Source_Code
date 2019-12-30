#include "bsp_beep.h"
#include "bsp_gpio.h"

/*初始化beep*/
void beep_init(void)
{
	GPIO_PIN_CONFIG beep_gpio_config;

	IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);/*复用为GPIO5_IO01*/
	IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0x10B0);

	/*GPIO初始化*/
	beep_gpio_config.direction = KGPIO_DIGITAL_OUTPUT;
	beep_gpio_config.output_logic = 1;
	gpio_init(GPIO5, 1, &beep_gpio_config);
}

/*蜂鸣器控制函数*/
void beep_switch(int status)
{
	if (status == ON)
		gpio_pin_set_logic(GPIO5, 1, 0);
	else
		gpio_pin_set_logic(GPIO5, 1, 1);
}
