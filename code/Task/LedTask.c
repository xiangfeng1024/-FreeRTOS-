#include "LedTask.h"

void Led_task(void *pvParameters)
{
	volatile u16 i=0,k=0,j1=0,j2=100;
	u8 TickCnt=0;
	volatile float juli;
	while(1)
	{
		if(k==0)  i+=70;
		else			i-=70;
		LED_PWMOut(i);
		if(i>=7000 | i<=0) k=~k;
		if((TickCnt++)==30) 
		{
			juli=HC_SR04_Get();
			j2=juli*100.0f/15.0f;
		}
		if((j1++)>=j2) 
		{
			LED_1=~LED_1;
			j1=0;
		}
		vTaskDelay(10);
	}
}

