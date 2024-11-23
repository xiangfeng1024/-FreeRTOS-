#include "csb.h"

void HC_SR04_IO_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(HC_SR_Trig_PORT_RCC | HC_SR_Echo_PORT_RCC, ENABLE);	 //使能PB端口时钟
	
 GPIO_InitStructure.GPIO_Pin = HC_SR_Echo_PIN;				 // 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //推挽输出
 GPIO_Init(HC_SR_Echo_PORT, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.12
	
 GPIO_InitStructure.GPIO_Pin = HC_SR_Trig_PIN;				 // 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(HC_SR_Trig_PORT, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.13
	
	HC_SR_Trig=0;
}

void HC_SR04_Init(void)
{
	HC_SR04_IO_Init();
}

int32_t times=0;
extern u8 Timess;

float HC_SR04_Get(void)
{
	float juli;
	
	vTaskSuspendAll();  //关闭任务调度器
	
	HC_SR_Trig=1;
	delay_us(20);
	HC_SR_Trig=0;
	while(!HC_SR_Echo);
	Timess=0;
	times=TIM3->CNT;
	
	while(HC_SR_Echo);
	
	times=((TIM3->CNT)-times)+Timess*10000;
	
	juli=340.0f*times/200000.0f;
	times=0;
	
	xTaskResumeAll ();  //开启任务调度器
	return juli;
}

