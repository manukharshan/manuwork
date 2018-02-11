/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "system_config.h"
#include "system_definitions.h"

#define MAX_LEN_ETH 25
#define MAX_LEN_COPLEY_CMD 20
typedef enum
{
	APP_STATE_INIT=0,
    APP_TCPIP_WAITING_FOR_COMMAND,
    APP_TCPIP_WAIT_FOR_CONNECTION,
    APP_TCPIP_WAIT_FOR_RESPONSE,
    UART_IDLE,
    UART_TX_READY,
    UART_TX_STATE,
    TCP_IP_RECEIVED_STRING,
    UART_RX_STATE,
    UART_RX_READY,
    TCPIP_WAIT_START,
    TCP_IP_WAIT_START_DELAY,        
    TCPIP_WAITING_FOR_COMMAND,
    TCPIP_WAIT_FOR_CONNECTION,
    UDP_WAITING_FOR_COMMAND,
    TCPIP_WAIT_FOR_RESPONSE,
    APP_TCPIP_OPENING_SERVER,
    APP_TCPIP_SERVING_CONNECTION,
    APP_TCPIP_CLOSING_CONNECTION,
    APP_UDP_OPENING_SERVER,
    APP_UDP_WAITING_FOR_TANSMIT,
    APP_UDP_TRANSMIT,
    I2C_READ_DEV_ID,
    I2C_READ_INIT,           
} APP_STATES;



typedef struct
{
    APP_STATES  state;
    APP_STATES  clientState;
    APP_STATES  serverState;
    TCP_SOCKET  tcpClientSocket;
    TCP_SOCKET  tcpServerSocket;
    UDP_SOCKET  udpClientSocket;
    UDP_SOCKET  udpServerSocket;
    char *      host;
    char *      path;
    uint16_t    tcpPort;
    uint16_t    udpPort;
    uint64_t    mTimeOut;
} APP_DATA;

typedef struct
{
    uint8_t ucStartByte;
    uint16_t uiCommand;
    uint8_t ucStopByte;
}tcpipRecvData;

typedef struct
{
    uint16_t uiInPtr;
    uint16_t uiOutPtr;
    uint16_t uiProcessCntr;
}tcpipEventPtr;

typedef struct
{
    tcpipEventPtr sTcpipEvents;
    tcpipRecvData sData[MAX_LEN_ETH];
}tcpipEventData;

typedef struct
{
    uint16_t uiIndex;
    uint8_t ucCommand[MAX_LEN_COPLEY_CMD];
    //uint16_t uiCmdLen;
}copleyCmdTable;
void APP_Initialize ( void );
void APP_Tasks ( void );
void mainActionSMHandler(void);
void mainMotorSMHandler(void);
void mainLoraSMHandler(void);
void mainGsmSMHandler(void);
//void rxBuffMng(void);
void copleyUartTxString(uint8_t *ucString);
void initAll ();
void _APP_ServerTasks();
void _APP_LoraTasks(void);
void _APP_GsmTasks(void);
void _APP_CopleyTasks(void);
void _APP_WifiTasks(void);
void _APP_EepromTasks(void);
void _APP_Rs485Task(void);
void _APP_Continuous_Monitor();
extern APP_DATA appData;
#endif /* _APP_H */
/*******************************************************************************
 End of File
 */

