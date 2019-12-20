#include "bsp_gpio.h"

/*Initialize GPIOx Pin_x*/
void gpio_init(GPIO_Type *base, int pin, GPIO_PIN_CONFIG *config)
{
	if (config->direction == KGPIO_DIGITAL_INPUT){
		base->GDIR &= ~(1 << pin);
	}
	else{
		base->GDIR |= (1 << pin);
		/*设置默认输出低电平*/		
		gpio_pin_set_logic(base, pin, config->output_logic);
	}
	gpio_pin_int_init(base, pin, config->interrupt_mode);
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

/*Enable GPIOx Pin_xinterrupt*/
void gpio_pin_int_enable(GPIO_Type *base, int pin)
{
	base->IMR |= (1 << pin);
}

/*Disable GPIOx Pin_x interrupt*/
void gpio_pin_int_disable(GPIO_Type *base, int pin)
{
	base->IMR &= ~(1 << pin);
}

/*Clear interrupt flag*/
void gpio_pin_intflag_clear(GPIO_Type *base, int pin)
{
	base->ISR |= (1 << pin);
}

/*GPIO_x Interrupt initialize*/
void gpio_pin_int_init(GPIO_Type *base, int pin, GPIO_INTERRUPT_TYPE pin_int_mode)
{
	volatile uint32_t *icr;
	uint32_t icr_shift;

	icr_shift = pin;
	base->EDGE_SEL &= ~(1 << pin);
	if (pin < 16){
		icr = &(base->ICR1);
	} else {
		icr = &(base->ICR2);
		icr_shift -= 16;
	}
	switch (pin_int_mode) {
		case KGPIO_INT_LOW_LEVEL:
			*icr &= ~(3 << (2*icr_shift));
			break;
		case KGPIO_INT_HIGH_LEVEL:
			*icr &= ~(3 << (2*icr_shift));
			*icr |= (1 << (2*icr_shift));
			break;
		case KGPIO_INT_RISINGEDGE:
			*icr &= ~(3 << (2*icr_shift));
			*icr |= (2 << (2*icr_shift));
			break;
		case KGPIO_INT_FALLINGEDGE:
			*icr &= ~(3 << (2*icr_shift));
			*icr |= (3 << (2*icr_shift));
			break;
		default:
			break;
	}
}
