#ifndef _IIC_H
#define _IIC_H

#include "public.h"
sbit SCL=P2^5;
sbit SDA=P2^6;


void iicStart();
void iicStop();
void iicSendData(uchar dat);
bit iicAck(uchar ack);
bit iicWaitAck();
#endif