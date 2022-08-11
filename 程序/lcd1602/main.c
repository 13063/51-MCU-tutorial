#include "lcd1602.h"
#include "key.h"
#include "led.h"
void Init_INT0()
{
	IT0=1;//�����ⲿ�ж�0;�½��ش��� 
	EX0=1;//�����ⲿ�ж�0; 
	EA=1;//�����ж��ܿ��� 
} 

void Init_INT1()
{
	IT1=1;//�����ⲿ�ж�1;�½��ش��� 
	EX1=1;//�����ⲿ�ж�1; 
	EA=1;//�����ж��ܿ��� 
} 


 
void main()
{
	//uint i,j;
	lcdInit();
	//lcdShowChar(2,2,'b');
	lcdShowString(1,1,"unicorn");
	
	lcdShowString(2,1,"tankionline tankionline");
	lcdShowNum(1,10,2456458);
	lcdShowNum(2,28,24568);
	//Init_INT0();
	//Init_INT1();
	while(1)
	{
		if(keydown(1))
			lcdRmove(1);
		else if(keydown(2))
			lcdLmove(1);
		else if(keydown(3))
			lcdClear();
		else if(keydown(4))
			lcdInit();
	}
	
}

void RSI_INT0() interrupt 0
{
	//P0=~P0;//��������P0�ڵ�LEDȡ�� 
	lcdRmove(1);
}
void RSI_INT1() interrupt 2
{
	//P0=~P0;//��������P0�ڵ�LEDȡ�� 
	//lcdLmove(1);
	lcdClear();
}