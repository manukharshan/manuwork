/* 
 * File:   loraModem.h
 * Author: Manu K Harshan
 *
 * Created on 24 January, 2017, 4:44 PM
 */

#ifndef LORAMODEM_H
#define	LORAMODEM_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include "deviceDetails.h"    
#include "commandSetup.h"    
#include "loraevents.h"
#include "lorauarthandler.h"    
    
    
LoraEventType lmProcessReceiveEvent(char* response);
void loraWansetRadioSF(char* sprfact);
void loraWansetRadioPower(int8_t pwr);
void loraWansetRadioFreq(uint32_t freq);
void loraWansetRadioCRC(char* state);
void loraWansetRadioCR(char* codingrate);
void loraWanmacPause(void);
void loraWansetWdt(uint32_t wdt);
void loraTransmit(char* message);
void loraReceive(void);
LoraEventType loraProcessReceivecommand(char* Response);


#ifdef	__cplusplus
}
#endif

#endif	/* LORAMODEM_H */

