/* 
 * File:   datatypeconversion.h
 * Author: mgopianth
 *
 * Created on August 31, 2015, 11:05 PM
 */

#ifndef DATATYPECONVERSION_H
#define	DATATYPECONVERSION_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "events.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
    
    typedef enum
    {
        DIGIT_1 = 1,
        DIGIT_2,
        DIGIT_3,
        DIGIT_4,
        DIGIT_5,
        DIGIT_6,
        DIGIT_7,
        DIGIT_8,
        DIGIT_9,
        DIGIT_10,
        DIGIT_11        
    }eDigits;

void unsignedIntToString(uint16_t uiValue,eDigits eDigitNumber,uint8_t cString[]);
void stringToUnsignedInt(uint8_t pString[],eDigits eDigitNumber,uint16_t *puiValue);
void unsignedIntToStringHex(uint16_t uiValue, 
                                 eDigits eNumberOfDigits,
                                 uint8_t cString[]);
void dtcStringToSignedInt(int8_t cString[], eDigits eNumberOfDigits,
                               int16_t *psiValue);
uint16_t dtcIntToString(int32_t sliValue,eDigits eNumberOfDigits,
                         uint8_t cString[]);
int valid_digit(int8_t *ip_str);
int dcttoint(char str[]);
void HexStringToString(char* str,char* strH);
void StringToHexString(char* strH,char* str);
#ifdef	__cplusplus
}
#endif

#endif	/* DATATYPECONVERSION_H */

