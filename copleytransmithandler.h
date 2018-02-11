/* 
 * File:   copleytransmithandler.h
 * Author: PRASATH
 *
 * Created on August 31, 2015, 1:38 AM
 */

#ifndef COPLEYTRANSMITHANDLER_H
#define	COPLEYTRANSMITHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "copleycommandinterface.h"
    
void postCopleyTransmitEvent(uint8_t *copleyCommand);
void copleyTransmitHandle(void);
void initCopleyTransmitEvent(void);
void SendCommandToCopley(eCommandToCopley ecmdtoCopley, uint8_t ucCmdData[]);
#ifdef	__cplusplus
}
#endif

#endif	/* COPLEYTRANSMITHANDLER_H */

