#include "gui.h"

void MAIN_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/MainInterface.gif";
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0  

}

void SETTING_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/Setting.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0  	
}

void MP3_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/MP3.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0  
	
}

void RECORD_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/¼��.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0 
}

void LIST_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/�б�.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0  
	
}

void RECU_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/����.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//��ʾͼƬ      //�л�Ϊ0  
}
