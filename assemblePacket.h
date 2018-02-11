/* 
 * File:   assemblePacket.h
 * Author: SenthilKumarRamasamy
 *
 * Created on 2 February, 2017, 11:35 AM
 */

#ifndef ASSEMBLEPACKET_H
#define	ASSEMBLEPACKET_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "deviceDetails.h"
#include "defaultvalue.h"
#include "continuousMonitor.h"
#include "datatypeconversion.h"
#include "i2cinterface.h"    
    
#define SIZE_COMMAND 3U
#define SIZE_NUMBEROFDEVICES 2U
#define SIZE_DEVICEID 4U
#define SIZE_STATUS 1U    
    

#define VALVE_ON_COMMAND 01
#define VALVE_OFF_COMMAND 02
#define VALVE_CONTINUOUS_MON 03    
#define VALVE_ACK 04

 typedef enum
 {
     GETALLDEVICESTATUS,
     GETCURRENTCOUNT,
     GETCALPOSITON,
     GETOPENPERCENTAGE,
     GET_DEVICE_STATUS_REMOTE,        
 }packetType;
 
 typedef enum
 {
     EEPROMWRITECURRENTCOUNT,
     EEPROMWRITECALIBRATIONDETAILS,       
     EEPROMWRITEALLDEVICEDETAILS,
 }eepromPacketType;


void frameResponse(packetType ePacketType,valveCtrlMod ctrlMod,uint8_t* messagePacket);
void assembleEEpromPacket(eepromPacketType ePacketType,uint8_t* messagePacket);

#ifdef	__cplusplus
}
#endif

#endif	/* ASSEMBLEPACKET_H */

