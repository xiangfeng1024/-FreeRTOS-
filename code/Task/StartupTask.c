#include "StartupTask.h"

#define START_TASK_PRIO 10  						//�������ȼ�
#define START_STK_SIZE 128 							//�����ջ
static TaskHandle_t StartTask_Handler; 	//������

#define LED_TASK_PRIO 5  							//�������ȼ�
#define LED_STK_SIZE 128 							//�����ջ
static TaskHandle_t LedTask_Handler; 	//������

#define LANYA_TASK_PRIO 20  						//�������ȼ�
#define LANYA_STK_SIZE 256 							//�����ջ
static TaskHandle_t LanYaTask_Handler; 	//������

#define MPU_TASK_PRIO 18  					//�������ȼ�
#define MPU_STK_SIZE 1024 					//�����ջ
TaskHandle_t MPUTask_Handler; 			//������

#define CONTROL_TASK_PRIO 19  			//�������ȼ�
#define CONTROL_STK_SIZE 512 				//�����ջ
TaskHandle_t CONTROLTask_Handler; 	//������

QueueHandle_t LanYaRxQueue;         		//������Ϣ����
#define LanYaRxQueueSize       10

QueueHandle_t mpu6050Queue;        			//imu����
#define mpu6050QueueSize       1

QueueHandle_t SpeedQueue;        	 			//�ٶ�����
#define SpeedQueueSize       	1

QueueHandle_t ControlDataQueue;    			//ң������
#define ControlDataQueueSize       	1

TaskHandle_t GetLanYaHandler(void)
{
	return LanYaTask_Handler;
}

/**********************************************************************************************************
*�� �� ��: start_task
*����˵��: ������������
*��    ��: *pvParameters
*�� �� ֵ: ��
**********************************************************************************************************/
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//�����ٽ���
	
	LanYaRxQueue = xQueueCreate(LanYaRxQueueSize, sizeof(u8));  					//�������ڽ�����Ϣ����
	mpu6050Queue = xQueueCreate(mpu6050QueueSize, sizeof(u32));   				//����imu������Ϣ����
	SpeedQueue = xQueueCreate(SpeedQueueSize, sizeof(u32));   						//�����ٶȽ�����Ϣ����
	ControlDataQueue = xQueueCreate(ControlDataQueueSize, sizeof(u32));   //����ң�����ݽ�����Ϣ����
	
	//1.�����������ڴ�������
	xTaskCreate((TaskFunction_t ) LanYaRx_task,          //������
							(char*          ) "LanYaRx",             //��������  
							(uint16_t       ) LANYA_STK_SIZE,     	 //�����ջ
							(void*          ) NULL,                	 //������������
							(UBaseType_t    ) LANYA_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  ) &LanYaTask_Handler);   //������
	
	//2.���������ƴ�������
	xTaskCreate((TaskFunction_t ) Led_task,          	 //������
							(char*          ) "Led",           		 //��������  
							(uint16_t       ) LED_STK_SIZE,     	 //�����ջ
							(void*          ) NULL,                //������������
							(UBaseType_t    ) LED_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  ) &LedTask_Handler); 	 //������
							
	//3.����imu��������
	xTaskCreate((TaskFunction_t ) mpu6050_task,        //������
							(char*          ) "MPU",           		 //��������  
							(uint16_t       ) MPU_STK_SIZE,     	 //�����ջ
							(void*          ) NULL,                //������������
							(UBaseType_t    ) MPU_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  ) &MPUTask_Handler); 	 //������
							
	//4.������������������
	xTaskCreate((TaskFunction_t ) Control_task,        			//������
							(char*          ) "Control",           			//��������  
							(uint16_t       ) CONTROL_STK_SIZE,    			//�����ջ
							(void*          ) NULL,                			//������������
							(UBaseType_t    ) CONTROL_TASK_PRIO,        //�������ȼ�
							(TaskHandle_t*  ) &CONTROLTask_Handler); 	  //������
	
	
	
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����
	
  taskEXIT_CRITICAL();            //�˳��ٽ���
}

/**********************************************************************************************************
*�� �� ��: StartupTast
*����˵��: ������ʼ������
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void StartupTask(void)
{
	//����һ�����񴴽�����������������Ҫʵ�ֹ��ܵĸ�����
	xTaskCreate((TaskFunction_t ) start_task,          //������
							(char*          ) "start_task",        //��������  
							(uint16_t       ) START_STK_SIZE,      //�����ջ
							(void*          ) NULL,                //������������
							(UBaseType_t    ) START_TASK_PRIO,     //�������ȼ�
							(TaskHandle_t*  ) &StartTask_Handler); //������
}

