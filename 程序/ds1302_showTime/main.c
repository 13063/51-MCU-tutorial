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
		lcdShowNum(1,1,time.year+2000);//��ʾ��
		
		lcdShowNum(1,6,time.mon);//��ʾ��
		lcdShowNum(1,9,time.date);//��ʾ��
		
		
		lcdShowNum(2,1,time.hour);//��ʾʱ
		lcdShowNum(2,4,time.min);//��ʾ��
		
		lcdShow0Num(2,7,time.sec,2);//��ʾ��
		//lcdShowChar(2,8,time.sec%10+'0');//��ʾ��

		//Delay1ms(200);
	}
}