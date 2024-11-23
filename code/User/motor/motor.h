#ifndef _MOTOR_H
#define _MOTOR_H

#include "system.h"

#define zuo_lun1        PAout(3)
#define zuo_lun2        PAout(4)
#define you_lun1        PBout(12)
#define you_lun2        PBout(13)
 
void Motor_GPIO_Init(void);
void Motor_Init(void);
int Fabs(int p);
void Motor_Write(int PWMA,int PWMB);
void Limit(int *PWMA,int *PWMB);

#endif


