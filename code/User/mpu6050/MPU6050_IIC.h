#ifndef _MPU6050_IIC_H
#define _MPU6050_IIC_H

#include "system.h"

/*  IIC_SCLʱ�Ӷ˿ڡ����Ŷ��� */
#define MPU6050_IIC_SCL_PORT 		GPIOB   
#define MPU6050_IIC_SCL_PIN 		(GPIO_Pin_8)
#define MPU6050_IIC_SCL_PORT_RCC	RCC_APB2Periph_GPIOB

/*  IIC_SDAʱ�Ӷ˿ڡ����Ŷ��� */
#define MPU6050_IIC_SDA_PORT 		GPIOB  
#define MPU6050_IIC_SDA_PIN 		(GPIO_Pin_9)
#define MPU6050_IIC_SDA_PORT_RCC	RCC_APB2Periph_GPIOB

//IO��������	 
#define MPU6050_IIC_SCL    PBout(8) //SCL
#define MPU6050_IIC_SDA    PBout(9) //��� SDA
#define MPU6050_READ_SDA   PBin(9)  //���� SDA


//IIC���в�������
void MPU6050_IIC_Init(void);            //��ʼ��IIC��IO��				 
void MPU6050_IIC_Start(void);			//����IIC��ʼ�ź�
void MPU6050_IIC_Stop(void);	  		//����IICֹͣ�ź�
void MPU6050_IIC_Send_Byte(u8 txd);		//IIC����һ���ֽ�
u8 MPU6050_IIC_Read_Byte(u8 ack);		//IIC��ȡһ���ֽ�
u8 MPU6050_IIC_Wait_Ack(void); 			//IIC�ȴ�ACK�ź�
void MPU6050_IIC_Ack(void);				//IIC����ACK�ź�
void MPU6050_IIC_NAck(void);			//IIC������ACK�ź�

#endif
