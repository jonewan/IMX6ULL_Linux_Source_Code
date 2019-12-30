#include "bsp_key.h"
#include "bsp_gpio.h"

void key_init(void)
{
	GPIO_PIN_CONFIG key_config;

	/*复用为GPIO1_IO18*/
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
	/*设置为输入*/
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

	key_config.direction =  KGPIO_DIGITAL_INPUT;
	gpio_init(GPIO1, 18, &key_config);
}

static int read_key(void)
{
	int ret = 0;

	ret = gpio_pin_get_logic(GPIO1, 18);

	return ret;
}

int get_key_value(void)
{
	int ret = 0;
	static unsigned char release = 1;

	if ((release == 1) && (read_key() == 0)){
		delay(10);
		release = 0;
		if(read_key() == 0)
				ret = KEY0_VALUE;
	}
	else if (read_key() == 1){
		ret = KEY_NONE;
		release = 1;
	}

	return ret;
}
