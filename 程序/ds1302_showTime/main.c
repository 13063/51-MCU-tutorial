#include <public.H>
#include "lcd1602.h"
#include "ds1302.h"

struct RTCtime time;


void main()
{
	lcdInit();
	ds1302Init();
	//ds1302SetTime();
	//ds1302ReadTime();
	
	//DS1302_Time[0]=22;
	
	while(1)
	{
		time=ds1302ReadTime();
		lcdShowNum(1,1,time.year+2000);//显示年
		
		lcdShowNum(1,6,time.mon);//显示月
		lcdShowNum(1,9,time.date);//显示日
		
		
		lcdShowNum(2,1,time.hour);//显示时
		lcdShowNum(2,4,time.min);//显示分
		
		lcdShow0Num(2,7,time.sec,2);//显示秒
		//lcdShowChar(2,8,time.sec%10+'0');//显示秒

		//Delay1ms(200);
	}
}