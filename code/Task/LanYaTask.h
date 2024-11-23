#ifndef _LANYATASK_H
#define _LANYATASK_H

#include "system.h"

typedef struct {
	float Up;
	float Turn;
}YK;

void LanYaRx_task(void *pvParameters);


#endif

