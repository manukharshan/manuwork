#include "motorSmHandler.h"
#include "loraSmHandler.h"
#include "copleytransmithandler.h"
#include "copleycommandinterface.h"
#include "continuousMonitor.h"
#include "debuguarthandler.h"

motorSmStates gemotorSmstates = MOTOR_SM_IDLE;
extern sConfigflag gSconfigflag;
sMotorcontrolstate gSmotorcontrolstate;

static unsigned char motorRetry;

static motorsmTable gmotorsmTable[MOTOR_SM_MAX_STATE] = 
{
    {MOTOR_SM_IDLE,motorstateidle},
    {MOTOR_SM_CONFIG,motorstateconfig},
    {MOTOR_START_MOV,motorstartmov},
    {MOTOR_SM_HOMECONFIG,motorstatehomeconfig},
    {MOTOR_STOP_MOV,motorstopmov},
    {MOTOR_HOMING,motorhoming},
    {MOTOR_COPLEY_DISABLE,motorcopleyDisable},
};


motorSmStates motorSmhandler(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    motorsmTable *motorSmTab = gmotorsmTable;
    while(motorSmTab != &gmotorsmTable[MOTOR_SM_MAX_STATE])
    {
        if(motorSmTab->emotorSmStates == gemotorSmstates)
        {
            break;
        }
        motorSmTab++;
    }
    gemotorSmstates =  motorSmTab->motorSmFuncitons(psmotorsysEvents,psmotorEventhandled);
    return gemotorSmstates;
}

motorSmStates motorstateidle(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
   motorSmStates emotorstate  =  MOTOR_SM_IDLE;
   if((gSconfigflag.emotorconfigflag == MOTOR_NOT_CONFIGUED)&&(1 == HWSENSOR))
   {
       duSendData1("motor configuring...\r\n",strlen("motor configuring...\r\n"));
       emotorstate = MOTOR_SM_CONFIG;
   }
   else if((gSconfigflag.emotorhomeconfig == MOTOR_NOT_HOMECONFIGURED)&&(1 == HWSENSOR))
   {
       duSendData1("motor home configuring...\r\n",strlen("motor home configuring...\r\n"));
       emotorstate = MOTOR_SM_HOMECONFIG;
   }
   else if((gSconfigflag.emotorconfigflag == MOTOR_CONFIGUED)&&(gSconfigflag.emotorhomeconfig == MOTOR_HOMECONFIGURED)&&(MOTORCONTROL_EVENT == psmotorsysEvents->eTypeEvent))
   { 
        stopTimer(MOTORTIMER);
        gSmotorcontrolstate.gemotormonitorstate = MOTORCURRPOSITION;
        emotorstate = motorContorlAction(psmotorsysEvents);
   }
   else if((gSconfigflag.emotorconfigflag == MOTOR_CONFIGUED)&&(gSconfigflag.emotorhomeconfig == MOTOR_HOMECONFIGURED))
   {
       if(1 == HWSENSOR)
       {
         emotorstate = motorMonitorTask(psmotorsysEvents);
       }
       else
       {
          stopTimer(MOTORTIMER);
          gSmotorcontrolstate.gemotormonitorstate = MOTORCURRPOSITION;
//          gSconfigflag.emotorconfigflag = MOTOR_NOT_CONFIGUED;
//          gSconfigflag.emotorhomeconfig = MOTOR_NOT_HOMECONFIGURED;
       }
   }
  return emotorstate; 
}

