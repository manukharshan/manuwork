/* 
 * File:   loraSmHandler.h
 * Author: manu k harshan
 *
 * Created on 24 January, 2017, 5:36 PM
 */

#ifndef LORASMHANDLER_H
#define	LORASMHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "loraevents.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>  
    
typedef enum
{
    LORA_NOT_CONFIGURED,
    LORA_CONFIGURED,
}loraconflag;

typedef enum
{
    MOTOR_NOT_CONFIGUED,
    MOTOR_CONFIGUED,
}motorconfig;

typedef enum
{
    MOTOR_NOT_HOMECONFIGURED,
    MOTOR_HOMECONFIGURED,
}motorhomeconfig;

typedef enum
{
    GSM_NOT_CONFIGURED,
    GSM_CONFIGURED,
}gsmconfig;

typedef struct
{
    loraconflag eloraconflag;
    motorconfig emotorconfigflag;
    motorhomeconfig emotorhomeconfig;
    gsmconfig egsmconfigflag;
}sConfigflag;
    

typedef enum
{
    LORA_SM_IDEAL,
    LORA_SM_CONFIG,        
    LORA_SM_TRANSMIT,
    LORA_SM_MAX_STATE
}loraSmStates;
    

typedef struct
{
    loraSmStates eloraSmStates;
    loraSmStates(*LoraSmFuncitons)(lorasysEvents*,bool*);
}lorasmTable;

loraSmStates loraSmhandler(lorasysEvents* pslorasysEvents,bool* psloraEventhandled);
loraSmStates lorastateideal(lorasysEvents* pslorasysEvents,bool* psloraEventhandled);
loraSmStates lorastateconfig(lorasysEvents* pslorasysEvents,bool* psloraEventhandled);
loraSmStates lorastatetransmit(lorasysEvents* pslorasysEvents,bool* psloraEventhandled);


loraSmStates loraReceiveTask(lorasysEvents* pslorasysEvents,loraSmStates eLorastate);


#ifdef	__cplusplus
}
#endif

#endif	/* LORASMHANDLER_H */

