#include "deviceDetails.h"
#include "defaultvalue.h"
#include "continuousMonitor.h"

sCommondefaultdata gsCommondefaultdata;
sSlavedetails gsSlavedetails;
bool devDetailsupdated = false;
uint8_t aSlaveDetails[19];

void intitDefaultValueforMotorconfig(void)
{
    strcpy(gMotorConfigdetails.copleyDesState,"31");
    //strcpy(gMotorConfigdetails.copleyMotVel,"40000");
    strcpy(gMotorConfigdetails.copleyAccTime,"20000");
    strcpy(gMotorConfigdetails.copleyDecTime,"20000");
}
void intitDefaultValueforMotorHomeConfig(void)
{
    strcpy(gMotorHomeConfigState.copleyfastHomeVel,"133333");
    strcpy(gMotorHomeConfigState.copleySlowHomeVel,"133333");
    strcpy(gMotorHomeConfigState.copleyHomeAcc,"20000");
    strcpy(gMotorHomeConfigState.copleyHomeOffset,"0");
    strcpy(gMotorHomeConfigState.copleyHomewithoutsetzero,"516");
}

void setVelocityMode(void)
{
    strcpy(gMotorConfigdetails.copleyProfType,"256");
    //strcpy(gMotorConfigdetails.copleyMotVel,"233333");
    strcpy(gMotorConfigdetails.copleyMotVel,"233333");//500rpm
    //strcpy(gMotorConfigdetails.copleyMotVel,"200000");
    //strcpy(gMotorConfigdetails.copleyMotVel,"160000");
    //strcpy(gMotorConfigdetails.copleyMotVel,"223000");
}

void setJogMod(void)
{
    strcpy(gMotorConfigdetails.copleyProfType,"2");
    strcpy(gMotorConfigdetails.copleyMotVel,"233333");
    //strcpy(gMotorConfigdetails.copleyMotVel,"200000");
    //strcpy(gMotorConfigdetails.copleyMotVel,"160000");
    //strcpy(gMotorConfigdetails.copleyMotVel,"223000");
}

void setAbsoluteMode(void)
{
   strcpy(gMotorConfigdetails.copleyProfType,"0");
   //strcpy(gMotorConfigdetails.copleyMotVel,"233333");//7000rpm
   strcpy(gMotorConfigdetails.copleyMotVel,"233333");//500rpm
}

void setHardStopHomePositive(void)
{
    //strcpy(gMotorHomeConfigState.copleyHomeType,"516");
    strcpy(gMotorHomeConfigState.copleyHomeType,"1540");
    strcpy(gMotorHomeConfigState.copleyCurrentlimit,"380");
    strcpy(gMotorHomeConfigState.copleyCurrentdelay,"200");
}

void setHardStopHomeNegative(void)
{
   //strcpy(gMotorHomeConfigState.copleyHomeType,"532");
   strcpy(gMotorHomeConfigState.copleyHomeType,"1556");  
   strcpy(gMotorHomeConfigState.copleyCurrentlimit,"380");
   strcpy(gMotorHomeConfigState.copleyCurrentdelay,"200");
}

void initdefaultvalues(void)
{
    gsCommondefaultdata.gsGsmcommondata.gmobnumber = 918296448053;
    gsCommondefaultdata.gsLoracommondata.gTxpwr = 15;
    gsCommondefaultdata.gsLoracommondata.glorafreq = 865000000;
    gsCommondefaultdata.gsLoracommondata.watchdogtimeout = 10000;
    memcpy(gsSlavedetails.signature,"MANU",4);
    memcpy(gsSlavedetails.devID,"8001",4);
    strcpy(gsSlavedetails.ipaddress,TCPIP_NETWORK_DEFAULT_IP_ADDRESS);
    strcpy(gsSlavedetails.portNo,TCPIP_PORT_NO);
    gsSlavedetails.calibrationstatus = 0;
    //gsSlavedetails.closecountnum = 3885514;
    gsSlavedetails.closecountnum = 100000;
    gsSlavedetails.opencountnum = 0;
    //gsSlavedetails.noofRotation = 3885514;
    gsSlavedetails.noofRotation = 3885514; //100000;
    intitDefaultValueforMotorconfig();
    intitDefaultValueforMotorHomeConfig();
    CountToRun = 0;
    setVelocityMode();
}

void setCountToRun(stateToMove gStateTomove)
{
    switch(gStateTomove)
    {
        case FULLCLOSE:
        {
            CountToRun = gsSlavedetails.closecountnum;
            break;
        }
        case NIGHTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(10/100))));
            break;
        }
        case EIGHTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(20/100))));
            break;
        }
        case SEVENTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(30/100))));
            break;
        }
        case SIXTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(40/100))));
            break;
        }
        case FIFTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(50/100))));
            break;
        }
        case FOUTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(60/100))));
            break;
        }
        case THIRTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(70/100))));
            break;
        }
        case TWENTYCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(80/100))));
            break;
        }
        case TENCLOSE:
        {
            CountToRun = -(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(90/100))));
            break;
        }
        case FULLOPEN:
        {
            CountToRun = gsSlavedetails.opencountnum; //-(getCurrentEncoderPosition() - (gsSlavedetails.closecountnum + (gsSlavedetails.noofRotation*(100/100))));
            break;
        }
        case JOGPOS:
        {
            CountToRun = 1;
            break;
        }
        case JOGNEG:
        {
            CountToRun = -1;
            break;
        }
        case JOGABSOLUTEZERO:
        {
            CountToRun = 0;
            break;
        }
    }
    
}


void setDevicedetails(sSlavedetails* gsTSlavedetails)
{
    memcpy(&(gsSlavedetails.devID[0]),&(gsTSlavedetails->devID[0]),4);
    gsSlavedetails.calibrationstatus = gsTSlavedetails->calibrationstatus;
    gsSlavedetails.percentageopen = gsTSlavedetails->percentageopen;
    gsSlavedetails.noofRotation = gsTSlavedetails->noofRotation;
    gsSlavedetails.opencountnum = gsTSlavedetails->opencountnum;
    gsSlavedetails.closecountnum = gsTSlavedetails->closecountnum;
    devDetailsupdated = true;
}


sSlavedetails* getDevicedetails(void)
{
    return (&gsSlavedetails);
}

bool isDevicedetailsupdated(void)
{
    if(devDetailsupdated)
    {
        devDetailsupdated = false;
        return true;
    }
    else
    {
        return false;
    }
}

int32_t getCountToRun(void)
{
    return CountToRun;
}

void setCopleyPositionLoop(void)
{
   strcpy(gMotorConfigdetails.copleyProfType,"256"); 
}

void setCopleyVelocityLoop(void)
{
  strcpy(gMotorConfigdetails.copleyProfType,"2");  
}

void setCopleyHomeTypeNegHard(void)
{
    strcpy(gMotorHomeConfigState.copleyHomeType,"516");
}

void setCopleyHomeTypePosHard(void)
{
    strcpy(gMotorHomeConfigState.copleyHomeType,"532");
}