#include "system.h"

int main(void)
{
	System_Init();  					//系统初始化
	StartupTask();						//任务创建初始化
	vTaskStartScheduler();  	//开启任务调度
	
	while(1)
	{
	}
}

/**********************************************************************************************************
*函 数 名: System_Init
*功能说明: 系统初始化
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void System_Init(void)
{
	SysTick_Init();           //滴答计时器初始化
	NVIC_Config();						//NVIC配置
	LED_Init();								//LED
	Motor_Init();							//电机
	LanYa_Init();							//蓝牙
	KEY_GPIO_Init();     			//按键
	HC_SR04_Init();						//超声波
	Encoder_Init();						//编码器
	MPU6050_Init();						//陀螺仪
	mpu_dmp_init();
}

