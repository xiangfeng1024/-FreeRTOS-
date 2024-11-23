#ifndef _CSB_H
#define _CSB_H

#include "system.h"

/*  IIC_SCL时钟端口、引脚定义 */
#define HC_SR_Trig_PORT 				GPIOB   
#define HC_SR_Trig_PIN 					(GPIO_Pin_14)
#define HC_SR_Trig_PORT_RCC			RCC_APB2Periph_GPIOB

/*  IIC_SDA时钟端口、引脚定义 */
#define HC_SR_Echo_PORT 				GPIOB  
#define HC_SR_Echo_PIN 					(GPIO_Pin_15)
#define HC_SR_Echo_PORT_RCC			RCC_APB2Periph_GPIOB

//IO操作函数	 
#define HC_SR_Trig    PBout(14) //SCL
#define HC_SR_Echo    PBin(15) //输出 SDA

float HC_SR04_Get(void);
void HC_SR04_Init(void);

#endif


