#include "sys.h"


int page_id = 1;
int State = 0;//0:撤防模式，1:布防模式
int	LedPower = 50;

int main(void)
{
	u8 *pname;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	LCD_Init();			   		//初始化LCD 
	Lsens_Init(); 			//初始化光敏传感器
	AT24CXX_Init();	
	tp_dev.init();//触屏
	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
	POINT_COLOR=RED;      //设置画笔颜色
	while(SD_Init())			//检测SD卡
	{
		delay_ms(200);
	}	
	piclib_init();										//初始化画图
	pname = "0:/GUI/InitInterface.gif";   
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//显示图片      //切换为0 
	POINT_COLOR=RED;      //设置画笔颜色
	while(AT24CXX_Check())//检测不到24c02
	{
		delay_ms(100);
	}
	while(DHT11_Init())	//DHT11初始化	
	{
 		delay_ms(100);
	}	
	LED_Init();
	TIM2_PWM_Init(999,1199);
	BEEP_Init();
	DCMOTOR_Init();
 	while(1)
	{
		switch(page_id)
		{
			case 1:MainFace();break;
			case 2:SettingF();break;
			default:break;
		}		
	}
}

