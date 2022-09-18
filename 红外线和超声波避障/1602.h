/* 用法：
   LCD_init();
   LCD_write_string(列,行,"字符串");
   LCD_write_char(列,行,'字符'); 
 ---------------------------------------------------------------
下面是AVR与LCD连接信息
PA4 ->RS
PA5	->RW
PA6 ->EN
PB	->D4-D7
要使用本驱动，改变下面配置信息即可
-----------------------------------------------------------------*/
#define LCD_EN_PORT    PORTA   //以下2个要设为同一个口
#define LCD_EN_DDR     DDRA
#define LCD_RS_PORT    PORTA   //以下2个要设为同一个口
#define LCD_RS_DDR     DDRA
#define LCD_RW_PORT    PORTA   //以下2个要设为同一个口
#define LCD_RW_DDR     DDRA
#define LCD_DATA_PORT  PORTB   //以下3个要设为同一个口
#define LCD_DATA_DDR   DDRB   //默认情况下连线必须使用高四位端口,如果不是请注意修改
#define LCD_DATA_PIN   PINB
#define LCD_RS         (1<<PA4) //       out
#define LCD_EN         (1<<PA6) //       out
#define LCD_RW         (1<<PA5) //      out  可以直接接地
#define LCD_DATA       (1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7)//((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|
/*--------------------------------------------------------------------------------------------------
函数说明
--------------------------------------------------------------------------------------------------*/
void LCD_init(void);
void LCD_en_write(void);
void LCD_write_command(uchar command) ;
void LCD_write_data(uchar data);
void LCD_set_xy (uchar x, uchar y);
void LCD_write_string(uchar X,uchar Y,uchar *s);
void LCD_write_char(uchar X,uchar Y,uchar data);

//-----------------------------------------------------------------------------------------

void LCD_init(void)         //液晶初始化
{
  LCD_DATA_DDR|=LCD_DATA;   //数据口方向为输出
  LCD_EN_DDR|=LCD_EN;       //设置EN方向为输出
  LCD_RS_DDR|=LCD_RS;       //设置RS方向为输出
  LCD_RW_DDR|=LCD_RW;       //设置RW方向为输出
  LCD_RW_PORT&=~LCD_RW;        //RW=0
  LCD_write_command(0x28); 
  LCD_en_write();
  delay_nus(40);
  LCD_write_command(0x28);  //0x38为8位显示   0x28为4位显示
  LCD_write_command(0x0c);  //显示开
  LCD_write_command(0x01);  //清屏
  delay_nms(2);
  

  
}

void LCD_en_write(void)  //液晶使能
{
  LCD_EN_PORT|=LCD_EN;
  delay_nus(1);
  LCD_EN_PORT&=~LCD_EN;
}





void LCD_write_command(uchar command) //写指令
{
//连线为高4位的写法
  delay_nus(16);
  LCD_RS_PORT&=~LCD_RS;        //RS=0
  LCD_DATA_PORT&=0X0f;         //清高四位
  LCD_DATA_PORT|=command&0xf0; //写高四位
  LCD_en_write();
  command=command<<4;          //低四位移到高四位
  LCD_DATA_PORT&=0x0f;         //清高四位
  LCD_DATA_PORT|=command&0xf0; //写低四位
  LCD_en_write();
/*
   //数据线8线写法
  delay_nus(16);
  LCD_RS_PORT&=~LCD_RS;        //RS=0
  LCD_DATA_PORT=command;
  LCD_en_write();

  
 

  //连线为低四位的写法
  delay_nus(16);
  LCD_RS_PORT&=~LCD_RS;        //RS=0
  LCD_DATA_PORT&=0xf0;         //清高四位
  LCD_DATA_PORT|=(command>>4)&0x0f; //写高四位
  LCD_en_write();
  LCD_DATA_PORT&=0xf0;         //清高四位
  LCD_DATA_PORT|=command&0x0f; //写低四位
  LCD_en_write(); 
*/
  
}

void LCD_write_data(uchar data) //写数据   对rs高电平是为数据
{
 //连线为高4位的写法
  delay_nus(16);
  LCD_RS_PORT|=LCD_RS;       //RS=1
  LCD_DATA_PORT&=0X0f;       //清高四位
  LCD_DATA_PORT|=data&0xf0;  //写高四位
  LCD_en_write();
  data=data<<4;               //低四位移到高四位
  LCD_DATA_PORT&=0X0f;        //清高四位
  LCD_DATA_PORT|=data&0xf0;   //写低四位
  LCD_en_write();
/*
  //数据线8线写法
  delay_nus(16);
  LCD_RS_PORT|=LCD_RS;       //RS=1
  LCD_DATA_PORT=data;
  LCD_en_write();
  
 
  
/*
  //连线为低四位的写法 
  delay_nus(16);
  LCD_RS_PORT|=LCD_RS;       //RS=1
  LCD_DATA_PORT&=0Xf0;       //清高四位
  LCD_DATA_PORT|=(data>>4)&0x0f;  //写高四位
  LCD_en_write();
 
  LCD_DATA_PORT&=0Xf0;        //清高四位
  LCD_DATA_PORT|=data&0x0f;   //写低四位
  LCD_en_write();
*/
  
}
//1602 F=2^4 分别是0F,F0两种状况所以用四位就可以了

void LCD_set_xy( uchar x, uchar y )  //写地址函数，对rs高电平是为数据
{
    uchar address;
    if (y == 0) address = 0x80 + x;
    else   address = 0xc0 + x;
    LCD_write_command( address);
}
  
void LCD_write_string(uchar X,uchar Y,uchar *s) //列x=0~15,行y=0,1
{
    LCD_set_xy( X, Y ); //写地址    
    while (*s)  // 写显示字符
    {
      LCD_write_data( *s );
      s ++;
    }
      
}

void LCD_write_char(uchar X,uchar Y,uchar data) //列x=0~15,行y=0,1
{
  LCD_set_xy( X, Y ); //写地址
  LCD_write_data( data);
  
}