motorSmStates motorstateconfig(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    motorSmStates emotorstate =  MOTOR_SM_CONFIG;
    switch(gSmotorcontrolstate.geMotorconfigstate)
    {
        case MOTORPOSITION:
        {
            //SendCommandToCopley(COPLEY_SET_DESIRED_STATE,gMotorConfigdetails.copleyDesState);
            SendCommandToCopley(COPLEY_SET_ACCEL_TIME,gMotorConfigdetails.copleyAccTime);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.geMotorconfigstate = MOTORPOSITIONRES;
            break;
        }
        case MOTORPOSITIONRES:
        {
            if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
            {
               gSmotorcontrolstate.geMotorconfigstate = MOTORSETACCEL;
               stopTimer(MOTORTIMER);
            }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               motorRetry++;
               gSmotorcontrolstate.geMotorconfigstate = MOTORPOSITION;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    gSmotorcontrolstate.geMotorconfigstate = MOTORPOSITION;
                    emotorstate =  MOTOR_SM_IDLE;
                    motorRetry = 0;
                      //print reason
                }
            }  
            break;
        }
        case MOTORSETACCEL:
        {
            SendCommandToCopley(COPLEY_SET_ACCEL_TIME,gMotorConfigdetails.copleyAccTime);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.geMotorconfigstate = MOTORSETACCELRES;
            break;
        }
       case MOTORSETACCELRES:
       {   
            if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
            {
               gSmotorcontrolstate.geMotorconfigstate = MOTORSETDECEL;
               stopTimer(MOTORTIMER);
            }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               motorRetry++;
               gSmotorcontrolstate.geMotorconfigstate = MOTORSETACCEL;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    gSmotorcontrolstate.geMotorconfigstate = MOTORPOSITION;
                    emotorstate =  MOTOR_SM_IDLE;
                    motorRetry = 0;
                      //print reason
                }
            }  
            break;
       }
      case MOTORSETDECEL:
      {
            SendCommandToCopley(COPLEY_SET_DECEL_TIME,gMotorConfigdetails.copleyDecTime);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.geMotorconfigstate = MOTORSETDECELRES;
            break;
      }
      case MOTORSETDECELRES:
      {
        
           if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
           {
               gSmotorcontrolstate.geMotorconfigstate = MOTORPOSITION;
               stopTimer(MOTORTIMER);
//               duSendData1("motoconfigured",14);
               duSendData1("motor configured\r\n",strlen("motor configured\r\n"));
               gSconfigflag.emotorconfigflag = MOTOR_CONFIGUED;
               emotorstate =  MOTOR_SM_IDLE;
           }
           else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               motorRetry++;
               gSmotorcontrolstate.geMotorconfigstate = MOTORSETDECEL;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    gSmotorcontrolstate.geMotorconfigstate = MOTORPOSITION;
                    emotorstate =  MOTOR_SM_IDLE;
                    motorRetry = 0;
                      //print reason
                }
            }  
           break;
      }
        
  }
 return emotorstate;    
}
motorSmStates motorstatehomeconfig(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    motorSmStates emotorstate = MOTOR_SM_HOMECONFIG;
    emotorstate = configureHome(psmotorsysEvents);
    return emotorstate;
}

