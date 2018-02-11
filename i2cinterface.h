/* 
 * File:   i2cinterface.h
 * Author: Davis
 *
 * Created on 9 February, 2016, 7:46 PM
 */

#ifndef I2CINTERFACE_H
#define	I2CINTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define EEPROMslaveAddress          0xA0

#define I2C_BUFFER_SIZE 60
    
#define ENABLE_I2C_DEBUG 0
    
//#define EEPROM_MAX_WRITE_LOCATIONS 1
// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/
typedef union
{
    uint16_t pageAddress;
    struct
    {
        uint8_t page_address_high;
        uint8_t page_address_low;
    };
}addr;
typedef struct
{
    addr ad;
    uint16_t length;
}addrPack;

typedef enum
{
    COUTDATA_ADDR,
    CALIBRATIONDETAILS_ADDR,
    DEVICE_DETAIL_ADDR,
    STATIC_IPV4_ADDR,
    DEVICE_CALIBRATION_DETAILS,        
    CURRENT_ENCODER_COUNT,
    EEPROM_MAX_WRITE_LOCATIONS,        
}eepromLocationIdentifier;
typedef enum
{
    /* Master initiates a stop condition */
    I2C_STATE_IDLE,

    /* Master initiates a start condition */
    I2C_STATE_SEND_START_CONDITION,
            
    I2C_STATE_WAIT_START_COMPLETE,

    /* Master sends out an address byte */
    I2C_STATE_SEND_ADDRESS_BYTE,

    /* Master sends data to a slave */
    I2C_STATE_SEND_DATA,

    I2C_WAIT_WRITE_BYTE_COMPLETE,
            
    I2C_IS_BYTE_ACK,
            
    I2C_WAIT_FOR_STOP_COPMLETE,
            
    I2C_WRITE_END,
    /* Master Send Start condition again to Read */
    I2C_SEND_PAGE_MARKER_START_CONDITON,

    /* Master Send Start Address */
    I2C_SEND_PAGE_MARKER_DEVICE_ADDRESS,

    /* Send Page address to mark for read */
    I2C_SEND_PAGE_ADDRESS,

    /* Master Send Start condition again to Read */
    I2C_READ_SEND_START_CONDITON,

    /*Master sends Read address byte to slave */
    I2C_STATE_SEND_READ_ADDRESS_BYTE,

    I2C_STATE_READ_DATA_START,
    
    I2C_WAIT_READ_BYTE_AVAILABLE,
            
    I2C_READ_TO_ARRAY,
            
    I2C_WAIT_FOR_ACK,
   /*Master Reads Data from Slave*/
    I2C_STATE_READ_DATA,

   /* Stop condition for Read */
    I2C_STATE_READ_STOP_CONDITION,

    /* Master initiates a stop condition */
    I2C_STATE_SEND_STOP_CONDITION,
            
    I2C_READ_END,
            
    I2C_OPERATION_COMPLETE

} I2C_STATES;

void initI2cState(void);
void addressLookUpTable(void);
bool waitI2cWriteCompleteToEeprom(void);
void I2cArrayPut(uint8_t *data,eepromLocationIdentifier location);
bool isI2cWriteByteComplete(void);
void i2cArrayGet(uint8_t *retArray);
void setEepromReadAddress(eepromLocationIdentifier id);
bool isI2cGetDataReadyFromEeprom(void);
void setEepromWriteAddress(addr address);
bool isI2cDataAvailableToWrite(void);
bool isI2cDataAvailableToRead(void);
void initiateI2cRead(void);

#ifdef	__cplusplus
}
#endif

#endif	/* I2CINTERFACE_H */

