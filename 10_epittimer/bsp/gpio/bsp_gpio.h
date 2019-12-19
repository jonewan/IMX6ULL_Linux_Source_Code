#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_ 

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"

/*中断触发类型*/
/*! \enum GPIO_INTERRUPT_TYPE
 *
 *  Detailed description
 */
typedef enum GPIO_INTERRUPT_TYPE {
	KGPIO_NO_INT_MODE = 0U,
	KGPIO_INT_LOW_LEVEL = 1U,
	KGPIO_INT_HIGH_LEVEL = 2U,
	KGPIO_INT_RISINGEDGE = 3U,
	KGPIO_INT_FALLINGEDGE = 4U,
	KGPIO_INT_RISING_OR_FALLING_EDGE = 5U,
}GPIO_INTERRUPT_TYPE;

/*! \enum GPIO_PIN_DIRECTION
 *
 *  Detailed description
 */
typedef enum GPIO_PIN_DIRECTION {
	KGPIO_DIGITAL_INPUT = 0U,
	KGPIO_DIGITAL_OUTPUT = 1U,
}GPIO_PIN_DIRECTION;

typedef struct GPIO_PIN_CONFIG {
	/* data */
	GPIO_PIN_DIRECTION direction;
	uint8_t output_logic;
	GPIO_INTERRUPT_TYPE interrupt_mode;//中断方式
}GPIO_PIN_CONFIG;

void gpio_init(GPIO_Type *base, int pin, GPIO_PIN_CONFIG *config);
void gpio_pin_set_logic(GPIO_Type *base, int pin, int logic);
int gpio_pin_get_logic(GPIO_Type *base, int pin);
/*Enable GPIOx Pin_xinterrupt*/
void gpio_pin_int_enable(GPIO_Type *base, int pin);
/*Disable GPIOx Pin_x interrupt*/
void gpio_pin_int_disable(GPIO_Type *base, int pin);
/*Clear interrupt flag*/
void gpio_pin_intflag_clear(GPIO_Type *base, int pin);
/*GPIO_x Interrupt initialize*/
void gpio_pin_int_init(GPIO_Type *base, int pin, GPIO_INTERRUPT_TYPE pin_int_mode);

#endif /* ifndef BSP_GPIO_H_ */
