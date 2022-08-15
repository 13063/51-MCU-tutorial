#ifndef _KEY_H
#define _KEY_H
#include "public.h"


sbit K1=P3^2;
sbit K2=P3^3;
sbit K3=P4^3;
sbit K4=P4^2;

uchar keydown(uchar n);
uchar key();
#endif