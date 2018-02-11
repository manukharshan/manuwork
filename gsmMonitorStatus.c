#include"gsmMonitorStatus.h"

extern gsmState gsgsmState;
static unsigned char gsmrtry = 0;

gsmSmStates gsmMonitorSignalStrength(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate)
{
  switch(gsgsmState.egsmmonitorstate)
  {
    case GSMSIGSTRMONITOR:
     {
       gsmSignalSrength();
       gsgsmState.egsmmonitorstate = GSMSIGSTRMONITORRES;
       startGsmTimeoutTimer(2000);
       break;
     }
    case GSMSIGSTRMONITORRES:
     {
       if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
         {
            stopGsmTimeoutTimer();
            //duSendData1("send4\r\n",strlen("send4\r\n"));
            gsmrtry = 0;
            gsgsmState.egsmmonitorstate = GSMSIGSTRMONITOR;
         }
       if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
         {
            gsmrtry++;
            stopGsmTimeoutTimer();
            //duSendData1("configured",10);
            gsgsmState.egsmmonitorstate = GSMSIGSTRMONITOR;
            if(gsmrtry>=5)
            {
                eGsmstate =  GSM_SM_IDEAL;
                gsgsmState.egsmmonitorstate = GSMSIGSTRMONITOR;
                gsmrtry = 0;
                //print reason
            }
          }
        break;
     }
  }
}

void signalStrenthindication(void)
{
    if((20 <= getrssi()) && (30 >= getrssi()))
    {
        //High range
    }
    else if((15 <= getrssi()) && (20 > getrssi()))
    {
        //middle range
    }
    else if((10 <= getrssi()) && (15 > getrssi()))
    { 
        //low range
    }
    else if((2 <= getrssi()) && (10 > getrssi()))
    {
        //very low range
    }
    else
    {
        //no range
    }
}
