#include "bsp_lcd.h"
#include "bsp_gpio.h"
#include "stdio.h"
#include "bsp_delay.h"

/*屏幕参数结构体变量*/
TFT_LCD_t tftlcd_dev;

/*像素时钟初始化
 *loop_div 设置DIV_SELECT,范围27~54
 *pre_div 设置为1~8用来设置分频数
 *div 范围1~8
 *LCD_CLK = 24*loop_div/prediv/div
 * */
void lcd_clk_init(uint8_t loop_div, uint8_t pre_div, uint8_t div)
{
	if (loop_div < 27)
		loop_div = 27;
	else if (loop_div > 54)
		loop_div = 54;

	if (pre_div < 1)
		pre_div = 1;
	else if (pre_div > 8)
		pre_div = 8;

	if (div < 1)
		div = 1;
	else if (div > 8)
		div = 8;

	/*不使用小数分频*/
	CCM_ANALOG->PLL_VIDEO_NUM = 0;
	CCM_ANALOG->PLL_VIDEO_DENOM = 0;
	CCM_ANALOG->PLL_VIDEO = (1 << 13) | (2 << 19) | (loop_div << 0);
	CCM_ANALOG->MISC2 &= ~(3 << 30);
	CCM->CSCDR2 &= ~(7 << 15);
	CCM->CSCDR2 |= (2 << 15);

	CCM->CSCDR2 &= ~(7 << 12);
	CCM->CSCDR2 |= ((pre_div-1) << 12);

	CCM->CBCMR &= ~(7 << 23);
	CCM->CBCMR |= ((div-1) << 23);

	CCM->CSCDR2 &= ~(7 << 9);
	CCM->CSCDR2 |= (0 << 9);
}

/*LCD复位*/
void lcd_reset(void)
{
	LCDIF->CTRL |= 1 << 31;
}

/*LCD停止复位*/
void lcd_no_reset(void)
{
	LCDIF->CTRL &= ~(1 << 31);
}

/*使能LCD控制器*/
void lcd_enable(void)
{
	LCDIF->CTRL |= (1 << 0);
}

/*读取屏幕ID, 针对正点原子开发板*/
unsigned short lcd_read_id(void)
{
	unsigned char id;
	/*打开模拟开关，设置LCD_VSYNC为高电平*/
	GPIO_PIN_CONFIG lcd_gpio_config;

	IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_GPIO3_IO03, 0);/*复用为GPIO5_IO01*/
	IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_GPIO3_IO03,0x10B0);

	/*GPIO初始化*/
	lcd_gpio_config.direction = KGPIO_DIGITAL_OUTPUT;
	lcd_gpio_config.output_logic = 1;
	gpio_init(GPIO3, 3, &lcd_gpio_config);

	/*读取屏幕ID*/
	/*设置管教复用为I/O功能*/
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_GPIO3_IO12, 0);/*复用B7*/
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_GPIO3_IO20, 0);/*复用G7*/
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_GPIO3_IO28, 0);/*复用R7*/

	/*设置电器属性为输入功能*/
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_GPIO3_IO12,0xf080);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_GPIO3_IO20,0xf080);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_GPIO3_IO28,0xf080);

	/*GPIO初始化*/
	lcd_gpio_config.direction = KGPIO_DIGITAL_INPUT;
	gpio_init(GPIO3, 12, &lcd_gpio_config);
	gpio_init(GPIO3, 20, &lcd_gpio_config);
	gpio_init(GPIO3, 28, &lcd_gpio_config);

	/*读取ID*/
	id = (unsigned char)gpio_pin_get_logic(GPIO3, 12);
	id |= (unsigned char)gpio_pin_get_logic(GPIO3, 20) << 1;
	id |= (unsigned char)gpio_pin_get_logic(GPIO3, 28) << 2;

	if (id == 0x0)
		return ATK4342;
	else if (id == 0x1)
		return ATK7084;
	else if (id == 0x2)
		return ATK7016;
	else if (id == 0x4)
		return ATK4384;
	else if (id == 0x5)
		return ATK1018;
	else
		return 0;
}

/*屏幕IO初始化*/
void lcd_gpio_init(void)
{
	GPIO_PIN_CONFIG bl_gpio_config;
	/* 1、IO初始化复用功能 */
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0);
	/* 背光BL引脚 */
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08,0);
	/* 2、配置LCD IO属性
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 0 默认22K上拉
	 *bit [13]: 0 pull功能
	 *bit [12]: 0 pull/keeper使能
	 *bit [11]: 0 关闭开路输出
	 *bit [7:6]: 10 速度100Mhz
	 *bit [5:3]: 111 驱动能力为R0/7
	 *bit [0]: 1 高转换率
	 */
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0xB9);
	/* 背光BL引脚*/
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08,0x10B0);

	bl_gpio_config.direction = KGPIO_DIGITAL_OUTPUT;
	bl_gpio_config.output_logic = 1;
	gpio_init(GPIO1, 8, &bl_gpio_config);
}

