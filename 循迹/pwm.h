#ifndef _PWM_H_
#define _PWM_H_
#define uchar unsigned char 
#define uint unsigned int

//IOC�ڵ�4��5�ܽţ��ֱ��Ӧ�������ϵ�PWMA��PWMB



//�����
uchar DUTY1;//����PWM����ռ�ձ�
uchar DUTY2;//����PWM����ռ�ձ�
uchar CYCLE=100;//��ռ�ձ�
uint count;//�ۼӱ���


void timer0_init(void)
{
	TCCR0 = 0x00; //ֹͣ
	TCNT0 = 0xF6; //���ü���,10us
	OCR0  = 0x0A;  //���ñȽ�ģʽ
	TCCR0 = 0x02; //��ʼ
}

#pragma interrupt_handler timer0_ovf_isr:10 //timer0 ���
void timer0_ovf_isr(void)
{
	TCNT0=0xF6;
	count++;

	if(count<=DUTY1)
	{
		PORTC|=(1<<PC4);//�ߵ�ƽʱ�����
	}
else
	{
		PORTC&=~(1<<PC4);//�͵�ƽʱ�����
	}

	if(count<=DUTY2)
	{
		PORTC|=(1<<PC5);
	}
else
	{
		PORTC&=~(1<<PC5);
	}

	if(count==CYCLE)//�����������Զ���0
	{
		count=0;
	}
}

#endif
