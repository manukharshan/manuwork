#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "monitorinoutpin.h"
#include "continuousMonitor.h"
#include "ledindication.h"
#include "assemblePacket.h"
#include "timerfunctions.h"

extern sSlavedetails gsSlavedetails;
sMonitorMotorparameter gsMonitorMotorparameter;
sDeviceCtrlState gsDeviceCtrlState;

uint8_t messagePacket[64];
bool bmotorStatusupdated;
extern bool powerstartflag;
bool gbHandwheelSensor = false;
//bool homeflag = false;

void handweelSenMonitor(void)
{
    int mod;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
    if((0 == HWSENSOR) && (MOTORUNLOCKED == deviceCtrlState.eMotorCtrlState.eMotorStatus))
    {
        deviceCtrlState.eMotorCtrlState.eMotorStatus = MOTORLOCKED;
        deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;
        setDeviceCtrlState(&deviceCtrlState);
    }
    else if ((1 == HWSENSOR) && (MOTORLOCKED == deviceCtrlState.eMotorCtrlState.eMotorStatus))
    {
        if((1 == LOCALMODSEL)&&(1 == REMOTMODSEL))
        {
            gbHandwheelSensor = true;
        }
        else
        {
            deviceCtrlState.eMotorCtrlState.eMotorStatus = MOTORUNLOCKED;
            deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;
            setStatusledindicationState(VALVE_IDLE);
            setDeviceCtrlState(&deviceCtrlState);
            gbHandwheelSensor = true;
            startTimer(HOMETIMER,HOMING_START_DELAY);
        }    
    }
}

void remoteLocalSelswitch(void)
{
    int mod;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
    if((LOCAL_MODE_ON == LOCALMODSEL)&&(REMOTE_MODE_OFF == REMOTMODSEL)&&
            ((NO_SELECTION == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod) ||
            (REMOTE_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)))
    {
        deviceCtrlState.eValveCtrlState.eValveCtrlcommMod = LOCAL_MODE_SELECTED;
        deviceCtrlState.eValveCtrlState.evalveCtrlMod = LOCALMOD;
        deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;//emergency stop the motor here
        deviceCtrlState.eMotorCtrlState.eMotorStatus = MOTORUNLOCKED;
        if(powerstartflag)
        {
          startTimer(HOMETIMER,HOMING_START_DELAY);
        }
        else if(true == gbHandwheelSensor)
        {
            startTimer(HOMETIMER,HOMING_START_DELAY);
        }
        setDeviceCtrlState(&deviceCtrlState);
    }
    if((LOCAL_MODE_OFF == LOCALMODSEL)&&(REMOTE_MODE_ON == REMOTMODSEL)&&
            ((NO_SELECTION == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod) ||
            (LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)))
    {
        deviceCtrlState.eValveCtrlState.eValveCtrlcommMod = REMOTE_MODE_SELECTED;
//        deviceCtrlState.eValveCtrlState.evalveCtrlMod = LOCALMOD;
        deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;//emergency stop the motor here
        deviceCtrlState.eMotorCtrlState.eMotorStatus = MOTORUNLOCKED;
        
        if(powerstartflag)
        {
          startTimer(HOMETIMER,HOMING_START_DELAY);
        }
        else if(true == gbHandwheelSensor)
        {
            startTimer(HOMETIMER,HOMING_START_DELAY);
        }
        
         setDeviceCtrlState(&deviceCtrlState);
    }
    else if((1 == LOCALMODSEL)&&(1 == REMOTMODSEL) && (MOTORUNLOCKED == deviceCtrlState.eMotorCtrlState.eMotorStatus)
            && (NO_SELECTION != deviceCtrlState.eValveCtrlState.eValveCtrlcommMod))
    {
        //deviceCtrlState.eMotorCtrlState.eMotorStatus = MOTORLOCKED;
        stopTimer(HOMETIMER);
        deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;
        setStatusledindicationState(VALVE_IDLE);
        deviceCtrlState.eValveCtrlState.eValveCtrlcommMod = NO_SELECTION;
        reportMotorEvent(MOTORSTOP);
        setDeviceCtrlState(&deviceCtrlState);
    }
}

