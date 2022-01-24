#include "Information.h"
#include "sys.h"

extern int page_id;
extern int State;////0:撤防模式，1:布防模式
extern int LedPower;

u8 AlarmState = 0;//报警铃 默认0表示off
u8 WindowState = 0;//窗户 默认0表示off
u8 CurtainState = 0;//窗帘 默认0表示off

u8 *pname;
u8 temperature; //温度 	    
u8 humidity; //湿度
u8 Light;	//光照强度
	
int TouchArea;//点触范围
	/***************************
	1:报警铃
	2:窗户
	3:遮阳帘
	***************************/

int LedValue1 = 20;
int LedValue2 = 40;
int LedValue3 = 60;
int LedValue4 = 80;
int TemperatureValue = 25;
int HumidityValue = 50;


void MainFace()
{	
	MAIN_GUI();	
	LCD_ShowString(430,48,36,12,12,"OFF");//入侵状态
	LCD_ShowString(430,96,36,12,12,"OFF");//窗户状态
	LCD_ShowString(430,148,36,12,12,"OFF");//报警器状态
	LCD_ShowString(430,196,36,12,12,"OFF");//遮阳帘状态
	if(State == 0)
			pname = "0:/GUI/CheFang.gif";
		if(State == 1)
			pname = "0:/GUI/BuFang.gif";
		ai_load_picfile(pname,190,33,104,19,0);//显示图片      //切换为0  	
	TouchArea=0;//开启扫描
	while(page_id == 1)
	{		
		/*触点检测*/
		while(TouchArea == 0)
		{
			ctp1_val();
			/*UI左侧数据*/
			POINT_COLOR=BLUE;
			DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值				
			LCD_ShowNum(88,48,temperature,2,16);	//显示温度	   		   
			LCD_ShowNum(88,96,humidity,2,16);		//显示湿度	 
			Light=Lsens_Get_Val();//读取光照强度
			LCD_ShowxNum(88,148,Light,2,16,0);//显示光照强度
			LCD_ShowNum(88,196,(LedPower/200)+1,1,16);	//显示补光等级			
			TIM_SetCompare1(TIM2,LedPower);	//设置灯光光强
			POINT_COLOR=RED;
			if(INFRARED_Check() == 1)//检测有无入侵
			{
				LCD_ShowString(430,48,36,12,12,"ON ");//入侵状态
			}
			if(INFRARED_Check() == 0)//检测有无入侵
			{
				LCD_ShowString(430,48,36,12,12,"OFF");//入侵状态
			}
			DeployMode();
		}		
		switch(TouchArea)
		{
			case 1://警报
				AlarmState = !AlarmState;TouchArea=0;tp_dev.init();
			break;
			case 2://窗户
				WindowState = !WindowState;TouchArea=0;tp_dev.init();
			break;
			case 3://窗帘
				CurtainState = !CurtainState;TouchArea=0;tp_dev.init();
			break;
			case 4://光照+
				if(LedPower<800)
				{
					LedPower+=200;
				}
				TIM_SetCompare1(TIM2,LedPower);	//设置灯光光强
				TouchArea=0;tp_dev.init();
			break;
			case 5://光照-
				if(LedPower>200)
				{
					LedPower-=200;
				}
				TIM_SetCompare1(TIM2,LedPower);	//设置灯光光强
				TouchArea=0;tp_dev.init();
			break;
			case 6://模式切换
				State = !State;TouchArea=0;
				if(State == 0)
						pname = "0:/GUI/chefang.gif";
				if(State == 1)
						pname = "0:/GUI/bufang.gif";
				ai_load_picfile(pname,190,33,104,19,0);//显示图片      //切换为0  
			tp_dev.init();
			break;
			default:
				tp_dev.init();
			break;
		}
		/*UI右侧数据*/
		POINT_COLOR=RED;		
		if(AlarmState == 0)//OFF
		{
			LCD_ShowString(430,148,36,12,12,"OFF");//报警器状态
			BEEP_OFF();
		}else
		{
			LCD_ShowString(430,148,36,12,12,"ON ");//报警器状态
			BEEP_ON();
		}
		if(WindowState == 0)//OFF
		{
			LCD_ShowString(430,96,36,12,12,"OFF");//窗户状态
			RELAY_OFF();
		}else
		{
			LCD_ShowString(430,96,36,12,12,"ON ");//窗户状态
			RELAY_ON();
		}
		if(CurtainState == 0)//OFF
		{
			LCD_ShowString(430,196,36,12,12,"OFF");//遮阳帘状态
			DCMOTOR_OFF();
		}else
		{
			LCD_ShowString(430,196,36,12,12,"ON ");//遮阳帘状态
			DCMOTOR_ON();
		}
	}
}


