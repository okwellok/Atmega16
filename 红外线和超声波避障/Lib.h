uchar checksum (uchar * paddr,uchar len);
void change(uint i,uchar *p);
void hex16to8(uint i,uchar *p);

/*****************计算校验和*************************/
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

/*****************拆分成个十百千********************/
void change(uint i,uchar *p)		 //显示处理
{p[3]=i%10+48;//个
 p[2]=i/10%10+48;//十
 p[1]=i/100%10+48;//百
 p[0]=i/1000%10+48;//千
}
 
/*******************拆分16位数据，分存成两个8位***********/
void hex16to8(uint i,uchar *p)   
{
   p[1]=i>>8;
   p[0]=(uchar)i;
}
