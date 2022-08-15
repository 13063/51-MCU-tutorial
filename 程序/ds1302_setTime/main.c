#include <public.H>
#include "lcd1602.h"
#include "ds1302.h"
#include "key.h"


uchar k,MODE,TimeSetSelect,TimeSetFlashFlag;

struct RTCtime time;
struct RTCtime* p;
void  setTime();
void showTime();
void Timer0Init(void);
void Timer0_Routine();
uchar i;
uchar *pti;    									//指向存储变量的指针
uchar *ptime;									//指向全局变量的指针
struct RTCtime ti;								//存储变量用于修改


void showTime()
{
	ti=ds1302ReadTime();
	
	
	lcdShow0Num(1,1,ti.year,2);					//显示年
	lcdShow0Num(1,4,ti.mon,2);					//显示月
	lcdShow0Num(1,7,ti.date,2);					//显示日
	
	lcdShow0Num(2,1,ti.hour,2);					//显示时
	lcdShow0Num(2,4,ti.min,2);					//显示分
	lcdShow0Num(2,7,ti.sec,2);					//显示秒
	
}

///////修改全局变量time////////
void setTime()			
{
	uchar hour=time.hour;
	if(k==2)										//按键2按下
	{
		TimeSetSelect++;							//设置选择位加1
		TimeSetSelect%=6;							//越界清零
	}
	if(k==3)										//按键3按下
	{
		
		(*(ptime+TimeSetSelect))++;
		if(time.year>99){time.year=0;}				//年越界判断
		if(time.mon>12){time.mon=1;}				//月越界判断
		if( time.mon==1 || time.mon==3 || time.mon==5 || time.mon==7 || 
			time.mon==8 || time.mon==10 || time.mon==12)//日越界判断
		{
			if(time.date>31){time.date=1;}			//大月
		}
		else if(time.mon==4 || time.mon==6 || time.mon==9 || time.mon==11)
		{
			if(time.date>30){time.date=1;}			//小月
		}
		else if(time.mon==2)
		{
			if(time.year%4==0)
			{
				if(time.date>29){time.date=1;}		//闰年2月
			}
			else
			{
				if(time.date>28){time.date=1;}		//平年2月
			}
		}
		
		if(time.hour>23){time.hour=0;}				//时越界判断
		if(time.min>59){time.min=0;}				//分越界判断
		if(time.sec>59){time.sec=0;}				//秒越界判断
	}
	if(k==4)//按键4按下
	{
		(*(ptime+TimeSetSelect))--;					//时间设置位数值减1
		if(time.year<0){time.year=99;}				//年越界判断
		if(time.mon<1){time.mon=12;}				//月越界判断
		if( time.mon==1 || time.mon==3 || time.mon==5 || time.mon==7 || 
			time.mon==8 || time.mon==10 || time.mon==12)//日越界判断
		{
			if(time.date<1){time.date=31;}			//大月
			if(time.date>31){time.date=1;}
		}
		else if(time.mon==4 || time.mon==6 || time.mon==9 || time.mon==11)
		{
			if(time.date<1){time.date=30;}			//小月
			if(time.date>30){time.date=1;}
		}
		else if(time.mon==2)
		{
			if(time.year%4==0)
			{
				if(time.date<1){time.date=29;}		//闰年2月
				if(time.date>29){time.date=1;}
			}
			else
			{
				if(time.date<1){time.date=28;}		//平年2月
				if(time.date>28){time.date=1;}
			}
		}
	}
	if(time.hour<0){time.hour=23;}					//时越界判断
	if(time.min<0){time.min=59;}					//分越界判断
	if(time.sec<0){time.sec=59;}					//秒越界判断

	//更新显示，根据TimeSetSelect和TimeSetFlashFlag判断可完成闪烁功能
	if(TimeSetSelect==0 && TimeSetFlashFlag==1){lcdShowString(1,1,"  ");}
	else {lcdShow0Num(1,1,time.year,2);}
	if(TimeSetSelect==1 && TimeSetFlashFlag==1){lcdShowString(1,4,"  ");}
	else {lcdShow0Num(1,4,time.mon,2);}
	if(TimeSetSelect==2 && TimeSetFlashFlag==1){lcdShowString(1,7,"  ");}
	else {lcdShow0Num(1,7,time.date,2);}
	if(TimeSetSelect==3 && TimeSetFlashFlag==1){lcdShowString(2,1,"  ");}
	else {lcdShow0Num(2,1,time.hour,2);}
	if(TimeSetSelect==4 && TimeSetFlashFlag==1){lcdShowString(2,4,"  ");}
	else {lcdShow0Num(2,4,time.min,2);}
	if(TimeSetSelect==5 && TimeSetFlashFlag==1){lcdShowString(2,7,"  ");}
	else {lcdShow0Num(2,7,time.sec,2);}
}





void main()
{
	lcdInit();						//初始化lcd
	ds1302Init();					//初始化1302
	Timer0Init();					//初始化定时器

	ti=ds1302ReadTime();			//读取RTC时钟给ti结构体
		
	ptime=&(time.year);
	pti=&(ti.year);
	
	for(i=0;i<7;i++)
	{
		*(ptime+i)=*(pti+i);		//将读到的RTC时间给time结构体，相当于初始化time
	}
	
	lcdShowString(1,1,"  -  -  ");	//静态字符初始化显示
	lcdShowString(2,1,"  :  :  ");
	while(1)
	{
		k=key();
		if(k==1)
		{
			if(MODE==0)
			{
				MODE=1;
				TimeSetSelect=0;
			}						//功能切换
			else if(MODE==1)
			{
				MODE=0;
				ds1302SetTime(time);
			}
		}
		switch(MODE)				//根据不同的功能执行不同的函数
		{
			case 0:showTime();break;
			case 1:setTime();break;
		}
	}
}

void Timer0Init(void)
{
	TMOD &= 0xF0;					//设置定时器模式
	TMOD |= 0x01;					//设置定时器模式
	TL0 = 0x18;						//设置定时初值
	TH0 = 0xFC;						//设置定时初值
	TF0 = 0;						//清除TF0标志
	TR0 = 1;						//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;						//设置定时初值
	TH0 = 0xFC;						//设置定时初值
	T0Count++;
	if(T0Count>=500)				//每500ms进入一次
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;//闪烁标志位取反
	}
}