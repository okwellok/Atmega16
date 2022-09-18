//PB口只用到PB4~7
#define LCD_RS         (1<<PA4) //       out
#define LCD_EN         (1<<PA6) //       out
#define LCD_RW         (1<<PA5) //      out  可以直接接地
#define LCD_DATA       (1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7)//((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|


//-----------------------------------------------------------------------------------------

void LCD_init(void)         //液晶初始化
{
  DDRB|=LCD_DATA;   //数据口方向为输出
  DDRA|=LCD_EN;       //设置EN方向为输出
  DDRA|=LCD_RS;       //设置RS方向为输出
  DDRA|=LCD_RW;       //设置RW方向为输出
  PORTA&=~LCD_RW;        //RW=0
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
  PORTA&=~LCD_RS;        //RS=0
  PORTB&=0X0f;         //清高四位
  PORTB|=command&0xf0; //写高四位
  LCD_en_write();
  command=command<<4;          //低四位移到高四位
  PORTB&=0x0f;         //清高四位
  PORTB|=command&0xf0; //写低四位
  LCD_en_write();
}

void LCD_write_data(uchar data) //写数据
{
 //连线为高4位的写法
  delay_nus(16);
  PORTA|=LCD_RS;       //RS=1
  PORTB&=0X0f;       //清高四位
  PORTB|=data&0xf0;  //写高四位
  LCD_en_write();
  data=data<<4;               //低四位移到高四位
  PORTB&=0X0f;        //清高四位
  PORTB|=data&0xf0;   //写低四位
  LCD_en_write();
}


void LCD_set_xy( uchar x, uchar y )  //写地址函数
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


