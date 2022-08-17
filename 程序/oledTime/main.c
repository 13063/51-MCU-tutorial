#include <ds1302.H>
#include <public.H>
#include <key.H>
#include <ssd1306.H>

uchar k,TimeSetSelect,TimeSetFlashFlag;
uchar MODE=0;
struct RTCtime time;
struct RTCtime* p;
void  setTime();
void showTime();
void Timer0Init(void);
void Timer0_Routine();
uchar i;
uchar *pti;    									//ָ��洢������ָ��
uchar *ptime;									//ָ��ȫ�ֱ�����ָ��
struct RTCtime ti;								//�洢���������޸�


void showTime()
{
	
	ti=ds1302ReadTime();
	
	//�ֿ�8����16
	OLED_ShowNum(0,0,ti.hour,2,16);					//��ʾʱ
	OLED_ShowChar(16,0,':',16);
	OLED_ShowNum(24,0,ti.min,2,16);					//��ʾ��
	OLED_ShowChar(40,0,':',16);
	OLED_ShowNum(48,0,ti.sec,2,16);					//��ʾ��
	
	OLED_ShowNum(0,2,ti.year,2,16);					//��ʾ��
	OLED_ShowChar(16,2,'-',16);
	OLED_ShowNum(24,2,ti.mon,2,16);					//��ʾ��
	OLED_ShowChar(40,2,'-',16);
	OLED_ShowNum(48,2,ti.date,2,16);				//��ʾ��
}

///////�޸�ȫ�ֱ���time////////
void setTime()			
{
	uchar hour=time.hour;
	
	
	OLED_ShowChar(16,0,':',16);
	OLED_ShowChar(40,0,':',16);
	OLED_ShowChar(16,2,'-',16);
	OLED_ShowChar(40,2,'-',16);
	if(k==2)										//����2����
	{
		TimeSetSelect++;							//����ѡ��λ��1
		TimeSetSelect%=6;							//Խ������
	}
	if(k==3)										//����3����
	{
		(*(ptime+TimeSetSelect))++;
		if(time.year>99){time.year=0;}				//��Խ���ж�
		if(time.mon>12){time.mon=1;}				//��Խ���ж�
		if( time.mon==1 || time.mon==3 || time.mon==5 || time.mon==7 || 
			time.mon==8 || time.mon==10 || time.mon==12)//��Խ���ж�
		{
			if(time.date>31){time.date=1;}			//����
		}
		else if(time.mon==4 || time.mon==6 || time.mon==9 || time.mon==11)
		{
			if(time.date>30){time.date=1;}			//С��
		}
		else if(time.mon==2)
		{
			if(time.year%4==0)
			{
				if(time.date>29){time.date=1;}		//����2��
			}
			else
			{
				if(time.date>28){time.date=1;}		//ƽ��2��
			}
		}
		
		if(time.hour>23){time.hour=0;}				//ʱԽ���ж�
		if(time.min>59){time.min=0;}				//��Խ���ж�
		if(time.sec>59){time.sec=0;}				//��Խ���ж�
	}
	if(k==4)//����4����
	{
		(*(ptime+TimeSetSelect))--;					//ʱ������λ��ֵ��1
		if(time.year<0){time.year=99;}				//��Խ���ж�
		if(time.mon<1){time.mon=12;}				//��Խ���ж�
		if( time.mon==1 || time.mon==3 || time.mon==5 || time.mon==7 || 
			time.mon==8 || time.mon==10 || time.mon==12)//��Խ���ж�
		{
			if(time.date<1){time.date=31;}			//����
			if(time.date>31){time.date=1;}
		}
		else if(time.mon==4 || time.mon==6 || time.mon==9 || time.mon==11)
		{
			if(time.date<1){time.date=30;}			//С��
			if(time.date>30){time.date=1;}
		}
		else if(time.mon==2)
		{
			if(time.year%4==0)
			{
				if(time.date<1){time.date=29;}		//����2��
				if(time.date>29){time.date=1;}
			}
			else
			{
				if(time.date<1){time.date=28;}		//ƽ��2��
				if(time.date>28){time.date=1;}
			}
		}
	}
	if(time.hour<0){time.hour=23;}					//ʱԽ���ж�
	if(time.min<0){time.min=59;}					//��Խ���ж�
	if(time.sec<0){time.sec=59;}					//��Խ���ж�

	//������ʾ������TimeSetSelect��TimeSetFlashFlag�жϿ������˸����
	if(TimeSetSelect==0 && TimeSetFlashFlag==1){OLED_ShowString(0,2,"  ",16);}
	else {OLED_ShowNum(0,2,time.year,2,16);}
	if(TimeSetSelect==1 && TimeSetFlashFlag==1){OLED_ShowString(24,2,"  ",16);}
	else {OLED_ShowNum(24,2,time.mon,2,16);}
	if(TimeSetSelect==2 && TimeSetFlashFlag==1){OLED_ShowString(48,2,"  ",16);}
	else {OLED_ShowNum(48,2,time.date,2,16);}
	if(TimeSetSelect==3 && TimeSetFlashFlag==1){OLED_ShowString(0,0,"  ",16);}
	else {OLED_ShowNum(0,0,time.hour,2,16);}
	if(TimeSetSelect==4 && TimeSetFlashFlag==1){OLED_ShowString(24,0,"  ",16);}
	else {OLED_ShowNum(24,0,time.min,2,16);}
	if(TimeSetSelect==5 && TimeSetFlashFlag==1){OLED_ShowString(48,0,"  ",16);}
	else {OLED_ShowNum(48,0,time.sec,2,16);}
}





void main()
{
	OLED_Init();						//��ʼ��
	OLED_Clear();
	ds1302Init();					//��ʼ��1302
	Timer0Init();					//��ʼ����ʱ��

	ti=ds1302ReadTime();			//��ȡRTCʱ�Ӹ�ti�ṹ��
		
	ptime=&(time.year);
	pti=&(ti.year);
	
	for(i=0;i<7;i++)
	{
		*(ptime+i)=*(pti+i);		//��������RTCʱ���time�ṹ�壬�൱�ڳ�ʼ��time
	}
//	OLED_ShowString(1,0,"hh",16);
//	lcdShowString(1,1,"  -  -  ");	//��̬�ַ���ʼ����ʾ
//	lcdShowString(2,1,"  :  :  ");
	while(1)
	{
		
		k=key();
		if(k==1)
		{
			if(MODE==0)
			{
				MODE=1;
				TimeSetSelect=0;
			}						//�����л�
			else if(MODE==1)
			{
				MODE=0;
				ds1302SetTime(time);
			}
		}

		switch(MODE)				//���ݲ�ͬ�Ĺ���ִ�в�ͬ�ĺ���
		{
			case 0:showTime();break;
			case 1:setTime();break;
		}
	}
}

void Timer0Init(void)
{
	TMOD &= 0xF0;					//���ö�ʱ��ģʽ
	TMOD |= 0x01;					//���ö�ʱ��ģʽ
	TL0 = 0x18;						//���ö�ʱ��ֵ
	TH0 = 0xFC;						//���ö�ʱ��ֵ
	TF0 = 0;						//���TF0��־
	TR0 = 1;						//��ʱ��0��ʼ��ʱ
	ET0=1;
	EA=1;
	PT0=0;
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;						//���ö�ʱ��ֵ
	TH0 = 0xFC;						//���ö�ʱ��ֵ
	T0Count++;
	if(T0Count>=200)				//ÿ500ms����һ��
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;//��˸��־λȡ��
	}
}