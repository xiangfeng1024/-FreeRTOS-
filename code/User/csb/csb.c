#include "csb.h"

void HC_SR04_IO_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(HC_SR_Trig_PORT_RCC | HC_SR_Echo_PORT_RCC, ENABLE);	 //ʹ��PB�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = HC_SR_Echo_PIN;				 // �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //�������
 GPIO_Init(HC_SR_Echo_PORT, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.12
	
 GPIO_InitStructure.GPIO_Pin = HC_SR_Trig_PIN;				 // �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(HC_SR_Trig_PORT, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.13
	
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
	
	vTaskSuspendAll();  //�ر����������
	
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
	
	xTaskResumeAll ();  //�������������
	return juli;
}

