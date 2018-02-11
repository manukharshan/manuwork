#include "continuousMonitor.h"
#include "ledindication.h"
#include "actionHandler.h"
#include "keypadevent.h"
#include "timerfunctions.h"

SysCirBuffer2 GSActionEvent;
eActionEvent gEActionEvent[ACTIONMAXEVENT];

SysCirBuffer2 GSMotorEvent;
eMotorEvent gEMotorEvent[MOTORMAXEVENT];

  extern bool gbHandwheelSensor;
  extern bool powerstartflag;

eMotortoHomeState geMotortoHomeState = MOTOR_HARD_NEGSTOP;

actionSmStates gactionSmStates = ACTION_SM_IDLE;

static actionsmTable gActionsmTable[ACTION_SM_MAX_STATE] = 
{
    {ACTION_SM_IDLE,actionstateidle},
    {ACTION_SM_HOME,actionstatehome},
    {ACTION_SM_ROTATE,actionstaterotate},
    {ACTION_SM_VALVEOPEN,actionstatevalveopen},
    {ACTION_SM_VALVECLOSE,actionstatevalveclose},
    {ACTION_SM_STOPMOTOR,actionstopmotor},
    {ACTION_SM_HARDSTOPHOME,actionhardstophome},
};


actionSmStates actionSmhandler(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionsmTable *actionSmTab = gActionsmTable;
    while(actionSmTab != &gActionsmTable[ACTION_SM_MAX_STATE])
    {
        if(actionSmTab->eactionSmStates == gactionSmStates)
        {
            break;
        }
        actionSmTab++;
    }
    gactionSmStates =  actionSmTab->actionSmFuncitons(psactionsysEvents,psactionEventhandled);
    return gactionSmStates;
    
}

actionSmStates actionstateidle(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
     eactionSmStates = motorControlAction(psactionsysEvents);
    return eactionSmStates;
}

actionSmStates actionstatehome(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
//    if(isValveOperatable())
//    {
        eactionSmStates = tasksetMotorToHome();
        
//    }
//    else
//    {
//        eactionSmStates = ACTION_SM_IDLE;
//    }
    return eactionSmStates;   
}

actionSmStates actionstaterotate(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
    if(isValveOperatable())
    {
        setJogMod();
        reportMotorEvent(MOTORPOSVELJOG);
        eactionSmStates = ACTION_SM_IDLE;
    }
    else
    {
        eactionSmStates = ACTION_SM_IDLE;
    }
    return eactionSmStates;
}

actionSmStates actionstatevalveopen(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
    if(isValveOperatable())
    {
            setCountToRun(FULLOPEN);
            setAbsoluteMode();
            reportMotorEvent(MOTORPOSJOG); //if open direction is positive
            eactionSmStates = ACTION_SM_IDLE;
    }
    else
    {
        eactionSmStates = ACTION_SM_IDLE;
    }
    return eactionSmStates;
}

actionSmStates actionstatevalveclose(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
    if(isValveOperatable())
    {
            setCountToRun(FULLCLOSE);
            setAbsoluteMode();
            reportMotorEvent(MOTORPOSJOG); //if close direction is Negative
            eactionSmStates = ACTION_SM_IDLE;
        
    }
    else
    {
        eactionSmStates = ACTION_SM_IDLE;
    }
    return eactionSmStates;
}

actionSmStates actionstopmotor(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
    reportMotorEvent(MOTORSTOP);
    eactionSmStates = ACTION_SM_IDLE;
    return eactionSmStates;
}

actionSmStates actionhardstophome(actionsysEvents* psactionsysEvents,bool* psactionEventhandled)
{
    actionSmStates eactionSmStates;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
    if(isValveOperatable())
    {
            reportMotorEvent(MOTORHARDSTOP); //if close direction is Negative
            eactionSmStates = ACTION_SM_IDLE;
        
    }
    else
    {
        eactionSmStates = ACTION_SM_IDLE;
    }
    return eactionSmStates;
}

/*circular buffer for report action events*/

void reportActionEvent (eActionEvent eInputActionEvent)
{
    
    gEActionEvent[GSActionEvent.uiInPtr] = eInputActionEvent;
    GSActionEvent.uiInPtr++;
    GSActionEvent.uiProcessesCounter++;
    if (GSActionEvent.uiInPtr >= ACTIONMAXEVENT)
    {
        GSActionEvent.uiInPtr = 0;
    }
    
}

bool getActionEvent (eActionEvent *ActionEvent)
{
    bool bRetVal = false;
    
    if (GSActionEvent.uiProcessesCounter > 0)
    {
        bRetVal = true;
        *ActionEvent = gEActionEvent[GSActionEvent.uiOutPtr];
    }
    return bRetVal;
}

void disposeActionEvent (void)
{
    GSActionEvent.uiOutPtr ++;
    if (GSActionEvent.uiOutPtr >= ACTIONMAXEVENT)
    {
        GSActionEvent.uiOutPtr = 0;
    }
    GSActionEvent.uiProcessesCounter --;
}


