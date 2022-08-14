#include "public.h"

void Delay1ms(uint c)   //Îó²î 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}	
}

void Delay5us()		//@11.0592MHz
{
}

