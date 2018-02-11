#include "i2cinterface.h"
#include "timerfunctions.h"

static I2C_STATES i2cState,nextI2cState;
static uint16_t guiByteCounter = 0;
static uint16_t guiDataLength = 0;
static uint16_t guiReadDataLength = 0;
static int8_t gcI2cBuffer[I2C_BUFFER_SIZE];
static int8_t gcRxBuff[I2C_BUFFER_SIZE];
static bool gcI2cDataAvailableToWrite = 0;
static bool gcI2cDataAvailableToRead = 0;
static addrPack eepromAddress[EEPROM_MAX_WRITE_LOCATIONS];
static eepromLocationIdentifier eepromMemLocationId;

void initI2cState(void)
{
    i2cState = I2C_STATE_IDLE;
    addressLookUpTable();
    guiByteCounter = 0;
    guiDataLength = 0;
}

void addressLookUpTable(void)
{
    eepromAddress[COUTDATA_ADDR].ad.page_address_high = 0x00;
    eepromAddress[COUTDATA_ADDR].ad.page_address_low = 0x00;
    eepromAddress[COUTDATA_ADDR].length = 60;
    eepromAddress[CALIBRATIONDETAILS_ADDR].ad.page_address_high = 0x00;
    eepromAddress[CALIBRATIONDETAILS_ADDR].ad.page_address_low = 0x40;
    eepromAddress[CALIBRATIONDETAILS_ADDR].length = 60;
    eepromAddress[DEVICE_DETAIL_ADDR].ad.page_address_high = 0x00;
    eepromAddress[DEVICE_DETAIL_ADDR].ad.page_address_low = 0xC0;
    eepromAddress[DEVICE_DETAIL_ADDR].length = 60;
//    eepromAddress[STATIC_IPV4_ADDR].ad.page_address_high = 0x00;
//    eepromAddress[STATIC_IPV4_ADDR].ad.page_address_low = 0xC0;
//    eepromAddress[STATIC_IPV4_ADDR].length = 8;
//    eepromAddress[DEVICE_CALIBRATION_DETAILS].ad.page_address_high = 0x01;
//    eepromAddress[DEVICE_CALIBRATION_DETAILS].ad.page_address_low = 0x00;
//    eepromAddress[DEVICE_CALIBRATION_DETAILS].length = 40;
//    eepromAddress[CURRENT_ENCODER_COUNT].ad.page_address_high = 0x01;
//    eepromAddress[CURRENT_ENCODER_COUNT].ad.page_address_low = 0x50;
//    eepromAddress[CURRENT_ENCODER_COUNT].length = 11;
}
void I2cArrayPut(uint8_t *data,eepromLocationIdentifier location)
{
    eepromMemLocationId = location;
    memset(gcI2cBuffer,'\0',I2C_BUFFER_SIZE);
    guiDataLength = 0;
    if (*data != '\0')
    {
        while(*data != '\0' && guiDataLength < I2C_BUFFER_SIZE)
        {
            gcI2cBuffer[guiDataLength] = *data;
            guiDataLength ++;
            data ++;
        }
        gcI2cBuffer[guiDataLength] = '\r';
        guiDataLength ++;
        gcI2cDataAvailableToWrite = 1;
    }
}

