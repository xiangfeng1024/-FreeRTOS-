#ifndef _CSB_H
#define _CSB_H

#include "system.h"

/*  IIC_SCLʱ�Ӷ˿ڡ����Ŷ��� */
#define HC_SR_Trig_PORT 				GPIOB   
#define HC_SR_Trig_PIN 					(GPIO_Pin_14)
#define HC_SR_Trig_PORT_RCC			RCC_APB2Periph_GPIOB

/*  IIC_SDAʱ�Ӷ˿ڡ����Ŷ��� */
#define HC_SR_Echo_PORT 				GPIOB  
#define HC_SR_Echo_PIN 					(GPIO_Pin_15)
#define HC_SR_Echo_PORT_RCC			RCC_APB2Periph_GPIOB

//IO��������	 
#define HC_SR_Trig    PBout(14) //SCL
#define HC_SR_Echo    PBin(15) //��� SDA

float HC_SR04_Get(void);
void HC_SR04_Init(void);

#endif


