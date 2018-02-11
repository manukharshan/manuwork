#include "copleyreceivehandler.h"
#include "copleySmHandler.h"
#include "events.h"
#include "system_config.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/int/plib_int.h"
#include "system_definitions.h"
#define UART_BUF_LEN 100
static CopleyEventData gsCopleyReceiveEventData;

uint8_t gucUartBufRx[MAX_COPLEY_CMD_LEN];
uint16_t guiUReadI = 0;
uint8_t copleymessage[30];

void rxBuffMng()
{
    gucUartBufRx[guiUReadI] = DRV_USART2_ReadByte();
    if(gucUartBufRx[guiUReadI] == '\r')
    {
        postCopleyReceiveEvent((uint8_t *)&gucUartBufRx[0]);
        guiUReadI = 0;
    }
    else
    {
        if (gucUartBufRx[guiUReadI] != '\0')
        {
            guiUReadI ++;
        }
    }
    if (guiUReadI >= MAX_COPLEY_CMD_LEN)
    {
        guiUReadI = 0;
    }
}

void postCopleyReceiveEvent(uint8_t *copleyResponse)
{
    uint8_t index = 0;
    while(*copleyResponse != '\r')
    {
        gsCopleyReceiveEventData.sCopleyData[gsCopleyReceiveEventData.sCopleyEventPtr.uiInPtr].ucCopleyData[index] = *copleyResponse;
        index ++;
        copleyResponse ++;
    }
    gsCopleyReceiveEventData.sCopleyData[gsCopleyReceiveEventData.sCopleyEventPtr.uiInPtr].ucCopleyData[index] = *copleyResponse;
    gsCopleyReceiveEventData.sCopleyEventPtr.uiInPtr ++;
    index = 0;
    gsCopleyReceiveEventData.sCopleyEventPtr.uiProcessCtr++;
    if(gsCopleyReceiveEventData.sCopleyEventPtr.uiInPtr >= MAX_EVENTS)
    {
        gsCopleyReceiveEventData.sCopleyEventPtr.uiInPtr = 0;
    } 
}

bool getCopleyReceiveEvent(uint8_t **ucRecvData)
{
    bool bRetVal = true;
    if (gsCopleyReceiveEventData.sCopleyEventPtr.uiProcessCtr > 0)
    {
       *ucRecvData = &gsCopleyReceiveEventData.sCopleyData[gsCopleyReceiveEventData.sCopleyEventPtr.uiOutPtr].ucCopleyData[0];
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}

EventType checkCopleyRecvEventType(uint8_t ucRecvData[])
{
    EventType eEvType;
    if (ucRecvData[0] == 'o' && ucRecvData[1] == 'k')
    {
        eEvType = COPLEY_RESPONSE;
    }
    else if (ucRecvData[0] == 'v')
    {
        copleyMessageextract(&ucRecvData[2]);
        eEvType = COPLEY_MESSAGE;
    }
    else
    {
        eEvType = INVALID_EVENT;
    }
    return eEvType;
}

void disposeCopleyRecvEvent()
{
    gsCopleyReceiveEventData.sCopleyEventPtr.uiOutPtr ++;
    if (gsCopleyReceiveEventData.sCopleyEventPtr.uiOutPtr >= MAX_EVENTS)
    {
        gsCopleyReceiveEventData.sCopleyEventPtr.uiOutPtr = 0;
    }
    gsCopleyReceiveEventData.sCopleyEventPtr.uiProcessCtr --;
}

void copleyMessageextract(uint8_t* copleyMessage)
{
    uint8_t i = 0;
    while(*copleyMessage != '\r')
    {
         copleymessage[i++] = *copleyMessage;
         copleyMessage++;
    }
    copleymessage[i] = '\0';
    
}

void getCopleyMessage(uint8_t* copleyMessage)
{
    strcpy(copleyMessage,copleymessage);
}