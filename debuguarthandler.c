
#include "debuguarthandler.h"

#define TX_BUFFER_SIZE1 200U
#define RX_BUFFER_SIZE1 50U

static int8_t cTxBuffer1[TX_BUFFER_SIZE1];
//static int8_t cRxBuffer1[RX_BUFFER_SIZE1];
//
//static uint8_t ucInWriteBufferIndex1 = 0;
//static uint8_t ucInReadBufferIndex1 = 0;

static unsigned char ucOutWriteBufferIndex1 = 0;
static unsigned char ucOutReadBufferIndex1 = 0;

void duTransmitDataBuffer1(int8_t cTxData)
{
    cTxBuffer1[ucOutWriteBufferIndex1] = cTxData;
    ucOutWriteBufferIndex1 ++;
    if (ucOutWriteBufferIndex1 >= TX_BUFFER_SIZE1)
    {
        ucOutWriteBufferIndex1 = 0;
    }
    if (ucOutWriteBufferIndex1 == ucOutReadBufferIndex1)
    {
        /*Send Tx Buffer Overflow Err Msg*/
        //errorhandle(TX_BUFFER_OVERFLOW_ERROR);

    }
}

void duSendData1(char* csStringReceived,uint length)
{
  uint8_t uLoopIndex;
  for (uLoopIndex = 0; uLoopIndex < length; uLoopIndex ++)
  {
      duTransmitDataBuffer1(csStringReceived[uLoopIndex]);
  }
}

void duTransmitData1(void)
{
    if (ucOutWriteBufferIndex1 != ucOutReadBufferIndex1)
    {
        //uart6WriteByte(cTxBuffer1[ucOutReadBufferIndex1]);
        DRV_USART5_WriteByte(cTxBuffer1[ucOutReadBufferIndex1]);
        //DRV_USART0_WriteByte(cTxBuffer[ucOutReadBufferIndex]);	
        ucOutReadBufferIndex1 ++;
        if(ucOutReadBufferIndex1 >= TX_BUFFER_SIZE1)
        {
            ucOutReadBufferIndex1 = 0;
        }
    }
}
