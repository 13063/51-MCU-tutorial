#include "key.h"
#include "public.h"

uchar keydown(uchar n)
{
	switch (n)
	{
		case 1: 
		if(K1==0)
		{
			Delay1ms(20);
			if(K1==0)
				return 1;
			return 0;
		}
		return 0;
		case 2: 
		if(K2==0)
		{
			Delay1ms(20);
			if(K2==0)
				return 1;
			return 0;
		}
		return 0;
		case 3: 
		if(K3==0)
		{
			Delay1ms(20);
			if(K3==0)
				return 1;
			return 0;
		}
		return 0;
		case 4: 
		if(K4==0)
		{
			Delay1ms(20);
			if(K4==0)
				return 1;
			return 0;
		}
		return 0;
		default:
			return 0;
	}
}