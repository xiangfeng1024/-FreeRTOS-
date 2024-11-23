#include "ControlTask.h"

PID vel,ang,Angv,Turnv;

/**********************************************************************************************************
*�� �� ��: PID_Init
*����˵��: PID������ʼ��
*��    ��: ��
*�� �� ֵ: ��
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
*�� �� ��: Erect_pid
*����˵��: λ��ʽPID
*��    ��: PID�ṹ����  ����ֵ  ʵ��ֵ
*�� �� ֵ: PID���������
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

extern QueueHandle_t SpeedQueue;        	//�ٶ�����
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
	TIM3_Init(10000-1,72-1);  //����������
	
	while(1)
	{
		ulTaskNotifyTake(pdFALSE, portMAX_DELAY);  //����������֪ͨ������
		/* ��ȡ���� */
		if(SpeedQueue!=NULL)
		{
			err=xQueueReceive(SpeedQueue,&spp,0);  //�ٶ����ݶ�ȡ������
			if(err==pdTRUE)  //��ȡ��Ϣ�ɹ�
			{
				SpeedLeft	 = spp->Left;
				SpeedRight = spp->Right;
			}
		}
		
		if(mpu6050Queue!=NULL)
		{
			err=xQueueReceive(mpu6050Queue,&imuss,0);  //imu���ݶ�ȡ������
			if(err==pdTRUE)  //��ȡ��Ϣ�ɹ�
			{
				Pitch = imuss->Pitch;
				Yaw	  = imuss->Yaw;
				Gyroy = imuss->Gyroy;
			}
		}
		
		if(ControlDataQueue!=NULL)
		{
			err=xQueueReceive(ControlDataQueue,&lanya,0);  //�������ݶ�ȡ������
			if(err==pdTRUE)  //��ȡ��Ϣ�ɹ�
			{
				if(PitchHope<=20 && PitchHope>=-20) PitchHope +=lanya->Up;
				if(lanya->Up==0) PitchHope=0;
				YawHope		-=lanya->Turn;
			}
		}
		
		/* ��ʼ���� */
		Erect_pid(&ang,PitchHope,Pitch);
		Erect_pid(&Angv,PITCHV_HOPE,Gyroy);
		Erect_pid(&vel,SPEED_HOPE,(SpeedLeft+SpeedRight));
		Erect_pid(&Turnv,YawHope,Yaw);
		
		Motor_Write(ang.out+vel.out+Angv.out+Turnv.out,ang.out+vel.out+Angv.out-Turnv.out);
	}
}


