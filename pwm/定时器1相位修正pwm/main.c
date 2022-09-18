#include <iom16v.h> 
#include <macros.h>
//����PD4,5������ƥ��ʱ������PWM��ͨ��ƥ���ж�ʵ��PC4��PC5��PWM���������ҵ���ٶȡ�

void port_init(void)
{
  DDRC=0xff;//PC�˿�8�ܽŶ���Ϊ����˿�
  PORTC=0x30;//PC�˿����Ϊ00110000
  PORTD = 0X00; 
  DDRD |= (1 << PD4) | (1 << PD5); //��ʱ�������������Ƚ�ƥ������˿� PD4��OC1B����PD5(OC1A������Ϊ�����
}

void forward(void)			   //ǰ������
{
  PORTC|=(1<<PC6)|(1<<PC3);
  PORTC&=~((1<<PC7)|(1<<PC2));
}

void timer1_init(void)
{
 	CLI();
 	TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10);//�������ʱ�Ƚ�ƥ�佫��λ OC1A/OC1B���� �����ʱ�Ƚ�ƥ�佫���� OC1A/OC1B
	TCCR1B |= (1 << CS10); //8 λ��λ����PWM��ʱ�Ӳ���Ƶ

	TIMSK= (1 << OCIE1B) | (1 << OCIE1A);
	SEI();
}
int main(void) 
{
	OCR1A = 30;//�������ҵ���ٶ�
	OCR1B = 50;//��Ҫ����һ����Χ

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