//触屏扫描
void ctp1_val(void)
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
					
					if(tp_dev.x[t]<(lcddev.width-200)&&tp_dev.x[t]>(lcddev.width-230)&&tp_dev.y[t]<(lcddev.height-230)&&tp_dev.y[t]>(lcddev.height-280))
					{
						TouchArea = 1;
					}
					if(tp_dev.x[t]<(lcddev.width-60)&&tp_dev.x[t]>(lcddev.width-90)&&tp_dev.y[t]<(lcddev.height-230)&&tp_dev.y[t]>(lcddev.height-280))
					{
						TouchArea = 2;
					}
					if(tp_dev.x[t]<(lcddev.width-335)&&tp_dev.x[t]>(lcddev.width-385)&&tp_dev.y[t]<(lcddev.height-230)&&tp_dev.y[t]>(lcddev.height-280))
					{
						TouchArea = 3;
					}
					if(tp_dev.x[t]<(lcddev.width-200)&&tp_dev.x[t]>(lcddev.width-240)&&tp_dev.y[t]<(lcddev.height-180)&&tp_dev.y[t]>(lcddev.height-210))
					{
						TouchArea = 4;
					}
					if(tp_dev.x[t]<(lcddev.width-255)&&tp_dev.x[t]>(lcddev.width-295)&&tp_dev.y[t]<(lcddev.height-180)&&tp_dev.y[t]>(lcddev.height-210))
					{
						TouchArea = 5;
					}
					if(tp_dev.x[t]<(lcddev.width-430)&&tp_dev.x[t]>(lcddev.width-460)&&tp_dev.y[t]<(lcddev.height-230)&&tp_dev.y[t]>(lcddev.height-280))
					{
						TouchArea = 6;
					}
					if(tp_dev.x[t]<(lcddev.width-19)&&tp_dev.x[t]>(lcddev.width-60)&&tp_dev.y[t]<(lcddev.height-10)&&tp_dev.y[t]>(lcddev.height-45))
					{
						page_id = 2;//跳转至Setting
						TouchArea = 88;
					}
					if(tp_dev.x[t]<(lcddev.width-115)&&tp_dev.x[t]>(lcddev.width-165)&&tp_dev.y[t]<(lcddev.height-235)&&tp_dev.y[t]>(lcddev.height-270))
					{
						page_id = 3;//跳转至MP3
						TouchArea = 88;
					}
					if(tp_dev.x[t]<(lcddev.width-255)&&tp_dev.x[t]>(lcddev.width-300)&&tp_dev.y[t]<(lcddev.height-235)&&tp_dev.y[t]>(lcddev.height-270))
					{
						page_id = 4;//跳转至历史记录
						TouchArea = 88;
					}

				}
			}else 
			{
				lastpos[t][0]=0XFFFF;
			}
			tp_dev.x[t] = 0;
			tp_dev.y[t] = 0;	
		}
	delay_ms(5);
}

/*布防模式*/
void DeployMode(void)
{
	if(State == 1)//布防模式标志
	{
		/*光照强度*/
		if(Light < LedValue1)LedPower = 850;
		if(Light > LedValue1 - 1 && Light < LedValue2)LedPower=650;
		if(Light > LedValue2 - 1 && Light < LedValue3)LedPower=450;
		if(Light > LedValue3 - 1 && Light < LedValue4)LedPower=250;
		if(Light > LedValue4 - 1)LedPower = 50;
		/*温度与窗户*/
		if(temperature < TemperatureValue)//OFF
		{
			WindowState = 0;
			LCD_ShowString(430,96,36,12,12,"OFF");//窗户状态
			RELAY_OFF();
		}else
		{
			WindowState = 1;
			LCD_ShowString(430,96,36,12,12,"ON ");//窗户状态
			RELAY_ON();
		}
		/*湿度与窗帘*/
		if(humidity < HumidityValue)//OFF
		{
			CurtainState = 0;
			LCD_ShowString(430,196,36,12,12,"OFF");//遮阳帘状态
			DCMOTOR_OFF();
		}else
		{
			CurtainState = 1;
			LCD_ShowString(430,196,36,12,12,"ON ");//遮阳帘状态
			DCMOTOR_ON();
		}
		/*入侵信息与报警器*/
		if(INFRARED_Check() == 1)//检测有无入侵
		{
			LCD_ShowString(430,48,36,12,12,"ON ");//入侵状态
			BEEP_ON();
		}
		if(INFRARED_Check() == 0)//检测有无入侵
		{
			LCD_ShowString(430,48,36,12,12,"OFF");//入侵状态
			BEEP_OFF();
		}
	}
}

