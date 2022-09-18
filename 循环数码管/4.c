
#include "iom16v.h"
#include "macros.h"

//数组声明并定义在存储数据区code
//0~9
#pragrma data:code  
unsigned char const Number[]={0xaf,0xa0,0xc7,0xe6,0xe8,0x6e,0x6f,0xa2,
                                 0xef,0xee,};
//A~F
#pragrma data:code
unsigned char const Alpha[]={0xeb,0x6d,0x0f,0xe5,0x4f,0x4b,0x00,};

//枚举变量aplha声明
enum alpha{A,B,C,D,E,F};


//延迟函数
void Delay(unsigned long x)
{
   while(x--);
}

//动态显示函数
void Number_Show(unsigned int Num)
{
   unsigned char thousand,Hundred,Ten,One;
   thousand=Num/1000;
   Hundred=Num%1000/100;       //取百位
   Ten=Num%100/10;        //取十位
   One=Num%10;            //取个位
   
   PORTB=Number[thousand];
   Delay(100);
   PORTD|=BIT(PD5);
   Delay(100);
   PORTD&=~BIT(PD5);
   
   //显示百位
   PORTB=Number[Hundred];     //送模码
    Delay(100);         //稍微延迟     
   //送位选
   PORTD|=BIT(PD4);    //PD4高电平
   Delay(100);         //稍微延迟
   PORTD&=~BIT(PD4);   //PD4低电平
 
   //显示十位
   PORTB=Number[Ten];  //送模码
   Delay(100);         //稍微延迟     
    //送位选
   PORTC|=BIT(PC7);    //PC7高电平
   Delay(100);         //稍微延迟
   PORTC&=~BIT(PC7);   //PC7低电平
 
   //显示个位
   PORTB=Number[One];  //送模码
   Delay(100);         //稍微延迟
	     
   //送位选
   PORTC|=BIT(PC6);    //PC6高电平
   Delay(100);         //稍微延迟
   PORTC&=~BIT(PC6);   //PC6低电平
}

//IO初始化函数
void IO_Init()
{
   DDRA|=BIT(PA7);		//PA7设置为输出状态 用于LED流水灯控制总开关
   //PORTA|=BIT(PA7);	    //PA7输出高电平，打开LED流水灯锁存总开关
   PORTA&=BIT(PA7);	    //PA7输出低电平，关掉LED流水灯锁存总开关
   DDRA|=BIT(PA3);		//PA3设置为输出状态 用于控制蜂鸣器
   //数码管 位显示
   DDRC|=BIT(PC6);		//设置为输出状态 
   DDRC|=BIT(PC7);		//设置为输出状态 
   DDRD|=BIT(PD4);		//设置为输出状态 
   DDRD|=BIT(PD5);		//设置为输出状态   
   //数码管 段显示
   DDRB=0xff;				//PB0~7为输出状态
}

//主函数
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