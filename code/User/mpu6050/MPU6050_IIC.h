#ifndef _MPU6050_IIC_H
#define _MPU6050_IIC_H

#include "system.h"

/*  IIC_SCL时钟端口、引脚定义 */
#define MPU6050_IIC_SCL_PORT 		GPIOB   
#define MPU6050_IIC_SCL_PIN 		(GPIO_Pin_8)
#define MPU6050_IIC_SCL_PORT_RCC	RCC_APB2Periph_GPIOB

/*  IIC_SDA时钟端口、引脚定义 */
#define MPU6050_IIC_SDA_PORT 		GPIOB  
#define MPU6050_IIC_SDA_PIN 		(GPIO_Pin_9)
#define MPU6050_IIC_SDA_PORT_RCC	RCC_APB2Periph_GPIOB

//IO操作函数	 
#define MPU6050_IIC_SCL    PBout(8) //SCL
#define MPU6050_IIC_SDA    PBout(9) //输出 SDA
#define MPU6050_READ_SDA   PBin(9)  //输入 SDA


//IIC所有操作函数
void MPU6050_IIC_Init(void);            //初始化IIC的IO口				 
void MPU6050_IIC_Start(void);			//发送IIC开始信号
void MPU6050_IIC_Stop(void);	  		//发送IIC停止信号
void MPU6050_IIC_Send_Byte(u8 txd);		//IIC发送一个字节
u8 MPU6050_IIC_Read_Byte(u8 ack);		//IIC读取一个字节
u8 MPU6050_IIC_Wait_Ack(void); 			//IIC等待ACK信号
void MPU6050_IIC_Ack(void);				//IIC发送ACK信号
void MPU6050_IIC_NAck(void);			//IIC不发送ACK信号

#endif
