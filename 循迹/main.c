#include <iom16v.h>
#include <macros.h>
#include "pwm.h"
#define uchar unsigned char
#define uint unsigned int

#define Left (PINB&0x01)//左寻迹传感器接到PB0口
#define Right (PINB&0x02)//右寻迹传感器接到PB1口

void init_port(void)
{
	DDRB=0xf0;//PB端口低两位设置为输入端口
	PORTB=0xf0;//PB端口输出为1111 1100
	DDRC=0xff;//输出端口
	PORTC=0x30;//PC端口00110000

	MCUCR = 0x00;
	GICR  = 0x00;
	TIMSK = 0x01; //定时器中断
	SEI();
}

//前进函数
void forward(void)
{
	PORTC|=(1<<PC6)|(1<<PC3);
	PORTC&=~((1<<PC7)|(1<<PC2));
}
void back(void)  //注意关掉PC口中的仿真功能，用作普通IO口使用
{
	PORTC|=((1<<PC7)|(1<<PC2));
	PORTC&=~(1<<PC6)|(1<<PC3);
}

void left(void)
{
	PORTC|=((1<<PC3)|(1<<PC7)); //
	PORTC&=~((1<<PC2)|(1<<PC6));//
}

void right(void)
{
	PORTC|=(1<<PC6)|(1<<PC2); 
	PORTC&=~((1<<PC3)|(1<<PC7));
}
void stop(void)
{
	PORTC&=~((1<<PC2)|(1<<PC3)|(1<<PC6)|(1<<PC7));
}

void main(void)
{
	DUTY1=DUTY2=50; //PWM调速度
	timer0_init();
	init_port();
	stop();
	for(;;)
		{
			if (Left !=0&&Right ==0)//左遇到则右转
			{
				right();
			}
		else if (Right !=0&&Left ==0)//右遇则左转
			{
				left();
			}
		else if((Left !=1)&&Right !=1)//无事发生
			{
				forward();
			}

		}
}
