#include "bsp_delay.h"
#include "bsp_int.h"
#include "bsp_led.h"

/*延时初始化函数*/
void delay_init(void)
{
	GPT1->CR = 0;

	GPT1->CR = (1 << 15);
	while ((GPT1->CR >> 15) & 0x01)
		;
	/*设置GPT1时钟源为ipg_clk=66M
	 * restart模式
	 * 默认计数从0开始*/
	GPT1->CR |= (1 << 1) | (1 << 6);
	/*分频设置*/
	GPT1->PR = 65;//66分频，频率为66000000/66=1MHz
	/*在1MHz频率下，计数器值每增1代表1us*/
	GPT1->OCR[0] = 0xffffffff;
#if 0
	/*配置输出比较通道1*/
	GPT1->OCR[0] = 1000000/2;//设置中断周期为500ms
	/*打开GPT1输出比较中断*/
	GPT1->IR = (1 << 0);
	/*设置GIC*/
	GIC_EnableIRQ(GPT1_IRQn);
	/*注册中断*/
	system_register_irqhandler(GPT1_IRQn, gpt1_irqhandler, NULL);
#endif
	/*打开GPT1*/
	GPT1->CR |= (1 << 0);
}

/*微秒级延时*/
void delay_us(uint32_t us)
{
	uint32_t old_cnt = 0;
	uint32_t new_cnt = 0;
	uint32_t cnt_value = 0;

	old_cnt = GPT1->CNT;
	while (1){
		new_cnt = GPT1->CNT;
		if (new_cnt != old_cnt){
			if (new_cnt > old_cnt){
				cnt_value += (new_cnt - old_cnt);
			} else {
				cnt_value += (0xffffffff - old_cnt + new_cnt);
			}
			old_cnt = new_cnt;
			if (cnt_value >= us)
				break;
		}
	}
}

/*毫秒级延时*/
void delay_ms(uint32_t ms)
{
	while (ms--){
		delay_us(1000);
	}
}

#if 0
/*GPT1中断服务函数*/
void gpt1_irqhandler(unsigned int gicciar, void *param)
{
	static uint8_t state = 0;

	if (GPT1->SR & (1 << 0)){
		state = !state;
		led_switch(LED0, state);
	}
	/*清除中断标志位*/
	GPT1->SR |= (1 << 0);
}
#endif

/*
 * Delay function
 * */
void delay_short(volatile unsigned int n)
{
	while(n--)
		;
}

void delay(volatile unsigned int n)
{
	while(n--){
		delay_short(0x7ff);
	}
}


