#include "includes.h"

void Sbuf_Init(void)
{
	TMOD|=0X20;    //定时器1工作方式2（用于波特率产生器)
	TL1=0XFD;      //9600波特率      
	TH1=0XFD;
	PCON=0X00;     
	SCON=0X50;     //send and receive
	TR1=1;
	ES=1;							
}

char PutChar (char c) 
{
	ES=0;
	SBUF=c;
	while (!TI);
	TI = 0;
	ES=1;
	return (c);
}

void print_string(char *str)
{
	while(*str!=0)
	PutChar(*str++);
}


