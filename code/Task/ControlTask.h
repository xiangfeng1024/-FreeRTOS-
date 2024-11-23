#ifndef _CONTROLTASK_H
#define _CONTROLTASK_H

#include "system.h"

#define PITCHV_HOPE   0
#define YAW_HOPE      0

#define SPEED_HOPE    0


typedef struct{
	float kp;
	float ki;
	float kd;
	
	float err;
	float err_last;
	float err_last_dev;
	float err_add;
	
	float out;
}PID;

void Control_task(void *pvParameters);


#endif


