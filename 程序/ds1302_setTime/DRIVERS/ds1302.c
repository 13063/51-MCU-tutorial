#include <ds1302.h>

void ds1302Init()
{
	CE=0;
	SCL=0;
}

void ds1302Write(uchar cmd,uchar dat)
{
	uint i=0;
	CE=1;
	for(i=0;i<8;i++)
	{
		SDA=cmd&(0x01<<i);
		SCL=1;
		SCL=0;
	}
	for(i=0;i<8;i++)
	{
		SDA=dat&(0x01<<i);
		SCL=1;
		SCL=0;
	}
	CE=0;
}
uchar ds1302Read(uchar cmd)
{
	uchar i=0,dat=0x00;
	CE=1;
	cmd|=0x01;
	for(i=0;i<8;i++)
	{
		SDA=cmd&(0x01<<i);//把Command中的数据从低位，一位一位的取出来给到IO口
		SCL=0;
		SCL=1;
	}
	for(i=0;i<8;i++)
	{
		SCL=1;
		SCL=0;
		if(SDA)
		{
			dat|=(0x01<<i);
		}
	}
	CE=0;
	SDA=0;
	return dat;
}


 

void ds1302SetTime(struct RTCtime setTime)
{
	ds1302Write(DS1302_WP,0x00);//解除芯片写保护
	ds1302Write(DS1302_YEAR,setTime.year/10*16+setTime.year%10);
	ds1302Write(DS1302_MONTH,setTime.mon/10*16+setTime.mon%10);
	ds1302Write(DS1302_DATE,setTime.date/10*16+setTime.date%10);
	ds1302Write(DS1302_HOUR,setTime.hour/10*16+setTime.hour%10);
	ds1302Write(DS1302_MINUTE,setTime.min/10*16+setTime.min%10);
	ds1302Write(DS1302_SECOND,setTime.sec/10*16+setTime.sec%10);
	ds1302Write(DS1302_DAY,setTime.day/10*16+setTime.day%10);
	ds1302Write(DS1302_WP,0x80);//打开芯片写保护
}


struct RTCtime ds1302ReadTime()
{
	struct RTCtime readTime;
	uchar Temp;
	Temp=ds1302Read(DS1302_YEAR+1);
	readTime.year=Temp/16*10+Temp%16;//从芯片中读出的是BCD码，所以要把BCD码转为十进制
	
	Temp=ds1302Read(DS1302_MONTH+1);
	readTime.mon=Temp/16*10+Temp%16;
	
	Temp=ds1302Read(DS1302_DATE+1);
	readTime.date=Temp/16*10+Temp%16;
	
	Temp=ds1302Read(DS1302_HOUR+1);
	readTime.hour=Temp/16*10+Temp%16;
	
	Temp=ds1302Read(DS1302_MINUTE+1);
	readTime.min=Temp/16*10+Temp%16;
	
	Temp=ds1302Read(DS1302_SECOND+1);
	readTime.sec=Temp/16*10+Temp%16;
	
	Temp=ds1302Read(DS1302_DAY+1);
	readTime.day=Temp/16*10+Temp%16;
	return readTime;
}
