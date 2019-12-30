#ifndef _BSP_LCD_H_
#define _BSP_LCD_H_

#include "imx6u.h"

#define ATK4342	0X4342
#define ATK4384	0x4384
#define ATK7084	0x7084
#define ATK7016	0x7016
#define ATK1018	0x1018

/*显存起始地址定义*/
#define FRAM_BUFFER_ADDR	(0x89000000)

/* 颜色 */
#define LCD_BLUE		  0x000000FF
#define LCD_GREEN		  0x0000FF00
#define LCD_RED 		  0x00FF0000
#define LCD_CYAN		  0x0000FFFF
#define LCD_MAGENTA 	  0x00FF00FF
#define LCD_YELLOW		  0x00FFFF00
#define LCD_LIGHTBLUE	  0x008080FF
#define LCD_LIGHTGREEN	  0x0080FF80
#define LCD_LIGHTRED	  0x00FF8080
#define LCD_LIGHTCYAN	  0x0080FFFF
#define LCD_LIGHTMAGENTA  0x00FF80FF
#define LCD_LIGHTYELLOW   0x00FFFF80
#define LCD_DARKBLUE	  0x00000080
#define LCD_DARKGREEN	  0x00008000
#define LCD_DARKRED 	  0x00800000
#define LCD_DARKCYAN	  0x00008080
#define LCD_DARKMAGENTA   0x00800080
#define LCD_DARKYELLOW	  0x00808000
#define LCD_WHITE		  0x00FFFFFF
#define LCD_LIGHTGRAY	  0x00D3D3D3
#define LCD_GRAY		  0x00808080
#define LCD_DARKGRAY	  0x00404040
#define LCD_BLACK		  0x00000000
#define LCD_BROWN		  0x00A52A2A
#define LCD_ORANGE		  0x00FFA500
#define LCD_TRANSPARENT   0x00000000

typedef struct tft_lcd_typedef {
	uint16_t height;//屏幕高度
	uint16_t width;//屏幕宽度
	uint8_t	pixsize;//每个像素所占用的字节数
	/*帧时序时常=VSPW+VBP+LINE(height)+VFP*/
	uint16_t vspw;//帧(垂直)同步信号宽度
	uint16_t vbpd;
	uint16_t vfpd;
	/*行时序时常=HSPW+HBP+HOZVAL(width)+HFP*/
	uint16_t hspw;//行(水平)同步信号宽度
	uint16_t hbpd;
	uint16_t hfpd;
	uint32_t frame_buffer;//屏幕显存起始地址
	uint32_t fore_color;//屏幕前景色
	uint32_t back_color;//屏幕后景色
}TFT_LCD_t;

/*像素时钟初始化
 *loop_div 设置DIV_SELECT,范围27~54
 *pre_div 设置为1~8用来设置分频数
 *div 范围1~8
 *LCD_CLK = 24*loop_div/prediv/div
 * */
void lcd_clk_init(uint8_t loop_div, uint8_t pre_div, uint8_t div);
/*LCD复位*/
void lcd_reset(void);
/*LCD停止复位*/
void lcd_no_reset(void);
/*使能LCD控制器*/
void lcd_enable(void);
/*屏幕IO初始化*/
void lcd_gpio_init(void);
/*读取屏幕ID, 针对正点原子开发板*/
unsigned short lcd_read_id(void);
/*LCD初始化*/
void lcd_init(void);
/*画点函数*/
inline void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color);
/*读点函数*/
inline uint32_t lcd_read_point(uint16_t x, uint16_t y);
/*清屏函数*/
void lcd_clear(uint32_t color);
/*区块颜色填充函数*/
void lcd_fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color);

#endif /* ifndef _BSP_LCD_H_ */
