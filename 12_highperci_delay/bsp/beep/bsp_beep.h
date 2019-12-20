#ifndef _BSP_BEEP_H_
#define _BSP_BEEP_H_ 

#include "cc.h"
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

void beep_init(void);
void beep_switch(int status);

#endif /* ifndef _BSP_BEEP_H_ */

