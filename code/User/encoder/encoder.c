#include "encoder.h"

/**********************************************************************************************************
*函 数 名: Encoder_TIM4_Init
*功能说明: 编码器所需定时器初始化
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void Encoder_TIM4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=65535;// ARR的值,重装载的值
	TIM_TimeBaseStructure.TIM_Prescaler= 0;// PSC不分频
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//编码器模式
	
	TIM_ICStructInit(&TIM_ICStructure);//初始化输入捕获 
	TIM_ICStructure.TIM_ICFilter = 10;//滤波器  
  TIM_ICInit(TIM4,&TIM_ICStructure); 
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//清除溢出更新中断标志位
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位
	
	TIM_SetCounter(TIM4,0);//设置计数值为0，就是清除计数值
	TIM_Cmd(TIM4,ENABLE);
}

/**********************************************************************************************************
*函 数 名: Encoder_TIM2_Init
*功能说明: 编码器所需定时器初始化
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void Encoder_TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=65535;// ARR的值,重装载的值
	TIM_TimeBaseStructure.TIM_Prescaler= 0;// PSC不分频
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//编码器模式
	
	TIM_ICStructInit(&TIM_ICStructure); 
	TIM_ICStructure.TIM_ICFilter = 10;//滤波器  
  TIM_ICInit(TIM2,&TIM_ICStructure); 
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//清除标志位
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	  
	TIM_SetCounter(TIM2,0);//设置计数值为0，就是清除计数值
	TIM_Cmd(TIM2,ENABLE);
}

/**********************************************************************************************************
*函 数 名: Encoder_Read
*功能说明: 读取指定编码器
*形    参: 编码器号
*返 回 值: 编码器值
**********************************************************************************************************/
int Encoder_Read(int TIMx)
{
	int value;
	switch(TIMx)
	{
		case 4:value = (short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;
		case 2:value = (short)TIM_GetCounter(TIM2);TIM_SetCounter(TIM2,0);break;
		default:value = 0;
	}
	return value;
}

/**********************************************************************************************************
*函 数 名: Encoder_Init
*功能说明: 编码器设备初始化
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void Encoder_Init(void)
{	
	Encoder_TIM2_Init();
	Encoder_TIM4_Init();
}

void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM2时钟
	//初始化定时器2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//允许更新中断 ,
  TIM_Cmd(TIM3,ENABLE ); 	//使能定时器2
}

u8 Timess=0;
extern TaskHandle_t CONTROLTask_Handler; 	//任务句柄
extern QueueHandle_t SpeedQueue;        	//速度数据
void TIM3_IRQHandler(void)
{
	static speeds speed;
	static speeds *sp = &speed;
	BaseType_t err;
	BaseType_t xHigherPriorityTaskWokenSpeed=pdFALSE;  //判断是否需要切换任务
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;  //判断是否需要切换任务
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除中断标志位
		Timess++;
		speed.Left= Encoder_Read(2);
		speed.Right=Encoder_Read(4);
		
		if(SpeedQueue != NULL) 			 //队列可用
		{
			err=xQueueSendFromISR(SpeedQueue, &sp, &xHigherPriorityTaskWokenSpeed);
			if(err==NULL)
			{
			}
		}
		
		vTaskNotifyGiveFromISR(CONTROLTask_Handler, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}
