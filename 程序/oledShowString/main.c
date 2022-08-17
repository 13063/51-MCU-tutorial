#include <STC89C5xRC.H>
#include <public.H>
#include <ssd1306.H>

void main()
{
	SSD1306_init();
	OLED_Clear();
	while(1)
	{
//		OLED_ShowNum(1,6,123,3,16);
		OLED_ShowString(2,0,"unicorn",16);
		OLED_ShowString(2,2,"unicorn",16);
		OLED_ShowString(2,4,"unicorn",16);
		OLED_ShowString(2,6,"unicorn",16);
	}
	
}