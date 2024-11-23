#include "system.h"

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); 
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;                //Openmv
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=8;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;               //IMU
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=9;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;               	 //¿ØÖÆÖÜÆÚ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

