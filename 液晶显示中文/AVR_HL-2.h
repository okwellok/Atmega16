/*******************************************
  �ļ���AVR_HJ-2G.H
  ���ܣ�����һЩHJ-2G��������Ӧ�ó����õ��ĳ���
/******************************************/

#include <iom16v.h>			//�����ͺ�ͷ�ļ�
#include <macros.h>			//����"λ"����ͷ�ļ�

/******************�������ͺ궨��******************/
#define uchar unsigned char
#define uint unsigned int

/******************����ܺ�LED����******************/
#define LEDLK PA7	//LED���������ƶ�   ע�⣺�ɰ�ʹ�ã��°�HJ-2G ����Ҫʹ��



#define TRUE 1
#define FALSE 0
#define ALLLED 0XFF

//LED�����ܿ��غ���

void LEDON(void)   //��LED�ܿ���
{
         DDRA=0xff;                 //���ڴ�LED����
	// PORTA=0xfb;                //��LED������ PA2������͵�ƽ0���������ܿ���
}
void LEDOFF(void)  //�ر�LED�ܿ���
{
         DDRA|=BIT(PA7);                 //���ڴ�LED����
	 PORTA&=BIT(PA7);               //�ر�LED������ PA7������͵�ƽ0���ر�LED
}

//����ܿ��غ���

void SEGOFF(void)//��������ʾ�ܺ��� �����Լ���������ʾ��ʲô����,����û��ѧ�������ģ�飬����������ʱ��Ҫ��
{

   DDRB=0xff;			//PB������Ϊ���״̬
   PORTB=0xff;		   //����ģ��
	
    PORTC&=BIT(PC6);
    PORTD&=BIT(PD5);
    PORTD&=BIT(PD4);
    PORTC&=BIT(PC7);
}


/*******************************************
��������: Delayus
��    ��: ��ʱָ��΢�루8M����
��    ��: US--��ʱ��΢����(��Լ�����Ǻܾ�ȷ��MSԽ��Խ׼ȷ)
����ֵ  : ��
/********************************************/
void Delayus(uint US)		  
{
 uint i;
 US=US*5/4;		  	 //5/4����8MHz�����£�ͨ��������淴��ʵ��õ�����ֵ
 for( i=0;i<US;i++); 
}
/*******************************************
��������: Delayms
��    ��: ��ʱָ�����루8M����
��    ��: MS--��ʱ�ĺ�����
����ֵ  : ��
/********************************************/
void Delayms(uint MS)		  
{
 uint i,j;
 for( i=0;i<MS;i++)
 for(j=0;j<1141;j++);	//1141����8MHz�����£�ͨ��������淴��ʵ��õ�����ֵ
}
/*******************************************
��������: Board_init
��    ��: ��ʼ��ʵ��壬�ر�ȫ������
��    ��: ��
����ֵ  : ��
/********************************************/
void Board_init(void)
{
	DDRA=0xFF;	//���ĸ�IO��ȫ������Ϊ���
	DDRB=0xFF;
	DDRC=0xFF;
	DDRD=0xFF;

	SPCR=0x00;	//��ԭSPI�ڣ�ʹ��Ϊ�����˿�	

	PORTA|=BIT(PA3);//(BEEP)�رշ�����
	PORTC&=~BIT(PC6);	  //(RELAY)��ʼ���̵���Ϊ��������״̬	
	//PORTA&=~BIT(PA1);	//�ر�SPI����DA
	PORTB=0xFF;	//�ر�LED
	//PORTA|=BIT(LEDLK);	//�������ݣ�ʹLEDϨ��
 	//Delayus(5);		
 	//PORTA&=~BIT(LEDLK);
	
	//PORTB=0x00;	   //�����ѡ
// 	PORTA|=BIT(SEGLK);		  
 	//Delayus(50);			  
// 	PORTA&=~BIT(SEGLK);	    
 	
 	//PORTB=0xFF;	   //���λѡ
 	//PORTA|=BIT(BITLK);		   
 	//Delayus(50);				   
// 	PORTA&=~BIT(BITLK);	   
	
	//PORTD=0xFF;
	//PORTA|=BIT(PA7);
	//Delayus(50);
	//PORTA&=~BIT(PA7);

	
}
/******************1602Һ������������******************/
#define LCDa_CTRL	PORTA	//1602���ƶ˿ڶ���
#define LCDa_CTRL_DDR	DDRA	//���ƶ˿ڷ���Ĵ�������
#define LCDa_RS	       	PA4	//����������������
#define LCDa_RW		PA5
#define LCDa_E	       	PA6

