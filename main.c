#include "includes.h"

void MCU_Init(void);
void StartTimer(void);

INT8U tick_count = 0;
INT16U msec_tick = 0;
INT16U sec_tick = 0;
INT8U sbuf_cmd = 0;

void main(void)
{
	MCU_Init();
	ThreadInit();
	TmrInit();	
	StartTimer();

	#ifdef SBUF_DEBUG
	print_string("Power On.");
	PutChar(0x0a);
	PutChar(0x0d);
	#endif

	TmrStart(4,40);
	TmrStart(5,500);    
		
	while(1)
	{
		ThreadScheduler();
		if(sbuf_cmd!=0)
		{	
		    sbuf_cmd=0;
			#ifdef SBUF_DEBUG
		    print_string("Receive Command.");
		    PutChar(0x0a);
		    PutChar(0x0d);
		    #endif
				
		}
	}
}


void MCU_Init(void)
{
	//定时器初始化	
	TH0 = 0X1a;	//定时时间为250us
	TL0 = 0X1a;
	TMOD |= 0X02;	//定时器0采用工作方式2
	//中断初始化
	ET0 = 1;
    Sbuf_Init();
	EA = 1;
}

void StartTimer(void)
{
	//启动定时器单元
	TR0 = 1 ;			
}

//定时器中断初始化
void tm0_isr() interrupt 1
{
	if(++tick_count >= 4)
	{
		tick_count = 0;										 
		ThreadSet(8);
		if(++msec_tick >= 1000)
		{
			msec_tick = 0;
			sec_tick++;
		}
	}
}

 //串口中断服务子程序
void UART () interrupt 4  using 2
{
	if(RI==1)
	{ 
		RI=0;  
		sbuf_cmd = SBUF;
	}
	else
	{
		TI=0;
	}
}
