/* 
 * File:   lorauarthandler.c
 * Author: Manu K Harshan
 *
 * Created on 12 January, 2017, 11:56 AM
 */
#include "loraevents.h"
//#include "uart_handler.h"
#include "lorauarthandler.h"
#include "debuguarthandler.h"
//#include "events.h"

#define TX_BUFFER_SIZE 50U
#define RX_BUFFER_SIZE 50U
#define MAX_RECEIVE_COMMAND_LENGTH 100U

static uint8_t ucInWriteBufferIndex = 0;
static uint8_t ucInReadBufferIndex = 0;

static int8_t cTxBuffer[TX_BUFFER_SIZE];
static int8_t cRxBuffer[RX_BUFFER_SIZE];

static int8_t cRxCmdBuffer [MAX_RECEIVE_COMMAND_LENGTH];
static uint8_t ucCmdWriteBufferIndex = 0;
//static uint8_t ucCmdReadBufferIndex = 0;

static unsigned char ucOutWriteBufferIndex = 0;
static unsigned char ucOutReadBufferIndex = 0;

static loraEventdata loraReceiveEventdata;
static loraEventdata loraSendEventdata;

void luReceiveDataBuffer(void)
{ 
     cRxBuffer[ucInWriteBufferIndex++] = DRV_USART0_ReadByte();
       if (ucInWriteBufferIndex >= RX_BUFFER_SIZE)
        {
            ucInWriteBufferIndex = 0;
        }
        if (ucInWriteBufferIndex == ucInReadBufferIndex)
        {
            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
            /*Send Rx Buffer Overflow Err Message*/
        }    
}

void luProcessRecieveDataBuffer(void)
{
  while (ucInWriteBufferIndex != ucInReadBufferIndex)
  {     
      cRxCmdBuffer[ucCmdWriteBufferIndex]= cRxBuffer[ucInReadBufferIndex];
      ucCmdWriteBufferIndex++;
      if(ucCmdWriteBufferIndex >= MAX_RECEIVE_COMMAND_LENGTH)
      {
          ucCmdWriteBufferIndex = 0;
      }
      if (cRxBuffer[ucInReadBufferIndex] == '\n')
      {
         ucCmdWriteBufferIndex = 0;
         postLoraSerialReceiveEvent((unsigned char*)&cRxCmdBuffer[0]);
         //duSendData1(&cRxCmdBuffer[0] ,strlen(&cRxCmdBuffer[0]));
      }
    ucInReadBufferIndex ++;
    if (ucInReadBufferIndex >= RX_BUFFER_SIZE)
    {
        ucInReadBufferIndex = 0;
    }
  }  
}

void luTransmitDataBuffer(int8_t cTxData)
{
    cTxBuffer[ucOutWriteBufferIndex] = cTxData;
    ucOutWriteBufferIndex ++;
    if (ucOutWriteBufferIndex >= TX_BUFFER_SIZE)
    {
        ucOutWriteBufferIndex = 0;
    }
    if (ucOutWriteBufferIndex == ucOutReadBufferIndex)
    {
        /*Send Tx Buffer Overflow Err Msg*/
        //errorhandle(TX_BUFFER_OVERFLOW_ERROR);

    }
}

void luSendData(char* csStringReceived,uint length)
{
  uint8_t uLoopIndex;
  for (uLoopIndex = 0; uLoopIndex < length; uLoopIndex ++)
  {
      luTransmitDataBuffer(csStringReceived[uLoopIndex]);
  }
  //duSendData1(csStringReceived,strlen(csStringReceived));
}

void luTransmitData(void)
{
    if (ucOutWriteBufferIndex != ucOutReadBufferIndex)
    {
        DRV_USART0_WriteByte(cTxBuffer[ucOutReadBufferIndex]);
        //uart6WriteByte(cTxBuffer[ucOutReadBufferIndex]);
        //DRV_USART5_WriteByte(cTxBuffer[ucOutReadBufferIndex]);	
        ucOutReadBufferIndex ++;
        if(ucOutReadBufferIndex >= TX_BUFFER_SIZE)
        {
            ucOutReadBufferIndex = 0;
        }
    }
}
    
void postLoraSerialReceiveEvent(unsigned char* loraResponseData)
{
    unsigned char index = 0;
    while(*loraResponseData != '\n')
    {
        loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[index++] = *loraResponseData;
        loraResponseData++;
    }
    //duSendData1(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0] ,strlen(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]));
    loraReceiveEventdata.sloraeventptr.uiInPtr++;
    loraReceiveEventdata.sloraeventptr.uiProcessCtr++;
    if(loraReceiveEventdata.sloraeventptr.uiInPtr >= MAX_LORA_EVENTS)
    {
        loraReceiveEventdata.sloraeventptr.uiInPtr = 0;
    }
}

bool getLoraSerialReceiveEvent(unsigned char** ucRecevData)
{
    bool bRetval = false;
    if(loraReceiveEventdata.sloraeventptr.uiProcessCtr > 0)
    {
        *ucRecevData = &loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiOutPtr].loraData[0];
        //duSendData1(&(loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]) ,strlen(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]));
        //duSendData1(*ucRecevData,strlen(*ucRecevData));
        bRetval = true;
    }
    return bRetval;
}

void disposeLoraSerialReceiveEvent(void)
{
    loraReceiveEventdata.sloraeventptr.uiOutPtr++;
    if(loraReceiveEventdata.sloraeventptr.uiOutPtr >= MAX_LORA_EVENTS)
    {
        loraReceiveEventdata.sloraeventptr.uiOutPtr = 0;
    }
    loraReceiveEventdata.sloraeventptr.uiProcessCtr--;
}

void postLoraSendEvent(int8_t* loraSendData)
{
    unsigned char index = 0;
    while(*loraSendData != '\0')
    {
        loraSendEventdata.sloraData[loraSendEventdata.sloraeventptr.uiInPtr].loraData[index++] = *loraSendData;
        loraSendData++;
    }
    loraSendEventdata.sloraData[loraSendEventdata.sloraeventptr.uiInPtr].loraData[index] = '\0';
    loraSendEventdata.sloraeventptr.uiInPtr++;
    loraSendEventdata.sloraeventptr.uiProcessCtr++;
    if(loraSendEventdata.sloraeventptr.uiInPtr >= MAX_LORA_EVENTS)
    {
        loraSendEventdata.sloraeventptr.uiInPtr = 0;
    }
}

bool getLoraSendEvent(unsigned char** ucSendData)
{
    bool bRetval = false;
    if(loraSendEventdata.sloraeventptr.uiProcessCtr > 0)
    {
        *ucSendData = &loraSendEventdata.sloraData[loraSendEventdata.sloraeventptr.uiOutPtr].loraData[0];
        //duSendData1(&(loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]) ,strlen(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]));
        //duSendData1(*ucRecevData,strlen(*ucRecevData));
        bRetval = true;
    }
    return bRetval;
}

void disposeLoraSendEvent(void)
{
    loraSendEventdata.sloraeventptr.uiOutPtr++;
    if(loraSendEventdata.sloraeventptr.uiOutPtr >= MAX_LORA_EVENTS)
    {
        loraSendEventdata.sloraeventptr.uiOutPtr = 0;
    }
    loraSendEventdata.sloraeventptr.uiProcessCtr--;
}