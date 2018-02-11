/* 
 * File:   motorSmHandler.h
 * Author: Manu K Harshan
 *
 * Created on 8 June, 2017, 3:41 PM
 */

#ifndef MOTORSMHANDLER_H
#define	MOTORSMHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "motorEvents.h"
#include "actionHandler.h"
#include "copleyreceivehandler.h"    
    
typedef enum
{
    MOTOR_SM_IDLE,
    MOTOR_SM_CONFIG,
    MOTOR_SM_HOMECONFIG,
    MOTOR_START_MOV,
    MOTOR_STOP_MOV,
    MOTOR_HOMING,        
    MOTOR_COPLEY_DISABLE,       
    MOTOR_SM_MAX_STATE
}motorSmStates; 

typedef struct
{
    motorSmStates emotorSmStates;
    motorSmStates(*motorSmFuncitons)(motorsysEvents*,bool*);
}motorsmTable;

motorSmStates motorSmhandler(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorstateidle(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorstateconfig(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorstatehomeconfig(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorstartmov(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorstopmov(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorhoming(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);
motorSmStates motorcopleyDisable(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled);

motorSmStates motorMonitorTask(motorsysEvents* psmotorsysEvents);
motorSmStates motorContorlAction(motorsysEvents* psmotorsysEvents);


motorSmStates configureHome(motorsysEvents* psmotorsysEvents);
motorSmStates motorHoming(motorsysEvents* psmotorsysEvents);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTORSMHANDLER_H */