bool waitI2cWriteCompleteToEeprom(void)
{
    bool i2cSmStatus = false;
    if (DRV_I2C0_MasterBusIdle() )
    {
        switch (i2cState)
        {
            case I2C_STATE_IDLE:
                //PORTAbits.RA14 = 1;
                i2cState = I2C_STATE_SEND_START_CONDITION;
                break;

            case I2C_STATE_SEND_START_CONDITION:
                DRV_I2C0_MasterStart();
                i2cState = I2C_STATE_WAIT_START_COMPLETE;
                break;
                
            case I2C_STATE_WAIT_START_COMPLETE:
                if (PLIB_I2C_StartWasDetected(I2C_ID_3))
                {
                    //PORTAbits.RA14 = 0;
                    i2cState = I2C_STATE_SEND_ADDRESS_BYTE;
                }
                break;

            case I2C_STATE_SEND_ADDRESS_BYTE:
                if (DRV_I2C0_ByteWrite(EEPROMslaveAddress))
                {
                    i2cState = I2C_WAIT_WRITE_BYTE_COMPLETE;
                    nextI2cState = I2C_IS_BYTE_ACK;
                }
                break;
            
            case I2C_WAIT_WRITE_BYTE_COMPLETE:
                if (!PLIB_I2C_TransmitterIsBusy(I2C_ID_3) && PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_3))
                {
                    //PORTAbits.RA14 = 1;
                    i2cState = nextI2cState;
                    startTimer(I2CTIMER,1);
                }
                break;
                
            case I2C_IS_BYTE_ACK:
                if (DRV_I2C0_WriteByteAcknowledged())
                {
                    stopTimer(I2CTIMER);
                    i2cState = I2C_STATE_SEND_DATA;
                    //guiByteCounter = 0;
                }
                else if(getTimeOutOccur(I2CTIMER))
                {
                    stopTimer(I2CTIMER);
                    i2cState = I2C_OPERATION_COMPLETE;
                }
                break;
            case I2C_STATE_SEND_DATA:
                /* Total bytes send = page address + data */
                if ( guiByteCounter < (guiDataLength+2))
                {
                    if (guiByteCounter == 0)
                    {
                        DRV_I2C0_ByteWrite(eepromAddress[eepromMemLocationId].ad.page_address_high);
                        guiByteCounter ++;
                    }
                    else if (guiByteCounter == 1)
                    {
                        DRV_I2C0_ByteWrite(eepromAddress[eepromMemLocationId].ad.page_address_low);
                        guiByteCounter ++;
                    }  
                    else
                    {
                        DRV_I2C0_ByteWrite(gcI2cBuffer[guiByteCounter - 2]);
                        guiByteCounter ++;
                    }
                    i2cState = I2C_WAIT_WRITE_BYTE_COMPLETE;
                    //nextI2cState = I2C_STATE_SEND_DATA;
                    nextI2cState=I2C_IS_BYTE_ACK; 
                }
                else
                    i2cState = I2C_STATE_SEND_STOP_CONDITION;
                break;

            case I2C_STATE_SEND_STOP_CONDITION:
                if(DRV_I2C0_MasterStop())
                {
//                     DRV_I2C0_MasterStop();
                     i2cState = I2C_WAIT_FOR_STOP_COPMLETE;
                }
                break;
                
            case I2C_WAIT_FOR_STOP_COPMLETE:
//                if (PLIB_I2C_StopWasDetected(I2C_ID_3))
//                {
                    startTimer(I2CTIMER,6);
                    i2cState = I2C_WRITE_END;
//                }
                break;
                
            case I2C_WRITE_END:
                if (getTimeOutOccur(I2CTIMER))
                {
                    stopTimer(I2CTIMER);
                    i2cState = I2C_STATE_IDLE;
                    i2cSmStatus = true;
                    gcI2cDataAvailableToWrite = 0;
                    guiByteCounter = 0;
                    //PORTAbits.RA14 = 0;
                }
                break;
                
            case I2C_OPERATION_COMPLETE:
                i2cState = I2C_STATE_IDLE;
                i2cSmStatus = true;
                gcI2cDataAvailableToWrite = 0;
                guiByteCounter = 0;
                break;
                
            default:
                break;
        }
    }
    return i2cSmStatus;
}

