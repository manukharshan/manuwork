/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include "tcpip/src/tcpip_private.h"
#include "app.h"
#include "copleyreceivehandler.h"
#include "copleytransmithandler.h"
#include "tcpip/tcpip.h"
#include "copleySmHandler.h"
#include "events.h"
#include "app_commands.h"
#include "tcpip/tcpip_common_ports.h"
#include "tcpiphandler.h"
#include "timerfunctions.h"
#include"i2cinterface.h"
#include "lorauarthandler.h"
#include "gsmuarthandler.h"
#include "wifiuartHandler.h"
#include "loraSmHandler.h"
#include "gsmSmHandler.h"
#include "motorSmHandler.h"
#include "actionHandler.h"
#include "copleySmHandler.h"
#include "debuguarthandler.h"
#include "datatypeconversion.h"
#include "continuousMonitor.h"
#include "loraModem.h"
#include "gsmModem.h"
#include "analog.h"
#include "rs485Handler.h"
#include "userConfig.h"

bool value;
//int eepromWriteCount = 0;
extern uint8_t messagePacket[60];

//#include "tcpip_manager_control.h"
#define SERVER_PORT 60001
static sysEvents gsSysMainEvents;
//static copleySmStates geCopleyCurState = COPLEY_SM_IDLE;
bool gbEventHandle;
static int8_t gucpServerIp[15];
uint8_t discoverAckBuff[15];
uint8_t *dta,*dta1;
static int8_t port[6];

/*state machine related variables*/
static motorSmStates geMotorCurstate = MOTOR_SM_IDLE;
static motorsysEvents gsmotorsysEvents;

static actionSmStates geActionCurrentSmStates = ACTION_SM_IDLE;
actionsysEvents gsactionsysEvents;

/* State machine related variables*/
static loraSmStates geLoraCurState = LORA_SM_IDEAL;
lorasysEvents gsLorasysEvents;  
static bool gbEventhandled = false;
extern sConfigflag gSconfigflag;

uint8_t discoverPack[64]="VACTS_8001:192.168.100.115:60001\r";
uint16_t guiDiscoverCmdLen = 35;
static int8_t devId[8] = {'C','T','B','O','X','0','1','\0'};

/*gsm state machine related variable*/
static gsmSmStates geGsmCurState = GSM_SM_IDEAL;
gsmsysEvents gsGsmsysEvents;
static bool disconflag = false;
extern bool milliSecondflag;
bool powerstartflag = true;


int32_t _APP_ParseUrl(char *uri, char **host, char **path, uint16_t * port);
int8_t _APP_PumpDNS(const char * hostname, IPV4_ADDR *ipv4Addr);
#define MAX_BUF_LEN_ETH 25
#define MAX_BUF_LEN_UART 25
#define MAX_BUF_SUB_LEN_ETH 25
#define MAX_CMD_LEN_ETH 4
#define MAX_COMMAND 84

tcpipEventData gsTcpipRecv;
bool gbUDPServerOpenStatus;
static int8_t gucTemp[15];
uint8_t data[] = "abc\r";
APP_DATA appData;
SYSTEM_OBJECTS sysObj;
bool writeflag = true;
char writePacket[60] = "manukharshan";

uint8_t gucTempCounter  = 0;
void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    appData.clientState = TCPIP_WAIT_START;
    //appData.serverState = APP_UDP_WAITING_FOR_TANSMIT;
    appData.serverState = APP_TCPIP_OPENING_SERVER;
    startTimer(TCPTIMER,2000U);
//    startTimer(STATUSLED,3000U);
    appData.tcpPort = 5000;
    appData.udpPort = 60000;
    initI2cState();
    powerstartflag = true;
    PORTAbits.RA14 = 0;
    RS485PIN = disable;
}

