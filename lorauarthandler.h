/* 
 * File:   lorauarthandler.h
 * Author: Manu K Harshan
 *
 * Created on 24 January, 2017, 4:05 PM
 */

#ifndef LORAUARTHANDLER_H
#define	LORAUARTHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include "uart_handler.h"  
//#include "system_config.h"
//#include "system_definitions.h"
    
    
void luReceiveDataBuffer(void);
void luProcessRecieveDataBuffer(void);
void luTransmitDataBuffer(int8_t cTxData);
void luSendData(char* csStringReceived,uint length);
void luTransmitData(void);
void postLoraSerialReceiveEvent(unsigned char* loraResponseData);
bool getLoraSerialReceiveEvent(unsigned char** ucRecevData);
void disposeLoraSerialReceiveEvent(void);

void postLoraSendEvent(int8_t* loraSendData);
bool getLoraSendEvent(unsigned char** ucSendData);
void disposeLoraSendEvent(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LORAUARTHANDLER_H */