#define LCDa_L1		0x80	//��һ�еĵ�ַ��0x80+addr ,addrΪ����
#define LCDa_L2		0xC0	//�ڶ��еĵ�ַ��0x80+0x40+addr

#define LCDa_CGRAM_ADDR	0x40	//CGRAM�Ŀ�ʼ��ַ
#define LCDa_CGMAX 	64	//CGRAM�洢������ֽ���

#define LCDa_SET_RS		LCDa_CTRL|=BIT(LCDa_RS)	//�������ƹܽŵĿ��Ʋ���
#define LCDa_SET_RW 		LCDa_CTRL|=BIT(LCDa_RW)
#define LCDa_SET_E  		LCDa_CTRL|=BIT(LCDa_E)
#define LCDa_CLR_RS 		LCDa_CTRL&=~BIT(LCDa_RS)
#define LCDa_CLR_RW 		LCDa_CTRL&=~BIT(LCDa_RW)
#define LCDa_CLR_E  		LCDa_CTRL&=~BIT(LCDa_E)

#define LCDa_DO		PORTB	//����������߶˿ڶ���
#define LCDa_DI		PINB	//�����������߶˿ڶ���
#define LCDa_DATA_DDR	DDRB	//�������߷���Ĵ�������

#define LCDa_FUNCTION	0x38   	// Һ��ģʽΪ8λ��2�У�5*8�ַ�

#define iDat	1		//���ݱ�־
#define iCmd	0		//ָ���־

#define LCDa_CLS	0x01		// ����
#define LCDa_HOME	0x02		// ��ַ����ԭ�㣬���ı�DDRAM����
#define LCDa_ENTRY 	0x06		// �趨����ģʽ�����ӣ���Ļ���ƶ�
#define LCDa_C2L	0x10		// �������
#define LCDa_C2R	0x14		// �������
#define LCDa_D2L	0x18		// ��Ļ����
#define LCDa_D2R	0x1C		// ��Ļ����

#define LCDa_ON		0x0C		// ����ʾ
#define LCDa_OFF		0x08		// �ر���ʾ
#define LCDa_CURON		0x0E		// ��ʾ���
#define LCDa_CURFLA		0x0F		// �򿪹����˸

/******************12864Һ������������******************/
#define LCDb_CTRL	PORTA	//12864���ƶ˿ڶ���
#define LCDb_CTRL_DDR	DDRA	//���ƶ˿ڷ���Ĵ�������
#define LCDb_RS	       	PA4	//�����ĸ���������
#define LCDb_RW		PA5
#define LCDb_E	       	PA6
#define LCDb_RST	PA7


#define LCDb_L1		0x80	//��һ�еĵ�ַ
#define LCDb_L2		0x90	//�ڶ��еĵ�ַ
#define LCDb_L3		0x88	//�����еĵ�ַ
#define LCDb_L4		0x98	//�����еĵ�ַ

#define LCDb_CGRAM_ADDR	0x40	//CGRAM�Ŀ�ʼ��ַ
#define LCDb_CGMAX 	64	//CGRAM�洢������ֽ���

#define LCDb_SET_RS		LCDb_CTRL|=BIT(LCDb_RS)	//�ĸ����ƹܽŵĿ��Ʋ���
#define LCDb_SET_RW 		LCDb_CTRL|=BIT(LCDb_RW)
#define LCDb_SET_E  		LCDb_CTRL|=BIT(LCDb_E)
#define LCDb_SET_RST  		LCDb_CTRL|=BIT(LCDb_RST)
#define LCDb_CLR_RS 		LCDb_CTRL&=~BIT(LCDb_RS)
#define LCDb_CLR_RW 		LCDb_CTRL&=~BIT(LCDb_RW)
#define LCDb_CLR_E  		LCDb_CTRL&=~BIT(LCDb_E)
#define LCDb_CLR_RST 		LCDb_CTRL&=~BIT(LCDb_RST)

#define LCDb_DO		PORTB	//����������߶˿ڶ���
#define LCDb_DI		PINB	//�����������߶˿ڶ���
#define LCDb_DATA_DDR	DDRB	//�������߷���Ĵ�������

#define LCDb_FUNCTION	0x38   	// Һ��ģʽΪ8λ

