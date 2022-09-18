#include "iom16v.h"
#include "macros.h"
#include "AVR_HL-2.h"		//�����Զ��峣��ͷ�ļ�
#pragma interrupt_handler Increase_INT0_Ir:2
#pragma interrupt_handler Decrease_INT1_Ir:3
#define uchar unsigned char
 #define uint unsigned int 
 #define RS_CLR PORTA&=~BIT(4)              
 #define RS_SET PORTA|=BIT(4)
 #define RS_OUT DDRA|=BIT(4)
 #define RW_CLR PORTA&=~BIT(5)
 #define RW_SET PORTA|=BIT(5)
 #define RW_OUT DDRA|=BIT(5)
 #define E_CLR PORTA&=~BIT(6)
 #define E_SET PORTA|=BIT(6)
 #define E_OUT DDRA|=BIT(6)
 
 const uchar CGRAM[LCDa_CGMAX] =
{
	//8*5��ģ
	
		0x02,0x02,0x1F,0x06,0x0B,0x12,0x02,0x02,
		0x00,0x0E,0x0A,0x0A,0x0A,0x0A,0x0A,0x1B,
		0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,
		0x02,0x02,0x1F,0x06,0x0B,0x12,0x02,0x02,
		0x00,0x00,0x1F,0x00,0x05,0x1F,0x05,0x09,
		//0x00,0x00,0x1F,0x05,0x1F,0x05,0x09,0x11,
		//0x00,0x10,0x1F,0x09,0x06,0x06,0x09,0x00,
		0x10,0x10,0x1F,0x0A,0x04,0x0C,0x13,0x01,
		0x08,0x04,0x1F,0x09,0x0A,0x06,0x0A,0x11,
		0x00,0x00,0x11,0x01,0x09,0x09,0x09,0x03,
		

};
void LCD1602_gotoXY(uchar Row, uchar Col)
{	
	switch (Row)		  //ѡ����
	{
		case 2:
			LCD1602_sendbyte(iCmd, LCDa_L2 + Col); break;	//д���2�е�ָ����	
		default:
			LCD1602_sendbyte(iCmd, LCDa_L1 + Col); break;	//д���1�е�ָ����	
	}
}
void LCD1602_sendbyte(uchar DatCmd, uchar dByte)
{
	if (DatCmd == iCmd)		//ָ�����
		LCDa_CLR_RS;
	else
		LCDa_SET_RS;		//���ݲ���
		
	LCDa_CLR_RW;			//д��������
	LCDa_SET_E;
	LCDa_DO = dByte;		//д������
	Delayms(1);
	LCDa_CLR_E;	
}
void LCD1602_wrCGRAM(const uchar *ptCGRAM)
{
	uchar i;
	LCD1602_sendbyte(iCmd, LCDa_CGRAM_ADDR);  //д��CGRAM�׵�ַ
	for (i = 0; i < LCDa_CGMAX; i++)		  //д��64���ֽڵ�CGRAM����
	{
		LCD1602_sendbyte(iDat,ptCGRAM[i]);
	}
}
/*******************************************
��������: LCD1602_disCGRAM
��    ��: ��ʾCGRAM���ݣ���64���ֽ�д�����У�ÿ��32���ֽ�
��    ��: ��
����ֵ  : ��
/********************************************/
void LCD1602_disCGRAM(void)
{
	uchar i;
	LCD1602_gotoXY(1,3);   //�ӵ�1�е�6�п�ʼ��ʾ
	for (i = 0;i <4;i++)   //��ʾǰ32���ֽڵ�����
	{	 	
		LCD1602_sendbyte(iDat, i);		
	}
	LCD1602_gotoXY(1,7);   //�ӵ�2�е�6�п�ʼ��ʾ
	for (i = 4;i <8;i++)   //��ʾ��32���ֽڵ�����
	{	 	
		LCD1602_sendbyte(iDat,i);		
	}
}
void delay_1ms(void)                 //1ms��ʱ����
  {
   unsigned int i;
   for (i=0;i<1140;i++);
  }
 void delay_nms(unsigned int n)       //N ms��ʱ����
  {
   unsigned int i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }
 void write_com(uchar com)//д��������
 {
  RS_SET;//�ߵ�ƽ
  RW_SET;
  E_CLR;
  RS_CLR;
  RW_CLR;
  PORTB=com;//��E��ɸߵ�ƽ֮ǰ����������
  delay_nms(1);
  E_SET;
  delay_nms(1);
  E_CLR;
 }
  void write_data(uchar data)//����������
 {
  RS_CLR;
  RW_SET;
  E_CLR;
  RS_SET;
  RW_CLR;
  PORTB=data;
  delay_nms(1);
  E_SET;
  delay_nms(1);
  E_CLR;
 }
 void init (void)//���������ֲ��ʼ��
 {
  DDRB=0XFF;
  PORTB=0;
  RS_OUT;
  E_OUT;
  RW_OUT;
  E_CLR;//����Ϊ���
delay_nms(20);
  write_com(0x38);
  delay_nms(5);
  write_com(0x38);
  delay_nms(5);
  write_com(0x38);
  write_com(0x38);
  write_com(0x08);
  write_com(0x01);
  write_com(0x06);
  write_com(0x0c);
 }
void Interrupt_Init(void)
{
    PORTD = 0X08; 
    DDRD = 0XF3; //K1��K2 ����(PD2��PD3)����Ϊ����˿�
	MCUCR |= (1 << ISC11) | (1 << ISC01) | (1 << ISC00);
	//INT0 ����Ϊ�������жϣ�INT1 Ϊ�½����ж�����
	GICR |= (1 << INT0) | (1 << INT1); //���� INT0��INT1 �ж�
    GIFR |= (1 << INTF1) | (1 << INTF0); //��� INT0��INT1 �жϱ�־λ
}
void main(void)
{
	Interrupt_Init();	//�����жϳ�ʼ������
	SREG|=BIT(7);		//ȫ���ж�ʹ��λ��һ
}
void Increase_INT0_Ir(void)  //�ⲿ�ж� 0 ������������ K1 ���º󣬽�����ж�
{
	uchar table1[]="191  AVR-16";
 uchar i;
  init();
 write_com(0x01);
 delay_nms(2);
  write_com(0x80+0x0F);
  for(i=0;i<11;i++)
  {
   write_data(table1[i]);
   delay_nms(5);}

 for(i=0;i<12;i++)
	  {
	     write_com(0X18);
		 delay_nms(300);
	  }
}	/*void Decrease_INT1_Ir(void) //�ⲿ�ж� 1 ������������ K2 ���º󣬽�����ж�
{
	uchar table2[]="LCDAAAAAVR";
 uchar i;
  init();
  write_com(0x01);
  write_com(0x80+0x03);
  for(i=0;i<10;i++)
  {
   write_data(table2[i]);
   delay_nms(1);}
   delay_nms(5000);
   write_com(0x01);
}*/
/*void Decrease_INT1_Ir(void)
{uchar i;
init();
  write_com(0x01);
LCD1602_wrCGRAM(CGRAM);
  Delayms(90);
  write_com(0x80+0x03);
  for(i=0;i<8;i++)
  {
   write_data(CGRAM[i]);
   delay_nms(1);}
  Delayms(2000);
    write_com(0x01);

}*/
void Decrease_INT1_Ir(void)
{
init();
  
LCD1602_wrCGRAM(CGRAM);
  Delayms(90);
  LCD1602_disCGRAM();
  Delayms(5000);
    write_com(0x01);

}