void continuousMonitorMotorTemp(void)
{
    
}

void continuousMonitorMotorEncoder(void)
{ 
   getCurrentEncoderPosition();  
}

void continuousMonitorMotorCurrent(void)
{
    
}

void continuousMonitorMotorStatus(void)
{
  sDeviceCtrlState deviceCtrlState;
  static uint16_t temp = 0;
  static uint16_t temp1 = 0;
  deviceCtrlState = *getDeviceCtrlState();
  if(MOTORRUNNING == deviceCtrlState.eMotorCtrlState.eMotorState)
  {
    if(checkbitSetorNot(getCurrentMotorStatus(),27))
    {   
        temp = 0;
        //setStatusledindicationState(VALVE_RUNNING);
        YELLOWLED = LEDON;
        //come here if set
    }
    else
    { 
        temp++;
        if(temp>=500)
        {
        //come here if not set
          deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;
          setDeviceCtrlState(&deviceCtrlState);
          YELLOWLED = LEDOFF;
          //setStatusledindicationState(VALVE_IDLE);
          temp = 0;
        }
    }
  }
  if(MOTORISHOMING == deviceCtrlState.eMotorCtrlState.eMotorState)
  {
      if(checkbitSetorNot((uint32_t)getMotorTrajStatus(),12))
      {
          temp1++;
          //duSendData1("manu\r\n",strlen("manu\r\n"));
          if(temp1>=500)
          {
           YELLOWLED = LEDOFF;   
           //duSendData1("manu\r\n",strlen("manu\r\n"));    
           deviceCtrlState.eMotorCtrlState.eMotorState = MOTORHOMINGCOMPLETED;
           setDeviceCtrlState(&deviceCtrlState);
           temp1=0;
          }
      }
      else
      {
          //homing
          YELLOWLED = LEDON;
          //duSendData1("senth\r\n",strlen("senth\r\n"));
          temp1=0;
//          deviceCtrlState.eMotorCtrlState.eMotorState = MOTORSTOPPED;
//          setDeviceCtrlState(&deviceCtrlState);
      }   
  }
}
void continuousMonitorPowerStatus(void)
{
    static uint8_t powerstatusflag = 0;
    uint8_t powerflag = 0;
    if((true == PWRSTATUS)&&(powerstatusflag == 0))
    {
        powerflag = 1;
        powerstatusflag = 1;
        //duSendData1("copoff\r\n",strlen("copoff\r\n"));
        //assembleEEpromPacket(EEPROMWRITECURRENTCOUNT,&messagePacket[0]);
    }
    else if(false == PWRSTATUS)
    {
        powerstatusflag = 0;
         //PORTAbits.RA14 = 0;
    }
    if(powerflag)
    {
//        PORTAbits.RA14 = 1;
//        startTimer(STATUSLED,20);
//        while(!getTimeOutOccur(STATUSLED));
//        PORTAbits.RA14 = 0;
//        stopTimer(STATUSLED);
        assembleEEpromPacket(EEPROMWRITECURRENTCOUNT,&messagePacket[0]);
    }
}

