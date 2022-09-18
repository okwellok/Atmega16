/******************************����ͷ�ļ�*************************/
#include<iom16v.h> 
#include <macros.h>

//�������͵ĺ궨��
#define uchar unsigned char 
#define uint unsigned int

//IOD�ڵ�4��5�ܽţ��ֱ��Ӧ�������ϵ�PWMA��PWMB



//�����
uchar DUTY1;//����PWM����ռ�ձ�
uchar DUTY2;//����PWM����ռ�ձ�
uchar CYCLE=100;//��ռ�ձ�
uint count;//�ۼӱ���
/**********************�˿ڳ�ʹ��*******************************/
void port_init(void)
{
  DDRC=0xff;//PC�˿�8�ܽŶ���Ϊ����˿�
  PORTC=0x30;//PC�˿����Ϊ00110000
}

/**************************�Ӻ�������****************************/
void forward(void)			   //ǰ������
{
  PORTC|=(1<<PC6)|(1<<PC3);
  PORTC&=~((1<<PC7)|(1<<PC2));
}
/**************************��ʱ��0��ʹ��****************************/
void timer0_init(void)
{
 TCCR0 = 0x00; //stop
 TCNT0 = 0xF6; //set count,10us
 TCCR0 = 0x02; //start timer
}
/*********************��ʹ��************************************/
void init_devices(void)
{
 //stop errant interrupts until set up
 CLI(); //disable all interrupts//���ж�
 port_init();
 timer0_init();

 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x01; //timer interrupt sources//����ʱ���ж�
 SEI(); //re-enable interrupts//���ж�
 //all peripherals are now initialized
}
// ������
void main(void)
{
   init_devices();
   DUTY1=40;//����ռ�ձ�����
   DUTY2=40;//����ռ�ձ�����

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
  PORTC|=(1<<PC4);//�ߵ�ƽʱ�����
}
else
{
  PORTC&=~(1<<PC4);//�͵�ƽʱ�����
}

if(count<=DUTY2)
{
 PORTC|=(1<<PC5);
}
else
{
 PORTC&=~(1<<PC5);
}

if(count==CYCLE)//�����������Զ���0
{
count=0;
}
}