#include "LanYaTask.h"

#define DataFrameSize   5
extern QueueHandle_t LanYaRxQueue;
extern QueueHandle_t ControlDataQueue;

#define  FrameHeader  0XA5
#define  FrameEnd  		0X5A
/******************************************
函数功能：对串口屏接收的协议包进行解析
入口参数：原始协议包
返回  值：0：解析错误，协议包不正确
					1：解析正确，是要接收的数据
*******************************************/
static int LanYa_data_parse(u8 *pack)
{
	if(pack[0] != FrameHeader) 			return 0;
	if(pack[4] != FrameEnd) 			  return 0;
	return 1;
}

void LanYaRx_task(void *pvParameters)
{
	u8 i=0,Data,k=5;
	u8 DataBuff[DataFrameSize]={0};
	u8 RxFlag=0;
	
	YK lanya;
	YK *lanyas=&lanya;
	
	BaseType_t err;
	
	while(1)
	{
		if((LanYaRxQueue!=NULL))   //队列有效
		{
			err=xQueueReceive(LanYaRxQueue,&Data,portMAX_DELAY);
			if(err!=pdTRUE)	//接收错误
			{
			}
		}
		
		if(RxFlag==0 && Data==FrameHeader) //判断帧头
		{
			RxFlag=1;
			i=0;
		}
		if(RxFlag==1)  //接收到帧头，开始接收数据
		{
			DataBuff[i]=Data;
			if(i < (DataFrameSize-1) ) i++;
			else  //数据接收完，开始校验
			{
				RxFlag=0;
				i=0;
				if(LanYa_data_parse(DataBuff))  //校验成功，是要接收的数据
				{
					/* 数据处理 */
					lanya.Up=(DataBuff[2]-63)/25.0f;
					lanya.Turn=(DataBuff[1]-63)/5.0f;
					
					if((ControlDataQueue!=NULL))   //队列有效
					{
						err=xQueueSend(ControlDataQueue,&lanyas,0);
						if(err!=pdTRUE)	//发送错误
						{
							
						}
					}
					
					/* 数据包清空 */
					while(k--) DataBuff[i]=0;
					k=5;
				}
			}
		}
	}
}


