/* 
 * File:   gsmModem.h
 * Author: manu k harshan
 *
 * Created on 24 January, 2017, 4:44 PM
 */

#ifndef GSMMODEM_H
#define	GSMMODEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>
#include "gsmevents.h"
#include "gsmuarthandler.h"
#include "commandSetup.h"
#include "debuguarthandler.h"    

typedef enum
{
    SIMREADYCHECK,
    CALLRECEIVECHECK,
    SMSRECEIVECHECK,
    SMSRECEIVEINDEX,
    SMSRECEIVED,
    RSSIRECEIVED,
}recdatatype;

typedef struct
{
    int32_t rssi;
    int8_t simstatus;
    int32_t smsindex;
}gsmmonitor;

gsmEventType gsmProcessReceiveEvent(char* response);
gsmEventType gsmProcessReceivecommand(recdatatype gerecdatatype,char* response);
gsmEventType gsmProcessReceiveMsg(char* Response);

int32_t getsmsindex(void);
int32_t getrssi(void);

//commands
void gsmATcommand(void);
void gsmTurnOffecho(void);
void gsmSetErrcommand(char enable);
void gsmSetStartIndication(int8_t start,int8_t ready);
void gsmSetCallerID(char set);
void gsmSimStatus(void);
void gsmTestorPduMode(char mod);
void gsmSignalSrength(void);
void gsmSmsindication(int8_t mod,int8_t mt,int8_t bm,int8_t ds,int8_t bfr);
void gsmReadSms(int index1);
void gsmDeleteSms(int index1);
void gsmDeleteAllSms(void);
void gsmSendSms(char* mobNumber);
void gsmSendSmsData(char* msg);

#ifdef	__cplusplus
}
#endif

#endif	/* GSMMODEM_H */

