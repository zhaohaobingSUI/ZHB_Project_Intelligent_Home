#ifndef __INFRARED_H
#define __INFRARED_H	 
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//红外对管检测驱动代码									  
//////////////////////////////////////////////////////////////////////////////////   	 

void INFRARED_Init(void);//IO初始化

uint8_t INFRARED_Check(void);

				    
#endif
