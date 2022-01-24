#include "gui.h"

void MAIN_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/MainInterface.gif";
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//ÏÔÊ¾Í¼Æ¬      //ÇÐ»»Îª0  

}

void SETTING_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/Setting.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//ÏÔÊ¾Í¼Æ¬      //ÇÐ»»Îª0  	
}

void MP3_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/MP3.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//ÏÔÊ¾Í¼Æ¬      //ÇÐ»»Îª0  
	
}

void RECORD_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/Â¼Òô.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//ÏÔÊ¾Í¼Æ¬      //ÇÐ»»Îª0 
}

void LIST_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/ÁÐ±í.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//ÏÔÊ¾Í¼Æ¬      //ÇÐ»»Îª0  
	
}

void RECU_GUI ()
{
	u8 *pname;
	pname = "0:/GUI/¸´ÏÖ.gif";
	
 	LCD_Clear(BLACK);
 	ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,0);//ÏÔÊ¾Í¼Æ¬      //ÇÐ»»Îª0  
}
