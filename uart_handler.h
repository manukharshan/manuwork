#include<stdlib.h>
#include"typedef.h"
#include "system_config.h"
#include "system_definitions.h"
//#define MAX_NO_OF_COMMAND 10U
//#define MAX_RECEIVE_COMMAND_LENGTH 10U
//#define TX_BUFFER_SIZE 35U
//#define RX_BUFFER_SIZE 20U
//#define BLANK_CHARACTER '\0'
//#define END_OF_COMMAND_CHARACTER 0x0dU
//#define RESPONSE_STATUS_LENGTH 35U
//#define TOTAL_NO_OF_COMMANDS 100U 


void ciReceiveDataBuffer1(void);
void ciReceiveDataBuffer2(void);
void ciReceiveDataBuffer3(void);
void ciReceiveDataBuffer4(void);
void ciReceiveDataBuffer5(void);
void ciReceiveDataBuffer6(void);

void uart1WriteByte(const uint8_t cTxData);
void uart2WriteByte(const uint8_t cTxData);
void uart3WriteByte(const uint8_t cTxData);
void uart4WriteByte(const uint8_t cTxData);
void uart5WriteByte(const uint8_t cTxData);
void uart6WriteByte(const uint8_t cTxData);

void ciReceiveCmdDataBuffer1(void);