motorSmStates motorstartmov(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    motorSmStates emotorstate =  MOTOR_START_MOV;
    uint8_t countTorun[12] = {0};
    sDeviceCtrlState gsDeviceCtrlState;
    gsDeviceCtrlState = *getDeviceCtrlState();
    switch(gSmotorcontrolstate.geMotorstartmovstate)
    {
     case MOTORCLRFAULT:
      {
         SendCommandToCopley(COPLEY_SET_CLEAR_FAULTS,(uint8_t *)NULL);
         //SendCommandToCopley(COPLEY_SET_DESIRED_STATE,gMotorConfigdetails.copleyDesState); 
         startTimer(MOTORTIMER,1000U);
         gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULTRES;
         break;
      }
      case MOTORCLRFAULTRES:
      {
         if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
         {
            gSmotorcontrolstate.geMotorstartmovstate = MOTOR_DISABLE_AMP;
            stopTimer(MOTORTIMER);
         }
         else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
         {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
            {
                gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                emotorstate =  MOTOR_SM_IDLE;
                motorRetry = 0;
                //print reason
            }
         }  
         break;
      }
     case MOTOR_DISABLE_AMP:
     {
        //SendCommandToCopley(COPLEY_SET_DISABLE_AMP,(uint8_t *)NULL);
        SendCommandToCopley(COPLEY_SET_ACCEL_TIME,gMotorConfigdetails.copleyAccTime); 
        startTimer(MOTORTIMER,1000U);
        gSmotorcontrolstate.geMotorstartmovstate = MOTOR_DISABLE_AMP_RESP;
        break; 
     }
     case MOTOR_DISABLE_AMP_RESP:
     {
         if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
         {
            gSmotorcontrolstate.geMotorstartmovstate = MOTOR_ENABLE_AMP;
            stopTimer(MOTORTIMER);
         }
         else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
         {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTOR_DISABLE_AMP;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
            {
                gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                emotorstate =  MOTOR_SM_IDLE;
                motorRetry = 0;
                //print reason
            }
         }
         break;
     }
     case MOTOR_ENABLE_AMP:
     {
        //SendCommandToCopley(COPLEY_SET_DESIRED_STATE,gMotorConfigdetails.copleyDesState);
        SendCommandToCopley(COPLEY_SET_DECEL_TIME,gMotorConfigdetails.copleyDecTime);
        startTimer(MOTORTIMER,1000U);
        gSmotorcontrolstate.geMotorstartmovstate = MOTOR_ENABLE_RESP;
        break;    
     }
     case MOTOR_ENABLE_RESP:
     {
         if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
         {
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETPROFTYPE;
            stopTimer(MOTORTIMER);
         }
         else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
         {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTOR_ENABLE_AMP;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
            {
                gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                emotorstate =  MOTOR_SM_IDLE;
                motorRetry = 0;
                //print reason
            }
         }    
         break;
     }
     case MOTORSETPROFTYPE:
     {
         SendCommandToCopley(COPLEY_SET_PROFILE_TYPE,gMotorConfigdetails.copleyProfType);
         startTimer(MOTORTIMER,1000U);
         gSmotorcontrolstate.geMotorstartmovstate = MOTORSETPROFTYPERES;
         break;
     }
     case MOTORSETPROFTYPERES:
     {
         if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
         {
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETVEL;
            stopTimer(MOTORTIMER);
         }
         else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
         {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETPROFTYPE;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
            {
                gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                emotorstate =  MOTOR_SM_IDLE;
                motorRetry = 0;
                //print reason
            }
         }  
         break;
     }
     case MOTORSETVEL:
     {
        SendCommandToCopley(COPLEY_SET_VELOCITY,gMotorConfigdetails.copleyMotVel);
        startTimer(MOTORTIMER,1000U);
        gSmotorcontrolstate.geMotorstartmovstate = MOTORSETVELRES;
        break;
     }
     case MOTORSETVELRES:
     {
         if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
         {
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETDIR;
            stopTimer(MOTORTIMER);
         }
         else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
         {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETVEL;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
            {
                gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                emotorstate =  MOTOR_SM_IDLE;
                motorRetry = 0;
                //print reason
            }
         }
         break;
     }
     case MOTORSETDIR:
      {
            dtcIntToString(getCountToRun(),DIGIT_11,&countTorun[0]);
            duSendData1(&countTorun[0],strlen(&countTorun[0]));
            SendCommandToCopley(COPLEY_SET_TARGET,&countTorun[0]);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETDIRRESP;
            break;
      }
      case MOTORSETDIRRESP:
      {
        
        if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
        {
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSTARTMOV;
            stopTimer(MOTORTIMER);
        }
        else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
        {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSETDIR;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
             {
                gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                emotorstate =  MOTOR_SM_IDLE;
                motorRetry = 0;
                      //print reason
             }
        }  
        break;
      }
     case MOTORSTARTMOV:
      {
            SendCommandToCopley(COPLEY_START_MOVE,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSTARTMOVRES;
            break;
      }
      case MOTORSTARTMOVRES:
      {
        
          if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
          {
            gsDeviceCtrlState.eMotorCtrlState.eMotorState = MOTORRUNNING;
            gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
            emotorstate =  MOTOR_SM_IDLE;
//            duSendData1("motorrunning",strlen("motorrunning"));
            stopTimer(MOTORTIMER);
          }
          else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
          {
            motorRetry++;
            gSmotorcontrolstate.geMotorstartmovstate = MOTORSTARTMOV;
            stopTimer(MOTORTIMER);
            if(motorRetry>=3)
             {
                 gSmotorcontrolstate.geMotorstartmovstate = MOTORCLRFAULT;
                 emotorstate =  MOTOR_SM_IDLE;
                 motorRetry = 0;
                      //print reason
              }
            }  
          break;
      }
    }
  setDeviceCtrlState(&gsDeviceCtrlState);  
  return emotorstate;  
}

motorSmStates motorstopmov(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    motorSmStates emotorstate =  MOTOR_STOP_MOV;
//    sDeviceCtrlState gsDeviceCtrlState;
//    gsDeviceCtrlState = *getDeviceCtrlState();
   switch(gSmotorcontrolstate.geMotorstopmovstate)
    {
     case MOTORSTOPMOV:
      {
            SendCommandToCopley(COPLEY_STOP_MOVE,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.geMotorstopmovstate = MOTORSTOPMOVRES;
            break;
      }
      case MOTORSTOPMOVRES:
      {
        
          if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
            {
//              gsDeviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;
               gSmotorcontrolstate.geMotorstopmovstate = MOTORSTOPMOV;
               emotorstate =  MOTOR_SM_IDLE;
               stopTimer(MOTORTIMER);
            }
          else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               motorRetry++;
               gSmotorcontrolstate.geMotorstopmovstate = MOTORSTOPMOV;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    gSmotorcontrolstate.geMotorstopmovstate = MOTORSTOPMOV;
                    emotorstate =  MOTOR_SM_IDLE;
                    motorRetry = 0;
                      //print reason
                }
            }  
          break;
      }
    }
//  setDeviceCtrlState(&gsDeviceCtrlState);   
  return emotorstate;
}

