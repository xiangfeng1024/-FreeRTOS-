#include "system.h"

int main(void)
{
	System_Init();  					//ϵͳ��ʼ��
	StartupTask();						//���񴴽���ʼ��
	vTaskStartScheduler();  	//�����������
	
	while(1)
	{
	}
}

/**********************************************************************************************************
*�� �� ��: System_Init
*����˵��: ϵͳ��ʼ��
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void System_Init(void)
{
	SysTick_Init();           //�δ��ʱ����ʼ��
	NVIC_Config();						//NVIC����
	LED_Init();								//LED
	Motor_Init();							//���
	LanYa_Init();							//����
	KEY_GPIO_Init();     			//����
	HC_SR04_Init();						//������
	Encoder_Init();						//������
	MPU6050_Init();						//������
	mpu_dmp_init();
}