/*LCD初始化*/
void lcd_init(void)
{
	unsigned short lcd_id;

	lcd_id = lcd_read_id();
	printf("LCD ID=%x\r\n", lcd_id);
	lcd_gpio_init();//初始化屏幕IO
	lcd_reset();//复位
	delay_ms(10);
	lcd_no_reset();//停止复位

	/*初始化LCD控制器*/
	tftlcd_dev.frame_buffer = FRAM_BUFFER_ADDR;
	tftlcd_dev.pixsize = 4;//采用ARGB888格式编码，占用4字节
	tftlcd_dev.fore_color = LCD_WHITE;
	tftlcd_dev.back_color = LCD_BLACK;
	/*根据屏幕ID配置寄存器，设置兼容性*/
	switch (lcd_id) {
		case ATK4342:
			tftlcd_dev.width = 480;
			tftlcd_dev.height = 272;
			tftlcd_dev.hspw = 1;
			tftlcd_dev.hbpd = 40;
			tftlcd_dev.hfpd = 5;
			tftlcd_dev.vspw = 1;
			tftlcd_dev.vbpd = 8;
			tftlcd_dev.vfpd = 8;
			lcd_clk_init(27, 8, 8);//10.1MHz
			break;
		case ATK4384:
			tftlcd_dev.height = 480;
			tftlcd_dev.width = 800;
			tftlcd_dev.vspw = 3;
			tftlcd_dev.vbpd = 32;
			tftlcd_dev.vfpd = 13;
			tftlcd_dev.hspw = 48;
			tftlcd_dev.hbpd = 88;
			tftlcd_dev.hfpd = 40;
			lcd_clk_init(42, 4, 8);//31.5Mhz
			break;
		case ATK7084:
			tftlcd_dev.height = 480;
			tftlcd_dev.width = 800;
			tftlcd_dev.vspw = 1;
			tftlcd_dev.vbpd = 23;
			tftlcd_dev.vfpd = 22;
			tftlcd_dev.hspw = 1;
			tftlcd_dev.hbpd = 46;
			tftlcd_dev.hfpd = 210;
			lcd_clk_init(30,3,7);//34.2Mhz
			break;
		case ATK7016:
			tftlcd_dev.height = 600;
			tftlcd_dev.width = 1024;
			tftlcd_dev.vspw = 3;
			tftlcd_dev.vbpd = 20;
			tftlcd_dev.vfpd = 12;
			tftlcd_dev.hspw = 20;
			tftlcd_dev.hbpd = 140;
			tftlcd_dev.hfpd = 160;
			lcd_clk_init(32,3,5);//51.2Mhz
			break;
	}

	/*LCD控制寄存器配置*/
	LCDIF->CTRL = 0;
	LCDIF->CTRL |= (1 << 5) | (3 << 8) | (3 << 10)
									| (1 << 17) | (1 << 19);
	LCDIF->CTRL1 = 0;
	LCDIF->CTRL1 |= (7 << 16);
	LCDIF->TRANSFER_COUNT = 0;
	LCDIF->TRANSFER_COUNT = (tftlcd_dev.height << 16) |
													(tftlcd_dev.width << 0);
	LCDIF->VDCTRL0 = 0;
	LCDIF->VDCTRL0 |= (tftlcd_dev.vspw << 0) | (1 << 20) |
										(1 << 21) | (1 << 24) | (1 << 28);
	LCDIF->VDCTRL1 = tftlcd_dev.vspw + tftlcd_dev.vbpd +
									 tftlcd_dev.height + tftlcd_dev.vfpd;
	LCDIF->VDCTRL2 = ((tftlcd_dev.hspw + tftlcd_dev.hbpd +
									 tftlcd_dev.width + tftlcd_dev.hfpd) << 0)|
									 (tftlcd_dev.hspw << 18);
	LCDIF->VDCTRL3 = ((tftlcd_dev.vbpd + tftlcd_dev.vspw) << 0) |
										((tftlcd_dev.hbpd + tftlcd_dev.hspw) << 16);
	LCDIF->VDCTRL4 = (tftlcd_dev.width) | (1 << 18);
	LCDIF->CUR_BUF = tftlcd_dev.frame_buffer;
	LCDIF->NEXT_BUF = tftlcd_dev.frame_buffer;

	/*使能lcd*/
	lcd_enable();
	delay_ms(20);
	lcd_clear(LCD_BLUE);
}

/*画点函数*/
inline void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
	*(uint32_t *)((uint32_t)tftlcd_dev.frame_buffer +
								(uint32_t)tftlcd_dev.pixsize * ((uint32_t)tftlcd_dev.width *
								(uint32_t)y + (uint32_t)x)) = color;
}

/*读点函数*/
inline uint32_t lcd_read_point(uint16_t x, uint16_t y)
{
	return *(uint32_t *)((uint32_t)tftlcd_dev.frame_buffer +
								(uint32_t)tftlcd_dev.pixsize * ((uint32_t)tftlcd_dev.width *
								(uint32_t)y + (uint32_t)x));
}

/*清屏函数*/
void lcd_clear(uint32_t color)
{
	uint32_t *point_addr = (uint32_t *)tftlcd_dev.frame_buffer;
	uint32_t pixel_count = (uint32_t)tftlcd_dev.height * (uint32_t)tftlcd_dev.width;
	uint32_t i = 0;

	for (i = 0 ; i < pixel_count; i++)
		point_addr[i] = color;
}

/*区块颜色填充函数*/
void lcd_fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
	uint16_t x, y;

	if(x0 < 0) x0 = 0;
	if(y0 < 0) y0 = 0;
	if(x1 >= tftlcd_dev.width) x1 = tftlcd_dev.width - 1;
	if(y1 >= tftlcd_dev.height) y1 = tftlcd_dev.height - 1;

	for(y = y0; y <= y1; y++){
		for(x = x0; x <= x1; x++)
		lcd_draw_point(x, y, color);
	}
}
