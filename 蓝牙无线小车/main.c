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
 DDRA|=BIT(PA7);		//PA7����Ϊ���״̬ ����LED��ˮ�ƿ����ܿ���
 PORTA|=BIT(PA7);	//PA7����ߵ�ƽ����LED��ˮ�������ܿ���
 PORTC&=~BIT(PC6);   //PC6�͵�ƽ
 PORTC&=~BIT(PC7);   //PC7�͵�ƽ
 PORTD&=~BIT(PD4);   //PD4�͵�ƽ
 DDRA|=BIT(PA3);		//PA3����Ϊ���״̬ ���ڿ��Ʒ����� 
}

//ǰ������
void forward(void)
{
  PORTC|=(1<<PC6)|(1<<PC3);
  PORTC&=~((1<<PC7)|(1<<PC2));
}
//=====================���˺���===============================================//
void back(void)  //�ص�PC���еķ��湦�ܣ�������ͨIO��ʹ��
{
  PORTC|=((1<<PC7)|(1<<PC2));
  PORTC&=~(1<<PC6)|(1<<PC3);
}
//=====================��ת����===============================================//
void toleft(void)//��ߵ���������ұߵ��ǰ��
{
  PORTC|=(1<<PC3); //
  PORTC&=~((1<<PC7)|(1<<PC6)|(1<<PC2));//
}
//=====================ԭ����ת����===========================================//
void left(void)
{
  PORTC|=((1<<PC3)|(1<<PC7)); //
  PORTC&=~((1<<PC2)|(1<<PC6));//
}
//=====================��ת����===============================================//
void toright(void)
{
  PORTC|=(1<<PC6); 
  PORTC&=~((1<<PC2)|(1<<PC3)|(1<<PC7));
}
//=====================ԭ���ҹպ���===========================================//
void right(void)
{
  PORTC|=(1<<PC6)|(1<<PC2); 
  PORTC&=~((1<<PC3)|(1<<PC7));
}
//=====================ͣ������===============================================//
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