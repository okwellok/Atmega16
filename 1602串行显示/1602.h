//PB��ֻ�õ�PB4~7
#define LCD_RS         (1<<PA4) //       out
#define LCD_EN         (1<<PA6) //       out
#define LCD_RW         (1<<PA5) //      out  ����ֱ�ӽӵ�
#define LCD_DATA       (1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7)//((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|


//-----------------------------------------------------------------------------------------

void LCD_init(void)         //Һ����ʼ��
{
  DDRB|=LCD_DATA;   //���ݿڷ���Ϊ���
  DDRA|=LCD_EN;       //����EN����Ϊ���
  DDRA|=LCD_RS;       //����RS����Ϊ���
  DDRA|=LCD_RW;       //����RW����Ϊ���
  PORTA&=~LCD_RW;        //RW=0
  LCD_write_command(0x28); 
  LCD_en_write();
  delay_nus(40);
  LCD_write_command(0x28);  //0x38Ϊ8λ��ʾ   0x28Ϊ4λ��ʾ
  LCD_write_command(0x0c);  //��ʾ��
  LCD_write_command(0x01);  //����
  delay_nms(2);
}

void LCD_en_write(void)  //Һ��ʹ��
{
  LCD_EN_PORT|=LCD_EN;
  delay_nus(1);
  LCD_EN_PORT&=~LCD_EN;
}


void LCD_write_command(uchar command) //дָ��
{
//����Ϊ��4λ��д��
  delay_nus(16);
  PORTA&=~LCD_RS;        //RS=0
  PORTB&=0X0f;         //�����λ
  PORTB|=command&0xf0; //д����λ
  LCD_en_write();
  command=command<<4;          //����λ�Ƶ�����λ
  PORTB&=0x0f;         //�����λ
  PORTB|=command&0xf0; //д����λ
  LCD_en_write();
}

void LCD_write_data(uchar data) //д����
{
 //����Ϊ��4λ��д��
  delay_nus(16);
  PORTA|=LCD_RS;       //RS=1
  PORTB&=0X0f;       //�����λ
  PORTB|=data&0xf0;  //д����λ
  LCD_en_write();
  data=data<<4;               //����λ�Ƶ�����λ
  PORTB&=0X0f;        //�����λ
  PORTB|=data&0xf0;   //д����λ
  LCD_en_write();
}


void LCD_set_xy( uchar x, uchar y )  //д��ַ����
{
    uchar address;
    if (y == 0) address = 0x80 + x;
    else   address = 0xc0 + x;
    LCD_write_command( address);
}
  
void LCD_write_string(uchar X,uchar Y,uchar *s) //��x=0~15,��y=0,1
{
    LCD_set_xy( X, Y ); //д��ַ    
    while (*s)  // д��ʾ�ַ�
    {
      LCD_write_data( *s );
      s ++;
    }
      
}

void LCD_write_char(uchar X,uchar Y,uchar data) //��x=0~15,��y=0,1
{
  LCD_set_xy( X, Y ); //д��ַ
  LCD_write_data( data);
  
}


