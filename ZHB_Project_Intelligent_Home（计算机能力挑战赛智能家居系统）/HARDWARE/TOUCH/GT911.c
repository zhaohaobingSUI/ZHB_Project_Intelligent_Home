#include "GT911.h"

//==================================================================
//Name:						GT911_int_sync
//Author:					QD
//Date:						2017-07-06
//Function:				Sync GT911 INT signal
//								Sync is the most important part in initial stage
//Input:					unsigned int
//Output:					void
//option:
//==================================================================
void GT911_int_sync(u16 ms)
{
	INT_CTRL=0;
	delay_ms(ms);
	INT_IN();
}	

//==================================================================
//Name:						GT911_reset_guitar
//Author:					QD
//Date:						2017-07-06
//Function:				Rest GT911, and work with function GT911_int_sync
//								sync sequence depends on slave address
//Input:					unsigned char addr
//Output:					void
//option:
//==================================================================
void GT911_reset_guitar(u8 addr)
{
	INT_CTRL=1;
	RST_CTRL=1;
	delay_ms(20);
	RST_CTRL=0;
	INT_CTRL=0;
	delay_ms(20);
	INT_CTRL=(addr == 0x28);
	delay_ms(20);
	RST_CTRL=1;
	delay_ms(20);
}

//==================================================================
//Name:						GT911_reset
//Author:					QD
//Date:						2017-07-06
//Function:				Rest GT911, just reset without sync
//Input:					void
//Output:					void
//option:
//==================================================================
void GT911_reset(void)
{
	RST_CTRL=0;
	delay_ms(10);
	RST_CTRL=1;
	delay_ms(10);
}

//==================================================================
//Name:						GT911_gpio_init
//Author:					QD
//Date:						2017-07-06
//Function:				Init GT911 related GPIO: IIC,RST,INT
//Input:					void
//Output:					void
//option:
//==================================================================
void GT911_gpio_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //ʹ��PF�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 // PF11�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);//PF11�������
	GPIO_SetBits(GPIOF,GPIO_Pin_1);//����
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //PF10�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_Init(GPIOF, &GPIO_InitStructure);//PF10��������
	GPIO_SetBits(GPIOF,GPIO_Pin_10);//����		

	CT_IIC_Init();
	RST_OUT();
	INT_OUT();
	GT911_reset();
}

//==================================================================
//Name:						GT9XX_WriteHandle
//Author:					QD
//Date:						2017-07-06
//Function:				Handle GT911 write function
//Input:					unsigned int addr
//Output:					void
//option:
//==================================================================
u8 GT9XX_WriteHandle (u16 addr)
{
	u8 status;

	CT_IIC_Start();
	CT_IIC_Send_Byte(GT9XX_IIC_WADDR); //д����ָ��
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte((u8)(addr >> 8)); //д��16λ��ַ
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte((u8)addr);
	CT_IIC_Wait_Ack();
	status = SUCCESS;
	return status;	
}

//==================================================================
//Name:						GT9XX_WriteData
//Author:					QD
//Date:						2017-07-06
//Function:				Write data to GT911
//Input:					unsigned int addr				//address of register
//								unsigned char value			//value should be writed
//Output:					void
//option:
//==================================================================
u8 GT9XX_WriteData (u16 addr,u8 value)
{
	u8 status;
	CT_IIC_Start();

	GT9XX_WriteHandle(addr);
	CT_IIC_Send_Byte(value);
	CT_IIC_Wait_Ack();
	CT_IIC_Stop();	
	status = SUCCESS;
	return status;
}

//==================================================================
//Name:						GT9XX_ReadData
//Author:					QD
//Date:						2017-07-06
//Function:				Read data from GT911
//Input:					unsigned int addr				//address of register
//								unsigned char *value		//pointer of data output
//Output:					void
//option:
//==================================================================
u8 GT9XX_ReadData (u16 addr, u8 cnt, u8 *value)
{
	u8 status;
	u8 i;

	status = ERROR;
	CT_IIC_Start();
	GT9XX_WriteHandle(addr);
	CT_IIC_Start();
	delay_us(20);
	CT_IIC_Send_Byte(GT9XX_IIC_RADDR);
	CT_IIC_Wait_Ack();
	for(i = 0 ; i < cnt; i++)
	{
		if (i == (cnt - 1))
		{
			value[i] = CT_IIC_Read_Byte(0);
		}
		else
		{
			value[i] = CT_IIC_Read_Byte(1);
		}
	}					
	CT_IIC_Stop();
	status = SUCCESS;
	return (status);	
}


//==================================================================
//Name:						Touch_Init
//Author:					QD
//Date:						2017-07-06
//Function:				GT911 init, including GPIO init, sync, and version check
//Input:					unsigned int addr				//address of register
//								unsigned char *value		//pointer of data output
//Output:					void
//option:
//==================================================================
u8 GT911_Init(void)
{
	u8 touchIC_ID[4];	
	GT911_gpio_init();
//	GT9xx_Eint_Init();
	GT911_reset_guitar(GT9XX_IIC_WADDR);
	GT911_int_sync(50);
	GT9XX_ReadData (GT9XX_ID_ADDR,4,touchIC_ID);
	if( touchIC_ID[0] == '9' )
	{
		//printf("Touch ID: %s \r\n",touchIC_ID);
		//GT9xx_send_config();
		return 1;
	}
	else
	{
		//printf("Touch Error\r\n");
		return 0;
	}
}

u8 Touch_Get_Count(void)
{
	u8 count[1] = {0};
	GT9XX_ReadData (GT9XX_READ_ADDR,1,count);	//read touch data
	return (count[0]&0x0f);
}

const u16 TPX[] = {0x8150,0x8158,0x8160,0x8168,0x8170}; //���������������ݵ�ַ��1~5��

//==================================================================
//Name:						Touch_Get_Data
//Author:					QD
//Date:						2017-07-06
//Function:				Get GT911 data, such as point and coordinate
//Input:					void
//Output:					void
//option:
//==================================================================
u8 GT911_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	u8 tempsta;
 	static u8 t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
	t++;
	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{ 
 		GT9XX_ReadData(GT9XX_READ_ADDR, 1, &mode);
		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;	
			GT9XX_WriteData (GT9XX_READ_ADDR,temp);
		}		
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tempsta=tp_dev.sta;			//���浱ǰ��tp_dev.staֵ
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[4]=tp_dev.x[0];	//���津��0������
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//������Ч?
				{
					GT9XX_ReadData(TPX[i],4,buf);	//��ȡXY����ֵ
					if(tp_dev.touchtype&0X01)//����
					{
						tp_dev.y[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.x[i]=480-(((u16)buf[3]<<8)+buf[2]);
					}else
					{
						tp_dev.x[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((u16)buf[3]<<8)+buf[2];
					}  
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//�Ƿ�����(���곬����)
			{ 
				if((mode&0XF)>1)		//��������������,�򸴵ڶ�����������ݵ���һ������.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					t=0;				//����һ��,��������������10��,�Ӷ����������
				}else					//�Ƿ�����,����Դ˴�����(��ԭԭ����)  
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;		
					tp_dev.sta=tempsta;	//�ָ�tp_dev.sta
				}
			}else t=0;					//����һ��,��������������10��,�Ӷ����������
		}
	}
	if((mode&0X8F)==0X80)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
		}else						//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������Ч���	
		}	 
	} 	
	if(t>240)t=10;//���´�10��ʼ����
	return res;
}


