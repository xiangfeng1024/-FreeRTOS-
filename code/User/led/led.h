#ifndef _LED_H
#define _LED_H

#include "system.h"

#define LED_1        PAout(12)

#define LED_PWMOut(x)   TIM_SetCompare4(TIM1,x)

void LED_Init(void);
void PWM_Init_TIM1(uint16_t Psc,uint16_t arr);

#endif


