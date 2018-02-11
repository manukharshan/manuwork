#include "timerfunctions.h"
#include "loraModem.h"
#include "loraSmHandler.h"
#include "debuguarthandler.h"
#include "rs485Handler.h"
#include "assemblePacket.h"
#include "copleytransmithandler.h"
#include "copleycommandinterface.h"


extern int testrotate;

loraSmStates gloraSmStates = LORA_SM_IDEAL;
sConfigflag gSconfigflag;
configState geConfigState = RADIOMACPAUSE;
transmitState geTransmitState = TRANSMIT;
receiveState geReceiveState = LORARECIEVE;

//sMotorcontrolstate gSmotorcontrolstate;

//unsigned char dataReceived = 1;
extern int testrotate;

static unsigned char retry;

static unsigned char Transretry;

char* loratransmitData;

static lorasmTable gLorasmTable[LORA_SM_MAX_STATE] = 
{
    {LORA_SM_IDEAL,lorastateideal},
    {LORA_SM_CONFIG,lorastateconfig},
    {LORA_SM_TRANSMIT,lorastatetransmit},
};

loraSmStates loraSmhandler(lorasysEvents* pslorasysEvents,bool* psloraEventhandled)
{
    lorasmTable *loraSmTab = gLorasmTable;
    while(loraSmTab != &gLorasmTable[LORA_SM_MAX_STATE])
    {
        if(loraSmTab->eloraSmStates == gloraSmStates)
        {
            break;
        }
        loraSmTab++;
    }
    gloraSmStates =  loraSmTab->LoraSmFuncitons(pslorasysEvents,psloraEventhandled);
    return gloraSmStates;
}

loraSmStates lorastateideal(lorasysEvents* pslorasysEvents,bool* psloraEventhandled)
{
   loraSmStates eLorastate =  LORA_SM_IDEAL;
   if(gSconfigflag.eloraconflag == LORA_NOT_CONFIGURED)
   {
       //duSendData1("configuring Lora...\r\n",strlen("configuring Lora...\r\n"));
       rs485SendData("configuring Lora...\r\n",strlen("configuring Lora...\r\n"));
       eLorastate = LORA_SM_CONFIG;
       PORTAbits.RA14 = 0;
   }
   else if (gSconfigflag.eloraconflag == LORA_CONFIGURED)
   {
       eLorastate = loraReceiveTask(pslorasysEvents,eLorastate);
   }
   return eLorastate;
}

loraSmStates lorastateconfig(lorasysEvents* pslorasysEvents,bool* psloraEventhandled)
{
   loraSmStates eLorastate =  LORA_SM_CONFIG;
   if(gSconfigflag.eloraconflag == LORA_NOT_CONFIGURED)
   {
       switch(geConfigState)
       {
          case RADIOMACPAUSE:
           {
               loraWanmacPause();
               geConfigState = RADIOMACPAUSERES;
               startTimer(LORATIMER,2000U);
               break;
           }
           case RADIOMACPAUSERES:
           {
               if(pslorasysEvents->eLoraTypeEvent == LORA_MACPAUSE_OK)
               {
                   stopTimer(LORATIMER);
                   retry = 0;
                   //duSendData1("configured",10);
                   geConfigState = RADIOSETSF;
               }
               if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   stopTimer(LORATIMER);
                   //duSendData1("configured",10);
                   geConfigState = RADIOMACPAUSE;
                   if(retry>=5)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break;   
           }
           case RADIOSETSF:
           {
               loraWansetRadioSF("sf12");
               geConfigState = RADIOSETRESSF;
               //duSendData1("configured",10);
               startTimer(LORATIMER,2000U);
               break;
           }
           case RADIOSETRESSF:
           {
               if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
               {
                   stopTimer(LORATIMER);
                   retry = 0;
//                   duSendData1("radiosetsf\r\n",strlen("radiosetsf\r\n"));
                   geConfigState = RADIOSETPWR;
               }
               else if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   stopTimer(LORATIMER);
                   //duSendData1("configured",10);
                   geConfigState = RADIOSETSF;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break;
           }
           case RADIOSETPWR:
           {
               loraWansetRadioPower(15);
               geConfigState = RADIOSETPWRRES;
               //duSendData1("configured",10);
               startTimer(LORATIMER,1000U);
               break;
           }
           case RADIOSETPWRRES:
           {
              if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
               {
                   stopTimer(LORATIMER);
                   retry = 0;
                   //duSendData("configured",10);
                   geConfigState = RADIOSETFREQ;
               }
               else if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   geConfigState = RADIOSETPWR;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break; 
           }
           case RADIOSETFREQ:
           {
               loraWansetRadioFreq(865000000);
               geConfigState = RADIOSETFREQRES;
               startTimer(LORATIMER,1000U);
               break;
           }
           case RADIOSETFREQRES:
           {
              if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
               {
                   stopTimer(LORATIMER);
                   //duSendData("configured",10);
                   retry = 0;
                   geConfigState = RADIOSETCRC;
               }
               else if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   stopTimer(LORATIMER);
                   geConfigState = RADIOSETFREQ;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break; 
           }
           case RADIOSETCRC:
           {
               loraWansetRadioCRC("on");
               geConfigState = RADIOSETCRCRES;
               startTimer(LORATIMER,1000U);
               break;
           }
           case RADIOSETCRCRES:
           {
              if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
               {
                   stopTimer(LORATIMER);
                   retry = 0;
                   //duSendData("configured",10);
                   geConfigState = RADIOSETCR;
               }
               else if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   stopTimer(LORATIMER);
                   geConfigState = RADIOSETCRC;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break;   
           }
           case RADIOSETCR:
           {
               loraWansetRadioCR("4/5");
               geConfigState = RADIOSETCRRES;
               startTimer(LORATIMER,1000U);
               break;
           }
           case RADIOSETCRRES:
           {
               if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
               {
                   
                   stopTimer(LORATIMER);
                   retry = 0;
                   //duSendData("configured",10);
                   geConfigState = RADIOSETWATCHDOG;
               }
               else if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   stopTimer(LORATIMER);
                   geConfigState = RADIOSETCR;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break;  
           }
           case RADIOSETWATCHDOG:
           {
               loraWansetWdt(3000);
               geConfigState = RADIOSETWATCHDOGRES;
               startTimer(LORATIMER,1000U);
               break;
           }
           case RADIOSETWATCHDOGRES:
           {
               if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
               {
                   stopTimer(LORATIMER);
                   retry = 0;
                   //eLorastate = LORA_SM_TRANSMIT;
                   //eLorastate = LORA_SM_IDEAL;
                   eLorastate = LORA_SM_IDEAL;
                   gSconfigflag.eloraconflag = LORA_CONFIGURED;
                   //geloraconfigflag = LORA_TRANSMIT;
                   //geloraconfigflag = LORA_RECEIVE;
                   duSendData1("Lora configured\r\n",strlen("Lora configured\r\n"));
                   geConfigState = RADIOMACPAUSE;
               }
               else if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
               {
                   retry++;
                   stopTimer(LORATIMER);
                   geConfigState = RADIOSETWATCHDOG;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      //print reason
                   }
               }
               break;  
           }
       }
   }
   
   return eLorastate;
}

