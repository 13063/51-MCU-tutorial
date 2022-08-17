#include "iic.h"

void iicStart()
{
	iicSCL=1;
	iicSDA=1;
	//Delay5us();
	iicSDA=0;
	//Delay5us();
}

void iicStop()
{
	iicSCL=1;
	iicSDA=0;
	//Delay5us();
	iicSDA=1;
	//Delay5us();
}

void iicSendData(uchar dat)
{
	uint i;
	iicSCL=0;
	for(i=0;i<8;i++)
	{
		iicSDA=dat&0x80?1:0;
		iicSCL=1;
		_nop_();
		iicSCL=0;
		dat=dat<<1;
	}
}
void iicWaitAck()
{
	iicSCL=1;
	iicSCL=0;
}