#define LCDb_BASCMD	0x30		// ����ָ�
#define LCDb_CLS	0x01		// ����
#define LCDb_HOME	0x02		// ��ַ����ԭ�㣬���ı�DDRAM����
#define LCDb_ENTRY 	0x06		// �趨����ģʽ�����ӣ���Ļ���ƶ�
#define LCDb_C2L	0x10		// �������
#define LCDb_C2R	0x14		// �������
#define LCDb_D2L	0x18		// ��Ļ����
#define LCDb_D2R	0x1C		// ��Ļ����
#define LCDb_ON		0x0C		// ����ʾ
#define LCDb_OFF		0x08		// �ر���ʾ

#define LCDb_EXTCMD1	0x34		// ����ָ����رջ�ͼ��ʾ
#define LCDb_EXTCMD2	0x36		// ����ָ����򿪻�ͼ��ʾ
#define LCDb_EXTCLS	0x01		// ����
#define LCDb_REVL1	0x04		// ���Ե�1��
#define LCDb_REVL2	0x05		// ���Ե�2��
#define LCDb_REVL3	0x06		// ���Ե�3��
#define LCDb_REVL4	0x07		// ���Ե�4��

/******************��������******************/
#define KEY_DDR DDRD			//����������
#define KEY_PORTO PORTD			//�����Ͽ��������
#define KEY_PORTI PIND			//�����Ͽ����붨��
#define OUT 0xFF			//�������
#define IN  0xF0			//���볣��

/******************�����ⲿ�жϳ���******************/
#define GLOBAL 7	//ȫ���ж�λ�궨��
#define EXTINT1 7	//�ⲿ�ж�1λ�궨��
#define EXTINT0 6	//�ⲿ�ж�0λ�궨��


/******************DS18B20����******************/
#define DS18B20 PA2

/******************TWI(IIC)����******************/
#define START 0x08		//START�źŷ������״̬
#define MT_SLA_ACK 0x18		//��������ַ���ͣ�����ACK
#define MT_SLA_NOACK 0x20	//��������ַ���ͣ����Ƿ���NOACK
#define MT_DATA_ACK  0x28	//�����ѷ��ͣ�����ACK
#define MT_DATA_NOACK 0x30	//�����ѷ��ͣ�����NOACK

#define Start() (TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN))	//����START�ź�
#define Stop() (TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN))	//����STOP�ź�
#define Wait() while(!(TWCR&(1<<TWINT)))		//�ȴ���ǰ�������
#define TestACK() (TWSR&0xF8)				//ȡ��״̬��
#define SetACK() (TWCR|=(1<<TWEA))			//����ACK
#define Writebyte(twi_d) {TWDR=(twi_d);TWCR=(1<<TWINT)|(1<<TWEN);}	//����һ���ֽڣ�twi_dΪд������ݣ�

/******************���������ֳ���******************/
#define BEEP     PA3
//      ��ʱֵ=65536-8000000/8/2/Ƶ��  
//      ����     ��ʱֵ       Ƶ��Hz
#define DO_L     63627       //262
#define DOA_L    63731       //277
#define RE_L     63835       //294
#define REA_L    63928       //311
#define MI_L     64021       //330 
#define FA_L     64103       //349 
#define FAA_L    64185       //370
#define SO_L     64270       //392
#define SOA_L    64331       //415 
#define LA_L     64400       //440
#define LAA_L    64463       //466
#define TI_L     64524       //494 
#define DO       64580       //523
#define DOA      64633       //554
#define RE       64684       //587 
#define REA      64732       //622
#define MI       64777       //659 
#define FA       64820       //698 
#define FAA      64860       //740
#define SO       64898       //784 
#define SOA      64934       //831
#define LA       64968       //880  
#define LAA      65000       //932
#define TI       65030       //988                                               
#define DO_H     65058       //1046
#define DOA_H    65085       //1109
#define RE_H     65110       //1175
#define REA_H    65134       //1245 
#define MI_H     65157       //1318 
#define FA_H     65178       //1397
#define FAA_H    65198       //1480
#define SO_H     65217       //1568 
#define SOA_H    65235       //1661
#define LA_H     65252       //1760 
#define LAA_H    65268       //1865
#define TI_H     65283       //1976 
#define ZERO     0           //��ֹ��
//ʮ����:     0
//��ֹ��:     0
 
