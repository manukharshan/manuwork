/*
 *  Version:          0.0
 *  Design:           manu k harshan
 *  file :            loRaModem.c
 */
#include "loraModem.h"
#include "assemblePacket.h"
#include "defaultvalue.h"

int testrotate = 0;
char command[40];
char hexmessage[26];
char strmessage[52];
uint8_t command3[4];
uint8_t arg3[70];

LoraEventType lmProcessReceiveEvent(char* response)
{
    LoraEventType LoraEventType;
   //duSendData1(response,strlen(response));
   if(!memcmp(response,"ok\r",3))
        return LORA_ANSWER_OK;
   else if(!memcmp(response,"invalid_param\r",14))
       return LORA_ANSWER_ERROR;
   else if(!memcmp(response,"4294967245\r",11))
       return LORA_MACPAUSE_OK;
   else if (!memcmp(response,"radio_tx_ok\r",12))
       return LORA_TRANSMIT_OK;
   else if (!memcmp(response,"radio_rx",8))
   {
       LoraEventType = loraProcessReceivecommand(response);
       return LoraEventType;
   }
   else if(!memcmp(response,"radio_err\r",10))
       return LORA_RADIO_ERROR;
   else
       return LORA_NO_ANSWER; 
}

/*!
 *
 * @brief This function sets spreading factor for radio mode
 *
 * @param   char* sprfact:  spreading factor to be set [SF7..SF12]
 *
 *
 */
void loraWansetRadioSF(char* sprfact)
{
  //strcpy(command,"radio set sf %s\r\n");

  sprintf(command,"radio set sf %s\r\n",sprfact);

  //send command and wait for ans
  luSendData(command,strlen(command));
}

/*!
 *
 * @brief This function sets tx power for radio mode
 *
 * @param   int8_t pwr: power to be set [-3..15]
 *
 */
void loraWansetRadioPower(int8_t pwr)
{
  //strcpy(command,"radio set pwr %d\r\n");

  sprintf(command,"radio set pwr %d\r\n",pwr);

  //send command and wait for ans
  luSendData(command,strlen(command));
}

/*!
 * @brief This function sets the operating frequency for transceiver use
 *
 * @param uint32_t freq: operating frequency [863250000..869750000]
 *                                           [433250000..434550000]
 *    uint32_t freq: operating frequency [923550000..927250000] (RN2903)
 */
void loraWansetRadioFreq(uint32_t freq)
{
  //strcpy(command,"radio set freq %lu\r\n");

  sprintf(command,"radio set freq %lu\r\n",freq);

  //send command and wait for ans
  luSendData(command,strlen(command));
}
/*!
 * @brief This function sets the CRC header state for transceiver use
 *
 * @param uint16_t state: "on"/"off"
 */
void loraWansetRadioCRC(char* state)
{
  //strcpy(command,"radio set crc %s\r\n");

  sprintf(command,"radio set crc %s\r\n",state);

  //send command and wait for ans
  luSendData(command,strlen(command));
}

/*!
 * @brief This function sets the coding rate for transceiver use
 *
 * @param char* codingrate: "4/5","4/6","4/7","4/8"
 */
void loraWansetRadioCR(char* codingrate)
{
  //strcpy(command,"radio set cr %s\r\n");

  sprintf(command,"radio set cr %s\r\n",codingrate);

  //send command and wait for ans
  luSendData(command,strlen(command));
}

/*!
 * @brief This function pauses MAC functionality so the module is able
 *      to use radio functions.
 *
 * @remarks This function must be called before using radio RX and TX

 */
void loraWanmacPause(void)
{
  sprintf(command,"mac pause\r\n",NULL);

  //send command and wait for ans
  luSendData(command,strlen(command));
}

void loraWansetWdt(uint32_t wdt)
{
    //strcpy(command,"radio set wdt %lu\r\n");
    
    sprintf(command,"radio set wdt %lu\r\n",wdt);
    
    luSendData(command,strlen(command));
}

void loraTransmit(char* message)
{
    //strcpy(command,"radio tx %s\r\n");
    
    sprintf(command,"radio tx %s\r\n",message);
    
    luSendData(command,strlen(command));
}

void loraReceive(void)
{
    strcpy(command,"radio rx 0\r\n");
    luSendData(command,strlen(command));
}


LoraEventType loraProcessReceivecommand(char* Response)
{
    LoraEventType geLoraEventType;
    sSlavedetails slaveDetails;
    slaveDetails = *getDevicedetails();
    geLoraEventType = LORA_DATA_RECEIVE;
    int i = 0;
    while(*Response != '\r')
    {
       hexmessage[i++] = *Response;
       Response++;
    }
    hexmessage[i] = '\0';
    duSendData1(&hexmessage[0],strlen(&hexmessage[0]));
    HexStringToString(&strmessage[0],&hexmessage[10]);
    duSendData1(&strmessage[0],strlen(&strmessage[0]));
//    if(!memcmp(&strmessage[0],&(slaveDetails.devID[0]),4))
//    {
     strncpy(&command3[0],&strmessage[0],3);
     command3[3] = '\0';
     if(strmessage[3])
     strcpy(&arg3[0],&strmessage[3]);
     commandParse(&command3[0],&arg3[0],LORA);
 return geLoraEventType;    
}