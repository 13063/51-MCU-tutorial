#ifndef _PUBLIC_H
#define _PUBLIC_H
#include <STC89C5xRC.H>
#include "intrins.h"
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

void Delay1ms(uint c);
void Delay5us();
#endif