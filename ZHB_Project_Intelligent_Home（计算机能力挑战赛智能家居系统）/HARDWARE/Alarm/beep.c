#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 

//��������������
								  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PA15Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
	 
 GPIO_InitTypeDef  GPIO_InitStructure; 

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOA�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB8�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB8
	
 GPIO_SetBits(GPIOB,GPIO_Pin_8);//���1���رշ��������
}

void BEEP_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
}

void BEEP_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
}