void i2cHandler(void)
{
 //   uint8_t *ack = (uint8_t *)"ok\r";
    uint8_t recv[I2C_BUFFER_SIZE] = {0};
    if (isI2cDataAvailableToWrite())
    {
        if(waitI2cWriteCompleteToEeprom())
        {
//             setEepromReadAddress(COUTDATA_ADDR);
//             initiateI2cRead();
            //sendResposneViaUDP(ack, 3);
        }
    }
    else if (isI2cDataAvailableToRead())
    {
        if (isI2cGetDataReadyFromEeprom())
        {
//            i2cArrayGet(recv);
//            writeflag = true;
            //duSendData1(recv,strlen(recv));
            //sendResposneViaUDP(recv, 3);
        }
    }
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    //_APP_ClientTasks();

   mainActionSMHandler();
  _APP_ServerTasks();
  _APP_CopleyTasks();
#if LORAENABLE
  _APP_LoraTasks();
#endif  
  _APP_WifiTasks();
   ADCProcessValues();
  _APP_EepromTasks();
#if GSMENABLE   
   _APP_GsmTasks();
#endif   
   duTransmitData1();
   _APP_Continuous_Monitor();
   _APP_Rs485Task();
//   if(writeflag == true)
//   {
//    I2cArrayPut(&writePacket[0],COUTDATA_ADDR);
//    setEepromReadAddress(COUTDATA_ADDR);
//    writeflag = false;
//   }
   //while(!waitI2cWriteCompleteToEeprom());
}

void _APP_Continuous_Monitor()
{
    
    if(milliSecondflag)
    {
        static int secCount = 0;
       _APP_EepromTasks();  
       taskContinuousMonitorMotorParameters();
       milliSecondflag = false;
       rs485TransmitDataComplete();
//       eepromWriteCount++;
//       if(3000 <= eepromWriteCount)
//       {
//           assembleEEpromPacket(EEPROMWRITECURRENTCOUNT,&messagePacket[0]);
//           eepromWriteCount = 0;
//       }
       secCount++;
       if(secCount == 1000)
       {
           //rs485SendData("rs485 testing",strlen("rs485 testing"));
           secCount = 0;
       }
       
    }
}

void _APP_GsmTasks(void)
{
    mainGsmSMHandler();
    guProcessRecieveDataBuffer();
    guTransmitData();  
}

void _APP_CopleyTasks(void)
{
    mainMotorSMHandler();
    copleyTransmitHandle();
}

void _APP_WifiTasks(void)
{
    wifiTransmitData();
    processWifiData();
}

void _APP_EepromTasks(void)
{
    i2cHandler();
}

void _APP_Rs485Task(void)
{
    rs485TransmitDataInitilise();
}

void _APP_LoraTasks(void)
{
    mainLoraSMHandler();
    luProcessRecieveDataBuffer();
    luTransmitData();
}



void mainActionSMHandler(void)
{
    if(ACTION_SM_IDLE == geActionCurrentSmStates)
    {
        if(getActionEvent(&gsactionsysEvents.geActionEvent))
        {
            geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
            disposeActionEvent();
        }
        
    }
    if(ACTION_SM_HOME == geActionCurrentSmStates)
    {
            geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
    }
    if(ACTION_SM_ROTATE == geActionCurrentSmStates)
    {
            geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
    }
    if(ACTION_SM_VALVEOPEN == geActionCurrentSmStates)
    {
            geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
    }
    if(ACTION_SM_VALVECLOSE == geActionCurrentSmStates)
    {
         geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
    }
    if(ACTION_SM_STOPMOTOR == geActionCurrentSmStates)
    {
        geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
    }
    if(ACTION_SM_HARDSTOPHOME == geActionCurrentSmStates)
    {
       geActionCurrentSmStates = actionSmhandler(&gsactionsysEvents,&gbEventHandle);
    }
}

