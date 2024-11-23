#include "motor.h"

int PWM_MAX=7200,PWM_MIN=-7200;

/*电机初始化函数*/
void Motor_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                   //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                   //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}


void PWM_Init_TIM3(uint16_t Psc,uint16_t arr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=arr;// ARR
	TIM_TimeBaseStructure.TIM_Prescaler= Psc;// PSC分频
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);// 初始化定时器
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;// 输出使能	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;// 输出通道电平极性配置，高电平有效
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}

void Motor_Init(void)
{
	Motor_GPIO_Init();
	PWM_Init_TIM3(0,7200-1);
}

/*限幅函数*/
void Limit(int *PWMA,int *PWMB)
{
	if(*PWMA>PWM_MAX) *PWMA = PWM_MAX;
	if(*PWMA<PWM_MIN) *PWMA = PWM_MIN;
	
	if(*PWMB>PWM_MAX) *PWMB = PWM_MAX;
	if(*PWMB<PWM_MIN) *PWMB = PWM_MIN;
}

/*绝对值函数*/
int Fabs(int p)
{
	int q;
	q = p>0?p:(-p);
	return q;
}

/*************************
函数功能:驱动电机
入口参数:
PWMA or PWMB  ：载入PWM驱动电机
返回值:无
*************************/
void Motor_Write(int PWMA,int PWMB)
{
	Limit(&PWMA,&PWMB);
	if(PWMA>0) 	zuo_lun1 = 0,zuo_lun2 = 1;//PWM值大于0，正转
	else       	zuo_lun1 = 1,zuo_lun2 = 0;//PWM值小于0，反转
	TIM_SetCompare3(TIM3,Fabs(PWMA));
	
	if(PWMB>0) 	you_lun1 = 1,you_lun2 = 0;
	else 				you_lun1 = 0,you_lun2 = 1;
	TIM_SetCompare4(TIM3,Fabs(PWMB));
}

