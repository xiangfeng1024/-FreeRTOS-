#include "Mpu6050Task.h"

extern QueueHandle_t mpu6050Queue;

void mpu6050_task(void *pvParameters)
{
	imu mpu6050;
	imu *mpu=&mpu6050;
	BaseType_t err;
	volatile float Pitch,Poll,Yaw;
	
	EXTIX_Init();
	
	while(1)
	{
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);  //不覆盖任务通知，死等
		mpu_dmp_get_data(&(mpu6050.Pitch), &(mpu6050.Poll) ,&(mpu6050.Yaw));
		MPU6050_Get_Gyroscope(&(mpu6050.Gyrox), &(mpu6050.Gyroy), &(mpu6050.Gyroz));
		if((mpu6050Queue!=NULL))   //队列有效
		{
			err=xQueueSend(mpu6050Queue,&mpu,0);
			if(err!=pdTRUE)
			{
			}
		}
	}
}


