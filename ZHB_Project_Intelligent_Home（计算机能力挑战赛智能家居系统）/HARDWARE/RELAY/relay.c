#include "relay.h"
//////////////////////////////////////////////////////////////////////////////////	 

//�̵�����������
								  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PD7Ϊ�����.��ʹ������ڵ�ʱ��		    
//�̵�����ʼ��
void RELAY_Init(void)
{
	 
 GPIO_InitTypeDef  GPIO_InitStructure; 
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��GPIOD�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //PD7�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOD, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOD.7
	
 GPIO_SetBits(GPIOD,GPIO_Pin_7);//���1���رռ̵������
}

void RELAY_ON(void)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);//���0���򿪼̵������
}

void RELAY_OFF(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_7);//���1���رռ̵������
}
