/* 
 * File:   deviceDetails.h
 * Author: Manu K Harshan
 *
 * Created on 29 May, 2017, 12:30 PM
 */

#ifndef DEVICEDETAILS_H
#define	DEVICEDETAILS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <string.h>    
#include "system_config.h"   
#include "system_definitions.h"
#include "ledindication.h"

    
#define TOTALNOOFROTATION 3992021

typedef enum
{
    FULLCLOSE,
    NIGHTYCLOSE,
    EIGHTYCLOSE,
    SEVENTYCLOSE,
    SIXTYCLOSE,
    FIFTYCLOSE,
    FOUTYCLOSE,
    THIRTYCLOSE,
    TWENTYCLOSE,
    TENCLOSE,
    FULLOPEN,
    JOGPOS,
    JOGNEG,
    JOGABSOLUTEZERO,         
}stateToMove;
    
typedef enum
{
    MOTORUNLOCKED, 
    MOTORLOCKED,       
}motroStatus;

typedef enum
{
    MOTORSTOPPED,
    MOTORRUNNING,
    MOTORISHOMING,
    MOTORHOMINGCOMPLETED,       
}motorState;

typedef enum
{
    CLOSED,
    OPENED,     
    CLOSING,
    OPENING,           
}valveState;
    
typedef enum
{
    NO_SELECTION, 
    LOCAL_MODE_SELECTED,
    REMOTE_MODE_SELECTED,       
}valveCtrlcommMod;

typedef enum
{
    LOCALMOD,
    CONFIGMOD,        
    REMOTE,       
    MAXMOD,        
}valveCtrlMod;

typedef struct
{
    valveCtrlcommMod eValveCtrlcommMod;
    valveCtrlMod evalveCtrlMod;
    valveState eValveState;
}valveCtrlState;

typedef struct
{
    motroStatus eMotorStatus;
    motorState  eMotorState;
}motorCtrlState;

typedef struct
{
    valveCtrlState eValveCtrlState;
    motorCtrlState eMotorCtrlState;
}sDeviceCtrlState;

typedef struct
{
   uint8_t signature[4]; 
   uint8_t devID[5];
   uint8_t ipaddress[16];
   uint8_t portNo[6];
   uint8_t calibrationstatus;
   uint8_t percentageopen;
   int32_t noofRotation;
   int32_t opencountnum;
   int32_t closecountnum;
}sSlavedetails;

typedef struct
{
    uint8_t copleyDesState[3];
    uint8_t copleyProfType[4];
    uint8_t copleyMotVel[12];
    uint8_t copleyAccTime[12];
    uint8_t copleyDecTime[12];
}motorConfigdetails;

typedef struct
{
   uint8_t copleyfastHomeVel[8]; 
   uint8_t copleySlowHomeVel[8];
   uint8_t copleyHomeAcc[4];
   uint8_t copleyHomeOffset[8];
   uint8_t copleyHomeType[5];
   uint8_t copleyCurrentlimit[4];
   uint8_t copleyCurrentdelay[4];
   uint8_t copleyHomewithoutsetzero[5];
}motorHomeConfigState;

int32_t CountToRun;
motorConfigdetails gMotorConfigdetails;
motorHomeConfigState gMotorHomeConfigState;

//void setCountToRun(void);
void setCountToRun(stateToMove gStateTomove);
void setCopleyPositionLoop(void);
void setCopleyVelocityLoop(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DEVICEDETAILS_H */