motorSmStates motorhoming(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    motorSmStates emotorstate = MOTOR_HOMING;
    emotorstate = motorHoming(psmotorsysEvents);
    return emotorstate; 
}

motorSmStates motorcopleyDisable(motorsysEvents* psmotorsysEvents,bool* psmotorEventhandled)
{
    
}

motorSmStates motorMonitorTask(motorsysEvents* psmotorsysEvents)
{
    motorSmStates emotorstate = MOTOR_SM_IDLE;
    uint8_t replyMessage[30];
    switch(gSmotorcontrolstate.gemotormonitorstate)
    {
        case MOTORCURRPOSITION:
        {
            SendCommandToCopley(COPLEY_GET_EPORT_CURRENT_MOTOR_POSITION,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotormonitorstate = MOTORCURRPOSITIONRES;
            break;
        }
        case MOTORCURRPOSITIONRES:
        {
            if (psmotorsysEvents->eTypeEvent == COPLEY_MESSAGE)
            {
               getCopleyMessage(&replyMessage[0]); 
               setCurrentEncoderPosition(atoi(&replyMessage[0]));
//               sprintf(&replyMessage[0],"%d\r\n",atoi(&replyMessage[0]));
//               duSendData1(&replyMessage[0],strlen(&replyMessage[0]));
               gSmotorcontrolstate.gemotormonitorstate = MOTORSTATUS;
               stopTimer(MOTORTIMER);
            }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               gSmotorcontrolstate.gemotormonitorstate = MOTORCURRPOSITION;
               stopTimer(MOTORTIMER);
            }  
            break;
        }
        case MOTORSTATUS:
        {
            SendCommandToCopley(COPLEY_GET_DRIVE_EVENT_STATUS_REG,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotormonitorstate = MOTORSTATUSRES;
            break;
        }
        case MOTORSTATUSRES:
        {
            if (psmotorsysEvents->eTypeEvent == COPLEY_MESSAGE)
            {
               getCopleyMessage(&replyMessage[0]); 
               setCurrentMotorStatus(atoi(&replyMessage[0]));
//               sprintf(&replyMessage[0],"%d\r\n",atoi(&replyMessage[0]));
//               duSendData1(&replyMessage[0],strlen(&replyMessage[0]));
               gSmotorcontrolstate.gemotormonitorstate = MOTORHOMESTATUS;
               stopTimer(MOTORTIMER);
            }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               gSmotorcontrolstate.gemotormonitorstate = MOTORSTATUS;
               stopTimer(MOTORTIMER);
            }  
            break;
        }
        case MOTORHOMESTATUS:
        {
            SendCommandToCopley(COPLEY_GET_TRAJECTORY_STATUS,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotormonitorstate = MOTORHOMESTATUSRES;
            break;
        }
        case MOTORHOMESTATUSRES:
        {
            if (psmotorsysEvents->eTypeEvent == COPLEY_MESSAGE)
            {
               getCopleyMessage(&replyMessage[0]); 
               setMotorTrajStatus(atoi(&replyMessage[0]));
//               sprintf(&replyMessage[0],"%d\r\n",atoi(&replyMessage[0]));
//               duSendData1(&replyMessage[0],strlen(&replyMessage[0]));
               gSmotorcontrolstate.gemotormonitorstate = MOTORCURRENT;
               stopTimer(MOTORTIMER);
            }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               gSmotorcontrolstate.gemotormonitorstate = MOTORHOMESTATUS;
               stopTimer(MOTORTIMER);
            } 
            break;
        }
        case MOTORCURRENT:
        {
            SendCommandToCopley(COPLEY_GET_MOTOR_CURRENT,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotormonitorstate = MOTORCURRENTRES;
            break; 
        }
        case MOTORCURRENTRES:
        {
           if (psmotorsysEvents->eTypeEvent == COPLEY_MESSAGE)
            {
               getCopleyMessage(&replyMessage[0]); 
               setCurrentMotorCurrent(atoi(&replyMessage[0]));
//               sprintf(&replyMessage[0],"%d\r\n",atoi(&replyMessage[0]));
//               duSendData1(&replyMessage[0],strlen(&replyMessage[0]));
               gSmotorcontrolstate.gemotormonitorstate = MOTORCURRPOSITION;
               stopTimer(MOTORTIMER);
            }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
            {
               gSmotorcontrolstate.gemotormonitorstate = MOTORCURRENT;
               stopTimer(MOTORTIMER);
            } 
            break; 
        }
    }
  return emotorstate;  
}

motorSmStates configureHome(motorsysEvents* psmotorsysEvents)
{
     motorSmStates emotorstate =  MOTOR_SM_HOMECONFIG;
     
     switch(gSmotorcontrolstate.gemotorhomconfigstate)
     {
         case HOMINGFASTVELUNIT:
         {
            SendCommandToCopley(COPLEY_SET_FAST_HOME_VELOCITY,gMotorHomeConfigState.copleyfastHomeVel);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNITRES;
            break;
         }
         case HOMINGFASTVELUNITRES:
         {
            if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorhomconfigstate = HOMINGSLOWVELUNIT;
               stopTimer(MOTORTIMER);
               //duSendData1("motohomconfigured1",18);
             }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
                    motorRetry = 0;
                      //print reason
                }
             } 
             break;
         }
         case HOMINGSLOWVELUNIT:
         {
            SendCommandToCopley(COPLEY_SET_SLOW_HOME_VELOCITY,gMotorHomeConfigState.copleySlowHomeVel);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotorhomconfigstate = HOMINGSLOWVELUNITRES;
             break;
         }
         case HOMINGSLOWVELUNITRES:
         {
             if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorhomconfigstate = HOMINGACCDECUNIT;
               //duSendData1("motohomconfigured2",18);
               stopTimer(MOTORTIMER);
             }
             else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorhomconfigstate = HOMINGSLOWVELUNIT;
               stopTimer(MOTORTIMER);
               if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
                    motorRetry = 0;
                      //print reason
                }
             } 
             break;
         }
         case HOMINGACCDECUNIT:
         {
             SendCommandToCopley(COPLEY_SET_HOME_ACCELARATION,gMotorHomeConfigState.copleyHomeAcc);
             startTimer(MOTORTIMER,1000U);
             gSmotorcontrolstate.gemotorhomconfigstate = HOMINGACCDECUNITRES;
             break;
         }
         case HOMINGACCDECUNITRES:
         {
             if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorhomconfigstate = HOMEOFFSETUNIT;
               //duSendData1("motohomconfigured3",18);
               stopTimer(MOTORTIMER);
             }
             else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorhomconfigstate = HOMINGACCDECUNIT;
               stopTimer(MOTORTIMER);
               if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
                    motorRetry = 0;
                      //print reason
                }
             }
             break;
         }
         case HOMEOFFSETUNIT:
         {
             SendCommandToCopley(COPLEY_SET_HOME_OFFSET,gMotorHomeConfigState.copleyHomeOffset);
             startTimer(MOTORTIMER,1000U);
             gSmotorcontrolstate.gemotorhomconfigstate = HOMEOFFSETUNITRES;
             break;
         }
         case HOMEOFFSETUNITRES:
         {
             if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               //gSmotorcontrolstate.gemotorhomconfigstate = HOMECURRENTDELAYTIMEUNIT;
               //gSconfigflag.emotorhomeconfig = MOTOR_HOMECONFIGURED;
               //duSendData1("motohomconfigured4",18);
               //duSendData1("motor home configured\r\n",strlen("motor home configured\r\n"));
               gSmotorcontrolstate.gemotorhomconfigstate = HOME_WITHOUT_HOME_ADJUSTMENT;
               //emotorstate =  MOTOR_SM_IDLE;
               stopTimer(MOTORTIMER);
             }
             else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorhomconfigstate = HOMEOFFSETUNIT;
               stopTimer(MOTORTIMER);
               if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
                    motorRetry = 0;
                      //print reason
                }
             }
             break;
         }
         case HOME_WITHOUT_HOME_ADJUSTMENT:
         {
             SendCommandToCopley(COPLEY_SET_HOME_TYPE,gMotorHomeConfigState.copleyHomewithoutsetzero);
             startTimer(MOTORTIMER,1000U);
             gSmotorcontrolstate.gemotorhomconfigstate = HOME_WITHOUT_HOME_ADJUSTMENTRES;
             break;
         }
         case HOME_WITHOUT_HOME_ADJUSTMENTRES:
         {
             if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               //gSmotorcontrolstate.gemotorhomconfigstate = HOMECURRENTDELAYTIMEUNIT;
               gSconfigflag.emotorhomeconfig = MOTOR_HOMECONFIGURED;
               //duSendData1("motohomconfigured4",18);
               duSendData1("motor home configured\r\n",strlen("motor home configured\r\n"));
               gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
               emotorstate =  MOTOR_SM_IDLE;
               stopTimer(MOTORTIMER);
             }
             else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorhomconfigstate = HOME_WITHOUT_HOME_ADJUSTMENT;
               stopTimer(MOTORTIMER);
               if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorhomconfigstate = HOMINGFASTVELUNIT;
                    motorRetry = 0;
                      //print reason
                }
             }
             break;
         }
