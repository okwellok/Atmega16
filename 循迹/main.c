#include <iom16v.h>
#include <macros.h>
#include "pwm.h"
#define uchar unsigned char
#define uint unsigned int

#define Left (PINB&0x01)//��Ѱ���������ӵ�PB0��
#define Right (PINB&0x02)//��Ѱ���������ӵ�PB1��

void init_port(void)
{
	DDRB=0xf0;//PB�˿ڵ���λ����Ϊ����˿�
	PORTB=0xf0;//PB�˿����Ϊ1111 1100
	DDRC=0xff;//����˿�
	PORTC=0x30;//PC�˿�00110000

	MCUCR = 0x00;
	GICR  = 0x00;
	TIMSK = 0x01; //��ʱ���ж�
	SEI();
}

//ǰ������
void forward(void)
{
	PORTC|=(1<<PC6)|(1<<PC3);
	PORTC&=~((1<<PC7)|(1<<PC2));
}
void back(void)  //ע��ص�PC���еķ��湦�ܣ�������ͨIO��ʹ��
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
	DUTY1=DUTY2=50; //PWM���ٶ�
	timer0_init();
	init_port();
	stop();
	for(;;)
		{
			if (Left !=0&&Right ==0)//����������ת
			{
				right();
			}
		else if (Right !=0&&Left ==0)//��������ת
			{
				left();
			}
		else if((Left !=1)&&Right !=1)//���·���
			{
				forward();
			}

		}
}