void continousMonitoropenpercentage(void)
{
    float percentageopen;
    if(((gsSlavedetails.closecountnum)- getCurrentEncoderPosition())<=0)
    {
        percentageopen = (((float)(getCurrentEncoderPosition()- gsSlavedetails.closecountnum)/TOTALNOOFROTATION)*100); 
        gsSlavedetails.percentageopen = (int8_t)((ceil)(percentageopen));
    }
    else
    {
       percentageopen = ((((float)(gsSlavedetails.closecountnum) - getCurrentEncoderPosition())/TOTALNOOFROTATION)*100);
       gsSlavedetails.percentageopen = (int8_t)((ceil)(percentageopen));
    }
    if(percentageopen<=1)
    {
        setledinidicationstate(VALVECLOSE);
    }
    else if((percentageopen>1)&&(percentageopen<10))
    {
        setledinidicationstate(VALVENINETYPERCLOSE);
    }
    else if((percentageopen>=10)&&(percentageopen<20))
    {
        setledinidicationstate(VALVEEIGHTYPERCLOSE);
    }
    else if((percentageopen>=20)&&(percentageopen<30))
    {
        setledinidicationstate(VALVESEVENTYPERCLOSE);
    }
    else if((percentageopen>=30)&&(percentageopen<40))
    {
        setledinidicationstate(VALVESIXTYPERCLOSE);
    }
    else if((percentageopen>=40)&&(percentageopen<50))
    {
        setledinidicationstate(VALVEFIFTYPERCLOSE);
    }
    else if((percentageopen>=50)&&(percentageopen<60))
    {
        setledinidicationstate(VALVEFOURTYPERCLOSE);
    }
    else if((percentageopen>=60)&&(percentageopen<70))
    {
        setledinidicationstate(VALVETHIRTYPERCLOSE);
    }
    else if((percentageopen>=70)&&(percentageopen<80))
    {
       setledinidicationstate(VALVETWENTYPERCLOSE); 
    }
    else if((percentageopen>=80)&&(percentageopen<90))
    {
       setledinidicationstate(VALVETENPERCLOSE); 
    }
    else if((percentageopen>=90)&&(percentageopen<100))
    {
       setledinidicationstate(VALVEOPEN); 
    } 
}

void taskContinuousMonitorMotorParameters(void)
{
    handweelSenMonitor();
    remoteLocalSelswitch();
//    continuousMonitorMotorTemp();
//    continuousMonitorMotorEncoder();
//    continuousMonitorMotorCurrent();
    continuousMonitorPowerStatus();
    continuousMonitorKeypad();
    continuousMonitorMotorStatus();
    continousMonitoropenpercentage();
    ledindicationTask();
    taskStatusLedIndication();
    if(getTimeOutOccur(HOMETIMER))
    {
        duSendData1("homing\r\n",strlen("homing\r\n"));
        reportActionEvent(ACTIONVALVEHOME);
        //homeflag = false;
        stopTimer(HOMETIMER);
        
    }
}

void setCurrentMotorTemp(int value)
{
    gsMonitorMotorparameter.motorTemperature = value;
}

void setCurrentEncoderPosition(int value)
{
    gsMonitorMotorparameter.motorEncoderCount = value;
}

void setCurrentMotorStatus(int value)
{
    gsMonitorMotorparameter.motorStatus = (uint32_t)value;
}

void setMotorTrajStatus(int value)
{
    gsMonitorMotorparameter.trajectoryStatus = (int16_t)(value);
}

void setCurrentMotorCurrent(int value)
{
    gsMonitorMotorparameter.motorCurrent = value;
}



int getCurrentMotorTemp(void)
{
    return gsMonitorMotorparameter.motorTemperature;
}

int getCurrentMotorCurrent(void)
{
    return gsMonitorMotorparameter.motorCurrent;
}

int getCurrentEncoderPosition(void)
{
    return gsMonitorMotorparameter.motorEncoderCount;
}

uint32_t getCurrentMotorStatus(void)
{
    return gsMonitorMotorparameter.motorStatus;
}

int16_t getMotorTrajStatus(void)
{
    return gsMonitorMotorparameter.trajectoryStatus;
}

void setDeviceCtrlState(sDeviceCtrlState* gsTDeviceCtrlState)
{
    memcpy(&gsDeviceCtrlState,gsTDeviceCtrlState,sizeof(sDeviceCtrlState));
    bmotorStatusupdated = true;
}

sDeviceCtrlState* getDeviceCtrlState(void)
{
//    bmotorStatusupdated = false;
    return (&gsDeviceCtrlState);
}

bool isDeviceCtrlstatusUpdated(void)
{
    if(bmotorStatusupdated)
    {
       bmotorStatusupdated = false;
       return true;
    }
    else
    {
        return false;
    }
}

uint32_t checkbitSetorNot(uint32_t value,uint8_t positon)
{
    value = (value & (1<<positon));
    return value;
}

bool isValveOperatable(void)
{
    bool status = false;
    if(MOTORUNLOCKED == gsDeviceCtrlState.eMotorCtrlState.eMotorStatus)
    {
        if(MOTORSTOPPED == gsDeviceCtrlState.eMotorCtrlState.eMotorState)
        {
            status = true;
        }
    }
    return status;
}