#include "sys.h"


int page_id = 1;
int State = 0;//0:����ģʽ��1:����ģʽ
int	LedPower = 50;

int main(void)
{
	u8 *pname;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	LCD_Init();			   		//��ʼ��LCD 
	Lsens_Init(); 			//��ʼ������������
	AT24CXX_Init();	
	tp_dev.init();//����
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[0],"0:",1); 		//����SD�� 
	POINT_COLOR=RED;      //���û�����ɫ
	while(SD_Init())			//���SD��
	{
		delay_ms(200);
	}	
	piclib_init();										//��ʼ����ͼ
	pname = "0:/GUI/InitInterface.gif";   
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0 
	POINT_COLOR=RED;      //���û�����ɫ
	while(AT24CXX_Check())//��ⲻ��24c02
	{
		delay_ms(100);
	}
	while(DHT11_Init())	//DHT11��ʼ��	
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

