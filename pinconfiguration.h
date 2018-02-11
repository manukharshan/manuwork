/* 
 * File:   pinconfiguration.h
 * Author: Manu k Harshan
 *
 * Created on 30 March, 2017, 10:49 AM
 */

#ifndef PINCONFIGURATION_H
#define	PINCONFIGURATION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "p32xxxx.h"    

 //#define STOP_BTN PORTAbits.RA0
 #define JOGOPENVALVE_BTN PORTEbits.RE7
 #define JOGCLOSEVALVE_BTN PORTEbits.RE6
   



#ifdef	__cplusplus
}
#endif

#endif	/* PINCONFIGURATION_H */

