#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "imx6u.h"

/*UART1的IO初始化*/
void uart_io_init(void);
/*关闭UART*/
void uart_disable(UART_Type *base);
/*使能UART*/
void uart_enable(UART_Type *base);
/*复位UART*/
void uart_soft_reset(UART_Type *base);
/*初始化uart1，波特率为115200*/
void uart_init(void);
/*通过串口发送一个字符*/
void putc(unsigned char c);
/*通过串口接收一个字符*/
unsigned char getc(void);
/*通过串口发送一串字符*/
void puts(char *str);

/*
 * @description 		: 波特率计算公式，
 *    			  	  	  可以用此函数计算出指定串口对应的UFCR，
 * 				          UBIR和UBMR这三个寄存器的值
 * @param - base		: 要计算的串口。
 * @param - baudrate	: 要使用的波特率。
 * @param - srcclock_hz	:串口时钟源频率，单位Hz
 * @return		: 无
 */
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz);

#endif /* ifndef _BSP_UART_H_ */