//ʮ����:     1     2     3     4     5     6     7     8     9     10    11     12
//����  :     1     #1    2     #2    3     4     #4    5     #5    6     #6     7
 
//ʮ����:     13    14    15    16    17    18    19    20    21    22    23     24
// ���� :     1     #1    2     #2    3     4     #4    5     #5    6     #6     7

//ʮ����:     25    26    27    28    29    30    31    32    33    34    35     36
// ���� :     1     #1    2     #2    3     4     #4    5     #5    6     #6     7

/******************�̵�������******************/
#define RELAY PC6	//�̵����ܽź궨��

/******************�첽���ڳ���******************/
#define MCLK  8000000 	//��ʱ��Ƶ�ʺ궨��

/******************RTC����******************/
#define RTC_CLK   	   PB7
#define RTC_DATA  	PB6
#define RTC_CS    	PA1
	//����
#define RD	  	0x01
#define WR	  	0x00
#define C_SEC		0x80	//��
#define C_MIN		0x82	//��
#define C_HR		0x84	//ʱ
#define C_DAY		0x86	//��
#define C_MTH		0x88	//��
#define C_WK		0x8A	//���� DATE
#define C_YR		0x8C	//��
#define C_WP		0x8E	//����(д����)
#define C_CHARGE	0x90	//������
#define C_BURST		0xBE	//ʱ�Ӷ��ֽ�
	//����
#define CLK_HALT		0x80	//ֹͣʱ�ӿ���λ    SECOND	bit7
#define CLK_START		0x00	//����ʱ��
#define M12_24			0x80	//12/24Сʱֵѡ��λ HOUR		bit7 
#define PROTECT			0x80	//д��������λ      CONTROL	bit7 
#define UPROTECT		0x00	//д��������λ      CONTROL	bit7 
	//��������Ƴ���
#define TC_D1R2			0xA5	//high 1 Diode +2K Resistors  
#define TC_D2R8			0xAB	//low  2 Diodes+8K Resistors  
#define TC_DISABLED		0x00	//Disabled(TCS<>1010 or DS=00 or RS=00)
	//RAM ����
#define C_RAMBASE		0xC0	//RAM0~RAM30<<1 ��ַ������һλ 




/* �豸������: �����豸���� */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE                    0xdc
/*****   D12 ��������������  ******/
#define CONFIG_DESCRIPTOR_LENGTH    sizeof(USB_CONFIGURATION_DESCRIPTOR) \
									+ sizeof(USB_INTERFACE_DESCRIPTOR) \
									+ (NUM_ENDPOINTS * sizeof(USB_ENDPOINT_DESCRIPTOR))
/*****   D12 �ӿ���������: ���˵�0�Ķ˵�������Ŀ  ******/
#define NUM_ENDPOINTS	4
/* �豸������: �����豸���� */
#define USB_CLASS_CODE_TEST_CLASS_DEVICE                    0xdc

/* �ӿ�������: ������� */
#define USB_SUBCLASS_CODE_TEST_CLASS_D12                    0xA0

/* �ӿ�������: Э����� */
#define USB_PROTOCOL_CODE_TEST_CLASS_D12                    0xB0
	/*******************************************************
	** USB �˵��������ṹ��: �˵�����
	********************************************************/
#define USB_ENDPOINT_TYPE_MASK                    0x03

#define USB_ENDPOINT_TYPE_CONTROL                 0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS             0x01
#define USB_ENDPOINT_TYPE_BULK                    0x02
#define USB_ENDPOINT_TYPE_INTERRUPT               0x03

/******************ͨ���Ӻ���******************/
void Delayms(uint MS);

/******************LED�Ӻ���******************/
void One_led(uchar number,uchar light);
void All_led(uchar light);
void Flow_LED(uchar MS);
void Flash_LED(uchar number,uchar MS);

/******************������Ӻ���******************/
void One_smg_display(uchar data,uchar number);
void All_smg_display(uchar *pdata);
void Cycle_smg_display(uchar *pdata);

/******************1602Һ�����Ӻ���******************/
void LCD1602_portini(void);
uchar LCD1602_readbyte(uchar DatCmd);
void LCD1602_sendbyte(uchar DatCmd, uchar dByte);
void LCD1602_sendstr(uchar *ptString);
void LCD1602_clear(void);
uchar LCD1602_readBF(void);
void LCD1602_gotoXY(uchar Row, uchar Col);
void LCD1602_initial(void);

