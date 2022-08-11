#include <led.h>
#include <key.h>


void main()
{
	while(1)
	{
		if(keydown(3))
			l4=~l4;
	}	
}
void delay1s()
{
	uint i, j;
	for(i=500;i>0;i--)
		for(j=110;j>0;j--);//—” ±500ms
}