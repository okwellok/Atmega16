#include <iom16v.h>
#include <macros.h>
//定义数据类型的简单写法
#define uint unsigned int  
#define uchar unsigned char   
//8M的内部晶振
#define fosc 8000000


uchar command;
void init_port(void)//IO口初始化
{
  DDRB=0xff;
  PORTB=0xff;
  
  DDRA|=BIT(PA2);
  PORTA&=~BIT(PA2);
  PORTC&=~BIT(PC6);
  PORTC&=~BIT(PC7);
  PORTD&=~BIT(PD4);
  DDRA|=BIT(PA6);
  PORTA|=BIT(6);
  
}
void SEGOFF()
{
  DDRA|=BIT(PA3);
  DDRA|=BIT(PA4);
  DDRB=0xff;
  PORTB=0xff;
  PORTA|=BIT(PA3);
  PORTA&=~BIT(PA3);
  PORTB=0xff;
  PORTA|=BIT(PA4);
  PORTA&=~BIT(PA4);
  }



void stop(void)
{
  PORTC&=~((1<<PC2)|(1<<PC3)|(1<<PC6)|(1<<PC7));
  
  }
  
  
  void uar_init(uint baud)
  { 
   uint M;
   UCSRC=0x86;
   M=fosc/16/baud-1;
   UBRRH=M/256;
   UBRRL=M%256;
   UCSRB=0x90;
   SEI();
   }
   
   void delay_1us(void)
   {
   asm("nop");
   }
   
   void delay_nus(uint n)
   {
     uint i=0;
	 for(i=0;i<n;i++)
	 delay_1us();
  }
	
	 
	 
	 void main(void)
	 {
	 //int n;
	 SEGOFF(); 
	 init_port();
	 uar_init(9600);
	 while(1)
	 {
	 }
	 }
	 
	 #pragma interrupt_handler uartrece_isr:12
	 void uartrece_isr(void)
	 {
	 command=UDR;
	 switch(command)
	 {
	 case'1':
	   PORTB&=~(1<<PB0);
	   break;
	   
	 case'4':
	   PORTB|=(1<<PB0);
	   break;
	   
	  case'2':
	   PORTB&=~(1<<PB1);
	   break;  
   
      case'5':
	   PORTB|=(1<<PB1);
	   break;
	 
	  case'3':
	   PORTB&=~(1<<PB2);
	   
	   break;   
	   
	  case'6':
	   PORTB|=~(1<<PB2  );
		   break; 
		   
	  case'8':
	   PORTA|=BIT(6);
	   delay_nus(10);
		   break; 
		   
	   case'7':
	   PORTA&=~BIT(6);
		   break; 
		   
      default:
	      stop();
		  break;
		  
	}
	} 