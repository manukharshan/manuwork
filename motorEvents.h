/* 
 * File:   motorEvents.h
 * Author: Manu K Harshan
 *
 * Created on 8 June, 2017, 4:11 PM
 */

#ifndef MOTOREVENTS_H
#define	MOTOREVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "events.h"
#include "actionHandler.h"    

typedef struct
{
    EventType eTypeEvent;
    eMotorEvent eTypeMotorEvent;
    uint8_t *sCopleyData;
}motorsysEvents;

typedef enum
{
    MOTORPOSITION,
    MOTORPOSITIONRES,
    MOTORSETACCEL,
    MOTORSETACCELRES,        
    MOTORSETDECEL,
    MOTORSETDECELRES,    
}emotorconfigstate;

typedef enum
{
    HOMINGFASTVELUNIT,
    HOMINGFASTVELUNITRES,        
    HOMINGSLOWVELUNIT,
    HOMINGSLOWVELUNITRES,
    HOMINGACCDECUNIT,
    HOMINGACCDECUNITRES,
    HOMEOFFSETUNIT,
    HOMEOFFSETUNITRES,
    HOME_WITHOUT_HOME_ADJUSTMENT,
    HOME_WITHOUT_HOME_ADJUSTMENTRES,
    HOMEPOSSOFTLIMITUNIT,
    HOMEPOSSOFTLIMITUNITRES,
    HOMENEGSOFTLIMITUNIT,
    HOMENEGSOFTLIMITUNITRES   
}emotorhomconfigstate;

typedef enum
{
    MOTORCLRFAULT,
    MOTORCLRFAULTRES,
    MOTOR_DISABLE_AMP,
    MOTOR_DISABLE_AMP_RESP,        
    MOTOR_ENABLE_AMP,
    MOTOR_ENABLE_RESP,        
    MOTORSETPROFTYPE,
    MOTORSETPROFTYPERES,
    MOTORSETVEL,
    MOTORSETVELRES,
    MOTORSETDIR,
    MOTORSETDIRRESP,
    MOTORSTARTMOV,
    MOTORSTARTMOVRES,
}emotorstartmovstate;

typedef enum
{
    MOTORSTOPMOV,
    MOTORSTOPMOVRES,
}emotorstopmovstate;

typedef enum
{
    MOTORCURRPOSITION,
    MOTORCURRPOSITIONRES,
    MOTORSTATUS,
    MOTORSTATUSRES,
    MOTORHOMESTATUS,
    MOTORHOMESTATUSRES,
    MOTORCURRENT,
    MOTORCURRENTRES,         
}emotormonitorstate;

typedef enum
{
    MOTOR_SET_CURRENT,
    MOTOR_SET_CURRENTRES,
    MOTOR_SET_CURRENTDELAY,
    MOTOR_SET_CURRENTDELAYRES,        
    MOTORHOMINGTYPE,
    MOTORHOMINGTYPERESPONSE,
    MOTORHOMING,
    MOTORHOMINGRESP
}emotorHomemovState;

typedef struct
{
    emotorconfigstate geMotorconfigstate;
    emotorstartmovstate geMotorstartmovstate;
    emotorstopmovstate geMotorstopmovstate;
    emotormonitorstate gemotormonitorstate;
    emotorhomconfigstate gemotorhomconfigstate;
    emotorHomemovState gemotorHomemovState;
}sMotorcontrolstate;


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOREVENTS_H */

