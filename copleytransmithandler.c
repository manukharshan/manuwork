#include "copleyreceivehandler.h"
#include "copleytransmithandler.h"
#include "copleySmHandler.h"
#include "events.h"
#include "system_config.h"
#include "peripheral/usart/plib_usart.h"
#include "peripheral/int/plib_int.h"
#include "system_definitions.h"
#include "copleycommandinterface.h"

static CopleyTxEvent gsCopleyTransmitEventData;

void initCopleyTransmitEvent()
{
    gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr = 0;
    gsCopleyTransmitEventData.sCopleyEventPtr.uiOutPtr = 0;
    gsCopleyTransmitEventData.sCopleyEventPtr.uiProcessCtr = 0U;
}



void SendCommandToCopley(eCommandToCopley ecmdtoCopley, uint8_t ucCmdData[])
{
  
  CopleyEvent scommandtoCopley;
  uint32_t ulIndex,ullengthCounter = 0;
  while (ullengthCounter < sCopleyCommandTable[ecmdtoCopley].uiCommandLength)
  {
      scommandtoCopley.ucCopleyData[ullengthCounter] = sCopleyCommandTable[ecmdtoCopley].ucCommandWord[ullengthCounter];
      // scommandtoCopley.ucCopleyData[1] = sCopleyCommandTable[ecmdtoCopley].ucCommandWord[1];
      ullengthCounter++;
  }
  ullengthCounter = 0;
  ulIndex = 0U;
  if(ucCmdData != NULL)
  {
    while((ucCmdData[ulIndex] != '\0') && (ulIndex < (MAX_COPLEY_MESG_SIZE - 3U)))
    {
        scommandtoCopley.ucCopleyData[ulIndex + (sCopleyCommandTable[ecmdtoCopley].uiCommandLength)] = ucCmdData[ulIndex];
        ulIndex++;
    }
  }
   scommandtoCopley.ucCopleyData[ulIndex + (sCopleyCommandTable[ecmdtoCopley].uiCommandLength)] = '\r';
   scommandtoCopley.ucCopleyData[ulIndex + (sCopleyCommandTable[ecmdtoCopley].uiCommandLength + 1)] = '\0';
 
  postCopleyTransmitEvent(&scommandtoCopley.ucCopleyData[0]);
 
}

void postCopleyTransmitEvent(uint8_t *copleyCommand)
{
    uint16_t ind;
    ind = 0;
    while (copleyCommand[ind] != '\0')
    {
        gsCopleyTransmitEventData.ucCopleyData[gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr] = copleyCommand[ind];   
        gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr ++;
        //DRV_USART0_WriteByte((uint8_t)gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr);
        ind ++;
        if (gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr >= MAX_TX_BUF_SIZE)
        {
            gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr = 0;
        }
    }
}
    
void copleyTransmitHandle(void)
{
    if (gsCopleyTransmitEventData.sCopleyEventPtr.uiInPtr != gsCopleyTransmitEventData.sCopleyEventPtr.uiOutPtr)
    {
        DRV_USART2_WriteByte(gsCopleyTransmitEventData.ucCopleyData[gsCopleyTransmitEventData.sCopleyEventPtr.uiOutPtr]);
        gsCopleyTransmitEventData.sCopleyEventPtr.uiOutPtr ++;
        if (gsCopleyTransmitEventData.sCopleyEventPtr.uiOutPtr >= MAX_TX_BUF_SIZE)
        {
            gsCopleyTransmitEventData.sCopleyEventPtr.uiOutPtr = 0;
        }
    }
}

