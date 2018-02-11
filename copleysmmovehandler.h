/* 
 * File:   copleysmmovehandler.h
 * Author: mgopianth
 *
 * Created on August 31, 2015, 10:33 PM
 */

#ifndef COPLEYSMMOVEHANDLER_H
#define	COPLEYSMMOVEHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "events.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "copleySmHandler.h"    
    
    
typedef enum
{
    INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP,
    INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP,
    INIT_MOVE_COPLEY_SET_VELOCITY,
    INIT_MOVE_COPLEY_SET_ACCEL_TIME,
    INIT_MOVE_COPLEY_SET_DECL_TIME,
    INIT_MOVE_COPLEY_SET_DESIRED_STATE,
    INIT_MOVE_COPLEY_START_MOVE,
    INIT_MOVE_WAIT_END,
    INIT_MOVE_END,        
}copleyInitMoveStates;


typedef enum
{
    MONITOR_MOVE_STATUS,
    REPORT_COMMANDS,
    IDLE,        
    STOP_MOVE       
}copletMonitorMOveStates;
copleySmStates copleySMRelativeMovePosition0(sysEvents *psSysEvt, bool *pbEventHandled);    
copleySmStates copleySMRelativeMovePosition1(sysEvents *psSysEvt, bool *pbEventHandled);    
copleySmStates copleySMRelativeMovePosition2(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition3(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition4(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition5(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition6(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition7(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition8(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition9(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition10(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition11(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition12(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition13(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition14(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition15(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition16(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition17(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition18(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition19(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition20(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition21(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition22(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition23(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition24(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMRelativeMovePosition25(sysEvents *psSysEvt, bool *pbEventHandled);

copleySmStates copleySMAbsoluteMovePosition0(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition1(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition2(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition3(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition4(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition5(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition6(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition7(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition8(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition9(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition10(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition11(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition12(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition13(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition14(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition15(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition16(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition17(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition18(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition19(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition20(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition21(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition22(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition23(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition24(sysEvents *psSysEvt, bool *pbEventHandled);
copleySmStates copleySMAbsoluteMovePosition25(sysEvents *psSysEvt, bool *pbEventHandled);


void copleyInitMove (sysEvents *psSysEvt, bool *pbEventHandled);
void copleySetInitMoveState(copleyInitMoveStates eColeyInitMoveState);
#ifdef	__cplusplus
}
#endif

#endif	/* COPLEYSMMOVEHANDLER_H */

