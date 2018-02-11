/* 
 * File:   lorauarthandler.c
 * Author: Manu K Harshan
 *
 * Created on 09 february, 2017, 11:56 AM
 */
#include "gsmevents.h"
#include "gsmuarthandler.h"
#include "debuguarthandler.h"

#define GSM_TX_BUFFER_SIZE 50U
#define GSM_RX_BUFFER_SIZE 300U
#define GSM_MAX_RECEIVE_COMMAND_LENGTH 100U

static uint8_t ucInWriteBufferIndex1 = 0;
static uint8_t ucInReadBufferIndex1 = 0;

static int8_t cTxBuffer1[GSM_TX_BUFFER_SIZE];
static int8_t cRxBuffer1[GSM_RX_BUFFER_SIZE];

static int8_t cRxCmdBuffer1 [GSM_MAX_RECEIVE_COMMAND_LENGTH];
static uint8_t ucCmdWriteBufferIndex1 = 0;
//static uint8_t ucCmdReadBufferIndex = 0;

static unsigned char ucOutWriteBufferIndex1 = 0;
static unsigned char ucOutReadBufferIndex1 = 0;

static gsmEventdata gsmReceiveEventdata;
static gsmEventdata gsmSendEventdata;


void guReceiveDataBuffer(void)
{ 
     cRxBuffer1[ucInWriteBufferIndex1++] = DRV_USART4_ReadByte();
//     ucInWriteBufferIndex ++;
       if (ucInWriteBufferIndex1 >= GSM_RX_BUFFER_SIZE)
        {
            ucInWriteBufferIndex1 = 0;
        }
        if (ucInWriteBufferIndex1 == ucInReadBufferIndex1)
        {
            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
            /*Send Rx Buffer Overflow Err Message*/
        }    
}

void guProcessRecieveDataBuffer(void)
{
  while (ucInWriteBufferIndex1 != ucInReadBufferIndex1)
  {     
      cRxCmdBuffer1[ucCmdWriteBufferIndex1]= cRxBuffer1[ucInReadBufferIndex1];
      ucCmdWriteBufferIndex1++;
      if(ucCmdWriteBufferIndex1 >= GSM_MAX_RECEIVE_COMMAND_LENGTH)
      {
          ucCmdWriteBufferIndex1 = 0;
      }
      if (cRxBuffer1[ucInReadBufferIndex1] == '\n')
      {
         ucCmdWriteBufferIndex1 = 0;
         postGsmSerialReceiveEvent((unsigned char*)&cRxCmdBuffer1[0]);
         //duSendData1(&cRxCmdBuffer[0] ,strlen(&cRxCmdBuffer[0]));
      }
      else if(cRxBuffer1[ucInReadBufferIndex1] == '>')
      {
          cRxCmdBuffer1[ucCmdWriteBufferIndex1] = '\r';
          ucCmdWriteBufferIndex1++;
          cRxCmdBuffer1[ucCmdWriteBufferIndex1] = '\n';
          postGsmSerialReceiveEvent((unsigned char*)&cRxCmdBuffer1[0]);
          ucCmdWriteBufferIndex1 = 0;
      }
    ucInReadBufferIndex1 ++;
    if (ucInReadBufferIndex1 >= GSM_RX_BUFFER_SIZE)
    {
        ucInReadBufferIndex1 = 0;
    }
  }  
}


void guTransmitDataBuffer(int8_t cTxData)
{
    cTxBuffer1[ucOutWriteBufferIndex1] = cTxData;
    ucOutWriteBufferIndex1 ++;
    if (ucOutWriteBufferIndex1 >= GSM_TX_BUFFER_SIZE)
    {
        ucOutWriteBufferIndex1 = 0;
    }
    if (ucOutWriteBufferIndex1 == ucOutReadBufferIndex1)
    {
        /*Send Tx Buffer Overflow Err Msg*/
        //errorhandle(TX_BUFFER_OVERFLOW_ERROR);

    }
}

void guSendData(char* csStringReceived,uint length)
{
  uint8_t uLoopIndex;
  for (uLoopIndex = 0; uLoopIndex < length; uLoopIndex ++)
  {
      guTransmitDataBuffer(csStringReceived[uLoopIndex]);
  }
  //duSendData1(csStringReceived,strlen(csStringReceived));
}

