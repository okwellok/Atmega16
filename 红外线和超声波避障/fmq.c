#include <iom16v.h>
#include <macros.h>

void delay_fmq_ms(unsigned int k)
{
  unsigned int i,j;
  for(i=0;i<k;i++)
  {
    for(j=0;j<1140;j++);
  }
}
void fmq_init(void)
 {
 //���÷�����
  DDRA  |=BIT(3); //PA3���������Ϊ1
  PORTA &=~BIT(3); //PA3����Ϊ�͵�ƽ0
  
  }


void buzz(void)
{ PORTA  |=BIT(3); //�ߵ�ƽ��
  delay_fmq_ms(1500);
  PORTA &=~BIT(3); //�͵�ƽ����
  delay_fmq_ms(50);
  
}
