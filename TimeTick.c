#define  FW_TMR_GLOBALS
#include "includes.h"

void  TmrInit (void)
{
    INT8U  i;
    for (i = 0; i < TMR_MAX_TMR; i++) {         
        TmrCtrTbl[i]  = 0;
    }
}

void  TMR_Tick (void)
{
    INT8U i;
    for (i = 0; i < TMR_MAX_TMR; i++) {
        if (TmrCtrTbl[i] != 0) {
            if((-- TmrCtrTbl[i]) == 0){
                switch(i){
                    case 0:                       
                        break;
                    case 1:
                        ThreadSet(1);	//线程1，初始化
                        break;
                    case 2:
						ThreadSet(2);	//线程2，急停
                        break;
                    case 3:
					    ThreadSet(3);	//线程2，动作执行
                    	break;
                    case 4:
					    ThreadSet(4);	//led_display
						TmrStart(4,5); //5ms
                    	break;
                    case 5:
					    ThreadSet(5);	//led_display
						TmrStart(5,100); //100ms
						break;
					case 6:
					    ThreadSet(6);	//触发调节检测
                    	break;
                    case 7:
					    ThreadSet(7);	//LED显示检测
						TmrStart(7,500); //500ms
						break;
                }
            }
        }
    }
}



