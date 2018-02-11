#include "datatypeconversion.h"
#include "events.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>


#define CHAR_0 ((int8_t)'0')
#define CHAR_9 ((int8_t)'9')

#define CHAR_a ((int8_t)'a')
#define CHAR_f ((int8_t)'f')

void unsignedIntToString(uint16_t uiValue,eDigits eDigitNumber,uint8_t cString[])
{

    uint16_t uiIndex;
    int8_t cTemp;
    uint16_t uiTempValue;
    uiTempValue = uiValue;
    for(uiIndex = 0U; uiIndex < eDigitNumber; uiIndex++)
    {
        cString[uiIndex] =  (int8_t)(0x30) + (int8_t)(uiTempValue % 10U);
        uiTempValue = uiTempValue / 10;
    }
    cString[uiIndex] = '\0';
    /* Reverse the String */
    for(uiIndex = 0U; uiIndex < (eDigitNumber  / 2); uiIndex++)
    {
        cTemp = cString[uiIndex];
        cString[uiIndex] = cString[(eDigitNumber  - 1) - uiIndex];
        cString[(eDigitNumber  - 1) - uiIndex] = cTemp;
    }

}

/*
author : raad systems
date : 26/06/2017
function : Convert int to string
Param  : 
retrun :  
descriptiong : number of digits including sign '+' or '-'
*/

uint16_t dtcIntToString(int32_t sliValue,eDigits eNumberOfDigits,
                         uint8_t cString[])
{
    uint16_t uiErrorCode = 0;
    uint16_t uiIndex;
    uint16_t uiStringSize;
    uint16_t uiTempValue;
    uint32_t uliTempValue;
    int8_t cTempChar;

    /* Check for the sign of the given integer */
    if(sliValue >= 0)
    {
        uliTempValue = ((uint32_t)(sliValue));
    }
    else
    {
        uliTempValue = ((uint32_t)(-sliValue));
    }

    /* Generate digits in reverse order */
    for(uiIndex = 0U; uiIndex < (eNumberOfDigits - 1U); uiIndex++)
    {
        uiTempValue = (uint16_t)(uliTempValue % 10U);
        cString[uiIndex] = ((int8_t)(uiTempValue + 48U));
        uliTempValue = uliTempValue / 10U;
    }

    if(uiIndex == 0U)
    {
        cString[uiIndex] = '0';

    }

    /* Add sign to the string */
    if(sliValue < 0)
    {
        cString[uiIndex] = '-';
        uiIndex += 1U;
    }
    else
    {
        cString[uiIndex] = '+';
        uiIndex += 1U;
    }

    /* Add NULL character to the string to indicate the end of the string */
    cString[uiIndex] = '\0';

    uiStringSize = (uint16_t)(uiIndex - 1U);

    /* Reverse the string */
    for(uiIndex = 0U; uiIndex <= (uiStringSize / 2U); uiIndex++)
    {
        cTempChar = cString[uiIndex];
        cString[uiIndex] = cString[uiStringSize - uiIndex];
        cString[uiStringSize - uiIndex] = cTempChar;
    }

    return uiErrorCode;
}



void stringToUnsignedInt(uint8_t pString[],eDigits eDigitNumber,uint16_t *puiValue)
{
    
    uint16_t uiIndex;
 
    uint16_t uiValue;
   

    uiValue = 0U;

    for(uiIndex = 0U; uiIndex < eDigitNumber; uiIndex++)
    {
       
        if((pString[uiIndex] >= CHAR_0) && (pString[uiIndex] <= CHAR_9))
        {
               uiValue = (uiValue * 10U) + ((uint16_t)pString[uiIndex] - 48U);
        }
        else
        {
           
            break;
        }
   }

   *puiValue = uiValue;

}

void unsignedIntToStringHex(uint16_t uiValue, 
                                 eDigits eNumberOfDigits,
                                 uint8_t cString[])
{
    
    uint16_t uiIndex;
    int8_t cTemp;
    uint16_t uiTempValue;


    for(uiIndex = 0U; uiIndex < eNumberOfDigits; uiIndex++)
    {
        uiTempValue = ( (uiValue >> (4U * uiIndex) ) & 0x000FU);
        if(uiTempValue <= 9U)
        {
            /* 
            *  Note: Subtraction of 0U from uiTempValue in the below 
            *  statement is just to make the LDRA static analysis tool happy.
            */
            cTemp = ((int8_t)(0x30U) + (int8_t)(uiTempValue - 0U));
        }
        else
        {
            cTemp = (int8_t)(0x40U + (int8_t)(uiTempValue - 9U));
        }

        cString[uiIndex] =  cTemp;
    }
   
    cString[uiIndex] = '\0';

    for(uiIndex = 0U; uiIndex < (eNumberOfDigits / 2U); uiIndex++)
    {
        cTemp = cString[uiIndex];
        cString[uiIndex] = cString[(eNumberOfDigits - 1) - uiIndex];
        cString[(eNumberOfDigits - 1) - uiIndex] = cTemp;
    }
}

void dtcStringToSignedInt(int8_t cString[], eDigits eNumberOfDigits,
                               int16_t *psiValue)
{
    uint16_t uiIndex;
    int16_t siValue;


    siValue = 0;

    for(uiIndex = 1U; uiIndex < eNumberOfDigits; uiIndex++)
    {
        if((cString[uiIndex] >= CHAR_0) && (cString[uiIndex] <= CHAR_9))
        {
            siValue = (siValue * 10) + ((int16_t) cString[uiIndex] - 48);
        }
        else
        {
            //uiErrorCode = ERR_DTC_INV_INT_IN_STRING;
            break;
        }
    }


    /* Check and update for the sign of the integer */
    switch(cString[0])
    {
        case '-':
        {
            siValue = -siValue;
            break;
        }
        case '+':
        {
            /* Do nothing */
            break;
        }
        default:
        {
          //  uiErrorCode = ERR_DTC_INV_INT_IN_STRING;
            break;
        }
    }

    *psiValue = siValue;
}

int dcttoint(char str[])
{
    int len = strlen(str);
    unsigned int i, num = 0;
 
    for (i = 0; i < len; i++)
    {
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }
 
   return num;
}

int valid_digit(int8_t *ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            ++ip_str;
        else
            return 0;
    }
    return 1;
}

/*
author : Manu K Harshan
date : 26/06/2017
function : Convert Hex string to string
Param  :  
retrun :  no
descriptiong : 
*/

void HexStringToString(char* str, char* strH)
{
    size_t hexlength = strlen(strH);
      long i = 0;
      char a, b;
    for (; i < hexlength; i += 2) {
       a = strH[i + 0]; b = strH[i + 1];
       str[i / 2] =((a <= '9' ? a - '0' : a - 'A' + 10) << 4) + (b <= '9' ? b - '0' : b - 'A' + 10);
     }
    str[i / 2] = '\0';
}

/*
author : Manu K Harshan
date : 26/06/2017
function : Convert string to Hexstring
Param  :  
retrun :  no
descriptiong : 
*/

void StringToHexString(char* strH,char* str)
{
    int i,j;
    /*converting str character into Hex and adding into strH*/
    for(i=0,j=0;i<strlen(str);i++,j+=2)
    {
        sprintf((char*)strH+j,"%02x",str[i]);
    }
    strH[j]='\0'; /*adding NULL in the end*/
}