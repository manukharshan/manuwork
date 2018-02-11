/* 
 * File:   wifiuartHandler.h
 * Author: Manu K Harshan
 *
 * Created on 15 June, 2017, 12:29 PM
 */

#ifndef WIFIUARTHANDLER_H
#define	WIFIUARTHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdint.h"    
    
#define WIFI_RX_BUF_SIZE 150 
#define MAX_TX_BUF_SIZE 100
#define MAX_EVENTS 100    
    
typedef struct
{
   uint8_t uiInPtr;
   uint8_t uiOutPtr;
   uint8_t uiProcessCtr;  
}wifieventPtr;

typedef struct
{
   uint8_t ucData[WIFI_RX_BUF_SIZE];
}wifiEvent;
    
typedef struct
{
    wifieventPtr sEventPtr;
    wifiEvent sData[MAX_EVENTS];
}wifiEventData;    
    
void wifirxBuffMng();
void postwifiReceiveEvent(uint8_t *Response);
bool getwifiReceiveEvent(uint8_t **ucRecvData);
void disposewifiRecvEvent();
void wifiTransmitDataBuffer(int8_t cTxData);
void wifiTransmitData(void);
void wifiSendCmdData(int8_t csStringReceived[],int8_t length);
void wifiProcessReceivedData(void);
void processWifiData(void);



#ifdef	__cplusplus
}
#endif

#endif	/* COMMANDINTERFACE_H */

