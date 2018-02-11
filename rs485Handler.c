/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Raad System

  @File Name
    rs485Handler.c

  @Summary
    Rs485 receiver and transmitter handler

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdbool.h>
#include <string.h>
#include "rs485Handler.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
static uint8_t ucInWriteRs485BufferIndex = 0;
static uint8_t ucInReadRs485BufferIndex = 0;
static uint8_t ucOutWriteRs485BufferIndex = 0;
static uint8_t ucOutReadRs485BufferIndex = 0;

static int8_t cTxRs485Buffer[TX_RS485_BUFFER_SIZE];
static int8_t cRxRs485Buffer[RX_RS485_BUFFER_SIZE];
static bool gbTempFlag = false;
static int8_t gcRs485WriteByte;


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
 void rs485ReceiveDataBuffer(void)
 { 
     RS485PIN = disable;
      cRxRs485Buffer[ucInWriteRs485BufferIndex++] = DRV_USART1_ReadByte();
       if (ucInWriteRs485BufferIndex >= RX_RS485_BUFFER_SIZE)
        {
            ucInWriteRs485BufferIndex = 0;
        }
        if (ucInWriteRs485BufferIndex == ucInReadRs485BufferIndex)
        {
            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
            /*Send Rx Buffer Overflow Err Message*/
        }    
 }
 
 void rs485TransmitDataBuffer(int8_t cTxData)
{
    cTxRs485Buffer[ucOutWriteRs485BufferIndex] = cTxData;
    ucOutWriteRs485BufferIndex ++;
    if (ucOutWriteRs485BufferIndex >= TX_RS485_BUFFER_SIZE)
    {
        ucOutWriteRs485BufferIndex = 0;
    }
    if (ucOutWriteRs485BufferIndex == ucOutReadRs485BufferIndex)
    {
        /*Send Tx Buffer Overflow Err Msg*/
        //errorhandle(TX_BUFFER_OVERFLOW_ERROR);

    }
}

void rs485SendData(int8_t* csStringReceived,uint32_t length)
{
  uint8_t uLoopIndex;
  for (uLoopIndex = 0; uLoopIndex < length; uLoopIndex ++)
  {
      rs485TransmitDataBuffer(csStringReceived[uLoopIndex]);
  }
  //duSendData1(csStringReceived,strlen(csStringReceived));
}

void rs485TransmitDataInitilise(void)
{
    if ((ucOutWriteRs485BufferIndex != ucOutReadRs485BufferIndex)&&(!gbTempFlag))
    {     
        RS485PIN = enable;
        gbTempFlag = true;
        gcRs485WriteByte = cTxRs485Buffer[ucOutReadRs485BufferIndex];
        //uart6WriteByte(cTxBuffer[ucOutReadBufferIndex]);
        //DRV_USART5_WriteByte(cTxBuffer[ucOutReadBufferIndex]);	
        ucOutReadRs485BufferIndex ++;
        if(ucOutReadRs485BufferIndex >= TX_RS485_BUFFER_SIZE)
        {
            ucOutReadRs485BufferIndex = 0;
        }
    }
}

void rs485TransmitDataComplete(void)
{
    static uint32_t guiRs485TempDelayCounter=0;
    if(gbTempFlag)
    {
        guiRs485TempDelayCounter ++;
        
        if(guiRs485TempDelayCounter == 1U)
        {
                                   /*TX a byte of Data*/
            DRV_USART1_WriteByte(gcRs485WriteByte);
            
        }
        else if(guiRs485TempDelayCounter == 8U)
        {
            RS485PIN = disable;
            guiRs485TempDelayCounter = 0U;
            gbTempFlag = false;
        }
    }
}


/* *****************************************************************************
 End of File
 */
