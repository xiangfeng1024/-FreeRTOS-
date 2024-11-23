#include "ControlTask.h"

PID vel,ang,Angv,Turnv;

/**********************************************************************************************************
*函 数 名: PID_Init
*功能说明: PID参数初始化
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void PID_Init(void)
{
	ang.kp=-350.0f;
	
	Angv.kp=-1.05f;
	
	vel.kp=-130.0f;
	vel.ki=-130.0/200.0f;
	
	Turnv.kp=-30.0f;
}

/**********************************************************************************************************
*函 数 名: Erect_pid
*功能说明: 位置式PID
*形    参: PID结构体句柄  期望值  实际值
*返 回 值: PID运算结果输出
**********************************************************************************************************/
float Erect_pid(PID* para,float hope, float now)
{
	(*para).err = now - hope;
	
	(*para).err_last_dev = (*para).err - (*para).err_last;
	
	(*para).out = (*para).kp*(*para).err + (*para).kd*(*para).err_last_dev + (*para).ki*(*para).err_add;
	
	(*para).err_last =  (*para).err;
	
	(*para).err_add+=(*para).err;
	if((*para).err_add>=8000) (*para).err_add=8000;
	if((*para).err_add<=-8000) (*para).err_add=-8000;
	
	return (*para).out;
}

extern QueueHandle_t SpeedQueue;        	//速度数据
extern QueueHandle_t mpu6050Queue;
extern QueueHandle_t ControlDataQueue;

void Control_task(void *pvParameters)
{
	BaseType_t err;
	int SpeedLeft,SpeedRight;
	speeds *spp;
	imu *imuss;
	YK *lanya;
	float Pitch,Yaw;
	short Gyroy;
	float PitchHope,YawHope;
	
	PID_Init();
	TIM3_Init(10000-1,72-1);  //开启控制器
	
	while(1)
	{
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);  //不覆盖任务通知，死等
		/* 读取数据 */
		if(SpeedQueue!=NULL)
		{
			err=xQueueReceive(SpeedQueue,&spp,0);  //速度数据读取不阻塞
			if(err==pdTRUE)  //获取消息成功
			{
				SpeedLeft	 = spp->Left;
				SpeedRight = spp->Right;
			}
		}
		
		if(mpu6050Queue!=NULL)
		{
			err=xQueueReceive(mpu6050Queue,&imuss,0);  //imu数据读取不阻塞
			if(err==pdTRUE)  //获取消息成功
			{
				Pitch = imuss->Pitch;
				Yaw	  = imuss->Yaw;
				Gyroy = imuss->Gyroy;
			}
		}
		
		if(ControlDataQueue!=NULL)
		{
			err=xQueueReceive(ControlDataQueue,&lanya,0);  //蓝牙数据读取不阻塞
			if(err==pdTRUE)  //获取消息成功
			{
				if(PitchHope<=20 && PitchHope>=-20) PitchHope +=lanya->Up;
				if(lanya->Up==0) PitchHope=0;
				YawHope		-=lanya->Turn;
			}
		}
		
		/* 开始控制 */
		Erect_pid(&ang,PitchHope,Pitch);
		Erect_pid(&Angv,PITCHV_HOPE,Gyroy);
		Erect_pid(&vel,SPEED_HOPE,(SpeedLeft+SpeedRight));
		Erect_pid(&Turnv,YawHope,Yaw);
		
		Motor_Write(ang.out+vel.out+Angv.out+Turnv.out,ang.out+vel.out+Angv.out-Turnv.out);
	}
}


