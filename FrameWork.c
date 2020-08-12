#define  FRAMEWORK_GLOBALS
#include "includes.h"

INT8U const  PRIORITY_TABLE[] = {0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
INT8U const  READY_CLR_AND[] = {0xFF, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};


void ThreadInit(void)
{
	ThreadReadyList = 0;
}

void ThreadScheduler(void)
{
    INT8U prionum,ready;
	prionum = 0;
	ready = ThreadReadyList;
    if (ready != 0) {
        if ((ready & 0xF0) != 0U) {//找出就绪线程中的最高优先级的线程        
            prionum = PRIORITY_TABLE[ready >> 4] + 4;
        }else{
            prionum = PRIORITY_TABLE[ready];
        }
        ready = READY_CLR_AND[prionum];
        OS_ENTER_CRITICAL();
        ThreadReadyList &= ready;//执行完成，清就绪位
        OS_EXIT_CRITICAL();
        switch(prionum){
            case 8:
				TMR_Tick();
                break;
            case 7:   
				     
                break;
            case 6:
			    
                break;
            case 5: 
			   	Temperature = ReadTempreture(Serial,9);
				Change(Temperature);
                break;
            case 4:
				display_process();              
                break;
            case 3:

                break;
            case 2:
                break;	  
            case 1:
                break;
        }
    }
}


