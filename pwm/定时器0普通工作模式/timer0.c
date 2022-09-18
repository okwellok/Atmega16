/******************************定义头文件*************************/
#include<iom16v.h> 
#include <macros.h>

//变量类型的宏定义
#define uchar unsigned char 
#define uint unsigned int

//IOD口的4、5管脚，分别对应驱动器上的PWMA和PWMB



//输出端
uchar DUTY1;//左轮PWM调速占空比
uchar DUTY2;//右轮PWM调速占空比
uchar CYCLE=100;//总占空比
uint count;//累加变量
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
/**************************定时器0初使化****************************/
void timer0_init(void)
{
 TCCR0 = 0x00; //stop
 TCNT0 = 0xF6; //set count,10us
 TCCR0 = 0x02; //start timer
}
/*********************初使化************************************/
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts//关中断
 port_init();
 timer0_init();

 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x01; //timer interrupt sources//开定时器中断
 SEI(); //re-enable interrupts//开中断
 //all peripherals are now initialized
}
// 主程序
void main(void)
{
   init_devices();
   DUTY1=40;//左轮占空比设置
   DUTY2=40;//右轮占空比设置

  forward(); 
  while(1);
}

#pragma interrupt_handler timer0_ovf_isr:10 //timer0 overflow
void timer0_ovf_isr(void)
{
  TCNT0=0xF6;
  count++;
  
if(count<=DUTY1)
{
  PORTC|=(1<<PC4);//高电平时间比例
}
else
{
  PORTC&=~(1<<PC4);//低电平时间比例
}

if(count<=DUTY2)
{
 PORTC|=(1<<PC5);
}
else
{
 PORTC&=~(1<<PC5);
}

if(count==CYCLE)//超过最大比例自动清0
{
count=0;
}
}