void guTransmitData(void)
{
    if (ucOutWriteBufferIndex1 != ucOutReadBufferIndex1)
    {
        DRV_USART4_WriteByte(cTxBuffer1[ucOutReadBufferIndex1]);
        //uart6WriteByte(cTxBuffer[ucOutReadBufferIndex]);
        //DRV_USART5_WriteByte(cTxBuffer[ucOutReadBufferIndex]);	
        ucOutReadBufferIndex1 ++;
        if(ucOutReadBufferIndex1 >= GSM_TX_BUFFER_SIZE)
        {
            ucOutReadBufferIndex1 = 0;
        }
    }
}
    
void postGsmSerialReceiveEvent(unsigned char* gsmResponseData)
{
    unsigned char index = 0;
    while(*gsmResponseData != '\n')
    {
        gsmReceiveEventdata.sgsmData[gsmReceiveEventdata.sgsmeventptr.uiInPtr].gsmData[index++] = *gsmResponseData;
        gsmResponseData++;
    }
    //duSendData1(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0] ,strlen(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]));
    gsmReceiveEventdata.sgsmeventptr.uiInPtr++;
    gsmReceiveEventdata.sgsmeventptr.uiProcessCtr++;
    if(gsmReceiveEventdata.sgsmeventptr.uiInPtr >= MAX_GSM_EVENTS)
    {
        gsmReceiveEventdata.sgsmeventptr.uiInPtr = 0;
    }
}

bool getGsmSerialReceiveEvent(unsigned char** ucRecevData)
{
    bool bRetval = false;
    if(gsmReceiveEventdata.sgsmeventptr.uiProcessCtr > 0)
    {
        *ucRecevData = &gsmReceiveEventdata.sgsmData[gsmReceiveEventdata.sgsmeventptr.uiOutPtr].gsmData[0];
        //duSendData1(&(loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]) ,strlen(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]));
        //duSendData1(*ucRecevData,strlen(*ucRecevData));
        bRetval = true;
    }
    return bRetval;
}

void disposeGsmSerialReceiveEvent(void)
{
    gsmReceiveEventdata.sgsmeventptr.uiOutPtr++;
    if(gsmReceiveEventdata.sgsmeventptr.uiOutPtr >= MAX_GSM_EVENTS)
    {
        gsmReceiveEventdata.sgsmeventptr.uiOutPtr = 0;
    }
    gsmReceiveEventdata.sgsmeventptr.uiProcessCtr--;
}

void postGsmSendEvent(int8_t* gsmSendData)
{
    unsigned char index = 0;
    while(*gsmSendData != '\0')
    {
        gsmSendEventdata.sgsmData[gsmSendEventdata.sgsmeventptr.uiInPtr].gsmData[index++] = *gsmSendData;
        gsmSendData++;
    }
    gsmSendEventdata.sgsmData[gsmSendEventdata.sgsmeventptr.uiInPtr].gsmData[index] = '\0';
    gsmSendEventdata.sgsmeventptr.uiInPtr++;
    gsmSendEventdata.sgsmeventptr.uiProcessCtr++;
    if(gsmSendEventdata.sgsmeventptr.uiInPtr >= MAX_GSM_EVENTS)
    {
        gsmSendEventdata.sgsmeventptr.uiInPtr = 0;
    }
}

bool getGsmSendEvent(unsigned char** ucSendData)
{
    bool bRetval = false;
    if(gsmSendEventdata.sgsmeventptr.uiProcessCtr > 0)
    {
        *ucSendData = &gsmSendEventdata.sgsmData[gsmSendEventdata.sgsmeventptr.uiOutPtr].gsmData[0];
        //duSendData1(&(loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]) ,strlen(&loraReceiveEventdata.sloraData[loraReceiveEventdata.sloraeventptr.uiInPtr].loraData[0]));
        //duSendData1(*ucRecevData,strlen(*ucRecevData));
        bRetval = true;
    }
    return bRetval;
}

void disposegsmSendEvent(void)
{
    gsmSendEventdata.sgsmeventptr.uiOutPtr++;
    if(gsmSendEventdata.sgsmeventptr.uiOutPtr >= MAX_GSM_EVENTS)
    {
        gsmSendEventdata.sgsmeventptr.uiOutPtr = 0;
    }
    gsmSendEventdata.sgsmeventptr.uiProcessCtr--;
}