/*circular buffer for report motor events*/


void reportMotorEvent (eMotorEvent eInputMotorEvent)
{
    
    gEMotorEvent[GSMotorEvent.uiInPtr] = eInputMotorEvent;
    GSMotorEvent.uiInPtr++;
    GSMotorEvent.uiProcessesCounter++;
    if (GSMotorEvent.uiInPtr >= MOTORMAXEVENT)
    {
        GSMotorEvent.uiInPtr = 0;
    }
    
}

bool getMotorEvent (eMotorEvent *MotorEvent)
{
    bool bRetVal = false;
    
    if (GSMotorEvent.uiProcessesCounter > 0)
    {
        bRetVal = true;
        *MotorEvent = gEMotorEvent[GSMotorEvent.uiOutPtr];
    }
    return bRetVal;
}

void disposeMotorEvent (void)
{
    GSMotorEvent.uiOutPtr ++;
    if (GSMotorEvent.uiOutPtr >= MOTORMAXEVENT)
    {
        GSMotorEvent.uiOutPtr = 0;
    }
    GSMotorEvent.uiProcessesCounter --;
}

actionSmStates motorControlAction(actionsysEvents* psactionsysEvents)
{
    actionSmStates gTactionSmStates;
    switch(psactionsysEvents->geActionEvent)
    {
        case ACTIONVALVEHOME:
        {
            gTactionSmStates = ACTION_SM_HOME;
            setStatusledindicationState(VALVE_HOME_BLINK);
            break;
        }
        case ACTIONVALVEOPEN:
        {
            gTactionSmStates = ACTION_SM_VALVEOPEN;
            break;
        }
        case ACTIONVALVECLOSE:
        {
            gTactionSmStates = ACTION_SM_VALVECLOSE;
            break;
        }
        case ACTIONROTPOS:
        {
           setCountToRun(JOGPOS); 
           gTactionSmStates = ACTION_SM_ROTATE;
           break;
        }
        case ACTIONROTNEG:
        {
           setCountToRun(JOGNEG);  
           gTactionSmStates = ACTION_SM_ROTATE;
           break; 
        }
        case ACTIONROTPOSHARDSTOP:
        {
            setHardStopHomePositive();
            gTactionSmStates = ACTION_SM_HARDSTOPHOME;
            break;
        }
        case ACTIONROTNEGHARDSTOP:
        {
           setHardStopHomeNegative();
           gTactionSmStates = ACTION_SM_HARDSTOPHOME;
           break;
        }
        case ACTIONVALVEEMERGENCYSTOP:
        {
           gTactionSmStates = ACTION_SM_STOPMOTOR;
           break;
        }
    }
    
    return gTactionSmStates;
}

actionSmStates tasksetMotorToHome(void)
{
   actionSmStates gTactionSmStates = ACTION_SM_HOME;
   sDeviceCtrlState deviceCtrlState;
   sSlavedetails deviceDetails;
   deviceCtrlState = *getDeviceCtrlState();
   deviceDetails = *getDevicedetails();
   switch(geMotortoHomeState)
    {
        case MOTOR_HARD_NEGSTOP:
        {
            setHardStopHomePositive();
            reportMotorEvent(MOTORHARDSTOP);
            deviceCtrlState.eMotorCtrlState.eMotorState = MOTORISHOMING;
            setDeviceCtrlState(&deviceCtrlState);
            geMotortoHomeState = MOTOR_HARD_NEGSTOP_STOP;
            break;
        }
        case MOTOR_HARD_NEGSTOP_STOP:
        {
          if(MOTORHOMINGCOMPLETED == deviceCtrlState.eMotorCtrlState.eMotorState)
          {
           
            //duSendData1("back\r\n",strlen("back\r\n"));
            deviceDetails.closecountnum = getCurrentEncoderPosition();
            deviceDetails.opencountnum = (deviceDetails.closecountnum-TOTALNOOFROTATION);
            setDevicedetails(&deviceDetails);
            setCountToRun(JOGABSOLUTEZERO);
            setAbsoluteMode();
            //setVelocityMode();
            reportMotorEvent(MOTORPOSJOG);
            deviceCtrlState.eMotorCtrlState.eMotorState = MOTORRUNNING;
            setDeviceCtrlState(&deviceCtrlState);
            gTactionSmStates = ACTION_SM_IDLE;
            geMotortoHomeState = MOTOR_HARD_NEGSTOP;
            gbHandwheelSensor = false;
            powerstartflag = false;
            setStatusledindicationState (VALVE_IDLE);
            //startTimer(STATUSLED,10000);
          }
          else if (MOTORSTOPPED == deviceCtrlState.eMotorCtrlState.eMotorState)
          {
              gTactionSmStates = ACTION_SM_IDLE;
              geMotortoHomeState = MOTOR_HARD_NEGSTOP;
              setStatusledindicationState (VALVE_IDLE);
          }
          break;
        }
    }
    return gTactionSmStates;
}