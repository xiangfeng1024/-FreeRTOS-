#include <MPU6050_IIC.h> 
#include <systick.h>

void MPU6050_IIC_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO��ʼ���ṹ��
	
//	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOC,ENABLE); //��PB��ʱ�Ӻ�AFIO����ʱ��
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //��ӳ��
	
	RCC_APB2PeriphClockCmd(MPU6050_IIC_SCL_PORT_RCC|MPU6050_IIC_SDA_PORT_RCC,ENABLE);	//ʹ��ʱ��
	
	GPIO_InitStructure.GPIO_Pin=MPU6050_IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(MPU6050_IIC_SCL_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=MPU6050_IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(MPU6050_IIC_SDA_PORT,&GPIO_InitStructure);
	
	MPU6050_IIC_SCL=1;
	MPU6050_IIC_SDA=1;
}

void MPU6050_SDA_OUT()	//���ģʽ
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=MPU6050_IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	//�������
	GPIO_Init(MPU6050_IIC_SDA_PORT,&GPIO_InitStructure);
}

void MPU6050_SDA_IN(void)	//����ģʽ
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=MPU6050_IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������
	GPIO_Init(MPU6050_IIC_SDA_PORT,&GPIO_InitStructure);
}

void MPU6050_IIC_Start(void)	//��ʼ�ź�
{
	MPU6050_SDA_OUT();     //sda�����
	MPU6050_IIC_SDA=1;	  	  
	MPU6050_IIC_SCL=1;
	delay_us(5);	//Ҫ��ʱ��>4.7us
 	MPU6050_IIC_SDA=0;	
	delay_us(6);	//Ҫ��ʱ��>4us
	MPU6050_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

void MPU6050_IIC_Stop(void)	//ֹͣ�ź�
{
	MPU6050_SDA_OUT();//sda�����
	MPU6050_IIC_SCL=0;
	MPU6050_IIC_SDA=0;
 	MPU6050_IIC_SCL=1; 
	delay_us(6); 	//Ҫ��ʱ��>4us
	MPU6050_IIC_SDA=1;//����I2C���߽����ź�
	delay_us(6);	//Ҫ��ʱ��>4us							   	
}

u8 MPU6050_IIC_Wait_Ack(void)	//�ȴ�Ӧ���ź� ���� 0�ɹ� 1ʧ��
{
	u8 tempTime=0;
	
	MPU6050_IIC_SDA=1;
	delay_us(1);
	MPU6050_SDA_IN();      //SDA����Ϊ����  	   
	MPU6050_IIC_SCL=1;
	delay_us(1);	 
	while(MPU6050_READ_SDA)	//�ȴ�Ӧ��
	{
		tempTime++;
		if(tempTime>250)	//�ȴ�Ӧ������ʱ�� ������ʧ��
		{
			MPU6050_IIC_Stop();
			return 1;
		}
	}
	MPU6050_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 

void MPU6050_IIC_Ack(void)	//����Ӧ��
{
	MPU6050_IIC_SCL=0;
	MPU6050_SDA_OUT();
	MPU6050_IIC_SDA=0;
	delay_us(2);
	MPU6050_IIC_SCL=1;
	delay_us(5);	//Ҫ��>4us
	MPU6050_IIC_SCL=0;
}

void MPU6050_IIC_NAck(void)	//������Ӧ��
{
	MPU6050_IIC_SCL=0;
	MPU6050_SDA_OUT();
	MPU6050_IIC_SDA=1;
	delay_us(2);
	MPU6050_IIC_SCL=1;
	delay_us(5);	//Ҫ��>4us
	MPU6050_IIC_SCL=0;
}

void MPU6050_IIC_Send_Byte(u8 txd)	//����һ���ֽ�
{                        
    u8 t;   
	MPU6050_SDA_OUT(); 	    
    MPU6050_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        if((txd&0x80)>0) //�����λ��ʼ����
		{
			MPU6050_IIC_SDA=1;
		}
		else
		{
			MPU6050_IIC_SDA=0;
        }
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		MPU6050_IIC_SCL=1;
		delay_us(2); 
		MPU6050_IIC_SCL=0;	
		delay_us(2);
    }	 
}

u8 MPU6050_IIC_Read_Byte(u8 ack)	//��ȡһ���ֽ� ack=1 ����Ӧ��   ack=0  ���ͷ�Ӧ��
{
	u8 i,receive=0;
	MPU6050_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        MPU6050_IIC_SCL=0; 
        delay_us(2);
		MPU6050_IIC_SCL=1;
        receive<<=1;
        if(MPU6050_READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if(!ack)
	{
        MPU6050_IIC_NAck();//����nACK
    }
	else
	{
		MPU6050_IIC_Ack(); //����ACK   
	}
	return receive;
}

