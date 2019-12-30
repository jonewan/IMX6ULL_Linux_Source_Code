#ifndef _BSP_LCD_API_H_
#define _BSP_LCD_API_H_

#include "imx6u.h"
#include "bsp_lcd.h"

/*
 * @description		: 画线函数
 * @param - x1		: 线起始点坐标X轴
 * @param - y1		: 线起始点坐标Y轴
 * @param - x2		: 线终止点坐标X轴
 * @param - y2		: 线终止点坐标Y轴
 * @return 			: 无
 */
void lcd_drawline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/*
 * @description	: 画矩形函数
 * @param - x1	: 矩形坐上角坐标X轴
 * @param - y1	: 矩形坐上角坐标Y轴
 * @param - x2	: 矩形右下角坐标X轴
 * @param - y2	: 矩形右下角坐标Y轴
 * @return 		: 无
 */
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/*
 * @description	: 在指定位置画一个指定大小的圆
 * @param - x0	: 圆心坐标X轴
 * @param - y0	: 圆心坐标Y轴
 * @param - y2	: 圆形半径
 * @return 		: 无
 */
void lcd_draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);

/*
 * @description	: 在指定位置显示一个字符
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - num	: 显示字符
 * @param - size: 字体大小, 可选12/16/24/32
 * @param - mode: 叠加方式(1)还是非叠加方式(0)
 * @return 		: 无
 */
void lcd_showchar(uint16_t x, uint16_t y,
				      uint8_t num, uint8_t size,
				      uint8_t mode);

/*
 * @description	: 计算m的n次方
 * @param - m	: 要计算的值
 * @param - n	: n次方
 * @return 		: m^n次方.
 */
uint32_t lcd_pow(uint8_t m,uint8_t n);

/*
 * @description	: 显示指定的数字，高位为0的话不显示
 * @param - x	: 起始坐标点X轴。
 * @param - y	: 起始坐标点Y轴。
 * @param - num	: 数值(0~999999999)。
 * @param - len : 数字位数。
 * @param - size: 字体大小
 * @return 		: 无
 */
void lcd_shownum(uint16_t x,
					 uint16_t y,
					 uint32_t num,
					 uint8_t len,
					 uint8_t size);

/*
 * @description		: 显示指定的数字，高位为0,还是显示
 * @param - x	 	: 起始坐标点X轴。
 * @param - y	 	: 起始坐标点Y轴。
 * @param - num		: 数值(0~999999999)。
 * @param - len 	: 数字位数。
 * @param - size	: 字体大小
 * @param - mode	: [7]:0,不填充;1,填充0.
 * 					  [6:1]:保留
 *					  [0]:0,非叠加显示;1,叠加显示.
 * @return 	 		: 无
 */
void lcd_showxnum(uint16_t x, uint16_t y,
					  uint32_t num, uint8_t len,
					  uint8_t size, uint8_t mode);

/*
 * @description		: 显示一串字符串
 * @param - x		: 起始坐标点X轴。
 * @param - y		: 起始坐标点Y轴。
 * @param - width 	: 字符串显示区域长度
 * @param - height	: 字符串显示区域高度
 * @param - size	: 字体大小
 * @param - p		: 要显示的字符串首地址
 * @return 			: 无
 */
void lcd_show_string(uint16_t x,uint16_t y,
						  uint16_t width,uint16_t height,
						  uint8_t size,char *p);

#endif /* ifndef _BSP_LCD_API_H_ */
