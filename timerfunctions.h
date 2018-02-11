/* 
 * File:   timerfunctions.h
 * Author: Raad Sys
 *
 * Created on 6 September, 2015, 11:52 PM
 */

#ifndef TIMERFUNCTIONS_H
#define	TIMERFUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "events.h"
#include "app.h"
#include "string.h"
#include "stdlib.h"
    
#define MAX_TIMER 7

//bool millisecondcheck = false;    
    
typedef struct 
{
    uint16_t msec_timer;
    uint16_t timer_time;
    uint8_t timeout_flag;
    uint8_t timer_on;
    
}SOFT_TIMER;

SOFT_TIMER timer_array[MAX_TIMER];

#define MOTORTIMER  &timer_array[0]
#define LORATIMER &timer_array[1]
#define GSMTIMER &timer_array[2]
#define TCPTIMER &timer_array[3]
#define I2CTIMER &timer_array[4]
#define STATUSLED &timer_array[5]
#define HOMETIMER &timer_array[6]

void timerOperation(void);
void startTimer(SOFT_TIMER *timer_data,uint16_t timeMs);
void stopTimer(SOFT_TIMER *timer_data);
uint8_t  getTimeOutOccur(SOFT_TIMER *timer_data);
void interruptsetup(void);
#ifdef	__cplusplus
}
#endif

#endif	/* TIMERFUNCTIONS_H */

