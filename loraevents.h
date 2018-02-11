/* 
 * File:   loraevents.h
 * Author: Manu K Harshan
 *
 * Created on 24 January, 2017, 4:08 PM
 */

#ifndef LORAEVENTS_H
#define	LORAEVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h> 
#include "timerfunctions.h"
    
#define MAX_LORA_DATA_LENGTH 100
#define MAX_LORA_EVENTS 20    

#if 0    
typedef enum
{
    LORA_ANSWER_OK = 0,
    LORA_ANSWER_ERROR = 1,
    LORA_NO_ANSWER = 2,
    LORA_TIME_OUT = 3,
    LORA_DATA_RECEIVE = 4,
    //LORAWAN_INIT_ERROR = 3,
    //LORAWAN_LENGTH_ERROR = 4,
    //LORAWAN_SENDING_ERROR = 5,
    //LORAWAN_NOT_JOINED = 6,
    //LORAWAN_INPUT_ERROR = 7,
    //LORAWAN_VERSION_ERROR = 8
}LoraResponseType;

#endif
typedef enum
{
    LORA_NO_ANSWER = 0,
    LORA_ANSWER_ERROR = 1,
    LORA_ANSWER_OK = 2,
    LORA_MACPAUSE_OK = 3,
    LORA_TIME_OUT = 4,
    LORA_DATA_RECEIVE = 5,
    LORA_TRANSMIT_OK = 6,
    LORA_RADIO_ERROR = 7,
}LoraEventType;

typedef struct
{
//  LoraResponseType eLoraResponseEvent;
  //eKeypadEvent eLoraKeypadEvent;
  LoraEventType eLoraTypeEvent;
  uint8_t *sLoraData;
  //tcpipReceivePacket sTcpipRecvData;
  
}lorasysEvents;

typedef struct
 {
    unsigned short int uiInPtr;
    unsigned short int uiOutPtr;
    unsigned short int uiProcessCtr;  
 }loraeventPtr;
 
 typedef struct
 {
     
     unsigned char loraData[MAX_LORA_DATA_LENGTH];
 }loraevent;

typedef struct
{
    loraeventPtr sloraeventptr;
    loraevent sloraData[MAX_LORA_EVENTS];  
}loraEventdata;

typedef enum
{
    RADIOMACPAUSE,
    RADIOMACPAUSERES,
    RADIOSETSF,
    RADIOSETRESSF,
    RADIOSETPWR,
    RADIOSETPWRRES,
    RADIOSETFREQ,
    RADIOSETFREQRES,
    RADIOSETCRC,
    RADIOSETCRCRES,
    RADIOSETCR,
    RADIOSETCRRES,
    RADIOSETWATCHDOG,
    RADIOSETWATCHDOGRES,
}configState;

typedef enum
{
    TRANSMIT,
    TRANSMITRESP,
}transmitState;

typedef enum
{
    LORARECIEVE,
    LORARECEIVERESP,
}receiveState;



#ifdef	__cplusplus
}
#endif

#endif	/* LORAEVENTS_H */

