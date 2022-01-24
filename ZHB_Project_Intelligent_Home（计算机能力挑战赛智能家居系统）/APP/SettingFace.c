#include "SettingFace.h"

extern int page_id;
extern int LedValue1;
extern int LedValue2;
extern int LedValue3;
extern int LedValue4;
extern int TemperatureValue;
extern int HumidityValue;

int SettingTouchArea;//点触范围
int Point;

void SettingF(void)
{
	SETTING_GUI();
	LCD_ShowNum(130,55,LedValue1,2,16);
	LCD_ShowNum(130,95,LedValue2,2,16);
	LCD_ShowNum(130,130,LedValue3,2,16);
	LCD_ShowNum(130,170,LedValue4,2,16);
	LCD_ShowNum(130,210,TemperatureValue,2,16);
	LCD_ShowNum(130,250,HumidityValue,2,16);
	SettingTouchArea = 0;
	while(page_id == 2)
	{		
		while(SettingTouchArea == 0)
		{
			Setting_ctp1_val();
		}
		switch(SettingTouchArea)
		{
			case 1:
				Point = 1;
				POINT_COLOR=BLUE;
				LCD_ShowNum(130,55,LedValue1,2,16);
				POINT_COLOR=RED;
				LCD_ShowNum(130,95,LedValue2,2,16);
				LCD_ShowNum(130,130,LedValue3,2,16);
				LCD_ShowNum(130,170,LedValue4,2,16);
				LCD_ShowNum(130,210,TemperatureValue,2,16);
				LCD_ShowNum(130,250,HumidityValue,2,16);
				SettingTouchArea = 0;
				break;
			case 2:
				Point = 2;
				POINT_COLOR=BLUE;
				LCD_ShowNum(130,95,LedValue2,2,16);
				POINT_COLOR=RED;
				LCD_ShowNum(130,55,LedValue1,2,16);				
				LCD_ShowNum(130,130,LedValue3,2,16);
				LCD_ShowNum(130,170,LedValue4,2,16);
				LCD_ShowNum(130,210,TemperatureValue,2,16);
				LCD_ShowNum(130,250,HumidityValue,2,16);
				SettingTouchArea = 0;
				break;
			case 3:
				Point = 3;
				POINT_COLOR=BLUE;
				LCD_ShowNum(130,130,LedValue3,2,16);
				POINT_COLOR=RED;
				LCD_ShowNum(130,55,LedValue1,2,16);
				LCD_ShowNum(130,95,LedValue2,2,16);		
				LCD_ShowNum(130,170,LedValue4,2,16);
				LCD_ShowNum(130,210,TemperatureValue,2,16);
				LCD_ShowNum(130,250,HumidityValue,2,16);
				SettingTouchArea = 0;
				break;
			case 4:
				Point = 4;
				POINT_COLOR=BLUE;
				LCD_ShowNum(130,170,LedValue4,2,16);
				POINT_COLOR=RED;
				LCD_ShowNum(130,55,LedValue1,2,16);
				LCD_ShowNum(130,95,LedValue2,2,16);
				LCD_ShowNum(130,130,LedValue3,2,16);			
				LCD_ShowNum(130,210,TemperatureValue,2,16);
				LCD_ShowNum(130,250,HumidityValue,2,16);
				SettingTouchArea = 0;
				break;
			case 5:
				Point = 5;
				POINT_COLOR=BLUE;
				LCD_ShowNum(130,210,TemperatureValue,2,16);
				POINT_COLOR=RED;
				LCD_ShowNum(130,55,LedValue1,2,16);
				LCD_ShowNum(130,95,LedValue2,2,16);
				LCD_ShowNum(130,130,LedValue3,2,16);
				LCD_ShowNum(130,170,LedValue4,2,16);			
				LCD_ShowNum(130,250,HumidityValue,2,16);
				SettingTouchArea = 0;
				break;
			case 6:
				Point = 6;
				POINT_COLOR=BLUE;
				LCD_ShowNum(130,250,HumidityValue,2,16);
				POINT_COLOR=RED;
				LCD_ShowNum(130,55,LedValue1,2,16);
				LCD_ShowNum(130,95,LedValue2,2,16);
				LCD_ShowNum(130,130,LedValue3,2,16);
				LCD_ShowNum(130,170,LedValue4,2,16);	
				LCD_ShowNum(130,210,TemperatureValue,2,16);			
				SettingTouchArea = 0;
				break;
			case 7:
				switch(Point)
				{
					case 1:LedValue1 ++;SettingTouchArea=1;break;
					case 2:LedValue2 ++;SettingTouchArea=2;break;
					case 3:LedValue3 ++;SettingTouchArea=3;break;
					case 4:LedValue4 ++;SettingTouchArea=4;break;
					case 5:TemperatureValue ++;SettingTouchArea=5;break;
					case 6:HumidityValue ++;SettingTouchArea=6;break;
					default : break;
				}
				break;
			case 8:
				switch(Point)
				{
					case 1:LedValue1 --;SettingTouchArea=1;break;
					case 2:LedValue2 --;SettingTouchArea=2;break;
					case 3:LedValue3 --;SettingTouchArea=3;break;
					case 4:LedValue4 --;SettingTouchArea=4;break;
					case 5:TemperatureValue --;SettingTouchArea=5;break;
					case 6:HumidityValue --;SettingTouchArea=6;break;
					default : break;
				}
				break;
		}
	}
}

