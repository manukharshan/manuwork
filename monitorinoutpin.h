/* 
 * File:   monitorinoutpin.h
 * Author: Manu K Harshan
 *
 * Created on 30 March, 2017, 11:49 AM
 */

#ifndef MONITORINOUTPIN_H
#define	MONITORINOUTPIN_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "pinconfiguration.h"    
#include "keypadevent.h"
#include "continuousMonitor.h"
#include "actionHandler.h"    
  
    
   
    
void monitorinput(void);

void reportKeypadEvent (eKeypadEvent eInputKeyPadEvent);
bool getKeypadEvent (eKeypadEvent *KeyPadEvent);
void disposeKeypadEvent (void);

void continuousMonitorKeypad(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MONITORINOUTPIN_H */

