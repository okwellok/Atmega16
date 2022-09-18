#include <iom16v.h>
#include <macros.h>

#define uint unsigned int
#define uchar unsigned char

#define L_BZ (PINA&0x04) 
#define R_BZ (PINA&0x02)

#include "delay.h"
#include "1602.h"
#include "tiaosu.h"
#include "clock.h"
#include "Lib.h"
#include "fmq.h"
#pragma interrupt_handler timer0_ovf:10
//ʹ��ǰ�ǵý������·������
unsigned int number = 0;
unsigned int distance = 0;
unsigned char command;
unsigned char Data[5] = {0, 0, 0, 0, 0};
unsigned int average_distance = 1;
unsigned int i = 0;

void clock_init(void)
{
    TCNT0 = 0;
    number = 0;
}
void trig_fun(void)
{
    PORTB |= (1 << 3);
    delay_nus(15);
    PORTB &= (~(1 << 3));
}

//������ģ�� �������ؾ��� ��λcm
unsigned int detect(void)
{

    unsigned int flag;
    unsigned int distance1 = 0;
    trig_fun();
    while (!(PINB & 0x04))
    {;
    }
    clock_init();
    flag = 1;
    while ((PINB & 0x04) && flag)
    {
        ;
    }
    if (flag == 0)
    {
        distance1 = 0;
    }
    else
    {
distance1 =0.5*340*(number*256+TCNT0)*1*100/1000000;
        if (distance1 >= 800)
        {
            distance1 = 800;
        }
    }
    return distance1;
}
//�����ж�
void go_forward(unsigned int n)
{
    forward();
    tiaosu(n);
    stop();
}
void turn_left(unsigned int n)
{
    left();
    tiaosu(n);
    stop();
}
void turn_right(unsigned int n)
{
    right();
    tiaosu(n);
    stop();
}
void turn_back(unsigned int n)
{
    back();
    tiaosu(n);
    stop();
}
void all_port_init(void)
{
    LCD_init(); //Һ����PB 4-7
    init_devices(); //���PC3-PC7
    DDRB &= ~(1 << PB2);
    PORTB &= ~(1 << PB2);
    DDRB |= (1 << PB3);
    PORTB |= (1 << PB3);//������ trig e
    clock_port_init();//ʱ��
    fmq_init();// PA3 ������
	DDRA &= ~(1<<PA1);
    DDRA &= ~(1<<PA2);//������
    PORTA &= ~(1<<PA1);//PA1��PA3�˿�����Ϊ����ģʽ
    PORTA &= ~(1<<PA2);

}
void main(void)
{
     unsigned int j;
    all_port_init();
    LCD_write_command(0x01);//����
    clock_init();


	while(1)
	{
	
	    LCD_write_string(0, 0, "work!");
        LCD_write_string(7, 1, Data);
        LCD_write_string(12, 1, "cm");
		distance = detect();
        change(distance, Data);
        LCD_write_string(7, 1, Data);
  while(   L_BZ ==0&&R_BZ ==0 &&distance<=4)//ȫ�ϰ�
  {
  turn_back(150);
  LCD_write_string(0, 0, "back!");
  LCD_write_string(12, 1, "cm");
  distance = detect();
  change(distance, Data);
  LCD_write_string(7, 1, Data);
  }
  
  while(   L_BZ ==0&&R_BZ ==0 &&distance>4)//ȫ�ϰ�
  {
  turn_left(50);
  LCD_write_string(0, 0, "turn!");
  LCD_write_string(12, 1, "cm");
  distance = detect();
  change(distance, Data);
  LCD_write_string(7, 1, Data);
  }
  
  while(   L_BZ  !=0&&R_BZ ==0  ) //����ϰ���
  {
  turn_back(100);
  turn_right(250);
  distance = detect();
  change(distance, Data);
  LCD_write_string(7, 1, Data);
  LCD_write_string(0, 0, "right");
  LCD_write_string(12, 1, "cm");
  }
  
  while(    L_BZ  ==0&&R_BZ !=0  )//�Ҳ��ϰ���
  {
  turn_back(100);
  turn_left(250);
  distance = detect();
  change(distance, Data);
  LCD_write_string(7, 1, Data);
  LCD_write_string(0, 0, "left!");
  LCD_write_string(12, 1, "cm");
  }
  
   while(    L_BZ  !=0&&R_BZ !=0 )//���ϰ�
  {
  go_forward(300);
  LCD_write_string(0, 0, "slow!");
  LCD_write_string(12, 1, "cm");
  distance = detect();
  change(distance, Data);
  LCD_write_string(7, 1, Data);
  }
  if(distance<=2)//�����������
  {
  buzz();
  }
    }
    
}
void timer0_ovf(void)
{
    number = number + 1;
}