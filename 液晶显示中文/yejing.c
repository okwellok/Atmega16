#include "iom16v.h"
#include "macros.h"
#include "AVR_HL-2.h"		//包含自定义常量头文件
#pragma interrupt_handler Increase_INT0_Ir:2
#pragma interrupt_handler Decrease_INT1_Ir:3
#define uchar unsigned char
 #define uint unsigned int 
 #define RS_CLR PORTA&=~BIT(4)              
 #define RS_SET PORTA|=BIT(4)
 #define RS_OUT DDRA|=BIT(4)
 #define RW_CLR PORTA&=~BIT(5)
 #define RW_SET PORTA|=BIT(5)
 #define RW_OUT DDRA|=BIT(5)
 #define E_CLR PORTA&=~BIT(6)
 #define E_SET PORTA|=BIT(6)
 #define E_OUT DDRA|=BIT(6)
 
 const uchar CGRAM[LCDa_CGMAX] =
{
	//8*5字模
	
		0x02,0x02,0x1F,0x06,0x0B,0x12,0x02,0x02,
		0x00,0x0E,0x0A,0x0A,0x0A,0x0A,0x0A,0x1B,
		0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,
		0x02,0x02,0x1F,0x06,0x0B,0x12,0x02,0x02,
		0x00,0x00,0x1F,0x00,0x05,0x1F,0x05,0x09,
		//0x00,0x00,0x1F,0x05,0x1F,0x05,0x09,0x11,
		//0x00,0x10,0x1F,0x09,0x06,0x06,0x09,0x00,
		0x10,0x10,0x1F,0x0A,0x04,0x0C,0x13,0x01,
		0x08,0x04,0x1F,0x09,0x0A,0x06,0x0A,0x11,
		0x00,0x00,0x11,0x01,0x09,0x09,0x09,0x03,
		

};
void LCD1602_gotoXY(uchar Row, uchar Col)
{	
	switch (Row)		  //选择行
	{
		case 2:
			LCD1602_sendbyte(iCmd, LCDa_L2 + Col); break;	//写入第2行的指定列	
		default:
			LCD1602_sendbyte(iCmd, LCDa_L1 + Col); break;	//写入第1行的指定列	
	}
}
void LCD1602_sendbyte(uchar DatCmd, uchar dByte)
{
	if (DatCmd == iCmd)		//指令操作
		LCDa_CLR_RS;
	else
		LCDa_SET_RS;		//数据操作
		
	LCDa_CLR_RW;			//写操作操作
	LCDa_SET_E;
	LCDa_DO = dByte;		//写入数据
	Delayms(1);
	LCDa_CLR_E;	
}
void LCD1602_wrCGRAM(const uchar *ptCGRAM)
{
	uchar i;
	LCD1602_sendbyte(iCmd, LCDa_CGRAM_ADDR);  //写入CGRAM首地址
	for (i = 0; i < LCDa_CGMAX; i++)		  //写入64个字节的CGRAM内容
	{
		LCD1602_sendbyte(iDat,ptCGRAM[i]);
	}
}
/*******************************************
函数名称: LCD1602_disCGRAM
功    能: 显示CGRAM内容，将64个字节写在两行，每行32个字节
参    数: 无
返回值  : 无
/********************************************/
void LCD1602_disCGRAM(void)
{
	uchar i;
	LCD1602_gotoXY(1,3);   //从第1行第6列开始显示
	for (i = 0;i <4;i++)   //显示前32个字节的内容
	{	 	
		LCD1602_sendbyte(iDat, i);		
	}
	LCD1602_gotoXY(1,7);   //从第2行第6列开始显示
	for (i = 4;i <8;i++)   //显示后32个字节的内容
	{	 	
		LCD1602_sendbyte(iDat,i);		
	}
}
void delay_1ms(void)                 //1ms延时函数
  {
   unsigned int i;
   for (i=0;i<1140;i++);
  }
 void delay_nms(unsigned int n)       //N ms延时函数
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }
 void write_com(uchar com)//写操作函数
 {
  RS_SET;//高电平
  RW_SET;
  E_CLR;
  RS_CLR;
  RW_CLR;
  PORTB=com;//在E变成高电平之前把数据输入
  delay_nms(1);
  E_SET;
  delay_nms(1);
  E_CLR;
 }
  void write_data(uchar data)//读操作函数
 {
  RS_CLR;
  RW_SET;
  E_CLR;
  RS_SET;
  RW_CLR;
  PORTB=data;
  delay_nms(1);
  E_SET;
  delay_nms(1);
  E_CLR;
 }
 void init (void)//按照数据手册初始化
 {
  DDRB=0XFF;
  PORTB=0;
  RS_OUT;
  E_OUT;
  RW_OUT;
  E_CLR;//设置为输出
delay_nms(20);
  write_com(0x38);
  delay_nms(5);
  write_com(0x38);
  delay_nms(5);
  write_com(0x38);
  write_com(0x38);
  write_com(0x08);
  write_com(0x01);
  write_com(0x06);
  write_com(0x0c);
 }
void Interrupt_Init(void)
{
    PORTD = 0X08; 
    DDRD = 0XF3; //K1、K2 按键(PD2、PD3)设置为输入端口
	MCUCR |= (1 << ISC11) | (1 << ISC01) | (1 << ISC00);
	//INT0 设置为上升沿中断，INT1 为下降沿中断请求
	GICR |= (1 << INT0) | (1 << INT1); //允许 INT0、INT1 中断
    GIFR |= (1 << INTF1) | (1 << INTF0); //清除 INT0、INT1 中断标志位
}
void main(void)
{
	Interrupt_Init();	//调用中断初始化函数
	SREG|=BIT(7);		//全局中断使能位置一
}
void Increase_INT0_Ir(void)  //外部中断 0 函数，当按键 K1 按下后，进入此中断
{
	uchar table1[]="191  AVR-16";
 uchar i;
  init();
 write_com(0x01);
 delay_nms(2);
  write_com(0x80+0x0F);
  for(i=0;i<11;i++)
  {
   write_data(table1[i]);
   delay_nms(5);}

 for(i=0;i<12;i++)
	  {
	     write_com(0X18);
		 delay_nms(300);
	  }
}	/*void Decrease_INT1_Ir(void) //外部中断 1 函数，当按键 K2 按下后，进入此中断
{
	uchar table2[]="LCDAAAAAVR";
 uchar i;
  init();
  write_com(0x01);
  write_com(0x80+0x03);
  for(i=0;i<10;i++)
  {
   write_data(table2[i]);
   delay_nms(1);}
   delay_nms(5000);
   write_com(0x01);
}*/
/*void Decrease_INT1_Ir(void)
{uchar i;
init();
  write_com(0x01);
LCD1602_wrCGRAM(CGRAM);
  Delayms(90);
  write_com(0x80+0x03);
  for(i=0;i<8;i++)
  {
   write_data(CGRAM[i]);
   delay_nms(1);}
  Delayms(2000);
    write_com(0x01);

}*/
void Decrease_INT1_Ir(void)
{
init();
  
LCD1602_wrCGRAM(CGRAM);
  Delayms(90);
  LCD1602_disCGRAM();
  Delayms(5000);
    write_com(0x01);

}