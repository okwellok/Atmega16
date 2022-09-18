#ifndef _PWM_H_
#define _PWM_H_
#define uchar unsigned char 
#define uint unsigned int

//IOC口的4、5管脚，分别对应驱动器上的PWMA和PWMB



//输出端
uchar DUTY1;//左轮PWM调速占空比
uchar DUTY2;//右轮PWM调速占空比
uchar CYCLE=100;//总占空比
uint count;//累加变量


void timer0_init(void)
{
	TCCR0 = 0x00; //停止
	TCNT0 = 0xF6; //设置计数,10us
	OCR0  = 0x0A;  //设置比较模式
	TCCR0 = 0x02; //开始
}

#pragma interrupt_handler timer0_ovf_isr:10 //timer0 溢出
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

#endif