void mainMotorSMHandler(void)
{
    if(MOTOR_SM_IDLE == geMotorCurstate)
    {
        if (getCopleyReceiveEvent(&gsmotorsysEvents.sCopleyData))
        {            
            gsmotorsysEvents.eTypeEvent = checkCopleyRecvEventType(gsmotorsysEvents.sCopleyData);
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeCopleyRecvEvent();
        }
        else if (getMotorEvent(&gsmotorsysEvents.eTypeMotorEvent))
        {
            gsmotorsysEvents.eTypeEvent = MOTORCONTROL_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeMotorEvent();
        }
        else if (getTimeOutOccur(MOTORTIMER))
        {
            gsmotorsysEvents.eTypeEvent = TIME_OUT_EVENT;  
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);

        }
        else
        {
            gsmotorsysEvents.eTypeEvent = INVALID_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
        }
        
    }
    if(MOTOR_SM_CONFIG == geMotorCurstate)
    {
        if (getCopleyReceiveEvent(&gsmotorsysEvents.sCopleyData))
        {            
            gsmotorsysEvents.eTypeEvent = checkCopleyRecvEventType(gsmotorsysEvents.sCopleyData);
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeCopleyRecvEvent();
        }
        else if (getTimeOutOccur(MOTORTIMER))
        {
            gsmotorsysEvents.eTypeEvent = TIME_OUT_EVENT;  
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);

        }
        else
        {
            gsmotorsysEvents.eTypeEvent = INVALID_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
        }
    }
    if(MOTOR_SM_HOMECONFIG == geMotorCurstate)
    {
        if (getCopleyReceiveEvent(&gsmotorsysEvents.sCopleyData))
        {            
            gsmotorsysEvents.eTypeEvent = checkCopleyRecvEventType(gsmotorsysEvents.sCopleyData);
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeCopleyRecvEvent();
        }
        else if (getTimeOutOccur(MOTORTIMER))
        {
            gsmotorsysEvents.eTypeEvent = TIME_OUT_EVENT;  
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);

        }
        else
        {
            gsmotorsysEvents.eTypeEvent = INVALID_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
        }
    }
    if(MOTOR_START_MOV == geMotorCurstate)
    {
        if (getCopleyReceiveEvent(&gsmotorsysEvents.sCopleyData))
        {            
            gsmotorsysEvents.eTypeEvent = checkCopleyRecvEventType(gsmotorsysEvents.sCopleyData);
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeCopleyRecvEvent();
        }
        else if (getTimeOutOccur(MOTORTIMER))
        {
            gsmotorsysEvents.eTypeEvent = TIME_OUT_EVENT;  
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);

        }
        else
        {
            gsmotorsysEvents.eTypeEvent = INVALID_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
        }  
    }
    if(MOTOR_STOP_MOV == geMotorCurstate)
    {
        if (getCopleyReceiveEvent(&gsmotorsysEvents.sCopleyData))
        {            
            gsmotorsysEvents.eTypeEvent = checkCopleyRecvEventType(gsmotorsysEvents.sCopleyData);
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeCopleyRecvEvent();
        }
        else if (getTimeOutOccur(MOTORTIMER))
        {
            gsmotorsysEvents.eTypeEvent = TIME_OUT_EVENT;  
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);

        }
        else
        {
            gsmotorsysEvents.eTypeEvent = INVALID_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
        }  
        
    }
    if(MOTOR_HOMING == geMotorCurstate)
    {
        if (getCopleyReceiveEvent(&gsmotorsysEvents.sCopleyData))
        {            
            gsmotorsysEvents.eTypeEvent = checkCopleyRecvEventType(gsmotorsysEvents.sCopleyData);
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
            disposeCopleyRecvEvent();
        }
        else if (getTimeOutOccur(MOTORTIMER))
        {
            gsmotorsysEvents.eTypeEvent = TIME_OUT_EVENT;  
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);

        }
        else
        {
            gsmotorsysEvents.eTypeEvent = INVALID_EVENT;
            geMotorCurstate = motorSmhandler(&gsmotorsysEvents,&gbEventhandled);
        } 
    }
    
}

