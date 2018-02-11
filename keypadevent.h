/* 
 * File:   keypadevent.h
 * Author: Manu K Harshan
 *
 * Created on 30 March, 2017, 11:19 AM
 */

#ifndef KEYPADEVENT_H
#define	KEYPADEVENT_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include "keypadevent.h"
    
//#define PUSH_BTN PORTAbits.RA0

//#define SLEEPWAKE_DELAY 3000
#define DEBOUNCE_DELAY 70
#define CONTINUOUS_PRESS_DELAY 1000     

#define PRESS 0
#define RELEASE 1

typedef enum
{
    KEY_RELEASED,        
    KEY_PRESSED
}eKeyPressEvent;

typedef enum
{
    JOGOPENBUTTON_RELEASED,
    JOGOPENBUTTON_PRESSED,
    JOGCLOSEBUTTON_RELEASED,
    JOGCLOSEBUTTON_PRESSED,            
    KEY_ID_EVENT_MAX                  
}eKeypadEvent;

enum
{
    JOG_VALVE_OPEN,
    JOG_VALVE_CLOSE,
    MAX_NO_OF_KEY
};

typedef struct
{
  eKeyPressEvent gEKeypadPressEvent;
  unsigned short int uiDebounceCDelayCounter;
  unsigned short int uiContinuousPressDelayCounter;
}SKeyPressedEvent;

typedef struct
{
    unsigned short int uiInPtr;
    unsigned short int uiOutPtr;
    unsigned short int uiProcessesCounter;
    
}SysCirBuffer1;    

//void reportKeypadEvent (eKeypadEvent eInputKeyPadEvent);
//bool getKeypadEvent (eKeypadEvent *KeyPadEvent);
//void disposeKeypadEvent (void);

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPADEVENT_H */

