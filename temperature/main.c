#include <iom16v.h>
#include <macros.h>
#define  uchar unsigned char
#define  uint  unsigned int
#define DQ PA2

void Delay_1us(unsigned int x)
{
 		unsigned int i;
 		x=x*5/4;		  	 
 		for( i=0;i<x;i++); 
}

//DS18B20��λ����
void DS1302_Reset()
{	
	DDRA|=BIT(DQ);			//DQΪ���״̬
	PORTA&=~BIT(DQ);			//����͵�ƽ
	Delay_1us(500);			//�ӳ�500
	PORTA|=BIT(DQ);			//�ͷ�����
	Delay_1us(60);			//�ӳ�60
	DDRA&=~BIT(DQ);			//����
	while(PINA&BIT(DQ));		//�ȴ��ӻ�DS18B20Ӧ�𣨵͵�ƽ��Ч��
	while(!(PINA&BIT(DQ)));	//�ȴ��ӻ�DS18B20�ͷ�����
}

//DS1302д�ֽں���
void DS1302_Write(unsigned char Data)
{
	unsigned char i;
	DDRA|=BIT(DQ);		//���
	for(i=0;i<8;i++)
	{
			PORTA&=~BIT(DQ);				//��������
			Delay_1us(10);					//�ӳ�10~15
			
			if(Data&0x01) PORTA|=BIT(DQ);//�߼�0 �������ͣ��߼�1����
			else PORTA&=~BIT(DQ);		
			Delay_1us(40);		 			//�ӳ�40~45
			
			PORTA|=BIT(DQ);					//�ͷ�����
			Delay_1us(1);					//��΢�ӳ�
			Data>>=1;
	}
}

//DS1302���ֽں���
unsigned char DS1302_Read()
{
	unsigned char i,Temp;
												
	for(i=0;i<8;i++)
	{
			Temp>>=1;						//��������
			
			DDRA|=BIT(DQ);					//���״̬
			PORTA&=~BIT(DQ);				//��������
			PORTA|=BIT(DQ);					//�ͷ�����
			DDRA&=~BIT(DQ);					//����״̬
			
			if(PINA&BIT(DQ)) Temp|=0x80;	//�߼�0���ͣ��߼�1����
			Delay_1us(45);		 			//40~45
	}
	
	return Temp;
}

//���¶Ⱥ���
unsigned int Read_Temperature()
{
	unsigned int Temp1,Temp2;
	
	DS1302_Reset();			//DS1302��λ
	DS1302_Write(0xCC);		//����ROM
	DS1302_Write(0x44);		//�¶�ת��
	
	DS1302_Reset();			//DS1302��λ
	DS1302_Write(0xCC);		//����ROM
	DS1302_Write(0xbe);		//��ȡRAM
		
	Temp1=DS1302_Read();		//���Ͱ�λ��LS Byte, RAM0
	Temp2=DS1302_Read();		//���߰�λ��MS Byte, RAM1
	DS1302_Reset();			//DS1302��λ����ʾ��ȡ����

	return (((Temp2<<8)|Temp1)*6.25);	//0.0625=xx, 0.625=xx.x, 6.25=xx.xx
	//16λ�ֱ��� ����*��ѹ/�õ�ѹ����
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
void Lcd_Init()
{
	 DDRB=0XFF;
	 DDRA|=BIT(4)|BIT(5)|BIT(6);
	 PORTA&=~BIT(6);
	 
	  write_com(0X38);
	  write_com(0X01);
	  write_com(0X0C);
	  write_com(0X06);
}

void Show_Num(uint Num)
{

 unsigned char Thousand,Hundred,Ten,One;
 	Thousand=Num/1000 + 0x30;
    Hundred=Num%1000/100 + 0x30;       //ȡ��λ
    Ten=Num%100/10 + 0x30;        //ȡʮλ
    One=Num%10 + 0x30;           //ȡ��λ
	Show_Text("     ", 2);
	  //write_com(0X80+0X40);
	  write_dat(Thousand);
	  write_dat(Hundred);
	  write_dat('.');
	  write_dat(Ten);
	  write_dat(One);
	  write_dat(0xdf);
	  write_dat('C');
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

void main()
{
	unsigned int Temp;
	Lcd_Init();
	Show_Text("191 B8-308 AVR!!", 1);
	while(1)
	{	
			Temp=Read_Temperature();		//���ö�ȡ�¶Ⱥ���
			Show_Num(Temp);				//��ʾ�¶�
			delay(1000);					//��΢�ӳ�
	}
	
}
