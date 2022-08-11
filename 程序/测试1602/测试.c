#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit E=P2^2;
sbit RW=P2^1;
sbit RS=P2^0;
void delay()    //延时函数
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
bit Busy(void)
{
	bit busy_flag = 0;
	RS = 0;
	RW = 1;
	E = 1;
	delay();
	busy_flag = (bit)(P0 & 0x80);
	E = 0;
	return busy_flag;
}
void wcmd(uchar del)
{
	while(Busy());
	RS = 0;
	RW = 0;
	E = 0;
	delay();
	P0 = del;
	delay();
	E = 1;
	delay();
	E = 0;
}
void wdata(uchar del)
{
	while(Busy());
	RS = 1;
	RW = 0;
	E = 0;
	delay();
	P0 = del;
	delay();
	E = 1;
	delay();
	E = 0;
}
void L1602_init(void)
{
	wcmd(0x38);//设置16*2显示，5*7点阵，8位数据口
	wcmd(0x0c);
	wcmd(0x06);
	wcmd(0x01);
}
void L1602_char(uchar hang,uchar lie,char sign)
{
	uchar a;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	wcmd(a);
	wdata(sign);
}
void L1602_string(uchar hang,uchar lie,uchar *p)
{
	uchar a,b=0;
	if(hang == 1) a = 0x80;
	if(hang == 2) a = 0xc0;
	a = a + lie - 1;
	while(1)
	{
		wcmd(a++);
		b++;
		if((*p == '\0')||(b==16)) break;
		wdata(*p);
		p++;
	}
}
void Main()
{
	L1602_init();
	L1602_string(1,1,"1123456789   ");
	L1602_string(2,1,"   ABCDEFGHIJ   ");
	L1602_char(2,15,'O');
	L1602_char(2,16,'K');
	while(1);
}