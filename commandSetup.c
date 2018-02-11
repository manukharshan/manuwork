/* 
 * File:   tcpiphandler.h
 * Author: Manu K Harshan
 *
 * Created on 07 June, 2017, 12:29 AM
 */
#include "commandSetup.h"
#include "continuousMonitor.h"

//int8_t response[50];
extern sSlavedetails gsSlavedetails;

CmdTableEntry cmdTable[]={
    {"GDL",getDeviceList},
    {"RDL",registerDeviceList},
    {"GCC",getCurrentCount},
    {"SOP",setOpenPosition},
    {"SCP",setClosePosition},
    {"GDS",getDeviceStatus},
    {"GAS",getAllDeviceStatus},
    {"OPN",openValve},
    {"CLS",closeValve},
    {"STP",stopMotor},
    {"JMN",jogMotorNeg},
    {"JMP",jogMotorPos},
    {"GCP",getCalPosition},
    {"HMP",homePositive},
    {"HMN",homeNegative},
    {"CBR",calibrate},
    {"GOP",getopenpercentage},
    {"GSR",getdevicestatusremote},
    {"KA?",keepAlive},
    { '\0',cmdNull}
};

uint8_t commandParse(uint8_t* command1,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    CmdTableEntry *sCmdTable = cmdTable;
    while(sCmdTable->cmdString !='\0')
    {
        if(!strcmp(sCmdTable->cmdString,command1))
            status = sCmdTable->cmdFunction(command1,arg,sel);
        sCmdTable++;
    }
    return status;
}

uint8_t getDeviceList(uint8_t* comd,uint8_t *arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        
    }
    else if(UDP == sel)
    {
        
    }
    else if(WIFI_TCP == sel)
    {
        
    }
    else
    {
        
    }
    return status;
}

uint8_t registerDeviceList(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status; 
    if(TCP_IP == sel)
    {
        
    }
    else if(UDP == sel)
    {
        
    }
    else if(WIFI_TCP == sel)
    {
        
    }
    else if(LORA == sel)
    {
        
    } 
    else
    {
        
    }
   return status; 
}


uint8_t getDeviceStatus(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    
    if(TCP_IP == sel)
    {
        
    }
    else if(UDP == sel)
    {
        
    }
    else if(WIFI_TCP == sel)
    {
        
    }
    else if(LORA == sel)
    {
        
    } 
    else
    {
        
    }
   return status; 
}

uint8_t getAllDeviceStatus(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status,mod;
    uint8_t reply[60];
    uint8_t Hreply[60];
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();   
    if(TCP_IP == sel)
    {
        frameResponse(GETALLDEVICESTATUS,LOCALMOD,&reply[0]);
        TCPIP_TCP_ArrayPut(appData.tcpServerSocket, &reply[0], strlen(&reply[0]));
    }
    else if(WIFI_TCP == sel)
    {
        frameResponse(GETALLDEVICESTATUS,LOCALMOD,&reply[0]);
        wifiSendCmdData(&reply[0],strlen(&reply[0]));
    }
    else if(LORA == sel)
    {
        frameResponse(GETALLDEVICESTATUS,REMOTE,&reply[0]);
        StringToHexString(&Hreply[0],&reply[0]);
        postLoraSendEvent(&Hreply[0]);
    }
    else if (GSM == sel)
    {
        
    }
    else
    {
        //nothing
    }
  return status;  
}

