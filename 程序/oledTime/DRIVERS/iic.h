#ifndef _IIC_H
#define _IIC_H

#include "public.h"
sbit iicSCL=P2^4;
sbit iicSDA=P2^5;


void iicStart();
void iicStop();
void iicSendData(uchar dat);
void iicWaitAck();
#endif