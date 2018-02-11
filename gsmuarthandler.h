/* 
 * File:   gsmuarthandler.h
 * Author: Manu K Harshan
 *
 * Created on 15 February, 2017, 3:08 PM
 */

#ifndef GSMUARTHANDLER_H
#define	GSMUARTHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "uart_handler.h"      


void guReceiveDataBuffer(void);
void guProcessRecieveDataBuffer(void);
void guTransmitDataBuffer(int8_t cTxData);
void guSendData(char* csStringReceived,uint length);
void guTransmitData(void);
void postGsmSerialReceiveEvent(unsigned char* gsmResponseData);
bool getGsmSerialReceiveEvent(unsigned char** ucRecevData);
void disposeGsmSerialReceiveEvent(void);

void postGsmSendEvent(int8_t* gsmSendData);
bool getGsmSendEvent(unsigned char** ucSendData);
void disposegsmSendEvent(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GSMUARTHANDLER_H */

