#ifndef _DS1302_H
#define _DS1302_h

#include "public.h"

#define DS1302_SECOND  0x80
#define DS1302_MINUTE  0x82
#define DS1302_HOUR    0x84
#define DS1302_DATE    0x86
#define DS1302_MONTH   0x88
#define DS1302_DAY     0x8A
#define DS1302_YEAR    0x8C
#define DS1302_WP      0x8E


struct RTCtime
{
	char year;char mon;char date;
	char hour;char min;char sec;
	char day;
};


sbit CE=P2^7;
sbit SCL=P2^5;
sbit SDA=P2^6;

void ds1302Init();
void ds1302SetTime(struct RTCtime time);
struct RTCtime ds1302ReadTime(void);
#endif