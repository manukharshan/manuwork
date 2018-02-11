/* 
 * File:   copleySmHandler.h
 * Author: Davis
 *
 * Created on 27 August, 2015, 2:55 AM
 */

#ifndef COPLEYSMHANDLER_H
#define	COPLEYSMHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define MAX_CMD_LEN 20
    
#include "events.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
    /*Commands received and to be processed according to command index*/
    /*TODO: Add Commands*/

typedef enum 
{
    /* Motion related commands*/
    COPLEY_SM_IDLE,
    COPLEY_SM_EN_AMP_PGM_POSITION,
    COPLEY_SM_SET_ACCEL_TIME,
    COPLEY_SM_SET_DECL_TIME,
    COPLEY_SM_SET_ABORT_DECL_TIME,
    COPLEY_SM_SET_VELOCITY,
    COPLEY_SM_SET_JERK,
    COPLEY_SM_SET_TARGT_POSITION,
    COPLEY_SM_SET_PROFILE_TYPE,
    COPLEY_SM_START_MOVE,
    COPLEY_SM_STOP_MOVE,        
            COPLEY_SM_DUMMY_11,
            COPLEY_SM_DUMMY_12,
            COPLEY_SM_DUMMY_13,
            COPLEY_SM_DUMMY_14,
            COPLEY_SM_DUMMY_15,
            COPLEY_SM_DUMMY_16,
            COPLEY_SM_DUMMY_17,
            COPLEY_SM_DUMMY_18,
            COPLEY_SM_DUMMY_19,
            COPLEY_SM_DUMMY_20,
    /* Get parameters*/
    COPLEY_SM_GET_CURRENT_MOTOR_POSITION,
    COPLEY_SM_GET_MOTOR_CURRENT,
    COPLEY_SM_GET_FOLLOWING_ERROR,
    COPLEY_SM_GET_COMMANDED_POSITION,
    COPLEY_SM_GET_COPLEY_EVENT_STATUS,
            COPLEY_SM_DUMMY_26,
            COPLEY_SM_DUMMY_27,
            COPLEY_SM_DUMMY_28,
            COPLEY_SM_DUMMY_29,
            COPLEY_SM_DUMMY_30,
    /* Set Gain/ Limits Parameters*/
    /* Current Loop*/
    COPLEY_SM_SET_PEAK_CURRENT_LIMIT,
    COPLEY_SM_SET_I2T_TIME_LIMIT,
    COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT,
    COPLEY_SM_SET_CURRENT_LOOP_OFFSET,
    COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN,
    COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN,
            
    /* Velocity Loop*/
    COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT ,
    COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT,
    COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT,
    COPLEY_SM_SET_FAST_STOP_RAMP,
    COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN,
    COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN,
            
    /*Position Loop Gains*/
    COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN,
    COPLEY_SM_SET_POSIITON_LOOP_VFF,
    COPLEY_SM_SET_POSITION_LOOP_AFF,
    COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL,        
            COPLEY_SM_DUMMY_47,
            COPLEY_SM_DUMMY_48,
            COPLEY_SM_DUMMY_49,
            COPLEY_SM_DUMMY_50,
            
    /* Other Commands*/
    COPLEY_SM_DISABLE_DRIVE,
    COPLEY_SM_RESET_DRIVE,
    COPLEY_SM_CLEAR_FAULTS,
    COPLEY_SM_SET_CURR_POS_TO_ZERO,            
    COPLEY_SET_DIGITAL_BOARD_OUT,
    COPLEY_READ_DIGITAL_BOARD_INPUT,    
            COPLEY_SM_DUMMY_57,
            COPLEY_SM_DUMMY_58,
            COPLEY_SM_DUMMY_59,
            COPLEY_SM_DUMMY_60,
    /*Get Motion commands*/
    COPLEY_SM_GET_ACCEL_TIME,
    COPLEY_SM_GET_DECL_TIME,
    COPLEY_SM_GET_ABORT_DECL_TIME,
    COPLEY_SM_GET_VELOCITY,
    COPLEY_SM_GET_JERK,
    COPLEY_SM_GET_TARGT_POSITION,
            COPLEY_SM_DUMMY_67,
            COPLEY_SM_DUMMY_68,
            COPLEY_SM_DUMMY_69,
            COPLEY_SM_DUMMY_70,
    /* Get Gain/ Limits Parameters*/
    /* Current Loop*/
    COPLEY_SM_GET_PEAK_CURRENT_LIMIT,
    COPLEY_SM_GET_I2T_TIME_LIMIT,
    COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT,
    COPLEY_SM_GET_CURRENT_LOOP_OFFSET,
    COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN,
    COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN,
            
    /* Velocity Loop*/
    COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT ,
    COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT,
    COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT,
    COPLEY_SM_GET_FAST_STOP_RAMP,
    COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN,
    COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN,
            
    /*Position Loop Gains*/
    COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN,
    COPLEY_SM_GET_POSIITON_LOOP_VFF,
    COPLEY_SM_GET_POSITION_LOOP_AFF,
    COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL,        
            COPLEY_SM_DUMMY_87,
            COPLEY_SM_DUMMY_88,
            COPLEY_SM_DUMMY_89,
            COPLEY_SM_DUMMY_90,        
            
    COPLEY_SM_SET_CURRENT_POS_AS_HOME,
    COPLEY_SM_SET_SLOW_HOME_VELOCITY,
    COPLEY_SM_SET_HOME_ACCELARATION,
    COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW,
    COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH,
    COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE,
    COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE,
    COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME,
    COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME,
    COPLEY_SM_START_HOME,
    COPLEY_SM_SET_IN2_ACTIVE_HIGH,
    COPLEY_SM_SET_IN2_ACTIVE_LOW,
    COPLEY_SM_SET_HOME_OFFSET, 
            
    COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH,
    COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW,
    COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH,
    COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW,
            
#if 0        
    COPLEY_SM_GET_CURR_POSITION,
    COPLEY_SM_RELATIVE_MOVE_POSITION_0,        
    COPLEY_SM_RELATIVE_MOVE_POSITION_1,
    COPLEY_SM_RELATIVE_MOVE_POSITION_2,
    COPLEY_SM_RELATIVE_MOVE_POSITION_3,
    COPLEY_SM_RELATIVE_MOVE_POSITION_4,
    COPLEY_SM_RELATIVE_MOVE_POSITION_5,
    COPLEY_SM_RELATIVE_MOVE_POSITION_6,
    COPLEY_SM_RELATIVE_MOVE_POSITION_7,
    COPLEY_SM_RELATIVE_MOVE_POSITION_8,
    COPLEY_SM_RELATIVE_MOVE_POSITION_9,
    COPLEY_SM_RELATIVE_MOVE_POSITION_10,
    COPLEY_SM_RELATIVE_MOVE_POSITION_11,
    COPLEY_SM_RELATIVE_MOVE_POSITION_12,
    COPLEY_SM_RELATIVE_MOVE_POSITION_13,
    COPLEY_SM_RELATIVE_MOVE_POSITION_14,
    COPLEY_SM_RELATIVE_MOVE_POSITION_15,
    COPLEY_SM_RELATIVE_MOVE_POSITION_16,
    COPLEY_SM_RELATIVE_MOVE_POSITION_17,
    COPLEY_SM_RELATIVE_MOVE_POSITION_18,
    COPLEY_SM_RELATIVE_MOVE_POSITION_19,
    COPLEY_SM_RELATIVE_MOVE_POSITION_20,
    COPLEY_SM_RELATIVE_MOVE_POSITION_21,
    COPLEY_SM_RELATIVE_MOVE_POSITION_22,
    COPLEY_SM_RELATIVE_MOVE_POSITION_23,
    COPLEY_SM_RELATIVE_MOVE_POSITION_24,
    COPLEY_SM_RELATIVE_MOVE_POSITION_25,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_0,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_1,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_2,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_3,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_4,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_5,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_6,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_7,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_8,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_9,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_10,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_11,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_12,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_13,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_14,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_15,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_16,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_17,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_18,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_19,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_20,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_21,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_22,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_23,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_24,
    COPLEY_SM_ABSOLUTE_MOVE_POSITION_25,
            
#endif
    COPLEY_SM_MONITOR_MOVE_STATUS,        
    COPLEY_SM_MAX_STATE
}copleySmStates;
//
//typedef union
//{
//    uint16_t uiDigitalInputStatus;
//    
//    struct
//    {
//        uint8_t ucInputOne:1;
//        uint8_t ucInputTwo:1;
//        uint8_t ucInputThree:1;
//        uint8_t ucInputFour:1;
//        uint8_t ucInputFive:1;
//        uint8_t ucInputSix:1;
//        uint8_t ucInputSeven:1;
//        uint8_t ucInputEight:1;
//        
//    }SinputStatus;
//}UInputStatus;
//
//
//typedef struct
//{
//    copleySmStates eCopleySmStates;
//    copleySmStates(*SmFuncitons)(sysEvents*,bool*);
//}smTable;
//
//
//copleySmStates copleySmHandler(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleyStateIdle(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleyEnablePrgPositionMode(sysEvents *psSysEvt, bool *pbEventHandled);
void copleySMStateEntryActions(copleySmStates eCopleyStates);
//copleySmStates copleySMSetPositionToZero(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMGetPosition(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMGetEventStatus(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMGetCommandedPosition(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMGetFollowingError(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMGetMotorCurrent(sysEvents *psSysEvt, bool *pbEventHandled);
//
//
//copleySmStates copleySMSetAccelTime(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetDeclTime(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetAbortDeclTime(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetVelocity(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetJerk(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetTargetPosition(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySmSetProfileType(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMStartMove(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMStopMove(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMMonitorMoveStatus(sysEvents *psSysEvt, bool *pbEventHandled);
////copleySmStates copleySMDummy_10(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_11(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_12(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_13(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_14(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_15(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_16(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_17(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_18(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_19(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_20(sysEvents *psSysEvt, bool *pbEventHandled);
//
//copleySmStates copleySMDummy_26(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_27(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_28(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_29(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_30(sysEvents *psSysEvt, bool *pbEventHandled);
//
//
//copleySmStates copleySMSetPeakCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetI2TTimeLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetContinuousCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetCurrentLoopOffset(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetCLPG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetCurrentLPIG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetVLVelLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetVLAccelLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetVLDeclLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetFastStopRamp(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetVLPG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetVLIG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetPLPG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySetPositionLoopVFF(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySetPositionLoopAFF(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetPLGainMul(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_47(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_48(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_49(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_50(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDisableDrive(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates coleySMresetDrive(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMclearFaults(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetPositionToZero(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySetDigitalBoardOut(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleyReadDigitalBoardInput(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_57(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_58(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_59(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_60(sysEvents *psSysEvt, bool *pbEventHandled);
//
//copleySmStates copleySMgetAccelTime(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetDeclTime(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetAbortDeclTime(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetVelocity(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetJerk(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetTargetPosition(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_67(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_68(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_69(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_70(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetPeakCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetI2TTimeLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetContinuousCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetCurrentLoopOffset(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetCLPG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetCurrentLPIG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetVLVelLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetVLAccelLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetVLDeclLimit(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetFastStopRamp(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetVLPG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetVLIG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetPLPG(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleygetPositionLoopVFF(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleygetPositionLoopAFF(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMgetPLGainMul(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_87(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_88(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_89(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMDummy_90(sysEvents *psSysEvt, bool *pbEventHandled);
//
//copleySmStates copleySMSetCurrentPosasHome(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetSlowHomeVelocity(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetHomeAccelaration(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2HomeActiveLow(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2HomeActiveHigh(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetHomeDireationMovepositive(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copelySMSetHomeDireationMoveNegative(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetPositiveHardStopasHome(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetNegativeHardStopasHome(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMstatHomeMove(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2ActiveHigh(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2ActiveLow(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetOffset(sysEvents *psSysEvt, bool *pbEventHandled);
//
//copleySmStates copleySMSetIN2PosLimSwActHigh(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2PosLimSwActLow(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2NegLimSwActHigh(sysEvents *psSysEvt, bool *pbEventHandled);
//copleySmStates copleySMSetIN2NegLimSwActLow(sysEvents *psSysEvt, bool *pbEventHandled);
//void initCopleySMHandler (void);
#ifdef	__cplusplus
}
#endif

#endif	/* COPLEYSMHANDLER_H */