loraSmStates lorastatetransmit(lorasysEvents* pslorasysEvents,bool* psloraEventhandled)
{
   loraSmStates eLorastate =  LORA_SM_TRANSMIT;
   switch(geTransmitState)
    {
        case TRANSMIT:
        {
            loraTransmit(loratransmitData);
            geTransmitState = TRANSMITRESP;
            startTimer(LORATIMER,5000U);
            break;
        }
        case TRANSMITRESP:
        {
            if(pslorasysEvents->eLoraTypeEvent == LORA_TRANSMIT_OK)
            {
                stopTimer(LORATIMER);
                retry = 0;
                //duSendData1("transmit",8);
                geTransmitState = TRANSMIT;
//                eLorastate = MOTOR_START_MOV;
                //geloraconfigflag = LORA_RECEIVE;
                eLorastate = LORA_SM_IDEAL;
                //duSendData1("transmit",8);
            }
            if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
            {
                retry++;
                stopTimer(LORATIMER);
                geTransmitState = TRANSMIT;
                if(retry>=3)
                {
                    geTransmitState = TRANSMIT;
                    eLorastate =  LORA_SM_IDEAL;
                    retry = 0;
                      //print reason
                }
            }
            break;
        }
    } 
   return eLorastate;
}

loraSmStates loraReceiveTask(lorasysEvents* pslorasysEvents,loraSmStates eLorastate)
{
    switch(geReceiveState)
    {
        case LORARECIEVE:
        {
            loraReceive();
            //duSendData1("RECEIVE",7);
            geReceiveState = LORARECEIVERESP;
            //geReceiveState = LORA_SM_IDEAL;
            startTimer(LORATIMER,1000U);
            break;
        }
        case LORARECEIVERESP:
        {
            if(pslorasysEvents->eLoraTypeEvent == LORA_ANSWER_OK)
            {
               retry = 0;
               stopTimer(LORATIMER);
               //duSendData1("RECEIVE",7);
            }
            if(pslorasysEvents->eLoraTypeEvent == LORA_TIME_OUT)
            {
                   retry++;
                   stopTimer(LORATIMER);
                   geReceiveState = LORARECIEVE;
                   if(retry>=3)
                   {
                      eLorastate =  LORA_SM_IDEAL;
                      retry = 0;
                      geReceiveState = LORARECIEVE;
                      //print reason
                   }
            }
            if(pslorasysEvents->eLoraTypeEvent == LORA_RADIO_ERROR)
            {
                   stopTimer(LORATIMER);
                   if(getLoraSendEvent(&loratransmitData))
                   {
                     eLorastate =  LORA_SM_TRANSMIT;
                     disposeLoraSendEvent();
                   }
                   geReceiveState = LORARECIEVE;
            }
            if(pslorasysEvents->eLoraTypeEvent == LORA_DATA_RECEIVE)
            {
                stopTimer(LORATIMER);
                //duSendData1("RECEIVE",7);
                geReceiveState = LORARECIEVE;
                //eLorastate =  LORA_SM_TRANSMIT;
                //geloraconfigflag = LORA_TRANSMIT;
            }
            break;
        }
        
    }
    return eLorastate;
}