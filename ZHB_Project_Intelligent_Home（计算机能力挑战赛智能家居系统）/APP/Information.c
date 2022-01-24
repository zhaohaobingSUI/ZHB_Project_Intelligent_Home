#include "Information.h"
#include "sys.h"

extern int page_id;
extern int State;////0:����ģʽ��1:����ģʽ
extern int LedPower;

u8 AlarmState = 0;//������ Ĭ��0��ʾoff
u8 WindowState = 0;//���� Ĭ��0��ʾoff
u8 CurtainState = 0;//���� Ĭ��0��ʾoff

u8 *pname;
u8 temperature; //�¶� 	    
u8 humidity; //ʪ��
u8 Light;	//����ǿ��
	
int TouchArea;//�㴥��Χ
	/***************************
	1:������
	2:����
	3:������
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
	LCD_ShowString(430,48,36,12,12,"OFF");//����״̬
	LCD_ShowString(430,96,36,12,12,"OFF");//����״̬
	LCD_ShowString(430,148,36,12,12,"OFF");//������״̬
	LCD_ShowString(430,196,36,12,12,"OFF");//������״̬
	if(State == 0)
			pname = "0:/GUI/CheFang.gif";
		if(State == 1)
			pname = "0:/GUI/BuFang.gif";
		ai_load_picfile(pname,190,33,104,19,0);//��ʾͼƬ      //�л�Ϊ0  	
	TouchArea=0;//����ɨ��
	while(page_id == 1)
	{		
		/*������*/
		while(TouchArea == 0)
		{
			ctp1_val();
			/*UI�������*/
			POINT_COLOR=BLUE;
			DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ				
			LCD_ShowNum(88,48,temperature,2,16);	//��ʾ�¶�	   		   
			LCD_ShowNum(88,96,humidity,2,16);		//��ʾʪ��	 
			Light=Lsens_Get_Val();//��ȡ����ǿ��
			LCD_ShowxNum(88,148,Light,2,16,0);//��ʾ����ǿ��
			LCD_ShowNum(88,196,(LedPower/200)+1,1,16);	//��ʾ����ȼ�			
			TIM_SetCompare1(TIM2,LedPower);	//���õƹ��ǿ
			POINT_COLOR=RED;
			if(INFRARED_Check() == 1)//�����������
			{
				LCD_ShowString(430,48,36,12,12,"ON ");//����״̬
			}
			if(INFRARED_Check() == 0)//�����������
			{
				LCD_ShowString(430,48,36,12,12,"OFF");//����״̬
			}
			DeployMode();
		}		
		switch(TouchArea)
		{
			case 1://����
				AlarmState = !AlarmState;TouchArea=0;tp_dev.init();
			break;
			case 2://����
				WindowState = !WindowState;TouchArea=0;tp_dev.init();
			break;
			case 3://����
				CurtainState = !CurtainState;TouchArea=0;tp_dev.init();
			break;
			case 4://����+
				if(LedPower<800)
				{
					LedPower+=200;
				}
				TIM_SetCompare1(TIM2,LedPower);	//���õƹ��ǿ
				TouchArea=0;tp_dev.init();
			break;
			case 5://����-
				if(LedPower>200)
				{
					LedPower-=200;
				}
				TIM_SetCompare1(TIM2,LedPower);	//���õƹ��ǿ
				TouchArea=0;tp_dev.init();
			break;
			case 6://ģʽ�л�
				State = !State;TouchArea=0;
				if(State == 0)
						pname = "0:/GUI/chefang.gif";
				if(State == 1)
						pname = "0:/GUI/bufang.gif";
				ai_load_picfile(pname,190,33,104,19,0);//��ʾͼƬ      //�л�Ϊ0  
			tp_dev.init();
			break;
			default:
				tp_dev.init();
			break;
		}
		/*UI�Ҳ�����*/
		POINT_COLOR=RED;		
		if(AlarmState == 0)//OFF
		{
			LCD_ShowString(430,148,36,12,12,"OFF");//������״̬
			BEEP_OFF();
		}else
		{
			LCD_ShowString(430,148,36,12,12,"ON ");//������״̬
			BEEP_ON();
		}
		if(WindowState == 0)//OFF
		{
			LCD_ShowString(430,96,36,12,12,"OFF");//����״̬
			RELAY_OFF();
		}else
		{
			LCD_ShowString(430,96,36,12,12,"ON ");//����״̬
			RELAY_ON();
		}
		if(CurtainState == 0)//OFF
		{
			LCD_ShowString(430,196,36,12,12,"OFF");//������״̬
			DCMOTOR_OFF();
		}else
		{
			LCD_ShowString(430,196,36,12,12,"ON ");//������״̬
			DCMOTOR_ON();
		}
	}
}


//����ɨ��
void ctp1_val(void)
{
	u8 t=0;
 	u16 lastpos[5][2];		//��¼���һ�ε����� 
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
						page_id = 2;//��ת��Setting
						TouchArea = 88;
					}
					if(tp_dev.x[t]<(lcddev.width-115)&&tp_dev.x[t]>(lcddev.width-165)&&tp_dev.y[t]<(lcddev.height-235)&&tp_dev.y[t]>(lcddev.height-270))
					{
						page_id = 3;//��ת��MP3
						TouchArea = 88;
					}
					if(tp_dev.x[t]<(lcddev.width-255)&&tp_dev.x[t]>(lcddev.width-300)&&tp_dev.y[t]<(lcddev.height-235)&&tp_dev.y[t]>(lcddev.height-270))
					{
						page_id = 4;//��ת����ʷ��¼
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

/*����ģʽ*/
void DeployMode(void)
{
	if(State == 1)//����ģʽ��־
	{
		/*����ǿ��*/
		if(Light < LedValue1)LedPower = 850;
		if(Light > LedValue1 - 1 && Light < LedValue2)LedPower=650;
		if(Light > LedValue2 - 1 && Light < LedValue3)LedPower=450;
		if(Light > LedValue3 - 1 && Light < LedValue4)LedPower=250;
		if(Light > LedValue4 - 1)LedPower = 50;
		/*�¶��봰��*/
		if(temperature < TemperatureValue)//OFF
		{
			WindowState = 0;
			LCD_ShowString(430,96,36,12,12,"OFF");//����״̬
			RELAY_OFF();
		}else
		{
			WindowState = 1;
			LCD_ShowString(430,96,36,12,12,"ON ");//����״̬
			RELAY_ON();
		}
		/*ʪ���봰��*/
		if(humidity < HumidityValue)//OFF
		{
			CurtainState = 0;
			LCD_ShowString(430,196,36,12,12,"OFF");//������״̬
			DCMOTOR_OFF();
		}else
		{
			CurtainState = 1;
			LCD_ShowString(430,196,36,12,12,"ON ");//������״̬
			DCMOTOR_ON();
		}
		/*������Ϣ�뱨����*/
		if(INFRARED_Check() == 1)//�����������
		{
			LCD_ShowString(430,48,36,12,12,"ON ");//����״̬
			BEEP_ON();
		}
		if(INFRARED_Check() == 0)//�����������
		{
			LCD_ShowString(430,48,36,12,12,"OFF");//����״̬
			BEEP_OFF();
		}
	}
}

