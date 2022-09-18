#include <iom16v.h>
#include <macros.h>

#define uint unsigned int
#define uchar unsigned char


#include "delay.h"
#include "1602.h"


//uchar  Data[5]={0,0,0,0,0};//初始值为0000，最后一个0是结束
void main(void)
{	
 
  LCD_init();    //初始化
  LCD_write_command(0x01);  //清屏
   while(1)
   { 
   
   LCD_write_string(0,0,"ffdsa AVR");
   LCD_write_string(8,0,"CSfffB");
   LCD_write_string(0,1,"SPACE:");
   
	}
 }

