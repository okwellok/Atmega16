/* �÷���
   LCD_init();
   LCD_write_string(��,��,"�ַ���");
   LCD_write_char(��,��,'�ַ�'); 
 ---------------------------------------------------------------
������AVR��LCD������Ϣ
PA4 ->RS
PA5	->RW
PA6 ->EN
PB	->D4-D7
Ҫʹ�ñ��������ı�����������Ϣ����
-----------------------------------------------------------------*/
#define LCD_EN_PORT    PORTA   //����2��Ҫ��Ϊͬһ����
#define LCD_EN_DDR     DDRA
#define LCD_RS_PORT    PORTA   //����2��Ҫ��Ϊͬһ����
#define LCD_RS_DDR     DDRA
#define LCD_RW_PORT    PORTA   //����2��Ҫ��Ϊͬһ����
#define LCD_RW_DDR     DDRA
#define LCD_DATA_PORT  PORTB   //����3��Ҫ��Ϊͬһ����
#define LCD_DATA_DDR   DDRB   //Ĭ����������߱���ʹ�ø���λ�˿�,���������ע���޸�
#define LCD_DATA_PIN   PINB
#define LCD_RS         (1<<PA4) //       out
#define LCD_EN         (1<<PA6) //       out
#define LCD_RW         (1<<PA5) //      out  ����ֱ�ӽӵ�
#define LCD_DATA       (1<<PB4)|(1<<PB5)|(1<<PB6)|(1<<PB7)//((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|
/*--------------------------------------------------------------------------------------------------
����˵��
--------------------------------------------------------------------------------------------------*/
void LCD_init(void);
void LCD_en_write(void);
void LCD_write_command(uchar command) ;
void LCD_write_data(uchar data);
void LCD_set_xy (uchar x, uchar y);
void LCD_write_string(uchar X,uchar Y,uchar *s);
void LCD_write_char(uchar X,uchar Y,uchar data);

//-----------------------------------------------------------------------------------------

void LCD_init(void)         //Һ����ʼ��
{
  LCD_DATA_DDR|=LCD_DATA;   //���ݿڷ���Ϊ���
  LCD_EN_DDR|=LCD_EN;       //����EN����Ϊ���
  LCD_RS_DDR|=LCD_RS;       //����RS����Ϊ���
  LCD_RW_DDR|=LCD_RW;       //����RW����Ϊ���
  LCD_RW_PORT&=~LCD_RW;        //RW=0
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
  LCD_RS_PORT&=~LCD_RS;        //RS=0
  LCD_DATA_PORT&=0X0f;         //�����λ
  LCD_DATA_PORT|=command&0xf0; //д����λ
  LCD_en_write();
  command=command<<4;          //����λ�Ƶ�����λ
  LCD_DATA_PORT&=0x0f;         //�����λ
  LCD_DATA_PORT|=command&0xf0; //д����λ
  LCD_en_write();
/*
   //������8��д��
  delay_nus(16);
  LCD_RS_PORT&=~LCD_RS;        //RS=0
  LCD_DATA_PORT=command;
  LCD_en_write();

  
 

  //����Ϊ����λ��д��
  delay_nus(16);
  LCD_RS_PORT&=~LCD_RS;        //RS=0
  LCD_DATA_PORT&=0xf0;         //�����λ
  LCD_DATA_PORT|=(command>>4)&0x0f; //д����λ
  LCD_en_write();
  LCD_DATA_PORT&=0xf0;         //�����λ
  LCD_DATA_PORT|=command&0x0f; //д����λ
  LCD_en_write(); 
*/
  
}

void LCD_write_data(uchar data) //д����   ��rs�ߵ�ƽ��Ϊ����
{
 //����Ϊ��4λ��д��
  delay_nus(16);
  LCD_RS_PORT|=LCD_RS;       //RS=1
  LCD_DATA_PORT&=0X0f;       //�����λ
  LCD_DATA_PORT|=data&0xf0;  //д����λ
  LCD_en_write();
  data=data<<4;               //����λ�Ƶ�����λ
  LCD_DATA_PORT&=0X0f;        //�����λ
  LCD_DATA_PORT|=data&0xf0;   //д����λ
  LCD_en_write();
/*
  //������8��д��
  delay_nus(16);
  LCD_RS_PORT|=LCD_RS;       //RS=1
  LCD_DATA_PORT=data;
  LCD_en_write();
  
 
  
/*
  //����Ϊ����λ��д�� 
  delay_nus(16);
  LCD_RS_PORT|=LCD_RS;       //RS=1
  LCD_DATA_PORT&=0Xf0;       //�����λ
  LCD_DATA_PORT|=(data>>4)&0x0f;  //д����λ
  LCD_en_write();
 
  LCD_DATA_PORT&=0Xf0;        //�����λ
  LCD_DATA_PORT|=data&0x0f;   //д����λ
  LCD_en_write();
*/
  
}
//1602 F=2^4 �ֱ���0F,F0����״����������λ�Ϳ�����

void LCD_set_xy( uchar x, uchar y )  //д��ַ��������rs�ߵ�ƽ��Ϊ����
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


