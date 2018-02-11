/* 
 * File:   events.h
 * Author: Davis
 *
 * Created on 29 August, 2015, 8:19 PM
 */

#ifndef EVENTS_H
#define	EVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
    
#define MAX_COPLEY_CMD_LEN 100 
#define MAX_TX_BUF_SIZE 100
#define MAX_EVENTS 100
    typedef struct
    {
        uint8_t ucCommandByte[30];
        uint8_t ucCommSel;
        uint8_t ucSourceId[2];
    }tcpipReceivePacket;
    
    typedef struct
    {
        uint8_t ucCommSel;
        uint8_t ucMonitorCmd;
    }monitorCmdRecvPacket;
    
    typedef struct
    {
        uint16_t uiInPtr;
        uint16_t uiOutPtr;
        uint16_t uiProcessCtr;  
    }eventPtr;
    
    typedef struct
    {
        uint8_t ucCopleyData[MAX_COPLEY_CMD_LEN];
    }CopleyEvent;

    typedef struct
    {
        eventPtr sCopleyEventPtr;
        CopleyEvent sCopleyData[MAX_EVENTS];
    }CopleyEventData;
    
    typedef struct
    {
        uint8_t ucCopleyData[MAX_TX_BUF_SIZE];
        eventPtr sCopleyEventPtr;
    }CopleyTxEvent;
    

    typedef enum
    {
        COPLEY_RESPONSE,
        COPLEY_MESSAGE,
        TCPIP_EVENT_OCCURED,
        TIME_OUT_EVENT,
        MOTORCONTROL_EVENT,  
        INVALID_EVENT,
    }EventType;
    
    typedef struct
    {
        EventType eTypeEvent;
        uint8_t *sCopleyData;
        tcpipReceivePacket sTcpipRecvData;
    }sysEvents;

    



#ifdef	__cplusplus
}
#endif

#endif	/* EVENTS_H */

