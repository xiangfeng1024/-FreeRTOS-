#include "usart.h"		 

//void USART1_Init(u32 bound)
//{
//   //GPIO端口设置
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
////	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
// 
//	
//	/*  配置GPIO的模式和IO口 */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
//	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
//	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
//	

//	//USART1 初始化设置
//	USART_InitStructure.USART_BaudRate = bound;//波特率设置
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
//	USART_Init(USART1, &USART_InitStructure); //初始化串口1
//	
//	USART_Cmd(USART1, ENABLE);  //使能串口1 
//	
////	USART_ClearFlag(USART1, USART_FLAG_TC);
////		
////	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

////	//Usart1 NVIC 配置
////	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
////	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
////	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
////	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
////	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	
//}

//void USART2_Init(u32 bound)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
// 
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//	
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART2, &USART_InitStructure);
//	
//	USART_ClearFlag(USART2, USART_FLAG_TC);
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	USART_Cmd(USART2, ENABLE);
//}

//void USART3_Init(u32 bound)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
// 
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOB,&GPIO_InitStructure); 
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOB,&GPIO_InitStructure); 
//	
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART3, &USART_InitStructure);
//	
//	USART_ClearFlag(USART3, USART_FLAG_TC);
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//	USART_Cmd(USART3, ENABLE);
//}

//void USART4_Init(u32 bound)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
// 
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(UART4, &USART_InitStructure);
//	
//	USART_ClearFlag(UART4, USART_FLAG_TC);
//	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
//	USART_Cmd(UART4, ENABLE);
//}

//void USART5_Init(u32 bound)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
// 
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOD,&GPIO_InitStructure);
//	
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(UART5, &USART_InitStructure);
//	
//	USART_ClearFlag(UART5, USART_FLAG_TC);
//	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
//	USART_Cmd(UART5, ENABLE);
//}

//void USART1_IRQHandler(void)
//{
//	u8 x;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
//	{
//		x=USART_ReceiveData(USART1);
//		USART_SendData(USART1,x);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);	//等待数据发送结束
//	}
//	USART_ClearFlag(USART1,USART_FLAG_TC);	//清理串口数据 ，，，
//}

//void UART4_IRQHandler(void)
//{
//	u8 x;
//	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)
//	{
//		x=USART_ReceiveData(UART4);	
//		USART_SendData(UART4,x);
//		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);	//等待数据发送结束
//	}
//	USART_ClearFlag(UART4,USART_FLAG_TC);	//清理串口数据 ，，，
//}


//int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
//{
//	USART_SendData(USART1,(u8)ch);	
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
//	return ch;
//}
