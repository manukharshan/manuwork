#include"uart_handler.h"
#include"typedef.h"

//static u08 ucInWriteBufferIndex1 = 0,ucInWriteBufferIndex2 = 0,ucInWriteBufferIndex3 = 0,ucInWriteBufferIndex4 = 0,ucInWriteBufferIndex5 = 0,ucInWriteBufferIndex6 = 0;
//static u08 ucInReadBufferIndex1 = 0,ucInReadBufferIndex2 = 0,ucInReadBufferIndex3 = 0,ucInReadBufferIndex4 = 0,ucInReadBufferIndex5 = 0,ucInReadBufferIndex6 = 0;
//static u08 ucOutWriteBufferIndex = 0;
//static u08 ucOutReadBufferIndex = 0;
//static u08 ucCmdWriteBufferIndex = 0;
//static u08 ucCmdReadBufferIndex = 0;
//static u08 ucInWriteBufferIndex1 = 0;
//static u08 ucInReadBufferIndex1 = 0;
//static u08 ucCmdLinkIndex = 0;
//static c08 cRxBuffer1[RX_BUFFER_SIZE],cRxBuffer2[RX_BUFFER_SIZE],cRxBuffer3[RX_BUFFER_SIZE],cRxBuffer4[RX_BUFFER_SIZE],cRxBuffer5[RX_BUFFER_SIZE],cRxBuffer6[RX_BUFFER_SIZE];
//static c08 cTxBuffer1[TX_BUFFER_SIZE],cTxBuffer2[TX_BUFFER_SIZE],cTxBuffer3[TX_BUFFER_SIZE],cTxBuffer4[TX_BUFFER_SIZE],cTxBuffer5[TX_BUFFER_SIZE],cTxBuffer6[TX_BUFFER_SIZE];
//static c08 cRxCmdBuffer[MAX_NO_OF_COMMAND][MAX_RECEIVE_COMMAND_LENGTH];
//static cmdLinkPack sCmdLinkTable[TOTAL_NO_OF_COMMANDS];
//static u08 timerTaskCounter = 0;
//static u32 guiCommFaultCounter=0;
//static bool setCommunicationFault=false;
//static bool gbFirstCommandReceived = false;

/*****************************************************************************************
                             6_UART_RECEIVE_BUFFER_HANDLER
*****************************************************************************************/
void ciReceiveDataBuffer1(void)
{
    c08 rxdata1;
    rxdata1=DRV_USART0_ReadByte();
    uart6WriteByte(rxdata1);
//       cRxBuffer1[ucInWriteBufferIndex1] = DRV_USART0_ReadByte();
//   
//        ucInWriteBufferIndex1 ++;
//        if (ucInWriteBufferIndex1 >= RX_BUFFER_SIZE)
//        {
//            ucInWriteBufferIndex1 = 0;
//        }
//        if (ucInWriteBufferIndex1 == ucInReadBufferIndex1)
//        {
//            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
//            /*Send Rx Buffer Overflow Err Message*/
//  
//        } 
}  

void ciReceiveDataBuffer2(void)
{
    c08 rxdata2;
    rxdata2=DRV_USART1_ReadByte();
    uart2WriteByte(rxdata2);
//        cRxBuffer2[ucInWriteBufferIndex2] = DRV_USART1_ReadByte();
//   
//        ucInWriteBufferIndex2 ++;
//        if (ucInWriteBufferIndex2 >= RX_BUFFER_SIZE)
//        {
//            ucInWriteBufferIndex2 = 0;
//        }
//        if (ucInWriteBufferIndex2 == ucInReadBufferIndex2)
//        {
//            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
//            /*Send Rx Buffer Overflow Err Message*/
//  
//        } 
}  
void ciReceiveDataBuffer3(void)
{
    c08 rxdata3;
    rxdata3=DRV_USART2_ReadByte();
    uart3WriteByte(rxdata3);
//        cRxBuffer3[ucInWriteBufferIndex3] = DRV_USART3_ReadByte();
//   
//        ucInWriteBufferIndex3 ++;
//        if (ucInWriteBufferIndex3 >= RX_BUFFER_SIZE)
//        {
//            ucInWriteBufferIndex3 = 0;
//        }
//        if (ucInWriteBufferIndex3 == ucInReadBufferIndex3)
//        {
//            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
//            /*Send Rx Buffer Overflow Err Message*/
//  
//        } 
}  

