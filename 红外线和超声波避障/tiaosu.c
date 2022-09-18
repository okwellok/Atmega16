#include<iom16v.h> 
#include <macros.h>
//变量类型的宏定义
#define uchar unsigned char 
#define uint unsigned int

//IOC口的4、5管脚，分别对应驱动器上的PWMA和PWMB



//输出端
uchar n;
char m; 

/**********************端口初使化*******************************/
void port_init(void)
{
  DDRC=0xff;//PC端口8管脚都设为输出端口
  PORTC=0x30;//PC端口输出为00110000
}

/**************************子函数定义****************************/
void forward(void)			   //前进函数
{
  PORTC|=(1<<PC6)|(1<<PC3);
  PORTC&=~((1<<PC7)|(1<<PC2));
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
//=====================倒车函数===============================================//
void back(void)  
{
  PORTC|=((1<<PC7)|(1<<PC2));
  PORTC&=~(1<<PC6)|(1<<PC3);
}
/*********************初使化************************************/
void init_devices(void)
{
 port_init();
}

void delay_tiaosu_ms(uint k)
{
  uint i,j;
  for(i=0;i<k;i++)
  {
    for(j=0;j<1140;j++);
  }
}

void tiaosu(unsigned int time)//work_strike_must use the per
{
  unsigned int a=time/3;
  unsigned int i=0;
  for(;i<a;i++)
  {
  PORTC|=(1<<PC4);//高电平时间比例   先左再右有效作用时间大概是177 166
  PORTC|=(1<<PC5);
  delay_tiaosu_ms(1);
  PORTC&=~(1<<PC4);//低电平时间比例
  PORTC&=~(1<<PC5);
  delay_tiaosu_ms(2); 
  }
}