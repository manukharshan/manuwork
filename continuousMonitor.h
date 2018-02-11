/* 
 * File:   continuousMonitor.h
 * Author: Manu K Harshan
 *
 * Created on 03 April, 2017, 8:19 PM
 */

#ifndef CONTINUOUSMONITOR_H
#define	CONTINUOUSMONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h> 
#include <stdbool.h>
#include "deviceDetails.h"
#include "datatypeconversion.h"    
      
#define LOCALMODSEL PORTBbits.RB7
#define REMOTMODSEL PORTEbits.RE4
#define HWSENSOR PORTEbits.RE2 
    
#define HOMING_START_DELAY 8000U    
    
    
#define LOCAL_MODE_ON 0
#define LOCAL_MODE_OFF 1
#define REMOTE_MODE_ON 0
#define REMOTE_MODE_OFF 1   
    
#define TORQSW1 PORTFbits.RF12
#define TORQSW2 PORTBbits.RB4

#define PWRSTATUS PORTGbits.RG12    
    
typedef struct
{
    int motorTemperature;
    int motorEncoderCount;
    int motorCurrent;
    unsigned int motorStatus;
    int16_t trajectoryStatus;    
}sMonitorMotorparameter;

void handweelSenMonitor(void);
void remoteLocalSelswitch(void);
void continuousMonitorMotorTemp(void);       
void continuousMonitorMotorEncoder(void);
void continuousMonitorMotorCurrent(void);
void continuousMonitorMotorStatus(void);
void continuousMonitorPowerStatus(void);

void setCurrentEncoderPosition(int value);
int getCurrentEncoderPosition(void);
void setCurrentMotorStatus(int value);
uint32_t getCurrentMotorStatus(void);
void setMotorTrajStatus(int value);
int16_t getMotorTrajStatus(void);

void setCurrentMotorTemp(int value);
void setCurrentMotorCurrent(int value);

int getCurrentMotorTemp(void);
int getCurrentMotorCurrent(void);

void setDeviceCtrlState(sDeviceCtrlState* gsTDeviceCtrlState);
sDeviceCtrlState*  getDeviceCtrlState(void);
bool isDeviceCtrlstatusUpdated(void);

uint32_t checkbitSetorNot(uint32_t value,uint8_t positon);

void taskContinuousMonitorMotorParameters(void);

bool isValveOperatable(void);
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* EVENTS_H */
    