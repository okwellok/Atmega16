#include <iom16v.h>
#include <macros.h>

#define uint unsigned int
#define uchar unsigned char

#define fosc 8000000

uchar dis[]={"HL-2 AVR"};
uchar command;
void init_port()
{
 DDRC = 0xf0;
 PORTC = 0xf0;
 
 DDRB = 0xff;
 PORTB = 0x00;
 DDRA|=BIT(PA7);		//PA7设置为输出状态 用于LED流水灯控制总开关
 PORTA|=BIT(PA7);	//PA7输出高电平，打开LED流水灯锁存总开关
 PORTC&=~BIT(PC6);   //PC6低电平
 PORTC&=~BIT(PC7);   //PC7低电平
 PORTD&=~BIT(PD4);   //PD4低电平
 DDRA|=BIT(PA3);		//PA3设置为输出状态 用于控制蜂鸣器 
}

//前进函数
void forward(void)
{
  PORTC|=(1<<PC6)|(1<<PC3);
  PORTC&=~((1<<PC7)|(1<<PC2));
}
//=====================后退函数===============================================//
void back(void)  //关掉PC口中的仿真功能，用作普通IO口使用
{
  PORTC|=((1<<PC7)|(1<<PC2));
  PORTC&=~(1<<PC6)|(1<<PC3);
}
//=====================左转函数===============================================//
void toleft(void)//左边电机不动，右边电机前进
{
  PORTC|=(1<<PC3); //
  PORTC&=~((1<<PC7)|(1<<PC6)|(1<<PC2));//
}
//=====================原地左转函数===========================================//
void left(void)
{
  PORTC|=((1<<PC3)|(1<<PC7)); //
  PORTC&=~((1<<PC2)|(1<<PC6));//
}
//=====================右转函数===============================================//
void toright(void)
{
  PORTC|=(1<<PC6); 
  PORTC&=~((1<<PC2)|(1<<PC3)|(1<<PC7));
}
//=====================原地右拐函数===========================================//
void right(void)
{
  PORTC|=(1<<PC6)|(1<<PC2); 
  PORTC&=~((1<<PC3)|(1<<PC7));
}
//=====================停车函数===============================================//
void stop(void)
{
 PORTC&=~((1<<PC2)|(1<<PC3)|(1<<PC6)|(1<<PC7));
}

void uar_init(uint baud)
{
 uint M;
 UCSRC = 0x86;
 M = fosc/16/baud-1;
 UBRRH = M/256;
 UBRRL = M%256;
 UCSRB = 0x90;
 SEI();
}
/*
void uart_send(uchar data)
{
 while(!(UCSRA&=BIT(5)));
 UDR = data;
}*/

void main()
{
// int n;
   init_port();
 uar_init(9600);
 while(1)
 {
 /*for(n=0;n<8;n++)
 {
  uart_send(dis[n]);

 }
  uart_send(0x0d);
  uart_send(0x0a);*/
 }
}

#pragma interrupt_handler uartrece_isr:12
void uartrece_isr()
{
 command = UDR;
 switch(command)
 {
  case 'A':
  	   forward();
	   break;
  case 'B':
  	   back();
	   break;
  case 'C':
  	   left();
	   break;
  case 'D':
  	   right();
	   break;
  case 'E':
  	   stop();
	   break;
  default:
  	  stop();
	  break;
  }
}