#include "infrared.h"

//////////////////////////////////////////////////////////////////////////////////	
//红外对管检测驱动代码	   								  
//////////////////////////////////////////////////////////////////////////////////  
								    
//按键初始化函数
void INFRARED_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

uint8_t INFRARED_Check(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1)
	{
		return 0;//无人
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)//检测到
	{
		return 1;//有人
	}
}