bool isI2cGetDataReadyFromEeprom()        
{
    bool i2cSmStatus = false;
    if (DRV_I2C0_MasterBusIdle() )
    {
        switch (i2cState)
        {
            case I2C_STATE_IDLE: 
                memset(gcRxBuff,'\0',I2C_BUFFER_SIZE);
                i2cState = I2C_SEND_PAGE_MARKER_START_CONDITON;
                break;
            case I2C_SEND_PAGE_MARKER_START_CONDITON:
                DRV_I2C0_MasterStart();
                DRV_I2C0_WaitForStartComplete();
                i2cState = I2C_SEND_PAGE_MARKER_DEVICE_ADDRESS;
                break;

            case I2C_SEND_PAGE_MARKER_DEVICE_ADDRESS:
                if (DRV_I2C0_ByteWrite(EEPROMslaveAddress))
                {
                    DRV_I2C0_WaitForByteWriteToComplete();
                    if (DRV_I2C0_WriteByteAcknowledged())
                    {
                        i2cState = I2C_SEND_PAGE_ADDRESS;
                        guiByteCounter = 0;
                    }
                    else
                        i2cState = I2C_OPERATION_COMPLETE;
                }
                break;

            case I2C_SEND_PAGE_ADDRESS:
                if ( guiByteCounter < (2))
                {
                    if (guiByteCounter == 0)
                    {
                        DRV_I2C0_ByteWrite(eepromAddress[eepromMemLocationId].ad.page_address_high);
                        guiByteCounter ++;
                    }
                    else if (guiByteCounter == 1)
                    {
                        DRV_I2C0_ByteWrite(eepromAddress[eepromMemLocationId].ad.page_address_low);
                        guiByteCounter ++;
                    }  
                    DRV_I2C0_WaitForByteWriteToComplete();
                    while (!DRV_I2C0_WriteByteAcknowledged());
                }
                else
                    i2cState = I2C_READ_SEND_START_CONDITON;
                break;

            case I2C_READ_SEND_START_CONDITON:
                DRV_I2C0_MasterRestart();
                DRV_I2C0_WaitForStartComplete();
                i2cState = I2C_STATE_SEND_READ_ADDRESS_BYTE;
                break;

            case I2C_STATE_SEND_READ_ADDRESS_BYTE:
                if (DRV_I2C0_ByteWrite((EEPROMslaveAddress|0x01)))
                {
                    DRV_I2C0_WaitForByteWriteToComplete();
                    if (DRV_I2C0_WriteByteAcknowledged())
                    {
                        i2cState = I2C_STATE_READ_DATA;
                        guiByteCounter = 0;
                    }
                    else
                        i2cState = I2C_OPERATION_COMPLETE;
                }
                break;

            case I2C_STATE_READ_DATA:
                if (guiDataLength > 0)
                {
                    DRV_I2C0_SetUpByteRead();                   //Set Rx enable in MSTR which causes SLAVE to send data
                    while(!DRV_I2C0_WaitForReadByteAvailable());        // Wait till RBF = 1; Which means data is available in I2C2RCV reg
                    gcRxBuff[guiByteCounter] = DRV_I2C0_ByteRead();   //Read from I2CxRCV
                    guiByteCounter ++;
                    if (guiDataLength > 1)
                    {
                        DRV_I2C0_MasterACKSend();               //Send ACK to Slave
                    }
                    while (!DRV_I2C0_WaitForACKOrNACKComplete());
                    guiDataLength --;
                }
                else
                {
                    DRV_I2C0_MasterNACKSend();                      //last byte; send NACK to Slave, no more data needed
                    while (!DRV_I2C0_WaitForACKOrNACKComplete());   // wait till NACK sequence is complete i.e ACKEN = 0
                    i2cState = I2C_STATE_READ_STOP_CONDITION;
                }
                break;

            case I2C_STATE_READ_STOP_CONDITION:
                DRV_I2C0_MasterStop();
                DRV_I2C0_WaitForStopComplete();
                i2cState = I2C_OPERATION_COMPLETE;
                break;
            case I2C_OPERATION_COMPLETE:
                i2cState = I2C_STATE_IDLE;
                gcRxBuff[guiReadDataLength - 1] = '\r';
                i2cSmStatus = true;
                gcI2cDataAvailableToRead = 0;
                break;
            default:
                break;
        }
    }
    return i2cSmStatus;
}


bool isI2cWriteByteComplete(void)
{
    bool status = false;
    if (!PLIB_I2C_TransmitterIsBusy(I2C_ID_3) && PLIB_I2C_TransmitterByteHasCompleted(I2C_ID_3))
    {
        status = true;
    }
    return status;
}

void i2cArrayGet(uint8_t *retArray)
{
    memcpy(retArray,&gcRxBuff[0],guiReadDataLength);
    gcI2cDataAvailableToRead = 0;
}

void setEepromReadAddress(eepromLocationIdentifier id)
{
    eepromMemLocationId = id;
    guiReadDataLength = eepromAddress[id].length;
    guiDataLength = eepromAddress[id].length;
}

void setEepromWriteAddress(addr address)
{
    eepromAddress[0].ad.pageAddress = address.pageAddress;
}

bool isI2cDataAvailableToWrite(void)
{
    return gcI2cDataAvailableToWrite;
}

void initiateI2cRead(void)
{
    if (!gcI2cDataAvailableToWrite)
    {
        gcI2cDataAvailableToRead = 1;
    }
}

bool isI2cDataAvailableToRead(void)
{
    return gcI2cDataAvailableToRead;
}