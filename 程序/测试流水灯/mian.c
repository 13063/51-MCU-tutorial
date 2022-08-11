#include<reg52.h>
#include<intrins.h>//添加移位函数
#define uint unsigned int
#define uchar unsigned char
void delay(unit);
uchar aa;
void main()
{
	aa=0xfe;//初值11111110
	while(1)
	{
		P0=aa;//第一个LED点亮
		delay(138);//延时500ms
		aa=_crol_(aa,1);//左移1位
	}
}
void delay(uint t)
{
	uint i,j;
	for(i=t;i>0;i--)//延时t秒
		for(j=120;j>0;j--);
}