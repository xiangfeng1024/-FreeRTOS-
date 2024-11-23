#include "LanYaTask.h"

#define DataFrameSize   5
extern QueueHandle_t LanYaRxQueue;
extern QueueHandle_t ControlDataQueue;

#define  FrameHeader  0XA5
#define  FrameEnd  		0X5A
/******************************************
�������ܣ��Դ��������յ�Э������н���
��ڲ�����ԭʼЭ���
����  ֵ��0����������Э�������ȷ
					1��������ȷ����Ҫ���յ�����
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
		if((LanYaRxQueue!=NULL))   //������Ч
		{
			err=xQueueReceive(LanYaRxQueue,&Data,portMAX_DELAY);
			if(err!=pdTRUE)	//���մ���
			{
			}
		}
		
		if(RxFlag==0 && Data==FrameHeader) //�ж�֡ͷ
		{
			RxFlag=1;
			i=0;
		}
		if(RxFlag==1)  //���յ�֡ͷ����ʼ��������
		{
			DataBuff[i]=Data;
			if(i < (DataFrameSize-1) ) i++;
			else  //���ݽ����꣬��ʼУ��
			{
				RxFlag=0;
				i=0;
				if(LanYa_data_parse(DataBuff))  //У��ɹ�����Ҫ���յ�����
				{
					/* ���ݴ��� */
					lanya.Up=(DataBuff[2]-63)/25.0f;
					lanya.Turn=(DataBuff[1]-63)/5.0f;
					
					if((ControlDataQueue!=NULL))   //������Ч
					{
						err=xQueueSend(ControlDataQueue,&lanyas,0);
						if(err!=pdTRUE)	//���ʹ���
						{
							
						}
					}
					
					/* ���ݰ���� */
					while(k--) DataBuff[i]=0;
					k=5;
				}
			}
		}
	}
}


