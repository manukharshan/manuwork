/* 
 * File:   copleyreceivehandler.h
 * Author: Davis
 *
 * Created on 29 August, 2015, 8:18 PM
 */

#ifndef COPLEYRECEIVEHANDLER_H
#define	COPLEYRECEIVEHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "events.h"
#include "datatypeconversion.h"
#include "continuousMonitor.h"   

void disposeCopleyRecvEvent(void);
EventType checkCopleyRecvEventType(uint8_t ucRecvData[]);
bool getCopleyReceiveEvent(uint8_t **ucRecvData);
void postCopleyReceiveEvent(uint8_t *copleyResponse);
void rxBuffMng();
void copleyReceiveHandlerTask(void);
void copleyMessageextract(uint8_t* copleyMessage);
void getCopleyMessage(uint8_t* copleyMessage);


#ifdef	__cplusplus
}
#endif

#endif	/* COPLEYRECEIVEHANDLER_H */

