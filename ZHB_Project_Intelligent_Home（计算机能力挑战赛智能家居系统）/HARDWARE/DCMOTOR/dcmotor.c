#include "dcmotor.h"
//////////////////////////////////////////////////////////////////////////////////	 

//ֱ�������������
								  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB15��PG11Ϊ�����.��ʹ������ڵ�ʱ��		    
//ֱ�������ʼ��
void DCMOTOR_Init(void)
{
	 
 GPIO_InitTypeDef  GPIO_InitStructure; 
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��GPIOG�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //PG11 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOG, &GPIO_InitStructure);	 //���ݲ�����ʼ��PG11

 GPIO_ResetBits(GPIOG,GPIO_Pin_11);//

}

void DCMOTOR_ON(void)
{
	GPIO_SetBits(GPIOG,GPIO_Pin_11);//
}

void DCMOTOR_OFF(void)
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_11);//
}