uint8_t openValve(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
 if(LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
  {
    if(TCP_IP == sel)
    {            
            //report to actionHandler
            reportActionEvent(ACTIONVALVEOPEN);
                           
    }
    else if(WIFI_TCP == sel)
    {
            
            //report to actionHandler
            reportActionEvent(ACTIONVALVEOPEN);
    }
  }
 if(REMOTE_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
 {
    if(LORA == sel)
    {
            //report to actionHandler
            reportActionEvent(ACTIONVALVEOPEN);
    }
    else if(GSM == sel)
    {
        reportActionEvent(ACTIONVALVEOPEN);
    }
    else
    {
        //report coudn't open manually engaged
    }
 }
  return status;     
}

uint8_t closeValve(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
  if(LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
  {
    if(TCP_IP == sel)
    {
            //report to actionHandler
            reportActionEvent(ACTIONVALVECLOSE);   
    }
    else if(UDP == sel)
    {
            //report to actionHandler
            reportActionEvent(ACTIONVALVECLOSE);
    }
    else if(WIFI_TCP == sel)
    {
            //report to actionHandler
            reportActionEvent(ACTIONVALVECLOSE);
    }
  }
 if(REMOTE_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
  {   
    if(LORA == sel)
    {
            //report to actionHandler
           reportActionEvent(ACTIONVALVECLOSE);
    }
    else if (GSM == sel)
    {
        reportActionEvent(ACTIONVALVECLOSE);
    }
 }
   return status;    
}

uint8_t getCurrentCount(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    uint8_t reply[60];
    if(TCP_IP == sel)
    {
        frameResponse(GETCURRENTCOUNT,LOCALMOD,reply);
        TCPIP_TCP_ArrayPut(appData.tcpServerSocket, &reply[0], strlen(reply));                 
    }
    else if(WIFI_TCP == sel)
    {
        frameResponse(GETCURRENTCOUNT,LOCALMOD,reply);
        wifiSendCmdData(reply,strlen(reply));
    }
    return status;   
}

uint8_t setOpenPosition(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        gsSlavedetails.opencountnum = atoi(arg);
    }
    else if(WIFI_TCP == sel)
    {
       gsSlavedetails.opencountnum = atoi(arg);
    }  
  return status;  
}

uint8_t setClosePosition(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        gsSlavedetails.closecountnum = atoi(arg);
    }
    else if(WIFI_TCP == sel)
    {
       gsSlavedetails.closecountnum = atoi(arg);
    }
 return status;   
}

uint8_t stopMotor(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
     if(LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
     {
       if(TCP_IP == sel)
       {
               //report to actionHandler
              reportActionEvent(ACTIONVALVEEMERGENCYSTOP);   
       }
       else if(WIFI_TCP == sel)
       {
               //report to actionHandler
               reportActionEvent(ACTIONVALVEEMERGENCYSTOP); 
       }
     }
    if(REMOTE_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
     {   
       if(LORA == sel)
       {
               //report to actionHandler
              reportActionEvent(ACTIONVALVEEMERGENCYSTOP); 
       }
       else if (GSM == sel)
       {
           reportActionEvent(ACTIONVALVEEMERGENCYSTOP); 
       }
    }
 return status;   
}

uint8_t jogMotorNeg(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        reportActionEvent(ACTIONROTNEG);                
    }
    else if(WIFI_TCP == sel)
    {
       reportActionEvent(ACTIONROTNEG);
    }
 return status;   
}

uint8_t jogMotorPos(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        reportActionEvent(ACTIONROTPOS);                
    }
    else if(WIFI_TCP == sel)
    {
       reportActionEvent(ACTIONROTPOS);
    }
 return status;   
}

uint8_t getCalPosition(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
     uint8_t reply[60];
    if(TCP_IP == sel)
    {
        frameResponse(GETCALPOSITON,LOCALMOD,reply);
        TCPIP_TCP_ArrayPut(appData.tcpServerSocket, &reply[0], strlen(reply));                 
    }
    else if(WIFI_TCP == sel)
    {
        frameResponse(GETCALPOSITON,LOCALMOD,reply);
        wifiSendCmdData(reply,strlen(reply));
    }
  return status;     
}

uint8_t homePositive(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        reportActionEvent(ACTIONROTPOSHARDSTOP);                
    }
    else if(WIFI_TCP == sel)
    {
        reportActionEvent(ACTIONROTPOSHARDSTOP);
    }
  return status;   
}

uint8_t homeNegative(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        reportActionEvent(ACTIONROTNEGHARDSTOP);              
    }
    else if(WIFI_TCP == sel)
    {
        reportActionEvent(ACTIONROTNEGHARDSTOP);
    }
   return status; 
}

uint8_t calibrate(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    uint8_t msgPacket[64];
    if(TCP_IP == sel)
    {
        assembleEEpromPacket(EEPROMWRITECALIBRATIONDETAILS,&msgPacket[0]);
        //reportActionEvent(ACTIONROTNEGHARDSTOP);              
    }
    else if(WIFI_TCP == sel)
    {
        assembleEEpromPacket(EEPROMWRITECALIBRATIONDETAILS,&msgPacket[0]);
        //reportActionEvent(ACTIONROTNEGHARDSTOP);
    }
  return status;  
}

uint8_t getopenpercentage(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    uint8_t reply[60];
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
     if(LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
     {
       if(TCP_IP == sel)
       {
           
       }
       else if(WIFI_TCP == sel)
       {

       }
     }
    if(REMOTE_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
     {   
       if(LORA == sel)
       {

       }
       else if (GSM == sel)
       {
         frameResponse(GETOPENPERCENTAGE,REMOTE,&reply[0]);
         postGsmSendEvent(&reply[0]);     
       }
     }
  return status;    
}

uint8_t getdevicestatusremote(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
     uint8_t reply[60];
    uint8_t Hreply[60];
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
     if(LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
     {
       if(TCP_IP == sel)
       {
           
       }
       else if(WIFI_TCP == sel)
       {

       }
     }
    if(REMOTE_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
     {   
       if(LORA == sel)
       {
         frameResponse(GET_DEVICE_STATUS_REMOTE,REMOTE,&reply[0]);
         StringToHexString(&Hreply[0],&reply[0]);
         postLoraSendEvent(&Hreply[0]);
       }
       else if (GSM == sel)
       {    
       }
     }
  return status;   
}

uint8_t keepAlive(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    uint8_t status;
    if(TCP_IP == sel)
    {
        
    }
    else if(UDP == sel)
    {
        
    }
    else if(WIFI_TCP == sel)
    {
        
    }
    else if(LORA == sel)
    {
        
    } 
    else
    {
        
    }
 return status;    
}

uint8_t cmdNull(uint8_t* comd,uint8_t* arg,uint8_t sel)
{
    return 0;
}