void ciReceiveDataBuffer4(void)
{
      c08 rxdata4;
    rxdata4=DRV_USART3_ReadByte();
    uart4WriteByte(rxdata4);  
//    cRxBuffer4[ucInWriteBufferIndex4] = DRV_USART3_ReadByte();
//   
//        ucInWriteBufferIndex4 ++;
//        if (ucInWriteBufferIndex4 >= RX_BUFFER_SIZE)
//        {
//            ucInWriteBufferIndex4 = 0;
//        }
//        if (ucInWriteBufferIndex4 == ucInReadBufferIndex4)
//        {
//            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
//            /*Send Rx Buffer Overflow Err Message*/
//  
//        } 
}  

void ciReceiveDataBuffer5(void)
{
    c08 rxdata5;
    rxdata5=DRV_USART4_ReadByte();
    uart6WriteByte(rxdata5);  
//    cRxBuffer5[ucInWriteBufferIndex5] = DRV_USART4_ReadByte();
//   
//        ucInWriteBufferIndex5 ++;
//        if (ucInWriteBufferIndex5 >= RX_BUFFER_SIZE)
//        {
//            ucInWriteBufferIndex5 = 0;
//        }
//        if (ucInWriteBufferIndex5 == ucInReadBufferIndex5)
//        {
//            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
//            /*Send Rx Buffer Overflow Err Message*/
//  
//        } 
}  

void ciReceiveDataBuffer6(void)
{
    c08 rxdata6;
    rxdata6=DRV_USART5_ReadByte();
    uart5WriteByte(rxdata6); 
    
//        cRxBuffer1[ucInWriteBufferIndex6] = DRV_USART5_ReadByte();
//   
//        ucInWriteBufferIndex6 ++;
//        if (ucInWriteBufferIndex6 >= RX_BUFFER_SIZE)
//        {
//            ucInWriteBufferIndex6 = 0;
//        }
//        if (ucInWriteBufferIndex6 == ucInReadBufferIndex6)
//        {
//            //errorhandle(RX_BUFFER_OVERFLOW_ERROR);
//            /*Send Rx Buffer Overflow Err Message*/
//        } 
}  

#if 0
void ciReceiveCmdDataBuffer1(void)
{
    static u08 ucCmdWriteBufferSubIndex1 = 0;
    while (ucInWriteBufferIndex1 != ucInReadBufferIndex1)
    {
        if(cRxBuffer6[ucInReadBufferIndex1] != (c08) END_OF_COMMAND_CHARACTER)
        {
            cRxCmdBuffer[ucCmdWriteBufferIndex][ucCmdWriteBufferSubIndex1] =
                    cRxBuffer1[ucInReadBufferIndex1];
            ucCmdWriteBufferSubIndex1 ++;
            if (ucCmdWriteBufferSubIndex1 >= MAX_RECEIVE_COMMAND_LENGTH)
            {
                ucCmdWriteBufferSubIndex1 = 0;
                /*Send Max Command Length Exeeds Err Msg*/
                //errorhandle(MAX_COMMAND_LENGTH_EXCEEDS_ERROR);
            }
        }
        else
        {
            cRxCmdBuffer[ucCmdWriteBufferIndex][ucCmdWriteBufferSubIndex1] =
                    cRxBuffer1[ucInReadBufferIndex1];
            ucCmdWriteBufferSubIndex1 = 0;
            ucCmdWriteBufferIndex ++;
            if (ucCmdWriteBufferIndex >= MAX_NO_OF_COMMAND)
            {
                ucCmdWriteBufferIndex = 0;
            }
        }
        ucInReadBufferIndex1 ++;
        if (ucInReadBufferIndex1 >= RX_BUFFER_SIZE)
        {
            ucInReadBufferIndex1 = 0;
        }
    }
}
#endif

/*****************************************************************************************
                             6_UART_TRANSMIT_BUFFER_HANDLER
*****************************************************************************************/
void uart1WriteByte(const uint8_t cTxData)                      /*UART 1 Write*/
{
DRV_USART0_WriteByte(cTxData);	
}

void uart2WriteByte(const uint8_t cTxData)
{
DRV_USART1_WriteByte(cTxData);	
}

void uart3WriteByte(const uint8_t cTxData)
{
DRV_USART2_WriteByte(cTxData);	
}

void uart4WriteByte(const uint8_t cTxData)
{
DRV_USART3_WriteByte(cTxData);	
}

void uart5WriteByte(const uint8_t cTxData)
{
DRV_USART4_WriteByte(cTxData);	
}

void uart6WriteByte(const uint8_t cTxData)
{
DRV_USART5_WriteByte(cTxData);	
}