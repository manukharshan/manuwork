/* 
 * File:   gsmMonitorStatus.h
 * Author: Manu K Harshan
 *
 * Created on 7 March, 2017, 11:42 AM
 */

#ifndef GSMMONITORSTATUS_H
#define	GSMMONITORSTATUS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "gsmSmHandler.h"    
#include "gsmevents.h"    
    

gsmSmStates gsmMonitorSignalStrength(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate);
void signalStrenthindication(void);


#ifdef	__cplusplus
}
#endif

#endif	/* GSMMONITORSTATUS_H */

