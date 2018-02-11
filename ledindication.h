/* 
 * File:   ledindication.h
 * Author: Manu K Harshan
 *
 * Created on 4 April, 2017, 10:46 AM
 */

#ifndef LEDINDICATION_H
#define	LEDINDICATION_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "p32xxxx.h"
#include <stdbool.h>
    
#if 0
#define LEDINDICATION1 PORTCbits.RC14
#define LEDINDICATION2 PORTEbits.RE0
#define LEDINDICATION3 PORTEbits.RE1
#define LEDINDICATION4 PORTDbits.RD1
#define LEDINDICATION5 PORTFbits.RF4
#define LEDINDICATION6 PORTBbits.RB10
#define LEDINDICATION7 PORTDbits.RD9
#define LEDINDICATION8 PORTDbits.RD10
#define LEDINDICATION9 PORTDbits.RD15
#define LEDINDICATION10 PORTAbits.RA15
    
#endif 
    
#define LEDINDICATION10 LATCbits.LATC14
#define LEDINDICATION9 LATEbits.LATE0
#define LEDINDICATION8 LATEbits.LATE1
#define LEDINDICATION7 LATDbits.LATD1
#define LEDINDICATION6 LATFbits.LATF4
#define LEDINDICATION5 LATBbits.LATB10
#define LEDINDICATION4 LATDbits.LATD9
#define LEDINDICATION3 LATDbits.LATD10
#define LEDINDICATION2 LATDbits.LATD15
#define LEDINDICATION1 LATAbits.LATA15

#define YELLOWLED LATAbits.LATA10
#define REDLED LATCbits.LATC13    
#define GREENLED LATAbits.LATA7
#define ORANGELED LATAbits.LATA9
    
#define LEDON 1U
#define LEDOFF 0U    

typedef enum
{
    VALVEOPEN,
    VALVETENPERCLOSE,
    VALVETWENTYPERCLOSE,
    VALVETHIRTYPERCLOSE,
    VALVEFOURTYPERCLOSE,
    VALVEFIFTYPERCLOSE,
    VALVESIXTYPERCLOSE,
    VALVESEVENTYPERCLOSE,
    VALVEEIGHTYPERCLOSE,
    VALVENINETYPERCLOSE,
    VALVECLOSE,
}eledindicationState;

typedef enum
{
    VALVE_IDLE,
    VALVE_FAULT_BLINK,
    VALVE_HOME_BLINK,        
    VALVE_DEFAULT,        
}eStatusindicationState;

void ledPinitialize(void);
void ledindicationTask(void);
void taskStatusLedIndication(void);

eStatusindicationState getStatusledindicationState(void);
void setStatusledindicationState(eStatusindicationState ledindicationState);

eledindicationState getledindicationstate(void);
void setledinidicationstate(eledindicationState ledindicationState);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDINDICATION_H */

