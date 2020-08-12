#include "includes.h"

uchar data Disp_Buff[4] = {0x05,0x06,0x07,0x08};
uchar code SEG_DIGI[16]={0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0X88,0X83,0XC6,0XA1,0X86,0X8E};
uchar code BIT_DIGI[4] = {0x00,0x01,0x02,0x03};

static uchar BIT_Position = 0;

void display_process()				  
{

	P0 = 0XFF;
	P2 &= 0xf8; 

	P2 |= BIT_DIGI[BIT_Position];
	P0 = SEG_DIGI[Disp_Buff[BIT_Position]];

	BIT_Position++;

	if(BIT_Position>=4)
	{
		BIT_Position  = 0;	
	}
}
