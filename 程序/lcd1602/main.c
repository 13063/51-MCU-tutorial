#include "lcd1602.h"
#include "key.h"
#include "led.h"
void Init_INT0()
{
	IT0=1;//设置外部中断0;下降沿触发 
	EX0=1;//开启外部中断0; 
	EA=1;//开启中断总开关 
} 

void Init_INT1()
{
	IT1=1;//设置外部中断1;下降沿触发 
	EX1=1;//开启外部中断1; 
	EA=1;//开启中断总开关 
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
	//P0=~P0;//当触发中P0口的LED取反 
	lcdRmove(1);
}
void RSI_INT1() interrupt 2
{
	//P0=~P0;//当触发中P0口的LED取反 
	//lcdLmove(1);
	lcdClear();
}