#include "iom16v.h"  
#include "macros.h"
#define uint unsigned int
unsigned char Numk3=0;
unsigned char Numk4=0;
void init(void)//LED �ĳ�ʼ��
{
   DDRA|=BIT(PA7);		//PA7����Ϊ���״̬ ����LED��ˮ�ƿ����ܿ���
   PORTA|=BIT(PA7);	    //PA7����ߵ�ƽ����LED��ˮ�������ܿ���
   //PORTA&=BIT(PA7);	    //PA7����͵�ƽ���ص�LED��ˮ�������ܿ���
   DDRB=0xff;				//PB0~7Ϊ���״̬*/
   //KEY
   PORTB = 0X00;    //����ͣ�LED����
   PORTD = 0Xc0; //һ��Ҫʹ���������裬����k3k4 ������и���   1100 0000
   DDRD = 0X33;   //K3��K4����(PD6��PD7)����Ϊ����˿� 
}
void Delay(uint ms)
{
   uint i,j;
      for(i=0;i<ms;i++)
	      {
		  for(j=0;j<1000;j++);
		  }
}
void KEY(void)// ��������
{	
    if(!(PIND & (1 <<  PD6)))     //�жϰ����Ƿ���
		{
			Delay(20);//�жϰ������£���ʱһ�����ж��Ƿ��£� ����������
			if(!(PIND & (1 <<  PD6)))  // �����������º󣬽�����Ӧ����
			{		  Numk3++;
				PORTB = Numk3;	 //�������£�����	
				
				while(!(PIND & (1 <<  PD6)));//�ȴ������ͷ�
			}
		}
	if(!(PIND & (1 <<  PD7)))//�жϰ����Ƿ���
	{
		Delay(20);//�жϰ������£���ʱһ�����ж��Ƿ��£� ����������
		if(!(PIND & (1 <<  PD7)))// �����������º󣬽�����Ӧ����
		{	 ++Numk4;
				 if (Numk4>=8)
					Numk4=0;
			PORTB = 0X01<<Numk4;		      
			while(!(PIND & (1 <<  PD7)));  
			}
		}	
}
void main(void)  
{  		  
     init(); 
   while(1)
   {
	KEY();
   }
}