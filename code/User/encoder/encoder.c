#include "encoder.h"

/**********************************************************************************************************
*�� �� ��: Encoder_TIM4_Init
*����˵��: ���������趨ʱ����ʼ��
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void Encoder_TIM4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=65535;// ARR��ֵ,��װ�ص�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler= 0;// PSC����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//������ģʽ
	
	TIM_ICStructInit(&TIM_ICStructure);//��ʼ�����벶�� 
	TIM_ICStructure.TIM_ICFilter = 10;//�˲���  
  TIM_ICInit(TIM4,&TIM_ICStructure); 
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//�����������жϱ�־λ
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//������������жϱ�־λ
	
	TIM_SetCounter(TIM4,0);//���ü���ֵΪ0�������������ֵ
	TIM_Cmd(TIM4,ENABLE);
}

/**********************************************************************************************************
*�� �� ��: Encoder_TIM2_Init
*����˵��: ���������趨ʱ����ʼ��
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void Encoder_TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=65535;// ARR��ֵ,��װ�ص�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler= 0;// PSC����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI1,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//������ģʽ
	
	TIM_ICStructInit(&TIM_ICStructure); 
	TIM_ICStructure.TIM_ICFilter = 10;//�˲���  
  TIM_ICInit(TIM2,&TIM_ICStructure); 
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//�����־λ
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	  
	TIM_SetCounter(TIM2,0);//���ü���ֵΪ0�������������ֵ
	TIM_Cmd(TIM2,ENABLE);
}

/**********************************************************************************************************
*�� �� ��: Encoder_Read
*����˵��: ��ȡָ��������
*��    ��: ��������
*�� �� ֵ: ������ֵ
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
*�� �� ��: Encoder_Init
*����˵��: �������豸��ʼ��
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void Encoder_Init(void)
{	
	Encoder_TIM2_Init();
	Encoder_TIM4_Init();
}

void TIM3_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM2ʱ��
	//��ʼ����ʱ��2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//��������ж� ,
  TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��2
}

u8 Timess=0;
extern TaskHandle_t CONTROLTask_Handler; 	//������
extern QueueHandle_t SpeedQueue;        	//�ٶ�����
void TIM3_IRQHandler(void)
{
	static speeds speed;
	static speeds *sp = &speed;
	BaseType_t err;
	BaseType_t xHigherPriorityTaskWokenSpeed=pdFALSE;  //�ж��Ƿ���Ҫ�л�����
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;  //�ж��Ƿ���Ҫ�л�����
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//����жϱ�־λ
		Timess++;
		speed.Left= Encoder_Read(2);
		speed.Right=Encoder_Read(4);
		
		if(SpeedQueue != NULL) 			 //���п���
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
