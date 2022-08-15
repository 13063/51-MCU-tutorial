#include "lcd1602.h"
#include "public.h"

bit lcdBusy()
{
	lcdata=0xff;
	RS=0;
	RW=1;
	EN=1;
	return lcdata&0x80;
}

void writeCmd(uchar cmd)
{
	while(lcdBusy());
	RS=0;
	RW=0;
	lcdata=cmd;
	EN=1;
	EN=0;
}

void lcdWriteData(uchar dat)
{
	while(lcdBusy());
	RS=1;
	RW=0;
	lcdata=dat;
	EN=1;
	//Delay1ms(2);
	EN=0;
}
void lcdInit()
{
	writeCmd(0x38);
	writeCmd(0x0c);
	writeCmd(0x06);
	writeCmd(0x01);
	
	lcdShowString(1,5,"unicorn");
	Delay1ms(100);
	lcdClear();
}

void lcdClear()
{
	writeCmd(0x01);
}

void lcdRmove(uint n)
{
	uint i;
	for(i=n;i--;i>0)
		writeCmd(0x1d);
}

void lcdLmove(uint n)
{
	uint i;
	for(i=n;i--;i>0)
		writeCmd(0x18);
}

void lcdShowChar(uint row,uint pos,uchar ch)
{
	if(row==1)
	{
		writeCmd(0x80+pos-1);
		lcdWriteData(ch);
	}
	else
	{
		writeCmd(0x80+0x40+pos-1);
		lcdWriteData(ch);
	}
}

void lcdShowString(uint row,uint pos,uchar*s)
{
	uint i;
	if(row==1)
	{
		for(i=0;s[i]!='\0';i++)
		{
			writeCmd(0x80+pos-1+i);
			lcdWriteData(s[i]);
		}	
	}
	else
	{
		for(i=0;s[i]!='\0';i++)
		{
			writeCmd(0x80+0x40+pos-1+i);
			lcdWriteData(s[i]);
		}	
	}
}

void lcdShowNum(uint row,uint pos,unsigned long num)
{
	unsigned long i,j,width,k;
	i=1;j=1;
	width=1;				//数字的位数
	if(row==1)
	{
		writeCmd(0x80+pos-1);
		while(num/(i*10)!=0)
		{
			i=i*10;
			width++;	
		}
		for(k=width;k>=1;k--)
		{
			for(i=1;i<k;i++)
				j=j*10;
			lcdWriteData((num/j)%10+'0');
			j=1;
		}			
	}
	else
	{
		writeCmd(0x80+0x40+pos-1);
		while(num/(i*10)!=0)
		{
			i=i*10;
			width++;	
		}
		for(k=width;k>=1;k--)
		{
			for(i=1;i<k;i++)
				j=j*10;
			lcdWriteData((num/j)%10+'0');
			j=1;
		}
	}
}


void lcdShow0Num(uint row,uint pos,unsigned long num,uchar w)
{
	unsigned long i,j,width,k;
	i=1;j=1;
	width=1;				//数字的位数
	if(row==1)
	{
		writeCmd(0x80+pos-1);
		while(num/(i*10)!=0)
		{
			i=i*10;
			width++;	
		}
		for(k=w;k>=1;k--)
		{
			for(i=1;i<k;i++)
				j=j*10;
			lcdWriteData((num/j)%10+'0');
			j=1;
		}			
	}
	else
	{
		writeCmd(0x80+0x40+pos-1);
		while(num/(i*10)!=0)
		{
			i=i*10;
			width++;	
		}
		for(k=w;k>=1;k--)
		{
			for(i=1;i<k;i++)
				j=j*10;
			lcdWriteData((num/j)%10+'0');
			j=1;
		}
	}
}