void mainLoraSMHandler(void)
{
    if(LORA_SM_IDEAL == geLoraCurState)
    {
        if(getLoraSerialReceiveEvent(&gsLorasysEvents.sLoraData))
        {
            gsLorasysEvents.eLoraTypeEvent = lmProcessReceiveEvent(gsLorasysEvents.sLoraData);
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
            disposeLoraSerialReceiveEvent();
        }
        else if(getTimeOutOccur(LORATIMER))
        {
            gsLorasysEvents.eLoraTypeEvent = LORA_TIME_OUT;
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
        }
        else
        {
            gsLorasysEvents.eLoraTypeEvent = LORA_NO_ANSWER;
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
        }
    }
    if(LORA_SM_CONFIG == geLoraCurState)
    {
       if(getLoraSerialReceiveEvent(&gsLorasysEvents.sLoraData))
       {
               gsLorasysEvents.eLoraTypeEvent = lmProcessReceiveEvent(gsLorasysEvents.sLoraData);
               //duSendData1(gsLorasysEvents.sLoraData,strlen(gsLorasysEvents.sLoraData));
               geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
               disposeLoraSerialReceiveEvent();
        }
       else if(getTimeOutOccur(LORATIMER))
        {
              gsLorasysEvents.eLoraTypeEvent = LORA_TIME_OUT;
              //duSendData1(gsLorasysEvents.sLoraData,strlen(gsLorasysEvents.sLoraData));
              geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
        }
       else if(gSconfigflag.eloraconflag == LORA_NOT_CONFIGURED)
        {
            gsLorasysEvents.eLoraTypeEvent = LORA_NO_ANSWER;
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
        }
    }
    if(LORA_SM_TRANSMIT == geLoraCurState)
    {
        if(getLoraSerialReceiveEvent(&gsLorasysEvents.sLoraData))
        {
            gsLorasysEvents.eLoraTypeEvent = lmProcessReceiveEvent(gsLorasysEvents.sLoraData);
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
            disposeLoraSerialReceiveEvent();
        }
        else if(getTimeOutOccur(LORATIMER))
        {
            gsLorasysEvents.eLoraTypeEvent = LORA_TIME_OUT;
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
        }
        else if(gSconfigflag.eloraconflag == LORA_CONFIGURED)
        {
            gsLorasysEvents.eLoraTypeEvent = LORA_NO_ANSWER;
            geLoraCurState = loraSmhandler(&gsLorasysEvents,&gbEventhandled);
        }
    }
}

void mainGsmSMHandler(void)
{
    if(GSM_SM_IDEAL == geGsmCurState)
    {
        if(getGsmSerialReceiveEvent(&gsGsmsysEvents.sGsmData))
        {
            gsGsmsysEvents.eGsmTypeEvent = gsmProcessReceiveEvent(gsGsmsysEvents.sGsmData);
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
            disposeGsmSerialReceiveEvent();
        }
        else if(getTimeOutOccur(GSMTIMER))
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_TIME_OUT;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
        else
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_NO_ANSWER;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
    }
    if(GSM_SM_CONFIG == geGsmCurState)
    {
        if(getGsmSerialReceiveEvent(&gsGsmsysEvents.sGsmData))
        {
            gsGsmsysEvents.eGsmTypeEvent = gsmProcessReceiveEvent(gsGsmsysEvents.sGsmData);
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
            disposeGsmSerialReceiveEvent();
        }
        else if(getTimeOutOccur(GSMTIMER))
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_TIME_OUT;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
        else if(GSM_NOT_CONFIGURED == gSconfigflag.egsmconfigflag)
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_NO_ANSWER;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
    }
    if(GSM_SM_MESGREAD == geGsmCurState)
    {
        if(getGsmSerialReceiveEvent(&gsGsmsysEvents.sGsmData))
        {
            gsGsmsysEvents.eGsmTypeEvent = gsmProcessReceiveEvent(gsGsmsysEvents.sGsmData);
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
            disposeGsmSerialReceiveEvent();
        }
        else if(getTimeOutOccur(GSMTIMER))
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_TIME_OUT;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
        else if(GSM_CONFIGURED == gSconfigflag.egsmconfigflag)
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_NO_ANSWER;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
    }
    if(GSM_SM_MSGTRANMIT == geGsmCurState)
    {
        if(getGsmSerialReceiveEvent(&gsGsmsysEvents.sGsmData))
        {
            gsGsmsysEvents.eGsmTypeEvent = gsmProcessReceiveEvent(gsGsmsysEvents.sGsmData);
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
            disposeGsmSerialReceiveEvent();
        }
        else if(getTimeOutOccur(GSMTIMER))
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_TIME_OUT;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
        else if(GSM_CONFIGURED == gSconfigflag.egsmconfigflag)
        {
            gsGsmsysEvents.eGsmTypeEvent = GSM_NO_ANSWER;
            geGsmCurState = gsmSmhandler(&gsGsmsysEvents,&gbEventhandled);
        }
    }
    
}


