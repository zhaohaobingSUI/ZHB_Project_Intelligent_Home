#include "led.h"
//��ʼ��PA15Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure; 
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);    //��GPIOA��AFIOʱ��
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��GPIOA�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //BEEP-->PA15�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOA.15
	
 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//����JTAG�ڵ��ԣ�PA15��Ϊ��ͨIO
 
 GPIO_SetBits(GPIOA,GPIO_Pin_15);//���1
}
 
