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

//DS18B20复位函数
void DS1302_Reset()
{	
	DDRA|=BIT(DQ);			//DQ为输出状态
	PORTA&=~BIT(DQ);			//输出低电平
	Delay_1us(500);			//延迟500
	PORTA|=BIT(DQ);			//释放总线
	Delay_1us(60);			//延迟60
	DDRA&=~BIT(DQ);			//输入
	while(PINA&BIT(DQ));		//等待从机DS18B20应答（低电平有效）
	while(!(PINA&BIT(DQ)));	//等待从机DS18B20释放总线
}

//DS1302写字节函数
void DS1302_Write(unsigned char Data)
{
	unsigned char i;
	DDRA|=BIT(DQ);		//输出
	for(i=0;i<8;i++)
	{
			PORTA&=~BIT(DQ);				//拉低总线
			Delay_1us(10);					//延迟10~15
			
			if(Data&0x01) PORTA|=BIT(DQ);//逻辑0 持续拉低，逻辑1拉高
			else PORTA&=~BIT(DQ);		
			Delay_1us(40);		 			//延迟40~45
			
			PORTA|=BIT(DQ);					//释放总线
			Delay_1us(1);					//稍微延迟
			Data>>=1;
	}
}

//DS1302读字节函数
unsigned char DS1302_Read()
{
	unsigned char i,Temp;
												
	for(i=0;i<8;i++)
	{
			Temp>>=1;						//数据右移
			
			DDRA|=BIT(DQ);					//输出状态
			PORTA&=~BIT(DQ);				//拉低总线
			PORTA|=BIT(DQ);					//释放总线
			DDRA&=~BIT(DQ);					//输入状态
			
			if(PINA&BIT(DQ)) Temp|=0x80;	//逻辑0拉低，逻辑1拉高
			Delay_1us(45);		 			//40~45
	}
	
	return Temp;
}

//读温度函数
unsigned int Read_Temperature()
{
	unsigned int Temp1,Temp2;
	
	DS1302_Reset();			//DS1302复位
	DS1302_Write(0xCC);		//跳过ROM
	DS1302_Write(0x44);		//温度转换
	
	DS1302_Reset();			//DS1302复位
	DS1302_Write(0xCC);		//跳过ROM
	DS1302_Write(0xbe);		//读取RAM
		
	Temp1=DS1302_Read();		//读低八位，LS Byte, RAM0
	Temp2=DS1302_Read();		//读高八位，MS Byte, RAM1
	DS1302_Reset();			//DS1302复位，表示读取结束

	return (((Temp2<<8)|Temp1)*6.25);	//0.0625=xx, 0.625=xx.x, 6.25=xx.xx
	//16位分辨率 数据*电压/该电压数字
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
    Hundred=Num%1000/100 + 0x30;       //取百位
    Ten=Num%100/10 + 0x30;        //取十位
    One=Num%10 + 0x30;           //取个位
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
			Temp=Read_Temperature();		//调用读取温度函数
			Show_Num(Temp);				//显示温度
			delay(1000);					//稍微延迟
	}
	
}
