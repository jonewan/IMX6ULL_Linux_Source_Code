#include "main.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_clk.h"
#include "bsp_key.h"
#include "bsp_beep.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "bsp_epit.h"
#include "bsp_key_filter.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcd_api.h"

extern TFT_LCD_t tftlcd_dev;
int main(void)
{
	uint32_t colors[] = {
		LCD_BLUE,	LCD_GREEN, LCD_RED,	LCD_CYAN,	LCD_YELLOW,
		LCD_LIGHTBLUE, LCD_DARKBLUE, LCD_WHITE,	LCD_BLACK, LCD_ORANGE
	};
	uint8_t index = 0;
	/* static uint8_t state = OFF; */
	/* uint32_t color = LCD_WHITE; */
	int_init();
	imx6u_clk_init();
	clk_enable();
	delay_init();
	uart_init();
	led_init();
	beep_init();
	key_init();
	lcd_init();

	tftlcd_dev.fore_color = LCD_RED;
	tftlcd_dev.back_color = LCD_WHITE;
	/* lcd_show_string(10,10,400,32,32,(char*)"ZERO-IMX6UL ELCD TEST");  [> 显示字符串 <] */
 /*  lcd_draw_rectangle(10, 52, 1014, 290);	[> 绘制矩形框  		<] */
	/* lcd_drawline(10, 52,1014, 290);			[> 绘制线条		  	<] */
	/* lcd_drawline(10, 290,1014, 52);			[> 绘制线条 		<] */
	/* lcd_draw_Circle(512, 171, 119);			[> 绘制圆形 		<] */

	while(1){
		if(index >= 10)
			index = 0;
		/* lcd_clear(colors[index++]); */
		lcd_fill(0, 0, 20, 200, colors[index]);
		lcd_show_string(250,0,240,32,32,(char*)"INDEX=");  /*显示字符串				  */
		lcd_shownum(300, 0, index++, 2, 32); 					/* 显示数字，叠加显示	*/
		delay_ms(1000);
 /*    state = !state; */
		/* led_switch(LED0, state); */
		/* delay_ms(1000); */
	}
	return 0;
}
