#include "bsp_key.h"

void key_init(void)
{
	/*复用为GPIO1_IO18*/
	IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
	/*设置为输入*/
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

	GPIO1->GDIR &= ~(1 << 18);
}

static int read_key(void)
{
	int ret = 0;

	ret = (GPIO1->DR >> 18) & 0X1;

	return ret;
}

int get_key_value(void)
{
	int ret = 0;
	static unsigned char release = 1;

	if ((release == 1) && (read_key() == 0)){
		delay(10);
		release = 0;
		if(read_key() == 0)
				ret = KEY0_VALUE;
	}
	else if (read_key() == 1){
		ret = KEY_NONE;
		release = 1;
	}

	return ret;
}
