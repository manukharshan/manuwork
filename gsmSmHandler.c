#include <stdbool.h>
#include "timerfunctions.h"
#include "gsmSmHandler.h"
#include "loraSmHandler.h"
#include "gsmevents.h"
#include "gsmModem.h"

gsmSmStates ggsmSmStates = GSM_SM_IDEAL;
extern sConfigflag gSconfigflag;
gsmState gsgsmState;
static unsigned char gsmretry = 0;
static unsigned char gsmTretry = 0;
uint8_t* gsmTransmitdata;

static gsmsmTable gGsmsmTable[GSM_SM_MAX_STATE] = 
{
    {GSM_SM_IDEAL,gsmstateideal},
    {GSM_SM_CONFIG,gsmstateconfig},
    {GSM_SM_MESGREAD,gsmstatemsgread},
    {GSM_SM_MSGTRANMIT,gsmstatemsgtransmit},
};


gsmSmStates gsmSmhandler(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled)
{
    gsmsmTable *gsmSmTab = gGsmsmTable;
    while(gsmSmTab != &gGsmsmTable[GSM_SM_MAX_STATE])
    {
        if(gsmSmTab->egsmSmStates == ggsmSmStates)
        {
            break;
        }
        gsmSmTab++;
    }
    ggsmSmStates =  gsmSmTab->gsmSmFunctions(psgsmsysEvents,psgsmEventhandled);
    return ggsmSmStates;
}

gsmSmStates gsmstateideal(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled)
{
   gsmSmStates eGsmstate = GSM_SM_IDEAL;
   if(gSconfigflag.egsmconfigflag == GSM_NOT_CONFIGURED)
   {
       eGsmstate = GSM_SM_CONFIG;
   }
   else if((gSconfigflag.egsmconfigflag == GSM_CONFIGURED)&& (psgsmsysEvents->eGsmTypeEvent == GSM_MESG_REC))
   {
       eGsmstate = GSM_SM_MESGREAD;
      //eGsmstate = gsmReceiveEventTask(psgsmsysEvents,eGsmstate);
   }
   else if((gSconfigflag.egsmconfigflag == GSM_CONFIGURED)&&(getGsmSendEvent(&gsmTransmitdata)))
   {
       eGsmstate = GSM_SM_MSGTRANMIT;
       disposegsmSendEvent();
   }
   return eGsmstate; 
}

gsmSmStates gsmstateconfig(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled)
{
    gsmSmStates eGsmstate = GSM_SM_CONFIG;
    eGsmstate = gsmConfigTask(psgsmsysEvents,eGsmstate);
    return eGsmstate;
}

gsmSmStates gsmstatemsgread(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled)
{
    gsmSmStates eGsmstate = GSM_SM_MESGREAD;
    eGsmstate = gsmReceiveEventTask(psgsmsysEvents,eGsmstate);
    return eGsmstate;
}

gsmSmStates gsmstatemsgtransmit(gsmsysEvents* psgsmsysEvents,bool* psgsmEventhandled)
{
   gsmSmStates eGsmstate = GSM_SM_MSGTRANMIT;
   eGsmstate = gsmTransmitMsgTask(psgsmsysEvents,eGsmstate);
   return eGsmstate;
}

