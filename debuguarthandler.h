/* 
 * File:   debuguarthandler.h
 * Author: SenthilKumarRamasamy
 *
 * Created on 27 January, 2017, 3:57 PM
 */

#ifndef DEBUGUARTHANDLER_H
#define	DEBUGUARTHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>
#include "uart_handler.h"    
//#include "system_config.h"
//#include "system_definitions.h"    

void duTransmitDataBuffer1(int8_t cTxData);    
void duSendData1(char* csStringReceived,uint length);
void duTransmitData1(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUGUARTHANDLER_H */

