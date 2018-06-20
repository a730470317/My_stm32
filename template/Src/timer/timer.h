#ifndef __TIMER_H__
#define __TIMER_H__
#include "stm32h7xx_hal.h"
/* TIM7 init function */

void MX_TIM2_Init(void);
void MX_TIM3_Init(void);
void MX_TIM7_Init(void);
void PWM_TIM15_Init(void);

#define _Error_Handler(file,line) printf("%s, %d", __FILE__, __LINE__);

#endif