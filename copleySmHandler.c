#include "copleySmHandler.h"
#include "copleytransmithandler.h"
#include "events.h"
#include "app.h"
#include "string.h"
#include "stdlib.h"
//#include "copleysmmovehandler.h"
#include "tcpiphandler.h"
#include "timerfunctions.h"
#include "datatypeconversion.h"
//static copleySmStates geCopleySmStates = COPLEY_SM_IDLE;
//static copletMonitorMOveStates geCopleMonitorMoveStates;
//static UInputStatus guInputStatus;
//static tcpipReceivePacket tcpIpMonitorReceivepacket;
//static uint16_t guiTempCommand;
//static smTable gsSMTable[COPLEY_SM_MAX_STATE] = 
//{
//    {.eCopleySmStates = COPLEY_SM_IDLE, .SmFuncitons = copleyStateIdle},
//    {.eCopleySmStates = COPLEY_SM_EN_AMP_PGM_POSITION, .SmFuncitons = copleyEnablePrgPositionMode},
//    {.eCopleySmStates = COPLEY_SM_SET_ACCEL_TIME, .SmFuncitons = copleySMSetAccelTime},
//    {.eCopleySmStates = COPLEY_SM_SET_DECL_TIME, .SmFuncitons = copleySMSetDeclTime},
//    {.eCopleySmStates = COPLEY_SM_SET_ABORT_DECL_TIME, .SmFuncitons = copleySMSetAbortDeclTime},
//    {.eCopleySmStates = COPLEY_SM_SET_VELOCITY, .SmFuncitons = copleySMSetVelocity},
//    {.eCopleySmStates = COPLEY_SM_SET_JERK, .SmFuncitons = copleySMSetJerk},
//    {.eCopleySmStates = COPLEY_SM_SET_TARGT_POSITION, .SmFuncitons = copleySMSetTargetPosition},
//    {.eCopleySmStates = COPLEY_SM_SET_PROFILE_TYPE, .SmFuncitons = copleySmSetProfileType},
//    {.eCopleySmStates = COPLEY_SM_START_MOVE, .SmFuncitons = copleySMStartMove},
//    {.eCopleySmStates = COPLEY_SM_STOP_MOVE, .SmFuncitons = copleySMStopMove},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_11, .SmFuncitons = copleySMDummy_11},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_12, .SmFuncitons = copleySMDummy_12},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_13, .SmFuncitons = copleySMDummy_13},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_14, .SmFuncitons = copleySMDummy_14},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_15, .SmFuncitons = copleySMDummy_15},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_16, .SmFuncitons = copleySMDummy_16},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_17, .SmFuncitons = copleySMDummy_17},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_18, .SmFuncitons = copleySMDummy_18},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_19, .SmFuncitons = copleySMDummy_19},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_20, .SmFuncitons = copleySMDummy_20},
//    {.eCopleySmStates = COPLEY_SM_GET_CURRENT_MOTOR_POSITION, .SmFuncitons = copleySMGetPosition},
//    {.eCopleySmStates = COPLEY_SM_GET_MOTOR_CURRENT,.SmFuncitons = copleySMGetMotorCurrent},
//    {.eCopleySmStates = COPLEY_SM_GET_FOLLOWING_ERROR,.SmFuncitons = copleySMGetFollowingError},
//    {.eCopleySmStates = COPLEY_SM_GET_COMMANDED_POSITION,.SmFuncitons = copleySMGetCommandedPosition},
//    {.eCopleySmStates = COPLEY_SM_GET_COPLEY_EVENT_STATUS, .SmFuncitons = copleySMGetEventStatus},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_26, .SmFuncitons = copleySMDummy_26},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_27, .SmFuncitons = copleySMDummy_27},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_28, .SmFuncitons = copleySMDummy_28},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_29, .SmFuncitons = copleySMDummy_29},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_30, .SmFuncitons = copleySMDummy_30},
//    {.eCopleySmStates = COPLEY_SM_SET_PEAK_CURRENT_LIMIT, .SmFuncitons = copleySMSetPeakCurrentLimit},
//    {.eCopleySmStates = COPLEY_SM_SET_I2T_TIME_LIMIT, .SmFuncitons = copleySMSetI2TTimeLimit},
//    {.eCopleySmStates = COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT, .SmFuncitons = copleySMSetContinuousCurrentLimit},
//    {.eCopleySmStates = COPLEY_SM_SET_CURRENT_LOOP_OFFSET, .SmFuncitons = copleySMSetCurrentLoopOffset},
//    {.eCopleySmStates = COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN, .SmFuncitons = copleySMSetCLPG},
//    {.eCopleySmStates = COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN, .SmFuncitons = copleySMSetCurrentLPIG},
//    {.eCopleySmStates = COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT, .SmFuncitons = copleySMSetVLVelLimit},
//    {.eCopleySmStates = COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT, .SmFuncitons = copleySMSetVLAccelLimit},
//    {.eCopleySmStates = COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT, .SmFuncitons = copleySMSetVLDeclLimit},
//    {.eCopleySmStates = COPLEY_SM_SET_FAST_STOP_RAMP, .SmFuncitons = copleySMSetFastStopRamp},
//    {.eCopleySmStates = COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN, .SmFuncitons = copleySMSetVLPG},
//    {.eCopleySmStates = COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN, .SmFuncitons = copleySMSetVLIG},
//    {.eCopleySmStates = COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN, .SmFuncitons = copleySMSetPLPG},
//    {.eCopleySmStates = COPLEY_SM_SET_POSIITON_LOOP_VFF, .SmFuncitons = copleySetPositionLoopVFF},
//    {.eCopleySmStates = COPLEY_SM_SET_POSITION_LOOP_AFF, .SmFuncitons = copleySetPositionLoopAFF},
//    {.eCopleySmStates = COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL, .SmFuncitons = copleySMSetPLGainMul},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_47, .SmFuncitons = copleySMDummy_47},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_48, .SmFuncitons = copleySMDummy_48},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_49, .SmFuncitons = copleySMDummy_49},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_50, .SmFuncitons = copleySMDummy_50},
//    {.eCopleySmStates = COPLEY_SM_DISABLE_DRIVE, .SmFuncitons = copleySMDisableDrive},
//    {.eCopleySmStates = COPLEY_SM_RESET_DRIVE, .SmFuncitons = coleySMresetDrive},
//    {.eCopleySmStates = COPLEY_SM_CLEAR_FAULTS, .SmFuncitons = copleySMclearFaults},
//    {.eCopleySmStates = COPLEY_SM_SET_CURR_POS_TO_ZERO, .SmFuncitons = copleySMSetPositionToZero},
//    {.eCopleySmStates = COPLEY_SET_DIGITAL_BOARD_OUT, .SmFuncitons = copleySetDigitalBoardOut},
//    {.eCopleySmStates = COPLEY_READ_DIGITAL_BOARD_INPUT, .SmFuncitons = copleyReadDigitalBoardInput},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_57, .SmFuncitons = copleySMDummy_57},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_58, .SmFuncitons = copleySMDummy_58},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_59, .SmFuncitons = copleySMDummy_59},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_60, .SmFuncitons = copleySMDummy_60},
//    /*  Get Parameters*/
//    {.eCopleySmStates = COPLEY_SM_GET_ACCEL_TIME, .SmFuncitons = copleySMgetAccelTime},
//    {.eCopleySmStates = COPLEY_SM_GET_DECL_TIME, .SmFuncitons = copleySMgetDeclTime},
//    {.eCopleySmStates = COPLEY_SM_GET_ABORT_DECL_TIME, .SmFuncitons = copleySMgetAbortDeclTime},
//    {.eCopleySmStates = COPLEY_SM_GET_VELOCITY, .SmFuncitons = copleySMgetVelocity},
//    {.eCopleySmStates = COPLEY_SM_GET_JERK, .SmFuncitons = copleySMgetJerk},
//    {.eCopleySmStates = COPLEY_SM_GET_TARGT_POSITION, .SmFuncitons = copleySMgetTargetPosition},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_67, .SmFuncitons = copleySMDummy_67},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_68, .SmFuncitons = copleySMDummy_68},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_69, .SmFuncitons = copleySMDummy_69},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_70, .SmFuncitons = copleySMDummy_70},
//    
//    {.eCopleySmStates = COPLEY_SM_GET_PEAK_CURRENT_LIMIT, .SmFuncitons = copleySMgetPeakCurrentLimit},
//    {.eCopleySmStates = COPLEY_SM_GET_I2T_TIME_LIMIT, .SmFuncitons = copleySMgetI2TTimeLimit},
//    {.eCopleySmStates = COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT, .SmFuncitons = copleySMgetContinuousCurrentLimit},
//    {.eCopleySmStates = COPLEY_SM_GET_CURRENT_LOOP_OFFSET, .SmFuncitons = copleySMgetCurrentLoopOffset},
//    {.eCopleySmStates = COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN, .SmFuncitons = copleySMgetCLPG},
//    {.eCopleySmStates = COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN, .SmFuncitons = copleySMgetCurrentLPIG},
//    {.eCopleySmStates = COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT, .SmFuncitons = copleySMgetVLVelLimit},
//    {.eCopleySmStates = COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT, .SmFuncitons = copleySMgetVLAccelLimit},
//    {.eCopleySmStates = COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT, .SmFuncitons = copleySMgetVLDeclLimit},
//    {.eCopleySmStates = COPLEY_SM_GET_FAST_STOP_RAMP, .SmFuncitons = copleySMgetFastStopRamp},
//    {.eCopleySmStates = COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN, .SmFuncitons = copleySMgetVLPG},
//    {.eCopleySmStates = COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN, .SmFuncitons = copleySMgetVLIG},
//    {.eCopleySmStates = COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN, .SmFuncitons = copleySMgetPLPG},
//    {.eCopleySmStates = COPLEY_SM_GET_POSIITON_LOOP_VFF, .SmFuncitons = copleygetPositionLoopVFF},
//    {.eCopleySmStates = COPLEY_SM_GET_POSITION_LOOP_AFF, .SmFuncitons = copleygetPositionLoopAFF},
//    {.eCopleySmStates = COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL, .SmFuncitons = copleySMgetPLGainMul},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_87, .SmFuncitons = copleySMDummy_87},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_88, .SmFuncitons = copleySMDummy_88},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_89, .SmFuncitons = copleySMDummy_89},
//    {.eCopleySmStates = COPLEY_SM_DUMMY_90, .SmFuncitons = copleySMDummy_90},
//    {.eCopleySmStates = COPLEY_SM_SET_CURRENT_POS_AS_HOME, .SmFuncitons = copleySMSetCurrentPosasHome},
//    {.eCopleySmStates = COPLEY_SM_SET_SLOW_HOME_VELOCITY, .SmFuncitons = copleySMSetSlowHomeVelocity},
//    {.eCopleySmStates = COPLEY_SM_SET_HOME_ACCELARATION, .SmFuncitons = copleySMSetHomeAccelaration},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW, .SmFuncitons = copleySMSetIN2HomeActiveLow},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH, .SmFuncitons = copleySMSetIN2HomeActiveHigh},
//    {.eCopleySmStates = COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE, .SmFuncitons = copleySMSetHomeDireationMovepositive},
//    {.eCopleySmStates = COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE, .SmFuncitons = copelySMSetHomeDireationMoveNegative},
//    {.eCopleySmStates = COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME, .SmFuncitons = copleySMSetPositiveHardStopasHome},
//    {.eCopleySmStates = COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME, .SmFuncitons = copleySMSetNegativeHardStopasHome},
//    {.eCopleySmStates = COPLEY_SM_START_HOME, .SmFuncitons = copleySMstatHomeMove},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_ACTIVE_HIGH, .SmFuncitons = copleySMSetIN2ActiveHigh},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_ACTIVE_LOW, .SmFuncitons = copleySMSetIN2ActiveLow},
//    {.eCopleySmStates = COPLEY_SM_SET_HOME_OFFSET, .SmFuncitons = copleySMSetOffset},
//    
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH, .SmFuncitons = copleySMSetIN2PosLimSwActHigh},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW, .SmFuncitons = copleySMSetIN2PosLimSwActLow},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH, .SmFuncitons = copleySMSetIN2NegLimSwActHigh},
//    {.eCopleySmStates = COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW, .SmFuncitons = copleySMSetIN2NegLimSwActLow},
//    
//    
//    
//    {.eCopleySmStates = COPLEY_SM_MONITOR_MOVE_STATUS,.SmFuncitons = copleySMMonitorMoveStatus}
//};
//
//uint8_t gucCopleyParameter[30];
//
//void initCopleySMHandler (void)
//{
//    geCopleySmStates = COPLEY_SM_IDLE;
//    geCopleMonitorMoveStates = IDLE;
//    guiTempCommand = 0;
//}
//
//copleySmStates copleySmHandler(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    smTable *sSmTab = gsSMTable;
//    while (sSmTab != &gsSMTable[COPLEY_SM_MAX_STATE])
//    {
//        if (sSmTab->eCopleySmStates == geCopleySmStates)
//        {
//            break;
//        }
//        sSmTab ++;
//    }
//    
//    geCopleySmStates = sSmTab->SmFuncitons(psSysEvt,pbEventHandled);
//    
//    return geCopleySmStates;
//}
//
//
//
//copleySmStates copleyStateIdle(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_IDLE;
//    *pbEventHandled = false;
//    uint16_t uiTempCommand;
//    uint16_t uiTempCounter;
//    stringToUnsignedInt(psSysEvt->sTcpipRecvData.ucCommandByte,DIGIT_3,&uiTempCommand);
//    
//    memset(&gucCopleyParameter[0],'\0',sizeof(gucCopleyParameter));
//    uiTempCounter = 3U;
//    while((psSysEvt->sTcpipRecvData.ucCommandByte[uiTempCounter] != '\r') && (psSysEvt->sTcpipRecvData.ucCommandByte[uiTempCounter] != '\0'))
//    {
//        gucCopleyParameter[uiTempCounter - 3] = psSysEvt->sTcpipRecvData.ucCommandByte[uiTempCounter];
//        uiTempCounter ++;
//    }
//    gucCopleyParameter[uiTempCounter - 3] = '\0';
//   
//    
//    if ((uiTempCommand < 500) && (uiTempCommand > 0))
//    {
//        eCopleyState = uiTempCommand;
//        copleySMStateEntryActions(eCopleyState);
//        if (uiTempCommand == COPLEY_SM_RESET_DRIVE)
//        {
//            eCopleyState = COPLEY_SM_IDLE;
//        }
//    }
//    return eCopleyState;
//}
//
//
//
//
//
//
//
//
//
//copleySmStates copleyEnablePrgPositionMode(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_EN_AMP_PGM_POSITION;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_EN_AMP_PGM_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_EN_AMP_PGM_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetAccelTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_ACCEL_TIME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_ACCEL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_ACCEL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//
//copleySmStates copleySMSetDeclTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_DECL_TIME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetAbortDeclTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_ABORT_DECL_TIME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_ABORT_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_ABORT_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetVelocity(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetJerk(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_JERK;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetTargetPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_TARGT_POSITION;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//
//copleySmStates copleySmSetProfileType(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_PROFILE_TYPE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_PROFILE_TYPE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_PROFILE_TYPE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMStartMove(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_START_MOVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_START_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_START_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        //eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
//        //copleySMStateEntryActions(eCopleyState);
//        eCopleyState = COPLEY_SM_IDLE;
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//copleySmStates copleySMStopMove(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_STOP_MOVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_STOP_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_STOP_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        eCopleyState = COPLEY_SM_IDLE;
//        copleySMStateEntryActions(eCopleyState);
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//copleySmStates copleySMMonitorMoveStatus(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
//    
//    uint8_t *pucComplete = "Move Completed\r";
//    uint8_t *pucStop = "Move Stopped\r";
//    if(psSysEvt->eTypeEvent == COPLEY_MESSAGE || psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        *pbEventHandled = false;
//        stopCopleyTimeOutTimer();
//        
//        switch (geCopleMonitorMoveStates)
//        {
//            case MONITOR_MOVE_STATUS:
//            {
//                if(!tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//                {
//                    tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//                }
//                
//                if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
//                {
//                    eCopleyState = COPLEY_SM_IDLE;
//                    
//                    if(!tcpIPSendMesg(COPLEY_SM_START_MOVE,pucComplete,psSysEvt->sTcpipRecvData.ucCommSel))
//                    {
//                        tcpIPSendMesg(COPLEY_SM_START_MOVE,pucComplete,psSysEvt->sTcpipRecvData.ucCommSel);
//                    }     
//                }
//                
//                geCopleMonitorMoveStates = IDLE;
//                break;
//            }
//            case REPORT_COMMANDS:
//            {
//                
//                if(!tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//                {
//                    tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//                }
//               
//                geCopleMonitorMoveStates = IDLE;
//                break;
//            }
//            case STOP_MOVE:
//            {
//                if(!tcpIPSendMesg(guiTempCommand,pucStop,psSysEvt->sTcpipRecvData.ucCommSel))
//                {
//                    tcpIPSendMesg(guiTempCommand,pucStop,psSysEvt->sTcpipRecvData.ucCommSel);
//                }
//                eCopleyState = COPLEY_SM_IDLE;
//                
//                geCopleMonitorMoveStates = IDLE;
//                break;
//            }
//        }                 
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(guiTempCommand);
//        *pbEventHandled = false;
//    }
//    else if (TCPIP_EVENT_OCCURED == psSysEvt->eTypeEvent)
//    {
//        *pbEventHandled = false;
//        if(IDLE == geCopleMonitorMoveStates)
//        {
//            *pbEventHandled = true;
//            stringToUnsignedInt(psSysEvt->sTcpipRecvData.ucCommandByte,DIGIT_3,&guiTempCommand);
//    
//            if ((guiTempCommand < 500) && (guiTempCommand > 0))
//            {
//
//                if (guiTempCommand == 10)
//                {
//                    geCopleMonitorMoveStates = STOP_MOVE;
//                    copleySMStateEntryActions(guiTempCommand);
//                    
//                }
//                else if (guiTempCommand == 25)
//                {
//                    copleySMStateEntryActions(guiTempCommand);
//                    geCopleMonitorMoveStates = MONITOR_MOVE_STATUS;  
//                }
//                else
//                {
//                    copleySMStateEntryActions(guiTempCommand);
//                    geCopleMonitorMoveStates = REPORT_COMMANDS;
//                    
//                }
//            }
//        }  
//    }
//    
//    return eCopleyState;
//}
//
///*copleySmStates copleySMDummy_10(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}*/
//
//copleySmStates copleySMDummy_11(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_12(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_13(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_14(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_15(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_16(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_17(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_18(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_19(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_20(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//
//
//
//
//
//
//copleySmStates copleySMGetPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_MOTOR_POSITION;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_MOTOR_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_MOTOR_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMGetMotorCurrent(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_GET_MOTOR_CURRENT;
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_MOTOR_CURRENT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_MOTOR_CURRENT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMGetFollowingError(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_GET_FOLLOWING_ERROR;
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_FOLLOWING_ERROR,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_FOLLOWING_ERROR,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    return eCopleyState;
//}
//
//copleySmStates copleySMGetCommandedPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_GET_COMMANDED_POSITION;
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_COMMANDED_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_COMMANDED_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    return eCopleyState;
//}
//
//copleySmStates copleySMGetEventStatus(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_COPLEY_EVENT_STATUS;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_COPLEY_EVENT_STATUS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_COPLEY_EVENT_STATUS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMDummy_26(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_27(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_28(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_29(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_30(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//
//
//
//
//copleySmStates copleySMSetPeakCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_PEAK_CURRENT_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetI2TTimeLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_I2T_TIME_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetContinuousCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetCurrentLoopOffset(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_LOOP_OFFSET;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetCLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetCurrentLPIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLVelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLAccelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLDeclLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetFastStopRamp(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_FAST_STOP_RAMP;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetPLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySetPositionLoopVFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSIITON_LOOP_VFF;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySetPositionLoopAFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITION_LOOP_AFF;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetPLGainMul(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMDummy_47(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_48(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_49(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_50(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDisableDrive(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_DISABLE_DRIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_DISABLE_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_DISABLE_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates coleySMresetDrive(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_RESET_DRIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_RESET_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_RESET_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMclearFaults(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_CLEAR_FAULTS;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_CLEAR_FAULTS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_CLEAR_FAULTS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetPositionToZero(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURR_POS_TO_ZERO;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURR_POS_TO_ZERO,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURR_POS_TO_ZERO,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySetDigitalBoardOut(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SET_DIGITAL_BOARD_OUT;
//    
//    uint16_t uiTemStatus,uiOutputNumber;
//
//    if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        stringToUnsignedInt(&gucCopleyParameter[0],DIGIT_1,&uiOutputNumber);
//        stringToUnsignedInt(&gucCopleyParameter[1],DIGIT_1,&uiTemStatus);
//
//
//        switch (uiOutputNumber)
//        {
//            case 1:
//            {
//                LATAbits.LATA1 = uiTemStatus;
//                break;
//            }
//            case 2:
//            {
//                LATAbits.LATA2 = uiTemStatus;
//                break;
//            }
//            case 3:
//            {
//                LATAbits.LATA3 = uiTemStatus;
//                break;
//            }
//            case 4:
//            {
//                LATAbits.LATA4 = uiTemStatus;
//                break;
//            }
//            case 5:
//            {
//                LATAbits.LATA6 = uiTemStatus;
//                break;
//            }
//            case 6:
//            {
//                LATAbits.LATA7 = uiTemStatus;
//                break;
//            }
//            case 7:
//            {
//                LATAbits.LATA14 = uiTemStatus;
//                break;
//            }
//            case 8:
//            {
//                LATAbits.LATA15 = uiTemStatus;
//                break;
//            }
//            default:
//            {
//
//            }
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleyReadDigitalBoardInput(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_READ_DIGITAL_BOARD_INPUT;
//    uint8_t ucMesage[10];
//    
//    if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        
//        stopCopleyTimeOutTimer();
//        
//        guInputStatus.SinputStatus.ucInputOne = PORTEbits.RE0;
//        guInputStatus.SinputStatus.ucInputTwo = PORTEbits.RE1;
//        guInputStatus.SinputStatus.ucInputThree = PORTEbits.RE2;
//        guInputStatus.SinputStatus.ucInputFour = PORTEbits.RE3;
//        guInputStatus.SinputStatus.ucInputFive = PORTEbits.RE4;
//        guInputStatus.SinputStatus.ucInputSix = PORTEbits.RE6;
//        guInputStatus.SinputStatus.ucInputSeven = PORTEbits.RE7;
//        guInputStatus.SinputStatus.ucInputEight = PORTEbits.RE8;
//        
//        
//        unsignedIntToStringHex(guInputStatus.uiDigitalInputStatus,DIGIT_2,&ucMesage[0]);
//        ucMesage[2] = '\r';
//        if(!tcpIPSendMesg(COPLEY_READ_DIGITAL_BOARD_INPUT,&ucMesage[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_READ_DIGITAL_BOARD_INPUT,&ucMesage[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//     
//    return eCopleyState;
//}
//
//copleySmStates copleySMDummy_57(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_58(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_59(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_60(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMgetAccelTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_ACCEL_TIME;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_ACCEL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_ACCEL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetDeclTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_DECL_TIME;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//    
//copleySmStates copleySMgetAbortDeclTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_ABORT_DECL_TIME;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_ABORT_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_ABORT_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMgetVelocity(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetJerk(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_JERK;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetTargetPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_TARGT_POSITION;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMDummy_67(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_68(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_69(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_70(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMgetPeakCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_PEAK_CURRENT_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetI2TTimeLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_I2T_TIME_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetContinuousCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetCurrentLoopOffset(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_LOOP_OFFSET;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetCLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetCurrentLPIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLVelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLAccelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLDeclLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetFastStopRamp(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_FAST_STOP_RAMP;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetPLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleygetPositionLoopVFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSIITON_LOOP_VFF;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleygetPositionLoopAFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSITION_LOOP_AFF;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetPLGainMul(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMDummy_87(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_88(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_89(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_90(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//
//
//copleySmStates copleySMSetCurrentPosasHome(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_POS_AS_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_POS_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_POS_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//    
//copleySmStates copleySMSetSlowHomeVelocity(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_SLOW_HOME_VELOCITY;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_SLOW_HOME_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_SLOW_HOME_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetHomeAccelaration(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_HOME_ACCELARATION;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_ACCELARATION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_ACCELARATION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//
//copleySmStates copleySMSetIN2HomeActiveLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetIN2HomeActiveHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//
//copleySmStates copleySMSetHomeDireationMovepositive(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copelySMSetHomeDireationMoveNegative(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetPositiveHardStopasHome(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetNegativeHardStopasHome(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMstatHomeMove(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_START_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_START_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_START_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//    
//copleySmStates copleySMSetIN2ActiveHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//    
//copleySmStates copleySMSetIN2ActiveLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetOffset(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_HOME_OFFSET;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetIN2PosLimSwActHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetIN2PosLimSwActLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetIN2NegLimSwActHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetIN2NegLimSwActLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetVelocity(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetJerk(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_JERK;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetTargetPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_TARGT_POSITION;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//
//copleySmStates copleySmSetProfileType(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_PROFILE_TYPE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_PROFILE_TYPE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_PROFILE_TYPE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMStartMove(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_START_MOVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_START_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_START_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        //eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
//        //copleySMStateEntryActions(eCopleyState);
//        eCopleyState = COPLEY_SM_IDLE;
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//copleySmStates copleySMStopMove(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_STOP_MOVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_STOP_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_STOP_MOVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        eCopleyState = COPLEY_SM_IDLE;
//        copleySMStateEntryActions(eCopleyState);
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//copleySmStates copleySMMonitorMoveStatus(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
//    
//    uint8_t *pucComplete = "Move Completed\r";
//    uint8_t *pucStop = "Move Stopped\r";
//    if(psSysEvt->eTypeEvent == COPLEY_MESSAGE || psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        *pbEventHandled = false;
//        stopCopleyTimeOutTimer();
//        
//        switch (geCopleMonitorMoveStates)
//        {
//            case MONITOR_MOVE_STATUS:
//            {
//                if(!tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//                {
//                    tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//                }
//                
//                if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
//                {
//                    eCopleyState = COPLEY_SM_IDLE;
//                    
//                    if(!tcpIPSendMesg(COPLEY_SM_START_MOVE,pucComplete,psSysEvt->sTcpipRecvData.ucCommSel))
//                    {
//                        tcpIPSendMesg(COPLEY_SM_START_MOVE,pucComplete,psSysEvt->sTcpipRecvData.ucCommSel);
//                    }     
//                }
//                
//                geCopleMonitorMoveStates = IDLE;
//                break;
//            }
//            case REPORT_COMMANDS:
//            {
//                
//                if(!tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//                {
//                    tcpIPSendMesg(guiTempCommand,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//                }
//               
//                geCopleMonitorMoveStates = IDLE;
//                break;
//            }
//            case STOP_MOVE:
//            {
//                if(!tcpIPSendMesg(guiTempCommand,pucStop,psSysEvt->sTcpipRecvData.ucCommSel))
//                {
//                    tcpIPSendMesg(guiTempCommand,pucStop,psSysEvt->sTcpipRecvData.ucCommSel);
//                }
//                eCopleyState = COPLEY_SM_IDLE;
//                
//                geCopleMonitorMoveStates = IDLE;
//                break;
//            }
//        }                 
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(guiTempCommand);
//        *pbEventHandled = false;
//    }
//    else if (TCPIP_EVENT_OCCURED == psSysEvt->eTypeEvent)
//    {
//        *pbEventHandled = false;
//        if(IDLE == geCopleMonitorMoveStates)
//        {
//            *pbEventHandled = true;
//            stringToUnsignedInt(psSysEvt->sTcpipRecvData.ucCommandByte,DIGIT_3,&guiTempCommand);
//    
//            if ((guiTempCommand < 500) && (guiTempCommand > 0))
//            {
//
//                if (guiTempCommand == 10)
//                {
//                    geCopleMonitorMoveStates = STOP_MOVE;
//                    copleySMStateEntryActions(guiTempCommand);
//                    
//                }
//                else if (guiTempCommand == 25)
//                {
//                    copleySMStateEntryActions(guiTempCommand);
//                    geCopleMonitorMoveStates = MONITOR_MOVE_STATUS;  
//                }
//                else
//                {
//                    copleySMStateEntryActions(guiTempCommand);
//                    geCopleMonitorMoveStates = REPORT_COMMANDS;
//                    
//                }
//            }
//        }  
//    }
//    
//    return eCopleyState;
//}
//
///*copleySmStates copleySMDummy_10(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}*/
//
//copleySmStates copleySMDummy_11(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_12(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_13(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_14(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_15(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_16(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_17(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_18(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_19(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_20(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//
//
//
//
//
//
//copleySmStates copleySMGetPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_MOTOR_POSITION;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_MOTOR_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_MOTOR_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMGetMotorCurrent(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_GET_MOTOR_CURRENT;
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_MOTOR_CURRENT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_MOTOR_CURRENT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMGetFollowingError(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_GET_FOLLOWING_ERROR;
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_FOLLOWING_ERROR,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_FOLLOWING_ERROR,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    return eCopleyState;
//}
//
//copleySmStates copleySMGetCommandedPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_GET_COMMANDED_POSITION;
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_COMMANDED_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_COMMANDED_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    return eCopleyState;
//}
//
//copleySmStates copleySMGetEventStatus(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_COPLEY_EVENT_STATUS;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        if(!tcpIPSendMesg(COPLEY_SM_GET_COPLEY_EVENT_STATUS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_COPLEY_EVENT_STATUS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMDummy_26(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_27(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_28(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_29(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDummy_30(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//
//    
//    return COPLEY_SM_IDLE;
//}
//
//
//
//
//
//copleySmStates copleySMSetPeakCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_SET_PEAK_CURRENT_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//    
//}
//
//
//copleySmStates copleySMSetI2TTimeLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_I2T_TIME_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetContinuousCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetCurrentLoopOffset(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_LOOP_OFFSET;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetCLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetCurrentLPIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLVelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLAccelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLDeclLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetFastStopRamp(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_FAST_STOP_RAMP;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetVLIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetPLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySetPositionLoopVFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSIITON_LOOP_VFF;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySetPositionLoopAFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITION_LOOP_AFF;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetPLGainMul(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMDummy_47(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_48(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_49(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_50(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMDisableDrive(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_DISABLE_DRIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_DISABLE_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_DISABLE_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates coleySMresetDrive(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_RESET_DRIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_RESET_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_RESET_DRIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMclearFaults(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_CLEAR_FAULTS;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_CLEAR_FAULTS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_CLEAR_FAULTS,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySMSetPositionToZero(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURR_POS_TO_ZERO;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURR_POS_TO_ZERO,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURR_POS_TO_ZERO,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleySetDigitalBoardOut(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SET_DIGITAL_BOARD_OUT;
//    
//    uint16_t uiTemStatus,uiOutputNumber;
//
//    if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        stringToUnsignedInt(&gucCopleyParameter[0],DIGIT_1,&uiOutputNumber);
//        stringToUnsignedInt(&gucCopleyParameter[1],DIGIT_1,&uiTemStatus);
//
//
//        switch (uiOutputNumber)
//        {
//            case 1:
//            {
//                LATAbits.LATA1 = uiTemStatus;
//                break;
//            }
//            case 2:
//            {
//                LATAbits.LATA2 = uiTemStatus;
//                break;
//            }
//            case 3:
//            {
//                LATAbits.LATA3 = uiTemStatus;
//                break;
//            }
//            case 4:
//            {
//                LATAbits.LATA4 = uiTemStatus;
//                break;
//            }
//            case 5:
//            {
//                LATAbits.LATA6 = uiTemStatus;
//                break;
//            }
//            case 6:
//            {
//                LATAbits.LATA7 = uiTemStatus;
//                break;
//            }
//            case 7:
//            {
//                LATAbits.LATA14 = uiTemStatus;
//                break;
//            }
//            case 8:
//            {
//                LATAbits.LATA15 = uiTemStatus;
//                break;
//            }
//            default:
//            {
//
//            }
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//    }
//    
//    return eCopleyState;
//}
//copleySmStates copleyReadDigitalBoardInput(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_READ_DIGITAL_BOARD_INPUT;
//    uint8_t ucMesage[10];
//    
//    if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        
//        stopCopleyTimeOutTimer();
//        
//        guInputStatus.SinputStatus.ucInputOne = PORTEbits.RE0;
//        guInputStatus.SinputStatus.ucInputTwo = PORTEbits.RE1;
//        guInputStatus.SinputStatus.ucInputThree = PORTEbits.RE2;
//        guInputStatus.SinputStatus.ucInputFour = PORTEbits.RE3;
//        guInputStatus.SinputStatus.ucInputFive = PORTEbits.RE4;
//        guInputStatus.SinputStatus.ucInputSix = PORTEbits.RE6;
//        guInputStatus.SinputStatus.ucInputSeven = PORTEbits.RE7;
//        guInputStatus.SinputStatus.ucInputEight = PORTEbits.RE8;
//        
//        
//        unsignedIntToStringHex(guInputStatus.uiDigitalInputStatus,DIGIT_2,&ucMesage[0]);
//        ucMesage[2] = '\r';
//        if(!tcpIPSendMesg(COPLEY_READ_DIGITAL_BOARD_INPUT,&ucMesage[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_READ_DIGITAL_BOARD_INPUT,&ucMesage[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//     
//    return eCopleyState;
//}
//
//copleySmStates copleySMDummy_57(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_58(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_59(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_60(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMgetAccelTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_ACCEL_TIME;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_ACCEL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_ACCEL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetDeclTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_DECL_TIME;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//    
//copleySmStates copleySMgetAbortDeclTime(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_ABORT_DECL_TIME;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_ABORT_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_ABORT_DECL_TIME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMgetVelocity(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetJerk(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_JERK;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_JERK,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetTargetPosition(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_TARGT_POSITION;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_TARGT_POSITION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMDummy_67(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_68(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_69(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_70(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//copleySmStates copleySMgetPeakCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_PEAK_CURRENT_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_PEAK_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetI2TTimeLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_I2T_TIME_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_I2T_TIME_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetContinuousCurrentLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetCurrentLoopOffset(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_LOOP_OFFSET;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetCLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetCurrentLPIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLVelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLAccelLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLDeclLimit(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetFastStopRamp(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_FAST_STOP_RAMP;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_FAST_STOP_RAMP,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetVLIG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetPLPG(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleygetPositionLoopVFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSIITON_LOOP_VFF;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSIITON_LOOP_VFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleygetPositionLoopAFF(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSITION_LOOP_AFF;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_AFF,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMgetPLGainMul(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//   
//    copleySmStates eCopleyState = COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL;
// 
//    if (psSysEvt->eTypeEvent == COPLEY_MESSAGE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//        
//        eCopleyState = COPLEY_SM_IDLE;
//       
//        
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMDummy_87(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_88(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_89(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//copleySmStates copleySMDummy_90(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    return COPLEY_SM_IDLE;
//}
//
//
//
//copleySmStates copleySMSetCurrentPosasHome(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_CURRENT_POS_AS_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_CURRENT_POS_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_CURRENT_POS_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//    
//copleySmStates copleySMSetSlowHomeVelocity(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_SLOW_HOME_VELOCITY;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_SLOW_HOME_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_SLOW_HOME_VELOCITY,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetHomeAccelaration(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_HOME_ACCELARATION;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_ACCELARATION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_ACCELARATION,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//
//copleySmStates copleySMSetIN2HomeActiveLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetIN2HomeActiveHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//
//copleySmStates copleySMSetHomeDireationMovepositive(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copelySMSetHomeDireationMoveNegative(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetPositiveHardStopasHome(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetNegativeHardStopasHome(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMstatHomeMove(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//        copleySmStates eCopleyState = COPLEY_SM_START_HOME;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_START_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_START_HOME,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//    
//copleySmStates copleySMSetIN2ActiveHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//    
//copleySmStates copleySMSetIN2ActiveLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetOffset(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_HOME_OFFSET;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_HOME_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_HOME_OFFSET,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetIN2PosLimSwActHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//copleySmStates copleySMSetIN2PosLimSwActLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetIN2NegLimSwActHigh(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}
//
//
//copleySmStates copleySMSetIN2NegLimSwActLow(sysEvents *psSysEvt, bool *pbEventHandled)
//{
//    copleySmStates eCopleyState = COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW;
//    
//    if (psSysEvt->eTypeEvent == COPLEY_RESPONSE)
//    {
//        
//        if(!tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel))
//        {
//            tcpIPSendMesg(COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
//        }
//        eCopleyState = COPLEY_SM_IDLE;
//        *pbEventHandled = true;
//        stopCopleyTimeOutTimer();
//    }
//    else if (TIME_OUT_EVENT == psSysEvt->eTypeEvent)
//    {
//        stopCopleyTimeOutTimer();
//        copleySMStateEntryActions(eCopleyState);
//    }
//    else
//    {
//        *pbEventHandled = false;
//    }
//    
//    return eCopleyState;
//}



#if 0
           
void copleySMStateEntryActions(copleySmStates eCopleyStates)
{
    
    switch (eCopleyStates)
    {
        case COPLEY_SM_IDLE:
        {
            break;
        }
        case COPLEY_SM_EN_AMP_PGM_POSITION:
        {
            SendCommandToCopley(COPLEY_SET_EN_AMP_PGM_POSITION,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_ACCEL_TIME:
        {
            SendCommandToCopley(COPLEY_SET_ACCEL_TIME,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_DECL_TIME:
        {
            SendCommandToCopley(COPLEY_SET_DECEL_TIME,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_ABORT_DECL_TIME:
        {
            SendCommandToCopley(COPLEY_SET_ABORT_DECEL_TIME,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_VELOCITY:
        {
            SendCommandToCopley(COPLEY_SET_VELOCITY,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_JERK:
        {
            SendCommandToCopley(COPLEY_SET_JERK_RATE,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_TARGT_POSITION:
        {
           SendCommandToCopley(COPLEY_SET_TARGET,gucCopleyParameter);
           startCopleyCmdTimeOutTimer(1000U);
           break; 
        }
        case COPLEY_SM_SET_PROFILE_TYPE:
        {
            SendCommandToCopley(COPLEY_SET_PROFILE_TYPE,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_START_MOVE:
        {
            SendCommandToCopley(COPLEY_START_MOVE,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_STOP_MOVE:
        {
            SendCommandToCopley(COPLEY_STOP_MOVE,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_CURRENT_MOTOR_POSITION:
        {
            SendCommandToCopley(COPLEY_GET_ACTUAL_POSITION,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_MOTOR_CURRENT:
        {
            SendCommandToCopley(COPLEY_GET_MOTOR_CURRENT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_FOLLOWING_ERROR:
        {
            SendCommandToCopley(COPLEY_GET_FOLLOWING_ERROR,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_COMMANDED_POSITION:
        {
            SendCommandToCopley(COPLEY_GET_COMMANDED_POSITION,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_COPLEY_EVENT_STATUS:
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_PEAK_CURRENT_LIMIT:
        {
            SendCommandToCopley(COPLEY_SET_PEAK_CURRENT_LIMIT,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_I2T_TIME_LIMIT:
        {
            SendCommandToCopley(COPLEY_SET_I2T_TIME_LIMIT,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_CONTINUOUS_CURRENT_LIMIT:
        {
            SendCommandToCopley(COPLEY_SET_CONTINUOUS_CURRENT_LIMIT,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_CURRENT_LOOP_OFFSET:
        {
            SendCommandToCopley(COPLEY_SET_CURRENT_LOOP_OFFSET,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_CURRENT_LOOP_PROPORTIONAL_GAIN:
        {
            SendCommandToCopley(COPLEY_CURRENT_LOOP_PROPORTIONAL_GAIN,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_CURRENT_LOOP_INTEGRAL_GAIN:
        {
            SendCommandToCopley(COPLEY_CURRENT_LOOP_INTEGRAL_GAIN,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_VELOCITY_LOOP_VELOCIT_LIMIT:
        {
            SendCommandToCopley(COPLEY_SET_VELOCITY_LOOP_VELOCITY_LIMIT,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_VELOCITY_LOOP_ACCEL_LIMIT:
        {
            SendCommandToCopley(COPLEY_SET_VELOCITY_LOOP_ACCELERATION_LIMIT,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_VELOCITY_LOOP_DECL_LIMIT:
        {
            SendCommandToCopley(COPLEY_SET_VELOCITY_LOOP_DECELERATION_LIMIT,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_FAST_STOP_RAMP:
        {
            SendCommandToCopley(COPLEY_FAST_STOP_RAMP,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_VELOCITY_LOOP_PROP_GAIN:
        {
            SendCommandToCopley(COPLEY_VELOCITY_LOOP_PROPORTIONAL_GAIN,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_VELOCITY_LOOP_INTEGR_GAIN:
        {
            SendCommandToCopley(COPLEY_VELOCITY_LOOP_INTEGRAL_GAIN,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_POSITION_LOOP_PROP_GAIN:
        {
            SendCommandToCopley(COPLEY_POSITION_LOOP_PROPORTIONAL_GAIN,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_POSIITON_LOOP_VFF:
        {
            SendCommandToCopley(COPLEY_VELOCITY_FEED_FORWARD,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_POSITION_LOOP_AFF:
        {
            SendCommandToCopley(COPLEY_ACCELERATION_FEED_FORWARD,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_POSITION_LOOP_GAIN_MUL:
        {
            SendCommandToCopley(COPLEY_POSITION_LOOP_GAIN_MULTIPLIER,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_DISABLE_DRIVE:
        {
            SendCommandToCopley(COPLEY_SET_DISABLE_AMP,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_RESET_DRIVE:
        {
            SendCommandToCopley(COPLEY_SET_RESET_AMP,(uint8_t *)NULL);
            //startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_CLEAR_FAULTS:
        {
            SendCommandToCopley(COPLEY_SET_CLEAR_FAULTS,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_CURR_POS_TO_ZERO:
        {
           SendCommandToCopley(COPLEY_SET_CURRENT_POSITION_ZERO,(uint8_t *)NULL);
           startCopleyCmdTimeOutTimer(1000U);
           break;
        }
        case COPLEY_SET_DIGITAL_BOARD_OUT:
        {
            startCopleyCmdTimeOutTimer(100U);
            break;
        }
        case COPLEY_READ_DIGITAL_BOARD_INPUT:
        {
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_ACCEL_TIME:
        {
            SendCommandToCopley(COPLEY_GET_ACCEL_TIME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_DECL_TIME:
        {
            SendCommandToCopley(COPLEY_GET_DECEL_TIME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_ABORT_DECL_TIME:
        {
            SendCommandToCopley(COPLEY_GET_ABORT_DECEL_TIME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_VELOCITY:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_JERK:
        {
            SendCommandToCopley(COPLEY_GET_JERK_RATE,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_TARGT_POSITION:
        {
            SendCommandToCopley(COPLEY_GET_TARGET,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_PEAK_CURRENT_LIMIT:
        {
            SendCommandToCopley(COPLEY_GET_PEAK_CURRENT_LIMIT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_I2T_TIME_LIMIT:
        {
            SendCommandToCopley(COPLEY_GET_I2T_TIME_LIMIT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_CONTINUOUS_CURRENT_LIMIT:
        {
            SendCommandToCopley(COPLEY_GET_CONTINUOUS_CURRENT_LIMIT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_CURRENT_LOOP_OFFSET:
        {
            SendCommandToCopley(COPLEY_GET_CURRENT_LOOP_OFFSET,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_CURRENT_LOOP_PROPORTIONAL_GAIN:
        {
            SendCommandToCopley(COPLEY_GET_CURRENT_LOOP_PROPORTIONAL_GAIN,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_CURRENT_LOOP_INTEGRAL_GAIN:
        {
            SendCommandToCopley(COPLEY_GET_CURRENT_LOOP_INTEGRAL_GAIN,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_VELOCITY_LOOP_VELOCIT_LIMIT:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY_LOOP_VELOCITY_LIMIT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_VELOCITY_LOOP_ACCEL_LIMIT:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY_LOOP_ACCELERATION_LIMIT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_VELOCITY_LOOP_DECL_LIMIT:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY_LOOP_DECELERATION_LIMIT,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_FAST_STOP_RAMP:
        {
            SendCommandToCopley(COPLEY_GET_FAST_STOP_RAMP,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_VELOCITY_LOOP_PROP_GAIN:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY_LOOP_PROPORTIONAL_GAIN,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_VELOCITY_LOOP_INTEGR_GAIN:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY_LOOP_INTEGRAL_GAIN,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_POSITION_LOOP_PROP_GAIN:
        {
            SendCommandToCopley(COPLEY_GET_POSITION_LOOP_PROPORTIONAL_GAIN,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;   
        }
        case COPLEY_SM_GET_POSIITON_LOOP_VFF:
        {
            SendCommandToCopley(COPLEY_GET_VELOCITY_FEED_FORWARD,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_POSITION_LOOP_AFF:
        {
            SendCommandToCopley(COPLEY_GET_ACCELERATION_FEED_FORWARD,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_GET_POSITION_LOOP_GAIN_MUL:
        {
            SendCommandToCopley(COPLEY_GET_POSITION_LOOP_GAIN_MULTIPLIER,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_CURRENT_POS_AS_HOME:
        {
            SendCommandToCopley(COPLEY_SET_CURRENT_POS_AS_HOME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_SLOW_HOME_VELOCITY:
        {
            SendCommandToCopley(COPLEY_SET_SLOW_HOME_VELOCITY,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_HOME_ACCELARATION:
        {
            SendCommandToCopley(COPLEY_SET_HOME_ACCELARATION,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_HOME_ACTIVE_LOW:
        {
            SendCommandToCopley(COPLEY_SET_IN2_HOME_ACTIVE_LOW,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_HOME_ACTIVE_HIGH:
        {
            SendCommandToCopley(COPLEY_SET_IN2_HOME_ACTIVE_HIGH,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
            
        }
        case COPLEY_SM_SET_HOME_DIRECTION_MOVE_POSITIVE:
        {
            SendCommandToCopley(COPLEY_SET_HOME_DIRECTION_MOVE_POSITIVE,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_HOME_DIRECTION_MOVE_NEGATIVE:
        {
            SendCommandToCopley(COPLEY_SET_HOME_DIRECTION_MOVE_NEGATIVE,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_POSITIVE_HARDSTOP_AS_HOME:
        {
            SendCommandToCopley(COPLEY_SET_POSITIVE_HARDSTOP_HOME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_NEGATIVE_HARDSTOP_AS_HOME:
        {
            SendCommandToCopley(COPLEY_SET_NEGATIVE_HARDSTOP_HOME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_START_HOME:
        {
            SendCommandToCopley(COPLEY_START_HOME,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_ACTIVE_HIGH:
        {
            SendCommandToCopley(COPLEY_SET_IN2_ACTIVE_HIGH,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_ACTIVE_LOW:
        {
            SendCommandToCopley(COPLEY_SET_IN2_ACTIVE_LOW,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_HOME_OFFSET:
        {
            SendCommandToCopley(COPLEY_SET_HOME_OFFSET,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH:
        {
            SendCommandToCopley(COPLEY_SET_IN2_POSITIVE_LIM_SW_ACTIVE_HIGH,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW:
        {
            SendCommandToCopley(COPLEY_SET_IN2_POSITIVE_LIM_SW_ACTIVE_LOW,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH:
        {
            SendCommandToCopley(COPLEY_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_HIGH,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW:
        {
            SendCommandToCopley(COPLEY_SET_IN2_NEGATIVE_LIM_SW_ACTIVE_LOW,gucCopleyParameter);
            startCopleyCmdTimeOutTimer(1000U);
            break;
        }
        case COPLEY_SM_MONITOR_MOVE_STATUS:
        {
//            geCopleMonitorMoveStates = IDLE;
            break;
        }
    }
    
#if 0
    switch (eCopleyStates)
    {
        case COPLEY_SM_IDLE:
        {
            break;
        }
        case COPLEY_SM_EN_AMP_PGM_POSITION:
        {
            SendCommandToCopley(COPLEY_SET_EN_AMP_PGM_POSITION,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(2000U);
            break;
        }
        case COPLEY_SM_SET_CURR_POS_TO_ZERO:
        {
            SendCommandToCopley(COPLEY_SET_CURRENT_POSITION_ZERO,(uint8_t *)NULL);
            startCopleyCmdTimeOutTimer(2000U);
            break;
        }
        case COPLEY_SM_GET_CURR_POSITION:
        {
            SendCommandToCopley(COPLEY_GET_ACTUAL_POSITION,(uint8_t *)NULL);
            break;
        }
        case COPLEY_SM_GET_COPLEY_EVENT_STATUS:
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_0:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"10000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_1:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-10000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_2:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"20000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_3:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-20000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_4:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"30000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_5:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-30000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_6:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"40000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_7:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-40000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_8:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"50000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_9:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-50000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_10:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"60000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_11:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-60000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_12:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"70000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_13:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-70000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_14:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"80000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_15:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-80000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_16:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"90000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_17:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-90000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_18:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"100000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_19:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-100000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_20:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"110000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_21:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-110000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_22:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"120000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_23:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-120000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_24:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"130000");
            break;
        }
        case COPLEY_SM_RELATIVE_MOVE_POSITION_25:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-130000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_0:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"10000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_1:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-10000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_2:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"20000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_3:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-20000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_4:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"30000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_5:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-30000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_6:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"40000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_7:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-40000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_8:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"50000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_9:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-50000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_10:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"60000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_11:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-60000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_12:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"70000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_13:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-70000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_14:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"80000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_15:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-80000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_16:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"90000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_17:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-90000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_18:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"100000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_19:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-100000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_20:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"110000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_21:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-110000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_22:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"120000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_23:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-120000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_24:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"130000");
            break;
        }
        case COPLEY_SM_ABSOLUTE_MOVE_POSITION_25:
        {
            copleySetInitMoveState(INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP);
            SendCommandToCopley(COPLEY_SET_TARGET, (uint8_t *)"-130000");
            break;
        }
        case COPLEY_SM_GET_COMMANDED_POSITION:
        {
            SendCommandToCopley(COPLEY_GET_COMMANDED_POSITION,(uint8_t *)NULL);
            break;
        }
        case COPLEY_SM_GET_FOLLOWING_ERROR:
        {
            SendCommandToCopley(COPLEY_GET_FOLLOWING_ERROR,(uint8_t *)NULL);
            break;
        }
        case COPLEY_SM_GET_MOTOR_CURRENT:
        {
            SendCommandToCopley(COPLEY_GET_MOTOR_CURRENT,(uint8_t *)NULL);
            break;
        }
        case COPLEY_SM_MONITOR_MOVE_STATUS:
        { 
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            break;
        }
        default:
        {
            break;
        }
    }
    
    
#endif
    
  
    
    
}

#endif



