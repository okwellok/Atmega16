#include "iom16v.h"  
#include "macros.h"
#define uint unsigned int
unsigned char Numk3=0;
unsigned char Numk4=0;
void init(void)//LED 的初始化
{
   DDRA|=BIT(PA7);		//PA7设置为输出状态 用于LED流水灯控制总开关
   PORTA|=BIT(PA7);	    //PA7输出高电平，打开LED流水灯锁存总开关
   //PORTA&=BIT(PA7);	    //PA7输出低电平，关掉LED流水灯锁存总开关
   DDRB=0xff;				//PB0~7为输出状态*/
   //KEY
   PORTB = 0X00;    //输出低，LED不亮
   PORTD = 0Xc0; //一定要使能上拉电阻，按键k3k4 否则会有干扰   1100 0000
   DDRD = 0X33;   //K3、K4按键(PD6、PD7)设置为输入端口 
}
void Delay(uint ms)
{
   uint i,j;
      for(i=0;i<ms;i++)
	      {
		  for(j=0;j<1000;j++);
		  }
}
void KEY(void)// 按健函数
{	
    if(!(PIND & (1 <<  PD6)))     //判断按键是否按下
		{
			Delay(20);//判断按键按下，延时一会再判断是否按下， 以消除干扰
			if(!(PIND & (1 <<  PD6)))  // 按键真正按下后，进行相应处理
			{		  Numk3++;
				PORTB = Numk3;	 //按键按下，灯亮	
				
				while(!(PIND & (1 <<  PD6)));//等待按键释放
			}
		}
	if(!(PIND & (1 <<  PD7)))//判断按键是否按下
	{
		Delay(20);//判断按键按下，延时一会再判断是否按下， 以消除干扰
		if(!(PIND & (1 <<  PD7)))// 按键真正按下后，进行相应处理
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