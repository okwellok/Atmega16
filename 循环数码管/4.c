
#include "iom16v.h"
#include "macros.h"

//���������������ڴ洢������code
//0~9
#pragrma data:code  
unsigned char const Number[]={0xaf,0xa0,0xc7,0xe6,0xe8,0x6e,0x6f,0xa2,
                                 0xef,0xee,};
//A~F
#pragrma data:code
unsigned char const Alpha[]={0xeb,0x6d,0x0f,0xe5,0x4f,0x4b,0x00,};

//ö�ٱ���aplha����
enum alpha{A,B,C,D,E,F};


//�ӳٺ���
void Delay(unsigned long x)
{
   while(x--);
}

//��̬��ʾ����
void Number_Show(unsigned int Num)
{
   unsigned char thousand,Hundred,Ten,One;
   thousand=Num/1000;
   Hundred=Num%1000/100;       //ȡ��λ
   Ten=Num%100/10;        //ȡʮλ
   One=Num%10;            //ȡ��λ
   
   PORTB=Number[thousand];
   Delay(100);
   PORTD|=BIT(PD5);
   Delay(100);
   PORTD&=~BIT(PD5);
   
   //��ʾ��λ
   PORTB=Number[Hundred];     //��ģ��
    Delay(100);         //��΢�ӳ�     
   //��λѡ
   PORTD|=BIT(PD4);    //PD4�ߵ�ƽ
   Delay(100);         //��΢�ӳ�
   PORTD&=~BIT(PD4);   //PD4�͵�ƽ
 
   //��ʾʮλ
   PORTB=Number[Ten];  //��ģ��
   Delay(100);         //��΢�ӳ�     
    //��λѡ
   PORTC|=BIT(PC7);    //PC7�ߵ�ƽ
   Delay(100);         //��΢�ӳ�
   PORTC&=~BIT(PC7);   //PC7�͵�ƽ
 
   //��ʾ��λ
   PORTB=Number[One];  //��ģ��
   Delay(100);         //��΢�ӳ�
	     
   //��λѡ
   PORTC|=BIT(PC6);    //PC6�ߵ�ƽ
   Delay(100);         //��΢�ӳ�
   PORTC&=~BIT(PC6);   //PC6�͵�ƽ
}

//IO��ʼ������
void IO_Init()
{
   DDRA|=BIT(PA7);		//PA7����Ϊ���״̬ ����LED��ˮ�ƿ����ܿ���
   //PORTA|=BIT(PA7);	    //PA7����ߵ�ƽ����LED��ˮ�������ܿ���
   PORTA&=BIT(PA7);	    //PA7����͵�ƽ���ص�LED��ˮ�������ܿ���
   DDRA|=BIT(PA3);		//PA3����Ϊ���״̬ ���ڿ��Ʒ�����
   //����� λ��ʾ
   DDRC|=BIT(PC6);		//����Ϊ���״̬ 
   DDRC|=BIT(PC7);		//����Ϊ���״̬ 
   DDRD|=BIT(PD4);		//����Ϊ���״̬ 
   DDRD|=BIT(PD5);		//����Ϊ���״̬   
   //����� ����ʾ
   DDRB=0xff;				//PB0~7Ϊ���״̬
}

//������
void main()
{ int n,a; 
   IO_Init();
   for(n=0;;)
   {
      for(a=0;a<5;a++)
	  {
      Number_Show(n); 
      }
    n++;
	if(n>9999)n=0;
	}
} 