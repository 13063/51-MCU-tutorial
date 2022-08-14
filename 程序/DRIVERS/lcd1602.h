#ifndef _lcd1602_H
#define _lcd1602_H

#include "public.h"


sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
#define lcdata P0

void lcdWriteData(uchar dat);
void writeCmd(uchar cmd);
void lcdInit();
void lcdRmove(uint n);
void lcdLmove(uint n);
void lcdClear();
void lcdShowChar(uint row,uint pos,uchar ch);
void lcdShowString(uint row,uint pos,uchar*s);
void lcdShowNum(uint row,uint pos,unsigned long num);
void lcdShow0Num(uint row,uint pos,unsigned long num,uchar w);
#endif