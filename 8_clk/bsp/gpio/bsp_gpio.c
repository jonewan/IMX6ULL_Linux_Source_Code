#include "bsp_gpio.h"

/*Initialize GPIOx Pin_x*/
void gpio_init(GPIO_Type *base, int pin, GPIO_PIN_CONFIG *config)
{
	if (config->direction == KGPIO_DIGITAL_INPUT){
		base->GDIR &= ~(1 << pin);
	}
	else{
		base->GDIR |= (1 << pin);
		
	}
}

/*Set GPIOx Pin_x Logic*/
void gpio_pin_set_logic(GPIO_Type *base, int pin, int logic)
{
	if (logic == 0){
		base->DR &= ~(1 << pin);
	}
	else{
		base->DR |= (1 << pin);
	}
}

/*Read GPIOx Pin_x Logic*/
int gpio_pin_get_logic(GPIO_Type *base, int pin)
{
	return ((base->DR >> pin) & 0x1);
}