gsmSmStates gsmConfigTask(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate)
{   
    switch(gsgsmState.egsmconfigState)
    {
        case GSMTURNOFFECHO:
        {
            gsmTurnOffecho();
            gsgsmState.egsmconfigState = GSMTURNOFFECHORES;
            //duSendData1("send echo",strlen("send echo"));
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMTURNOFFECHORES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                duSendData1("send echo1\r\n",strlen("send echo1\r\n"));
                gsmretry = 0;
                gsgsmState.egsmconfigState = GSMATCMD;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   //duSendData1("send echo",strlen("send echo"));
                   gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMATCMD:
        {
            gsmATcommand();
            gsgsmState.egsmconfigState = GSMATCMDRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMATCMDRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                duSendData1("send2\r\n",strlen("send2\r\n"));
                gsmretry = 0;
                //eGsmstate =  GSM_SM_IDEAL;
                gsgsmState.egsmconfigState = GSMSIMSTATUS;
                //gsgsmState.egsmconfigState = GSMSETCALLID;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmconfigState = GSMATCMD;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMSIMSTATUS:
        {
            gsmSimStatus();
            gsgsmState.egsmconfigState = GSMSIMSTATUSRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMSIMSTATUSRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                duSendData1("simok\r\n",strlen("simok\r\n"));
                gsmretry = 0;
                gsgsmState.egsmconfigState = GSMGETSIGSTR;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmconfigState = GSMSIMSTATUS;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMGETSIGSTR:
        {
            gsmSignalSrength();
            gsgsmState.egsmconfigState = GSMGETSIGSTRRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMGETSIGSTRRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                //duSendData1("send4\r\n",strlen("send4\r\n"));
                gsmretry = 0;
                gsgsmState.egsmconfigState = GSMSETCALLID;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmconfigState = GSMGETSIGSTR;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMSETCALLID:
        {
            gsmSetCallerID(1);
            gsgsmState.egsmconfigState = GSMSETCALLIDRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMSETCALLIDRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                duSendData1("send5\r\n",strlen("send5\r\n"));
                gsmretry = 0;
                gsgsmState.egsmconfigState = GSMSMSSETMOD;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmconfigState = GSMSETCALLID;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMSMSSETMOD:
        {
            gsmTestorPduMode(1);
            gsgsmState.egsmconfigState = GSMSMSSETMODRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMSMSSETMODRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
                //duSendData1("configured\r\n",strlen("configured\r\n"));
                gsgsmState.egsmconfigState = GSMDELETEALLSMS;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmconfigState = GSMSMSSETMOD;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMDELETEALLSMS:
        {
            gsmDeleteAllSms();
            gsgsmState.egsmconfigState = GSMDELETEALLSMSRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMDELETEALLSMSRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
                duSendData1("smsdeleted\r\n",strlen("smsdeleted\r\n"));
                gsgsmState.egsmconfigState = GSMSMSINDICATION;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                gsmretry++;
                stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                gsgsmState.egsmconfigState = GSMDELETEALLSMS;
                if(gsmretry>=5)
                {
                    eGsmstate =  GSM_SM_IDEAL;
                    gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                    gsmretry = 0;
                      //print reason
                }
            }
            break;
        }
        case GSMSMSINDICATION:
        {
            gsmSmsindication(1,1,0,0,0);
            gsgsmState.egsmconfigState = GSMSMSINDICATIONRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMSMSINDICATIONRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
                duSendData1("gsmconfigured\r\n",strlen("gsmconfigured\r\n"));
                gSconfigflag.egsmconfigflag = GSM_CONFIGURED;
                eGsmstate =  GSM_SM_IDEAL;
                gsgsmState.egsmconfigState = GSMTURNOFFECHO;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmconfigState = GSMSMSINDICATION;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmconfigState = GSMTURNOFFECHO;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
    }
return eGsmstate;   
}

gsmSmStates gsmReceiveEventTask(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate)
{   
    switch(gsgsmState.egsmreadmsgstate)
    {
        case GSMREADMSG:
        {
            gsmReadSms(getsmsindex());
            gsgsmState.egsmreadmsgstate = GSMREADMSGRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMREADMSGRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmreadmsgstate = GSMREADMSG;
                   if(gsmretry>=5)
                   {
                      //eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmreadmsgstate = GSMDELETEMSG;
                      gsmretry = 0;
                      //print reason
                   }
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_KNOWN_MESG_REC)
            {
               //process msg
               stopTimer(GSMTIMER);
               gsmretry = 0;
               //gsgsmState.egsmreadmsgstate = GSMDELETEMSG;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_UNKNOWN_MESG_REC)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
               //gsgsmState.egsmreadmsgstate = GSMDELETEMSG; 
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
               gsgsmState.egsmreadmsgstate = GSMDELETEMSG; 
            }
            break;
        }
        case GSMDELETEMSG:
        {
            gsmDeleteSms(getsmsindex());
            gsgsmState.egsmreadmsgstate = GSMDELETEMSGRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMDELETEMSGRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
                duSendData1("\r\ndelete\r\n",strlen("\r\ndelete\r\n"));
                eGsmstate =  GSM_SM_IDEAL;
                //eGsmstate = GSM_SM_MSGTRANMIT;
                gsgsmState.egsmreadmsgstate = GSMREADMSG;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmreadmsgstate = GSMDELETEMSG;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmreadmsgstate = GSMREADMSG;
                      gsmretry = 0;
                      //print reason
                   }
            } 
            break;
        }
        
    }
    
return eGsmstate;       
}

gsmSmStates gsmTransmitMsgTask(gsmsysEvents* psgsmsysEvents,gsmSmStates eGsmstate)
{ 
    switch(gsgsmState.egsmtransmitmsgstate)
    {
        case GSMSETMOBFORMSG:
        {
            gsmSendSms("918317482672");
            gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSGRES;
            startTimer(GSMTIMER,2000U);
            break;
        }
        case GSMSETMOBFORMSGRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_SMS_TRANMIT_READY)
            {
                stopTimer(GSMTIMER);
                gsmretry = 0;
                //duSendData1("messagesend\r\n",strlen("messagesend\r\n"));
                gsgsmState.egsmtransmitmsgstate = GSMTRANMITMSG;   
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("messagesend\r\n",strlen("messagesend\r\n"));
                   //duSendData1("configured",10);
                   gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSG;
                   if(gsmretry>=5)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      //duSendData1("messagesend\r\n",strlen("messagesend\r\n"));
                      gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSG;
                      gsmretry = 0;
                      //print reason
                   }
            }
            break;
        }
        case GSMTRANMITMSG:
        {
            gsmSendSmsData(gsmTransmitdata);
            gsgsmState.egsmtransmitmsgstate = GSMTRANMITMSGRES;
            startTimer(GSMTIMER,5000U);
            break;
        }
        case GSMTRANMITMSGRES:
        {
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ANSWER_OK)
            {
                stopTimer(GSMTIMER);
                gsmTretry = 0;
                eGsmstate =  GSM_SM_IDEAL;
                duSendData1("messagesend\r\n",strlen("messagesend\r\n"));
                gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSG;
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_ERROR)
            {
                stopTimer(GSMTIMER);
                gsmTretry = 0;
                eGsmstate =  GSM_SM_IDEAL;
                duSendData1("messagenotsend\r\n",strlen("messagenotsend\r\n"));
                gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSG;  
            }
            if(psgsmsysEvents->eGsmTypeEvent == GSM_TIME_OUT)
            {
                   gsmTretry++;
                   stopTimer(GSMTIMER);
                   //duSendData1("configured",10);
                   gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSG;
                   if(gsmTretry>=3)
                   {
                      eGsmstate =  GSM_SM_IDEAL;
                      gsgsmState.egsmtransmitmsgstate = GSMSETMOBFORMSG;
                      gsmTretry = 0;
                      //print reason
                   }
            }
            break;
        }
    }
  return eGsmstate;  
}