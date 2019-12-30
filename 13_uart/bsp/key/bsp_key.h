#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_ 

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_delay.h"

/*按键值*/
/*! \enum KEY_VAL
 *
 *  Detailed description
 */
enum KEY_VAL {
	KEY_NONE = 0,
	KEY0_VALUE,
};

void key_init(void);
int get_key_value(void);

#endif /* ifndef _BSP_KEY_H_ */