void _APP_ServerTasks()
{
    uint8_t ipAddr[16];
    uint16_t uiPortNum;
    uint16_t i = 0,j = 0;
    switch(appData.serverState)
    {
        case APP_UDP_OPENING_SERVER:
        {
            sendResposneViaUDP((uint8_t *)"SW_Ver:ETH_DEV_29_JAN_2016_R03",30);
            appData.serverState = APP_UDP_WAITING_FOR_TANSMIT;
            gbUDPServerOpenStatus = true;
            startTimer(TCPTIMER,2000U);
        }
        break;
        case APP_UDP_WAITING_FOR_TANSMIT:
        {
            if(true == getTimeOutOccur(TCPTIMER))
            {
                stopTimer(TCPTIMER);
                appData.serverState = APP_UDP_TRANSMIT;
            }
            
           if (TCPIP_TCP_IsConnected(appData.tcpServerSocket)) 
            {
                    
                appData.serverState = APP_TCPIP_WAIT_FOR_CONNECTION;
                stopTimer(TCPTIMER);
            }
        }
        break;
        case APP_UDP_TRANSMIT:
        {   
            sendResposneViaUDP((uint8_t *)discoverPack,guiDiscoverCmdLen);
              appData.serverState = APP_UDP_WAITING_FOR_TANSMIT;
              startTimer(TCPTIMER,1000U);
//            }
//            else
//            {
//              appData.serverState = APP_TCPIP_OPENING_SERVER;  
//            }
           if (TCPIP_TCP_IsConnected(appData.tcpServerSocket)) 
            {
                    appData.serverState = APP_TCPIP_WAIT_FOR_CONNECTION; 
                    stopTimer(TCPTIMER);
            }
        }
        break;
           
        case APP_TCPIP_OPENING_SERVER:
        {
            getTcpPort(port);
            stringToUnsignedInt(port,DIGIT_5,&uiPortNum);
            appData.tcpServerSocket = TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE_IPV4, uiPortNum, 0);
            if (appData.tcpServerSocket == INVALID_SOCKET)
            {
                return;
            }
            else
            appData.serverState = APP_UDP_TRANSMIT;
        }
        break;
        case APP_TCPIP_WAIT_FOR_CONNECTION:
        {
            if (!TCPIP_TCP_IsConnected(appData.tcpServerSocket))
            {
                appData.serverState = APP_TCPIP_OPENING_SERVER;
                break;
            }
            else
            {
                 tcpipHandlerTask();
                 processTcpipData();
                //appData.serverState = TCPIP_WAIT_FOR_CONNECTION;
                appData.serverState = APP_TCPIP_WAIT_FOR_CONNECTION;
                //SYS_CONSOLE_MESSAGE("Server Received a connection\r\n");
            }
        }
        break;
    }    
}


void initAll(void)
{
    gsTcpipRecv.sTcpipEvents.uiInPtr = 0;
    gsTcpipRecv.sTcpipEvents.uiOutPtr = 0;
    gsTcpipRecv.sTcpipEvents.uiProcessCntr = 0;
    initCopleyTransmitEvent();
    //setConnectionStatus(0U);
    initTCPHandler ();
    initI2cState();
    
}

/*******************************************************************************
 End of File
 */