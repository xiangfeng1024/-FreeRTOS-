#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LED_1=1;
	
	PWM_Init_TIM1(0,7200-1);
	LED_PWMOut(3600);
}

void PWM_Init_TIM1(uint16_t Psc,uint16_t arr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=arr;// ARR
	TIM_TimeBaseStructure.TIM_Prescaler= Psc;// PSC分频
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);// 初始化定时器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;// 输出使能	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;// 输出通道电平极性配置，高电平有效
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_Cmd(TIM1,ENABLE);
}