//触屏扫描
void Setting_ctp1_val(void)
{
	u8 t=0;
 	u16 lastpos[5][2];		//记录最后一次的数据 
		tp_dev.scan(0);
		for(t=0;t<CT_MAX_TOUCH;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					
					if(tp_dev.x[t]<(lcddev.width-0)&&tp_dev.x[t]>(lcddev.width-50)&&tp_dev.y[t]<(lcddev.height-20)&&tp_dev.y[t]>(lcddev.height-50))
					{
						page_id = 1;//跳转至主界面
						SettingTouchArea = 88;
					}
					if(tp_dev.x[t]<(lcddev.width-40)&&tp_dev.x[t]>(lcddev.width-100)&&tp_dev.y[t]<(lcddev.height-280)&&tp_dev.y[t]>(lcddev.height-320))
					{
						SettingTouchArea = 1;
					}
					if(tp_dev.x[t]<(lcddev.width-150)&&tp_dev.x[t]>(lcddev.width-210)&&tp_dev.y[t]<(lcddev.height-280)&&tp_dev.y[t]>(lcddev.height-320))
					{
						SettingTouchArea = 2;
					}
					if(tp_dev.x[t]<(lcddev.width-280)&&tp_dev.x[t]>(lcddev.width-340)&&tp_dev.y[t]<(lcddev.height-280)&&tp_dev.y[t]>(lcddev.height-320))
					{
						SettingTouchArea = 3;
					}
					if(tp_dev.x[t]<(lcddev.width-410)&&tp_dev.x[t]>(lcddev.width-480)&&tp_dev.y[t]<(lcddev.height-280)&&tp_dev.y[t]>(lcddev.height-320))
					{
						SettingTouchArea = 4;
					}
					if(tp_dev.x[t]<(lcddev.width-270)&&tp_dev.x[t]>(lcddev.width-330)&&tp_dev.y[t]<(lcddev.height-160)&&tp_dev.y[t]>(lcddev.height-230))
					{
						SettingTouchArea = 5;
					}
					if(tp_dev.x[t]<(lcddev.width-380)&&tp_dev.x[t]>(lcddev.width-435)&&tp_dev.y[t]<(lcddev.height-160)&&tp_dev.y[t]>(lcddev.height-230))
					{
						SettingTouchArea = 6;
					}
					if(tp_dev.x[t]<(lcddev.width-245)&&tp_dev.x[t]>(lcddev.width-345)&&tp_dev.y[t]<(lcddev.height-45)&&tp_dev.y[t]>(lcddev.height-110))
					{
						SettingTouchArea = 7;
					}
					if(tp_dev.x[t]<(lcddev.width-375)&&tp_dev.x[t]>(lcddev.width-445)&&tp_dev.y[t]<(lcddev.height-45)&&tp_dev.y[t]>(lcddev.height-110))
					{
						SettingTouchArea = 8;
					}
				}
			}else 
			{
				lastpos[t][0]=0XFFFF;
			}
			tp_dev.x[t] = 0;
			tp_dev.y[t] = 0;	
		}
	delay_ms(40);
}

