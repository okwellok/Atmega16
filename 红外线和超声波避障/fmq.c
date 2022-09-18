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
 //配置蜂鸣器
  DDRA  |=BIT(3); //PA3口设置输出为1
  PORTA &=~BIT(3); //PA3设置为低电平0
  
  }


void buzz(void)
{ PORTA  |=BIT(3); //高电平响
  delay_fmq_ms(1500);
  PORTA &=~BIT(3); //低电平不响
  delay_fmq_ms(50);
  
}
