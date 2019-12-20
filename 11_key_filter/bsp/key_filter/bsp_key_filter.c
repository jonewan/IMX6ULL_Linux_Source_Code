#include "bsp_key_filter.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_beep.h"

/*key_filter初始化*/
void key_filter_init(void)
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
	system_register_irqhandler(GPIO1_Combined_16_31_IRQn, gpio1_16_31_irqhandler, NULL);
	gpio_pin_int_enable(GPIO1, 18);
	filter_timer_init(66000000/100);//定时器设置为10ms
}

/*初始化EPIT1定时器*/
void filter_timer_init(uint32_t value)
{
	/*配置EPIT1_CR寄存器*/
	EPIT1->CR = 0;
	EPIT1->CR = (1 << 1) | (1 << 2) |
							(1 << 3) | (1 << 24);
	EPIT1->LR = value;//设置加载值
	EPIT1->CMPR = 0;//设置比较寄存器的值为0

	/*初始化中断*/
	GIC_EnableIRQ(EPIT1_IRQn);
	system_register_irqhandler(EPIT1_IRQn, filter_timer_irqhandler, NULL);
}

/*关闭EPIT1定时器*/
void filter_timer_stop(void)
{
	EPIT1->CR &= ~(1 << 0);
}

/*重启EPIT1定时器*/
void filter_timer_restart(uint32_t value)
{
	EPIT1->CR &= ~(1 << 0);
	EPIT1->LR = value;
	EPIT1->CR |= (1 << 0);
}

/*EPIT1定时器中断处理函数*/
void filter_timer_irqhandler(unsigned int gicciar, void *param)
{
	static uint8_t state = OFF;

	if (EPIT1->SR &(1 << 0)){
		/*关闭定时器*/
		filter_timer_stop();
		if (gpio_pin_get_logic(GPIO1, 18) == 0){
			state = !state;
			beep_switch(state);
		}
	}
	EPIT1->SR |= (1 << 0);
}

/*按键中断服务函数*/
void gpio1_16_31_irqhandler(unsigned int gicciar, void *param)
{
	/*开启定时器*/
	filter_timer_restart(66000000/100);
	/*清除中断标志位*/
	gpio_pin_intflag_clear(GPIO1, 18);

}

