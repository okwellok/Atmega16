#include <iom16v.h>
#include <macros.h>

#define  uchar unsigned char
#define  uint  unsigned int

int Page = 0; //ԭ����uint����Ϊ��ѭ����ҳ

#pragma interrupt_handler Increase_INT0_Ir:2
#pragma interrupt_handler Decrease_INT1_Ir:3

void Port_Init()
{
	DDRB=0XFF;
	DDRA|=BIT(4)|BIT(5)|BIT(6);
	PORTA&=~BIT(6);

	DDRD &= ~(1 << 2);//INT0������
	PORTD |= (1 << 2);//�ڲ���������ʹ��
	DDRD &= ~(1 << 3);//INT1������
	PORTD |= (1 << 3);//�ڲ���������ر�
}

void Interrupt_Init()
{
    PORTD = 0X08; //һ��Ҫʹ�� K2 ���������裬������и���
    DDRD = 0XF3; //K1��K2 ����(PD2��PD3)����Ϊ����˿�
	
	MCUCR |= (1 << ISC11) | (1 << ISC01) | (1 << ISC00);//INT0 ����Ϊ�������жϣ�INT1 Ϊ�½����ж�����
	GICR |= (1 << INT0) | (1 << INT1); //���� INT0��INT1 �ж�
    GIFR |= (1 << INTF1) | (1 << INTF0); //��� INT0��INT1 �жϱ�־λ
}

void delay(uint ms)
{
        uint i,j;
	for(i=0;i<ms;i++)
	   {
	   for(j=0;j<1141;j++);
       }
}
void write_com(uchar com)
{
       PORTA&=~BIT(4);
	   PORTA&=~BIT(5);
	   PORTB=com;
	   PORTA|=BIT(6);
	   delay(1);
	   PORTA&=~BIT(6);
	   	delay(5);
}

void write_dat(uchar dat)
{     
       PORTA|=BIT(4);
	   PORTA&=~BIT(5);
	   PORTB=dat;
	   PORTA|=BIT(6);
	   delay(1);
	   PORTA&=~BIT(6);
	   delay(5);

}
void Lcd_init()
{
	  write_com(0X38);
	  delay(5);
	  write_com(0X01);
	  delay(5);
	  write_com(0X0C);
	  delay(5);
	  write_com(0X06);
	  delay(5);
}

void Show_Num(uint Num)
{

 unsigned char Thousand,Hundred,Ten,One;
 	Thousand=Num/1000 + 0x30;
    Hundred=Num%1000/100 + 0x30;       
    Ten=Num%100/10 + 0x30;        
    One=Num%10 + 0x30;           
	Show_Text("     ", 2);
	  write_dat(Thousand);
	  write_dat(Hundred);
	  write_dat(Ten);
	  write_dat(One);
}

void Show_Text(char *str, char line)
{
	char temp[16];
	int i,j;
	i=0;
	while(*(str+i)!='\0')
	{
		temp[i]=*(str+i);

	i++;
	}
	if (line==1) write_com(0X80+0X00);
	else write_com(0X80+0X40);
	  for(j=0;j<i;j++)
	  {
	     write_dat(temp[j]);
	  }
}

void show_page()
{
 	write_com(0X01);
 	delay(5);
    if(Page==0)
	  {
		Show_Text("191 B8-308 AVR!!", 1);
	  }
	  if(Page==1)
	  {
		Show_Num(1234);
	  }
}

void  main()
{
	  Port_Init();
	  Interrupt_Init();
	  SREG|=BIT(7);
	  Lcd_init();

	 while(1)
	 { 
	 }
	  
}

//INT0�жϺ���
void Increase_INT0_Ir()  //�ⲿ�ж� 0 ������������ K1 ���º󣬽�����ж�
{
 Page--;
 if(Page<0) Page=1;
 show_page();
}

//INT1�жϺ���
void Decrease_INT1_Ir() //�ⲿ�ж� 1 ������������ K2 ���º󣬽�����ж�
{
 Page++;
 if(Page>1) Page=0;
 show_page();
}


