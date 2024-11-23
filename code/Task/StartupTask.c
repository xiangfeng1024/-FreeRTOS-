#include "StartupTask.h"

#define START_TASK_PRIO 10  						//任务优先级
#define START_STK_SIZE 128 							//任务堆栈
static TaskHandle_t StartTask_Handler; 	//任务句柄

#define LED_TASK_PRIO 5  							//任务优先级
#define LED_STK_SIZE 128 							//任务堆栈
static TaskHandle_t LedTask_Handler; 	//任务句柄

#define LANYA_TASK_PRIO 20  						//任务优先级
#define LANYA_STK_SIZE 256 							//任务堆栈
static TaskHandle_t LanYaTask_Handler; 	//任务句柄

#define MPU_TASK_PRIO 18  					//任务优先级
#define MPU_STK_SIZE 1024 					//任务堆栈
TaskHandle_t MPUTask_Handler; 			//任务句柄

#define CONTROL_TASK_PRIO 19  			//任务优先级
#define CONTROL_STK_SIZE 512 				//任务堆栈
TaskHandle_t CONTROLTask_Handler; 	//任务句柄

QueueHandle_t LanYaRxQueue;         		//串口消息队列
#define LanYaRxQueueSize       10

QueueHandle_t mpu6050Queue;        			//imu数据
#define mpu6050QueueSize       1

QueueHandle_t SpeedQueue;        	 			//速度数据
#define SpeedQueueSize       	1

QueueHandle_t ControlDataQueue;    			//遥控数据
#define ControlDataQueueSize       	1

TaskHandle_t GetLanYaHandler(void)
{
	return LanYaTask_Handler;
}

/**********************************************************************************************************
*函 数 名: start_task
*功能说明: 创建所有任务
*形    参: *pvParameters
*返 回 值: 无
**********************************************************************************************************/
void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//进入临界区
	
	LanYaRxQueue = xQueueCreate(LanYaRxQueueSize, sizeof(u8));  					//创建串口接收消息队列
	mpu6050Queue = xQueueCreate(mpu6050QueueSize, sizeof(u32));   				//创建imu接收消息队列
	SpeedQueue = xQueueCreate(SpeedQueueSize, sizeof(u32));   						//创建速度接收消息队列
	ControlDataQueue = xQueueCreate(ControlDataQueueSize, sizeof(u32));   //创建遥控数据接收消息队列
	
	//1.创建蓝牙串口处理任务
	xTaskCreate((TaskFunction_t ) LanYaRx_task,          //任务函数
							(char*          ) "LanYaRx",             //任务名字  
							(uint16_t       ) LANYA_STK_SIZE,     	 //任务堆栈
							(void*          ) NULL,                	 //传入的任务参数
							(UBaseType_t    ) LANYA_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  ) &LanYaTask_Handler);   //任务句柄
	
	//2.创建呼吸灯处理任务
	xTaskCreate((TaskFunction_t ) Led_task,          	 //任务函数
							(char*          ) "Led",           		 //任务名字  
							(uint16_t       ) LED_STK_SIZE,     	 //任务堆栈
							(void*          ) NULL,                //传入的任务参数
							(UBaseType_t    ) LED_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  ) &LedTask_Handler); 	 //任务句柄
							
	//3.创建imu处理任务
	xTaskCreate((TaskFunction_t ) mpu6050_task,        //任务函数
							(char*          ) "MPU",           		 //任务名字  
							(uint16_t       ) MPU_STK_SIZE,     	 //任务堆栈
							(void*          ) NULL,                //传入的任务参数
							(UBaseType_t    ) MPU_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  ) &MPUTask_Handler); 	 //任务句柄
							
	//4.创建控制器处理任务
	xTaskCreate((TaskFunction_t ) Control_task,        			//任务函数
							(char*          ) "Control",           			//任务名字  
							(uint16_t       ) CONTROL_STK_SIZE,    			//任务堆栈
							(void*          ) NULL,                			//传入的任务参数
							(UBaseType_t    ) CONTROL_TASK_PRIO,        //任务优先级
							(TaskHandle_t*  ) &CONTROLTask_Handler); 	  //任务句柄
	
	
	
	vTaskDelete(StartTask_Handler); //删除开始任务
	
  taskEXIT_CRITICAL();            //退出临界区
}

/**********************************************************************************************************
*函 数 名: StartupTast
*功能说明: 创建初始化任务
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void StartupTask(void)
{
	//创建一个任务创建的任务，用来创建需要实现功能的各任务
	xTaskCreate((TaskFunction_t ) start_task,          //任务函数
							(char*          ) "start_task",        //任务名字  
							(uint16_t       ) START_STK_SIZE,      //任务堆栈
							(void*          ) NULL,                //传入的任务参数
							(UBaseType_t    ) START_TASK_PRIO,     //任务优先级
							(TaskHandle_t*  ) &StartTask_Handler); //任务句柄
}

