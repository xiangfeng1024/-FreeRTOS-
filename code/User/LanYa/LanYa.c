#include "LanYa.h"

void USART1_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

void LanYa_Init(void)
{
	USART1_Init(9600);
}

extern QueueHandle_t LanYaRxQueue;

void USART1_IRQHandler(void)
{
	u8 a;
	BaseType_t err;
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;  //判断是否需要切换任务
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		a=USART_ReceiveData(USART1);	//读取接收到的信息
		if(LanYaRxQueue != NULL) 			 //队列可用
		{
			err=xQueueSendFromISR(LanYaRxQueue, &a, &xHigherPriorityTaskWoken);
			if(err==NULL)
			{
				
			}
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}
	USART_ClearFlag(USART1,USART_FLAG_TC);	//清理串口数据 ，，，
}


