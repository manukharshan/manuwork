/* 
 * File:   commandSetup.h
 * Author: Manu K Harshan
 *
 * Created on 7 June, 2017, 10:44 AM
 */

#ifndef COMMANDSETUP_H
#define	COMMANDSETUP_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "stdint.h"
#include "assemblePacket.h"    
#include "actionHandler.h"
#include "wifiuartHandler.h"
#include "lorauarthandler.h"    
#include "gsmuarthandler.h"    
    
enum {
    LOCAL,
    TCP_IP,
    UDP,
    WIFI_TCP,
    LORA,
    GSM,
};    

typedef struct
{
    uint8_t* cmdString;
    uint8_t (*cmdFunction)(uint8_t* comd,uint8_t* arg,uint8_t sel);
}CmdTableEntry;

uint8_t commandParse(uint8_t* command1,uint8_t* arg,uint8_t sel);
uint8_t getDeviceList(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t registerDeviceList(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t getCurrentCount(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t setOpenPosition(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t setClosePosition(uint8_t* comd,uint8_t* arg,uint8_t sel);

uint8_t getDeviceStatus(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t getAllDeviceStatus(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t openValve(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t closeValve(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t stopMotor(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t jogMotorNeg(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t jogMotorPos(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t getCalPosition(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t homePositive(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t homeNegative(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t calibrate(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t getopenpercentage(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t getdevicestatusremote(uint8_t* comd,uint8_t* arg,uint8_t sel);

uint8_t keepAlive(uint8_t* comd,uint8_t* arg,uint8_t sel);
uint8_t cmdNull(uint8_t* comd,uint8_t* arg,uint8_t sel);

void framePacketForTcpIP(uint8_t* comnd);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMANDSETUP_H */

