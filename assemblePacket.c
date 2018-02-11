#include <string.h>
#include "assemblePacket.h"


extern sSlavedetails gsSlavedetails;
//int8_t messagePacket[30];

void frameResponse(packetType ePacketType,valveCtrlMod ctrlMod,uint8_t* messagePacket)
{
    sSlavedetails devicedetails;
    sDeviceCtrlState  deviceCtrlState;
    devicedetails = *getDevicedetails();
    deviceCtrlState = *getDeviceCtrlState();
    switch(ePacketType)
    {
        case GETALLDEVICESTATUS:
        {
            memcpy(&messagePacket[0],"GAS",SIZE_COMMAND);
            memcpy(&messagePacket[3],"01",SIZE_NUMBEROFDEVICES);
            memcpy(&messagePacket[5],"8001",4);
            messagePacket[9] = '1';
            if(MOTORUNLOCKED == deviceCtrlState.eMotorCtrlState.eMotorStatus)
            {
               messagePacket[10] = '0';
            }
            else
            {
               messagePacket[10] = '1'; 
            }
            if(LOCALMOD == ctrlMod)
            {
               messagePacket[11] = '1';
            }   
            else
            {
               messagePacket[11] = '1';  
            }
            if(LOCALMOD == ctrlMod)
            {
               messagePacket[12] = '1';
            }
            else
            {
               messagePacket[12] = '1';
            }
            unsignedIntToString((uint16_t)(devicedetails.percentageopen),DIGIT_3,&messagePacket[13]);
            if(ctrlMod == LOCALMOD)
            {
              dtcIntToString(getCurrentMotorCurrent(),DIGIT_11,&messagePacket[16]);  
              messagePacket[27] = '\r';
              messagePacket[28] = '\0';
            }
            else if(ctrlMod == REMOTE)
            {
              messagePacket[16] = '\0';  
            }
            break;   
        }
        case GETCURRENTCOUNT:
        {
            memcpy(&messagePacket[0],"GCC",SIZE_COMMAND);
            dtcIntToString(getCurrentEncoderPosition(),DIGIT_11,&messagePacket[3]);
            if(ctrlMod == LOCALMOD)
            {
              messagePacket[14] = '\r';
              messagePacket[15] = '\0';
            }
            break;
        }
        case GETCALPOSITON:
        {
            memcpy(&messagePacket[0],"GCP",SIZE_COMMAND);
            dtcIntToString(gsSlavedetails.opencountnum,DIGIT_11,&messagePacket[3]);
            dtcIntToString(gsSlavedetails.closecountnum,DIGIT_11,&messagePacket[14]);
            if(ctrlMod == LOCALMOD)
            {
              messagePacket[25] = '\r';
              messagePacket[26] = '\0';
            }
            break;
        }
        case GETOPENPERCENTAGE:
        {
            memcpy(&messagePacket[0],"GOP",SIZE_COMMAND);
            unsignedIntToString((uint16_t)(devicedetails.percentageopen),DIGIT_3,&messagePacket[3]);
            if(ctrlMod == LOCALMOD)
            {  
              messagePacket[6] = '\r';
              messagePacket[7] = '\0';
            }
            else if(ctrlMod == REMOTE)
            {
              messagePacket[6] = '\0';  
            }
            break;
        }
        case GET_DEVICE_STATUS_REMOTE:
        {
            memcpy(&messagePacket[0],"GSR",SIZE_COMMAND);
            memcpy(&messagePacket[3],"8001",4);
            if(MOTORUNLOCKED == deviceCtrlState.eMotorCtrlState.eMotorStatus)
            {
               messagePacket[7] = '0';
            }
            else
            {
               messagePacket[7] = '1'; 
            }
            unsignedIntToString((uint16_t)(devicedetails.percentageopen),DIGIT_3,&messagePacket[8]);
            messagePacket[11] = '\0';
            break;
        }
    }
}

void assembleEEpromPacket(eepromPacketType ePacketType,uint8_t* messagePacket)
{
    int encoderCount = 0;
    switch(ePacketType)
    {
        case EEPROMWRITECURRENTCOUNT:
        {
            encoderCount = getCurrentEncoderPosition();
            dtcIntToString(encoderCount,DIGIT_11,&messagePacket[0]);
//            memcpy(&messagePacket[0],(uint8_t*)&encoderCount,sizeof(int));
            I2cArrayPut(&messagePacket[0],COUTDATA_ADDR);
            setEepromReadAddress(COUTDATA_ADDR);
            //while(!waitI2cWriteCompleteToEeprom());
            break;
        }
        case EEPROMWRITECALIBRATIONDETAILS:
        {
            dtcIntToString(gsSlavedetails.opencountnum,DIGIT_11,&messagePacket[0]);
            dtcIntToString(gsSlavedetails.closecountnum,DIGIT_11,&messagePacket[11]);
            gsSlavedetails.calibrationstatus = 1;
            gsSlavedetails.noofRotation = (gsSlavedetails.opencountnum - gsSlavedetails.closecountnum);
            gsSlavedetails.noofRotation<0 ? (gsSlavedetails.noofRotation=-gsSlavedetails.noofRotation):0;
            messagePacket[22]='1';
            messagePacket[23]='\0';
            I2cArrayPut(&messagePacket[0],CALIBRATIONDETAILS_ADDR);
            setEepromReadAddress(CALIBRATIONDETAILS_ADDR);
            //while(!waitI2cWriteCompleteToEeprom());
            break;
        }
        case EEPROMWRITEALLDEVICEDETAILS:
        {
            sprintf(&messagePacket[0],"VACTS_%s:%s:%s",gsSlavedetails.devID,gsSlavedetails.ipaddress,gsSlavedetails.portNo);
            I2cArrayPut(&messagePacket[0],DEVICE_DETAIL_ADDR);
            setEepromReadAddress(DEVICE_DETAIL_ADDR);
            break;
        }
        
    }
    
}