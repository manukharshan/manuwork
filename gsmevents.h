/* 
 * File:   gsmevents.h
 * Author: Manu K Harshan
 *
 * Created on 9 February, 2017, 7:57 AM
 */

#ifndef GSMEVENTS_H
#define	GSMEVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>    
#include <stdbool.h>    
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h> 
#include "timerfunctions.h"    
    
#define MAX_GSM_DATA_LENGTH 100
#define MAX_GSM_EVENTS 20
    
typedef enum
{
    GSMTURNOFFECHO,
    GSMTURNOFFECHORES,
    GSMATCMD,
    GSMATCMDRES,
    GSMSIMSTATUS,
    GSMSIMSTATUSRES,
    GSMGETSIGSTR,
    GSMGETSIGSTRRES,   
    GSMSETCALLID,
    GSMSETCALLIDRES,
    GSMSMSSETMOD,
    GSMSMSSETMODRES,
    GSMSMSINDICATION,
    GSMSMSINDICATIONRES,
    GSMDELETEALLSMS,
    GSMDELETEALLSMSRES,
}gsmconfigState;

typedef enum
{
    GSMREADMSG,
    GSMREADMSGRES,
    GSMDELETEMSG,
    GSMDELETEMSGRES,
}gsmreadmsgstate;

//typedef enum
//{
//    GSMREADSMS,
//    GSMREADSMSRESP,
//}gsmreadsmsstate;

typedef enum
{
    GSMSIGSTRMONITOR,
    GSMSIGSTRMONITORRES,
}gsmmonitorstate;

typedef enum
{
    GSMSETMOBFORMSG,
    GSMSETMOBFORMSGRES,
    GSMTRANMITMSG,
    GSMTRANMITMSGRES,
}gsmtransmitmsgstate;

typedef enum
{
    GSM_NO_ANSWER = 0,
    GSM_ERROR = 1,
    GSM_ANSWER_OK = 2,
    GSM_CONNECT = 3,
    GSM_RING = 4,
    GSM_NO_CARRIER = 5,
    GSM_NO_DIALTONE = 6,
    GSM_BUSY = 7,
    GSM_NO_SUPPORT = 8,
    GSM_INVALIS_COMMAND_LINE = 9,
    GSM_CARRIAGE_RETURN = 10,
    GSM_MESG_REC = 11,
    GSM_KNOWN_MESG_REC = 12,
    GSM_UNKNOWN_MESG_REC = 13,
    GSM_SMS_TRANMIT_READY = 14,
    GSM_TIME_OUT = 15,
    GSM_CME_ERROR = 16,
}gsmEventType;

typedef struct
{
//  LoraResponseType eLoraResponseEvent;
  gsmEventType eGsmTypeEvent;
//  EventType eTypeEvent;
  uint8_t *sGsmData;
//  uint8_t *sCopleyData;
  //tcpipReceivePacket sTcpipRecvData;
  
}gsmsysEvents;

typedef struct
 {
    unsigned short int uiInPtr;
    unsigned short int uiOutPtr;
    unsigned short int uiProcessCtr;  
 }gsmeventPtr;
 
 typedef struct
 {
     
     unsigned char gsmData[MAX_GSM_DATA_LENGTH];
 }gsmevent;

typedef struct
{
    gsmeventPtr sgsmeventptr;
    gsmevent sgsmData[MAX_GSM_EVENTS];  
}gsmEventdata;

typedef struct
{
    gsmconfigState egsmconfigState;
    gsmreadmsgstate egsmreadmsgstate;
    gsmmonitorstate egsmmonitorstate;
    gsmtransmitmsgstate egsmtransmitmsgstate;
}gsmState;


#ifdef	__cplusplus
}
#endif

#endif	/* GSMEVENTS_H */

