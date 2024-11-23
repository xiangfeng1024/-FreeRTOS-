#ifndef _ENCODER_H
#define _ENCODER_H

#include "system.h"

typedef struct {
	int Left;
	int Right;
}speeds;

void Encoder_Init(void);
void Encoder_TIM4_Init(void);
void Encoder_TIM3_Init(void);
int Encoder_Read(int TIMx);
void TIM3_Init(u16 arr,u16 psc);

#endif


