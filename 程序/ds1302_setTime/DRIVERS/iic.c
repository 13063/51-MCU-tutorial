#include "iic.h"

void iicStart()
{
	SCL=1;
	SDA=1;
	Delay5us();
	SDA=0;
	Delay5us();
}

void iicStop()
{
	SCL=1;
	SDA=0;
	Delay5us();
	SDA=1;
	Delay5us();
}

void iicSendData(uchar dat)
{
	uint i;
	SCL=0;
	for(i=0;i<8;i++)
	{
		SDA=dat&0x80?1:0;
		SCL=1;
		_nop_();
		SCL=0;
		dat=dat<<1;
	}
}
bit iicWaitAck()
{
	uchar ack=0;
	SCL=1;
	Delay5us();
	if(SDA)
	{
		ack=1;
		iicStop();
	}
	else
	{
		ack=0;
		SCL=0;
		Delay5us();
	}
	return ack;
}
bit iicAck(uchar ack)
{
	SCL=0;
	Delay5us();
	if(ack)
		SDA=1;
	else
		SDA=0;
	Delay5us();
	SCL=1;
	Delay5us();
	SCL=0;
}
