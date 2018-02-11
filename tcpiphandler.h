/* 
 * File:   tcpiphandler.h
 * Author: Davis
 *
 * Created on 27 August, 2015, 12:41 AM
 */

#ifndef TCPIPHANDLER_H
#define	TCPIPHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif    
#include "events.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "copleySmHandler.h"
#include "commandSetup.h"    
    
#define UDP_ON 1
typedef enum
{
    CMD_INIT,
    CMD_RECV_CMD_IND,
    CMD_MONITOR_RECV,
    CMD_NORM_RECV,
}eRecvCmdStates;

void tcpipHandlerTask(void);
void udpHandlerTask(void);
bool getTcpipReceiveEvent(tcpipReceivePacket *psTcpipReceive);
void tcpipSmHandler(sysEvents *psSysEvt, bool *pbEventHandled);
void disposeTcpipReceiveEvent(void);
void disposeTcpipMontorReceiveEvent(); 
//bool tcpIPSendMesg(copleySmStates eCopleySmStats, uint8_t ucCopleyData[],uint8_t);
bool sendResposneViaUDP (uint8_t ucUDPResponse[],uint16_t uiSize);
//bool getTcpipMonitorReceiveEvent(tcpipReceivePacket *psTcpipReceive);
void processTcpipData(void);
void initTCPHandler (void);
#ifdef	__cplusplus
}
#endif

#endif	/* TCPIPHANDLER_H */

