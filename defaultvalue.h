/* 
 * File:   defaultvalue.h
 * Author: Manu K Harshan
 *
 * Created on 4 April, 2017, 4:33 PM
 */

#ifndef DEFAULTVALUE_H
#define	DEFAULTVALUE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "deviceDetails.h"
#include "actionHandler.h"     

typedef struct
{
    unsigned int gmobnumber;
}sGsmcommondata;

typedef struct
{
    unsigned int glorafreq;
    unsigned int watchdogtimeout;
    unsigned char gTxpwr;
}sLoracommondata;

typedef struct
{
    int gmaxmotortemp;
    int gmaxmotorcurrent;
}sdefaultcontmondata;

typedef struct
{
    sGsmcommondata gsGsmcommondata;
    sLoracommondata gsLoracommondata;
    sdefaultcontmondata gsdefaultcontmondata;
}sCommondefaultdata;

void initdefaultvalues(void);
void setVelocityMode(void);
void setJogMod(void);
void setAbsoluteMode(void);
void setHardStopHomePositive(void);
void setHardStopHomeNegative(void);

void setDevicedetails(sSlavedetails* gsTSlavedetails);
sSlavedetails* getDevicedetails(void);
bool isDevicedetailsupdated(void);
//uint8_t* getdevaddress(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DEFAULTVALUE_H */

