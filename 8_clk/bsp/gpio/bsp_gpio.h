#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_ 

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "cc.h"

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
}GPIO_PIN_CONFIG;

void gpio_init(GPIO_Type *base, int pin, GPIO_PIN_CONFIG *config);
void gpio_pin_set_logic(GPIO_Type *base, int pin, int logic);
int gpio_pin_get_logic(GPIO_Type *base, int pin);

#endif /* ifndef BSP_GPIO_H_ */
