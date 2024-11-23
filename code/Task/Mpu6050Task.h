#ifndef _MPU6050TASK_H
#define _MPU6050TASK_H

#include "system.h"

typedef struct {
	float Pitch;
	float Poll;
	float Yaw;
	
	short Gyrox;
	short Gyroy;
	short Gyroz;
}imu;


void mpu6050_task(void *pvParameters);



#endif