//         case HOMEPOSSOFTLIMITUNIT:
//         {
//             break;
//         }
//         case HOMEPOSSOFTLIMITUNITRES:
//         {
//             break;
//         }
//         case HOMENEGSOFTLIMITUNIT:
//         {
//             break;
//         }
//         case HOMENEGSOFTLIMITUNITRES:
//         {
//             break;
//         }
         
     }
     return emotorstate;
    
}


motorSmStates motorHoming(motorsysEvents* psmotorsysEvents)
{
     motorSmStates emotorstate =  MOTOR_HOMING;
     sDeviceCtrlState deviceCtrlState;
     sSlavedetails deviceDetails;
     deviceCtrlState = *getDeviceCtrlState();
     deviceDetails = *getDevicedetails();
     switch(gSmotorcontrolstate.gemotorHomemovState)
     {
         case MOTOR_SET_CURRENT:
         {
             SendCommandToCopley(COPLEY_SET_HOME_CURRENTLIMIT,gMotorHomeConfigState.copleyCurrentlimit);
             startTimer(MOTORTIMER,1000U);
             gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENTRES;
             deviceCtrlState.eMotorCtrlState.eMotorState = MOTORISHOMING;
             setDevicedetails(&deviceCtrlState);
             break;
         }
         case MOTOR_SET_CURRENTRES:
         {
            if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENTDELAY;
               stopTimer(MOTORTIMER);
             }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENT;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENT;
                    motorRetry = 0;
                      //print reason
                }
             } 
             break;
         }
         case MOTOR_SET_CURRENTDELAY:
         {
             SendCommandToCopley(COPLEY_SET_HOME_CURRENTLIMITDELAY,gMotorHomeConfigState.copleyCurrentdelay);
             startTimer(MOTORTIMER,1000U);
             gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENTDELAYRES;
             break;
         }
         case MOTOR_SET_CURRENTDELAYRES:
         {
             if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorHomemovState = MOTORHOMINGTYPE;
               stopTimer(MOTORTIMER);
             }
             else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENTDELAY;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENT;
                    motorRetry = 0;
                      //print reason
                }
             } 
             break; 
         }
         case MOTORHOMINGTYPE:
         {
            SendCommandToCopley(COPLEY_SET_HOME_TYPE,gMotorHomeConfigState.copleyHomeType);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotorHomemovState = MOTORHOMINGTYPERESPONSE;
            break;
         }
         case MOTORHOMINGTYPERESPONSE:
         {
            if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorHomemovState = MOTORHOMING;
               stopTimer(MOTORTIMER);
             }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorHomemovState = MOTORHOMINGTYPE;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENT;
                    motorRetry = 0;
                      //print reason
                }
             } 
             break;
         }
         case MOTORHOMING:
         {
            SendCommandToCopley(COPLEY_START_HOME,(uint8_t *)NULL);
            startTimer(MOTORTIMER,1000U);
            gSmotorcontrolstate.gemotorHomemovState = MOTORHOMINGRESP;
            break;
         }
         case MOTORHOMINGRESP:
         {
            if (psmotorsysEvents->eTypeEvent == COPLEY_RESPONSE)
             {
               gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENT;
               stopTimer(MOTORTIMER);
               deviceCtrlState.eMotorCtrlState.eMotorState = MOTORISHOMING;
               setDevicedetails(&deviceCtrlState);
               //duSendData1("motor homing\r\n",strlen("motor homing\r\n"));
               emotorstate =  MOTOR_SM_IDLE;
             }
            else if (TIME_OUT_EVENT == psmotorsysEvents->eTypeEvent)
             {
               motorRetry++;
               gSmotorcontrolstate.gemotorHomemovState = MOTORHOMING;
               stopTimer(MOTORTIMER);
                if(motorRetry>=3)
                {
                    emotorstate =  MOTOR_SM_IDLE;
                    gSmotorcontrolstate.gemotorHomemovState = MOTOR_SET_CURRENT;
                    motorRetry = 0;
                      //print reason
                }
             } 
             break;
         }
     }
 return emotorstate;  
}


motorSmStates motorContorlAction(motorsysEvents* psmotorsysEvents)
{
    motorSmStates emotorSmStates;
//    if(MOTORPOSJOG == psmotorsysEvents->eTypeMotorEvent)
//    {
//      PORTAbits.RA7 = 0;   
//      emotorSmStates = MOTOR_START_MOV;  
//    }
    switch(psmotorsysEvents->eTypeMotorEvent)
    {
        case MOTORPOSVELJOG:
        {
            emotorSmStates = MOTOR_START_MOV;
            break;
        }
        case MOTORNEGVELJOG:
        {
            emotorSmStates = MOTOR_START_MOV;
            break;
        }
        case MOTORPOSJOG:
        {
            duSendData1("motoraction",strlen("motoraction"));
            emotorSmStates = MOTOR_START_MOV;
            //PORTAbits.RA7 = 0;
            break;
        }
        case MOTORSTOP:
        {
            emotorSmStates = MOTOR_STOP_MOV;
            break;
        }
        case MOTORDISABLE:
        {
            break;
        }
        case MOTORENABLE:
        {
            break;
        }
        case MOTORHARDSTOP:
        {
            emotorSmStates = MOTOR_HOMING;
            break;
        }     
    }
    return emotorSmStates;
}