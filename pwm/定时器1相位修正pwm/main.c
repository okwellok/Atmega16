#include <iom16v.h> 
#include <macros.h>
//利用PD4,5两个口匹配时产生的PWM，通过匹配中断实现PC4，PC5的PWM来调节左右电机速度。

void port_init(void)
{
  DDRC=0xff;//PC端口8管脚都设为输出端口
  PORTC=0x30;//PC端口输出为00110000
  PORTD = 0X00; 
  DDRD |= (1 << PD4) | (1 << PD5); //定时计数器的两个比较匹配输出端口 PD4（OC1B）、PD5(OC1A）设置为输出口
}

void forward(void)			   //前进函数
{
  PORTC|=(1<<PC6)|(1<<PC3);
  PORTC&=~((1<<PC7)|(1<<PC2));
}

void timer1_init(void)
{
 	CLI();
 	TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10);//升序记数时比较匹配将置位 OC1A/OC1B，降 序记数时比较匹配将清零 OC1A/OC1B
	TCCR1B |= (1 << CS10); //8 位相位修正PWM。时钟不分频

	TIMSK= (1 << OCIE1B) | (1 << OCIE1A);
	SEI();
}
int main(void) 
{
	OCR1A = 30;//控制左右电机速度
	OCR1B = 50;//需要符合一定范围

	port_init();
	timer1_init();

	forward(); 
	while(1) 
	{
	} 
}

#pragma interrupt_handler Timer1_A:7
void Timer1_A(void)
{
		   if(PIND&(1<<PD5))
		   { 
		   	 PORTC |= (1 << PC5);
		   }
		   else
		   {
		   	 PORTC &= ~(1 << PC5);
		   }
}

#pragma interrupt_handler Timer1_B:8
void Timer1_B(void)
{
		   if(PIND&(1<<PD4))
		   { 
		   	 PORTC |= (1 << PC4);
		   }
		   else
		   {
		   	 PORTC &= ~(1 << PC4);
		   }
}