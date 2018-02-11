/* 
 * File:   gsmSmHandler.h
 * Author: Manu K Harshan
 *
 * Created on 20 February, 2017, 11:57 AM
 */

#ifndef GSMSMHANDLER_H
#define	GSMSMHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>  
#include "gsmevents.h"    
    
typedef enum
{
    GSM_SM_IDEAL,
    GSM_SM_CONFIG,
    GSM_SM_MESGREAD,
    GSM_SM_MSGTRANMIT,
    GSM_SM_MAX_STATE,       
}gsmSmStates;

typedef struct
{
    gsmSmStates egsmSmStates;
    gsmSmStates(*gsmSmFunctions)(gsmsysEvents*,bool*);
}gsmsmTable;

gsmSmStates gsmSmhandler(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled);
gsmSmStates gsmstateideal(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled);
gsmSmStates gsmstateconfig(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled);
gsmSmStates gsmstatemsgread(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled);
gsmSmStates gsmstatemsgtransmit(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled);

gsmSmStates gsmConfigTask(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate);
gsmSmStates gsmReceiveEventTask(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate);
gsmSmStates gsmTransmitMsgTask(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate);

#ifdef	__cplusplus
}
#endif

#endif	/* GSMSMHANDLER_H */

