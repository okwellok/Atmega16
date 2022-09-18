/*-----------------------------------------------------------------------
��ʱ����
��������ICC-AVR v6.31A 
Ŀ��оƬ : M16
ʱ��: 8.0000Mhz
-----------------------------------------------------------------------*/
#ifndef __delay_h
#define __delay_h
void delay_nus(uint n);
void delay_nms(uint n);
void delay_1us(void);
void delay_1ms(void) ; 

void delay_1us(void)                 //1us��ʱ����
  {
   asm("nop");
  }

void delay_nus(uint n)       //N us��ʱ����
  {
   uint i=0;
   for (i=0;i<n;i++)
   delay_1us();
  }
  
void delay_1ms(void)                 //1ms��ʱ����
  {
   uint i;
   for (i=0;i<1140;i++);
  }
  
void delay_nms(uint n)       //N ms��ʱ����
  {
   uint i=0;
   for (i=0;i<n;i++)
   delay_1ms();
  }
  
  #endif

 
