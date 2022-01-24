#include "lsens.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 

//LSENS(光敏传感器)驱动代码

//////////////////////////////////////////////////////////////////////////////////
 
//初始化光敏传感器
void Lsens_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟	
	
	// 作为模拟通道输入引脚   -->PB0                      
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
	Adc_Init();
}
//读取Light Sens的值
//0~100:0,最暗;100,最亮 
u8 Lsens_Get_Val(void)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<LSENS_READ_TIMES;t++)
	{
		temp_val+=Get_Adc(LSENS_ADC_CHX);	//读取ADC值
		delay_ms(5);
	}
	temp_val/=LSENS_READ_TIMES;//得到平均值 
	if(temp_val>4000)temp_val=4000;
	return (u8)(temp_val/40);
//	return (u8)(100-(temp_val/40));
}












