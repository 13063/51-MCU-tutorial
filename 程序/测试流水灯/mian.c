#include<reg52.h>
#include<intrins.h>//�����λ����
#define uint unsigned int
#define uchar unsigned char
void delay(unit);
uchar aa;
void main()
{
	aa=0xfe;//��ֵ11111110
	while(1)
	{
		P0=aa;//��һ��LED����
		delay(138);//��ʱ500ms
		aa=_crol_(aa,1);//����1λ
	}
}
void delay(uint t)
{
	uint i,j;
	for(i=t;i>0;i--)//��ʱt��
		for(j=120;j>0;j--);
}