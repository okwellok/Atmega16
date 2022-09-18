uchar checksum (uchar * paddr,uchar len);
void change(uint i,uchar *p);
void hex16to8(uint i,uchar *p);

/*****************����У���*************************/
uchar checksum (uchar * paddr,uchar len)
{
	uchar i; 
	uchar sum =0;
	for (i=0;i<len;i++)
	{
		sum += * (paddr+i);
	}
	return (sum);
}

/*****************��ֳɸ�ʮ��ǧ********************/
void change(uint i,uchar *p)		 //��ʾ����
{p[3]=i%10+48;//��
 p[2]=i/10%10+48;//ʮ
 p[1]=i/100%10+48;//��
 p[0]=i/1000%10+48;//ǧ
}
 
/*******************���16λ���ݣ��ִ������8λ***********/
void hex16to8(uint i,uchar *p)   
{
   p[1]=i>>8;
   p[0]=(uchar)i;
}
