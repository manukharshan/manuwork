/* 
 * File:   commandInterface.c
 * Author: Manu
 *
 * Created on 10 April, 2015, 4:09 PM
 */
#include <string.h>
#include <stdbool.h>
#include "wifiuartHandler.h"
#include "commandSetup.h"

#define WIFI_TX_BUFFER_SIZE 150

static uint8_t ucInWriteBufferIndex2 = 0;
static uint8_t ucInReadBufferIndex2 = 0;
static uint8_t ucOutWriteBufferIndex2 = 0;
static uint8_t ucOutReadBufferIndex2 = 0;
static uint8_t ucCmdWriteBufferIndex2 = 0;
static uint8_t ucCmdReadBufferIndex2 = 0;
static uint8_t ucCmdWriteBufferSubIndex2 = 0;

static int8_t cTxBuffer2[WIFI_TX_BUFFER_SIZE];

static wifiEventData gsReceiveEventData;

uint8_t gucUartBufRx2[WIFI_RX_BUF_SIZE];
uint16_t guiUReadI2 = 0;
int8_t* receivedData2;
uint8_t command2[4];
uint8_t arg2[40];

void wifirxBuffMng()
{
    gucUartBufRx2[guiUReadI2] = DRV_USART3_ReadByte();
    if(gucUartBufRx2[guiUReadI2] == '\r')
    {
        postwifiReceiveEvent((uint8_t *)&gucUartBufRx2[0]);
        guiUReadI2 = 0;
    }
    else
    {
        if (gucUartBufRx2[guiUReadI2] != '\0')
        {
            guiUReadI2 ++;
        }
    }
    if (guiUReadI2 >= WIFI_RX_BUF_SIZE)
    {
        guiUReadI2 = 0;
    }
}

void postwifiReceiveEvent(uint8_t *Response)
{
    uint8_t index = 0;
    while(*Response != '\r')
    {
        gsReceiveEventData.sData[gsReceiveEventData.sEventPtr.uiInPtr].ucData[index] = *Response;
        index ++;
        Response ++;
    }
    gsReceiveEventData.sData[gsReceiveEventData.sEventPtr.uiInPtr].ucData[index] = *Response;
    gsReceiveEventData.sEventPtr.uiInPtr ++;
    index = 0;
    gsReceiveEventData.sEventPtr.uiProcessCtr++;
    if(gsReceiveEventData.sEventPtr.uiInPtr >= MAX_EVENTS)
    {
        gsReceiveEventData.sEventPtr.uiInPtr = 0;
    } 
}

bool getwifiReceiveEvent(uint8_t **ucRecvData)
{
    bool bRetVal = true;
    if (gsReceiveEventData.sEventPtr.uiProcessCtr > 0)
    {
       *ucRecvData = &gsReceiveEventData.sData[gsReceiveEventData.sEventPtr.uiOutPtr].ucData[0];
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}

void disposewifiRecvEvent()
{
    gsReceiveEventData.sEventPtr.uiOutPtr ++;
    if (gsReceiveEventData.sEventPtr.uiOutPtr >= MAX_EVENTS)
    {
        gsReceiveEventData.sEventPtr.uiOutPtr = 0;
    }
    gsReceiveEventData.sEventPtr.uiProcessCtr --;
}

void wifiTransmitDataBuffer(int8_t cTxData)
{
    cTxBuffer2[ucOutWriteBufferIndex2] = cTxData;
    ucOutWriteBufferIndex2 ++;
    if (ucOutWriteBufferIndex2 >= WIFI_TX_BUFFER_SIZE)
    {
        ucOutWriteBufferIndex2 = 0;
    }
    if (ucOutWriteBufferIndex2 == ucOutReadBufferIndex2)
    {
        /*Send Tx Buffer Overflow Err Msg*/
        //errorhandle(TX_BUFFER_OVERFLOW_ERROR);

    }
}

void wifiSendCmdData(int8_t csStringReceived[],int8_t length)
{
  uint8_t uLoopIndex;
  for (uLoopIndex = 0; uLoopIndex < length; uLoopIndex ++)
  {
      wifiTransmitDataBuffer(csStringReceived[uLoopIndex]);
  }
}

void wifiTransmitData(void)
{
    if (ucOutWriteBufferIndex2 != ucOutReadBufferIndex2)
    {
        DRV_USART3_WriteByte(cTxBuffer2[ucOutReadBufferIndex2]);
        ucOutReadBufferIndex2 ++;
        if(ucOutReadBufferIndex2 >= WIFI_TX_BUFFER_SIZE)
        {
            ucOutReadBufferIndex2 = 0;
        }
    }
}

void processWifiData(void)
{
    int i = 0;
    if(getwifiReceiveEvent(&receivedData2))
    {
        memcpy(&command2[0],receivedData2,3);
        while(*receivedData2 != '\r')
        {
          arg2[i++] = *receivedData2;
          receivedData2++;
        }
        arg2[i]='\0';
        command2[3]='\0';
        //command purse function
        commandParse(&command2[0],&arg2[0],WIFI_TCP);
        disposewifiRecvEvent();
    }
}

