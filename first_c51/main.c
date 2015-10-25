#include<STC12C2052AD.h>

sbit SPEAKER = P3 ^ 7;
#define KEY P1
unsigned char MUSIC;
unsigned char STH0;
unsigned char STL0;
unsigned int code tab[] = {
	64021,64103,64260,64400,
	64524,64580,64684,64777,
	64820,64898,64968,65030,
	65058,65110,65157,65178
};
/*********************************************************************************************
函数名：毫秒级CPU延时函数
调  用：DELAY_MS (?);
参  数：1~65535（参数不可为0）
返回值：无
结  果：占用CPU方式延时与参数数值相同的毫秒时间
备  注：应用于1T单片机时i<600，应用于12T单片机时i<125
/*********************************************************************************************/
void DELAY_MS (unsigned int a){
	unsigned int i;
	while( a-- != 0){
		for(i = 0; i < 600; i++);
	}
}
/*********************************************************************************************/
sbit LED1 = P1 ^ 7;
sbit LED2 = P1 ^ 6;

/*********************************************************************************************
函数名：主函数
调  用：无
参  数：无
返回值：无
结  果：程序开始处，无限循环
备  注：
/**********************************************************************************************/
void main (void){
	P1M0 = 0x00;
	P1M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x80;
	TMOD = 0x01;
	ET0 = 1;
	EA = 1;
	KEY = 0xff;
	while(1){
		if(KEY != 0xff){
			switch(~KEY){
				case  0x01:
					MUSIC = 7;
					break;
				case  0x02:
					MUSIC = 6;
					break;
				case  0x04:
					MUSIC = 5;
					break;
				case  0x08:
					MUSIC = 4;
					break;
				case  0x10:
					MUSIC = 3;
					break;
				case  0x20:
					MUSIC = 2;
					break;
				case  0x40:
					MUSIC = 1;
					break;
				case  0x80:
					MUSIC = 0;
					break;
			}
			STH0 = tab[MUSIC] / 256;
			STL0 = tab[MUSIC] % 256;
			TR0 = 1;
		}else{
			SPEAKER = 1;
			TR0 = 0;
		}
	}
	
	
}
/**********************************************************************************************/
void t0(void) interrupt 1 using 0{
	TH0 = STH0;
	TL0 = STL0;
	SPEAKER = ~SPEAKER;
}

