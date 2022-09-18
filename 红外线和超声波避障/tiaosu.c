#include<iom16v.h> 
#include <macros.h>
//�������͵ĺ궨��
#define uchar unsigned char 
#define uint unsigned int

//IOC�ڵ�4��5�ܽţ��ֱ��Ӧ�������ϵ�PWMA��PWMB



//�����
uchar n;
char m; 

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
//=====================��������===============================================//
void back(void)  
{
  PORTC|=((1<<PC7)|(1<<PC2));
  PORTC&=~(1<<PC6)|(1<<PC3);
}
/*********************��ʹ��************************************/
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
  PORTC|=(1<<PC4);//�ߵ�ƽʱ�����   ����������Ч����ʱ������177 166
  PORTC|=(1<<PC5);
  delay_tiaosu_ms(1);
  PORTC&=~(1<<PC4);//�͵�ƽʱ�����
  PORTC&=~(1<<PC5);
  delay_tiaosu_ms(2); 
  }
}