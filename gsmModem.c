/*
 *  Version:          0.0
 *  Design:           manu k harshan
 *  file :            gsmmodem.c
 */
#include "datatypeconversion.h"
#include "gsmModem.h"

//int ginumber = 918610840814;
//int ginumber = 918296448053;
//int ginumber = 917795343490;
int ginumber = 918317482672;
char gcnumber[14];
char gsmcommandbuffer[40];
gsmmonitor gsgsmmonitor;
int sms = 0;
unsigned char command4[4];
unsigned char arg4[20];

gsmEventType gsmProcessReceiveEvent(char* response)
{
   gsmEventType egsmEventType = GSM_NO_ANSWER;
   //duSendData1(response,strlen(response));
   if(!memcmp(response,"OK\r",3))
        return GSM_ANSWER_OK;
   else if(!memcmp(response,"ERROR\r",6))
        return GSM_ERROR;
//   else if(!memcmp(response,"RING\r",14))
//       return GSM_RING;
   else if(!memcmp(response,"+CME ERROR:",11))
        return GSM_CME_ERROR;
   else if(!memcmp(response,"+CLIP:",6))
   {
       //egsmEventType = gsmProcessReceivecommand(response);
       gsmProcessReceivecommand(CALLRECEIVECHECK,response);
       //return egsmEventType;
       return GSM_RING;
   }
   else if(!memcmp(response,"NO CARRIER\r",11))
       return GSM_NO_CARRIER;
   
   else if(!memcmp(response,"+CMTI:",6))
   {
       gsmProcessReceivecommand(SMSRECEIVEINDEX,response);
       //duSendData1("smsrec\r\n",strlen("smsrec\r\n"));
       return GSM_MESG_REC;
   }
   else if(!memcmp(response,"+CMGR:",6))
   {
       egsmEventType = gsmProcessReceivecommand(SMSRECEIVECHECK,response);
       return egsmEventType;
   }
   else if(!memcmp(response,"+CSQ:",5))
   {
       gsmProcessReceivecommand(RSSIRECEIVED,response);
   }
   else if(!memcmp(response,"+CPIN:",6))
   {
       gsmProcessReceivecommand(SIMREADYCHECK,response);
   }
   else if(sms) 
   {
       gsmProcessReceivecommand(SMSRECEIVED,response);
   }
   else if(!memcmp(response,">\r",2))
   {
       return GSM_SMS_TRANMIT_READY;
   }
//   else if (!memcmp(response,"+CMGS:",6))
//   {
//       
//   }
}

gsmEventType gsmProcessReceivecommand(recdatatype gerecdatatype,char* response)
{
   gsmEventType gsmEvent;
   char message[40];
   int i = 0,j=0,k=0,number;
  switch(gerecdatatype)
  {
    case CALLRECEIVECHECK:
    {
       while(*response!='\r')
       {
         if(i>8)
         {
           message[k++] = *response;
         }
         response++;
         i++;
       }
       k = 0;
       while(message[k] !='"')
       {
         gcnumber[j++] = message[k];
         k++;
       }
       gcnumber[j]='\0';
       number = atoi(&gcnumber[0]);
       if(ginumber == number)
       {
         duSendData1("call\r\n",strlen("call\r\n"));  
       }
       gsmEvent = GSM_RING;
       break;
    }
   case SMSRECEIVECHECK:
    {
       response++; 
       while(*response!='+')
       {
          response++; 
       }
       response++;
       
       while(*response!='\r')
       {
         message[i++] = *response;
         response++;
       }
       i = 0;
       while(message[i] !='"')
       {
         gcnumber[j++] = message[i];
         i++;
       }
       gcnumber[j]='\0';
       number = atoi(&gcnumber[0]);
       if(ginumber == number)
       {
           duSendData1("sms\r\n",strlen("sms\r\n"));
           sms = 1;
           gsmEvent = GSM_KNOWN_MESG_REC;
       }
     gsmEvent = GSM_UNKNOWN_MESG_REC;
     break;
    }
    case SMSRECEIVEINDEX:
    {
       while(*response!='\r')
       {
         if(i>11)
         {
           message[k++] = *response;
         }
         response++;
         i++;
       }
       message[k] = '\0';
       gsgsmmonitor.smsindex = atoi(&message[0]);
       unsignedIntToString(gsgsmmonitor.smsindex,DIGIT_2,&message[0]);
       duSendData1(message,2);
       gsmEvent = GSM_MESG_REC;
       break;
    }
    case SMSRECEIVED:
    {
        gsmProcessReceiveMsg(response);
//        while(*response!='\r')
//        {
//         message[i++] = *response;
//         response++;
//        }
//        message[i] = '\0';
        sms = 0;
        duSendData1(response,strlen(response));
        break;
    }
    case RSSIRECEIVED:
    {
         while(*response!=':')
         {
          response++; 
         }
         response++;
         while(*response!=',') 
         {
          message[i++] = *response;
          response++;
         }
         message[i] = '\0';
        gsgsmmonitor.rssi = atoi(&message[0]);
        unsignedIntToString(gsgsmmonitor.rssi,DIGIT_2,&message[0]);
        duSendData1(message,strlen(message));
        break;
    }
    case SIMREADYCHECK:
    {
       if(!memcmp(response,"+CPIN: READY",12))
       {
           gsgsmmonitor.simstatus = 1;
           duSendData1("READY\r\n",strlen("READY\r\n"));
           gsmEvent = GSM_ANSWER_OK;
       }
       else
       {
           gsgsmmonitor.simstatus = 0;
           duSendData1("NOTREADY\r\n",strlen("NOTREADY\r\n"));
           gsmEvent = GSM_NO_ANSWER;
       } 
      break;
    }
  }
  return gsmEvent;
}

int32_t getsmsindex(void)
{
   return gsgsmmonitor.smsindex; 
}

int32_t getrssi(void)
{
      return gsgsmmonitor.rssi;  
}


void gsmATcommand(void)
{
  //strcpy(command,"radio set sf %s\r\n");

  sprintf(gsmcommandbuffer,"AT\r",NULL);

  //send command
  guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmTurnOffecho(void)
{
    sprintf(gsmcommandbuffer,"ATE0\r",NULL);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSetErrcommand(char enable)
{
    sprintf(gsmcommandbuffer,"AT+CMEE=%d\r",enable);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSetStartIndication(int8_t start,int8_t ready)
{
    sprintf(gsmcommandbuffer,"AT+MSTART:%d,%d\r",start,ready);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSetCallerID(char set)
{
    sprintf(gsmcommandbuffer,"AT+CLIP=%d\r",set);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSimStatus(void)
{
    sprintf(gsmcommandbuffer,"AT+CPIN?\r",NULL);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmTestorPduMode(char mod)
{
    sprintf(gsmcommandbuffer,"AT+CMGF=%d\r",mod);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSmsindication(int8_t mod,int8_t mt,int8_t bm,int8_t ds,int8_t bfr)
{
    sprintf(gsmcommandbuffer,"AT+CNMI=%d,%d,%d,%d,%d\r",mod,mt,bm,ds,bfr);
    
    //send command 
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmReadSms(int index1)
{
    sprintf(gsmcommandbuffer,"AT+CMGR=%d\r",index1);
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSignalSrength(void)
{
    sprintf(gsmcommandbuffer,"AT+CSQ?\r");
    
    //send command
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmDeleteSms(int index1)
{
    sprintf(gsmcommandbuffer,"AT+CMGD=%d\r",index1);
    
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmDeleteAllSms(void)
{
    sprintf(gsmcommandbuffer,"AT+CMGD=1,4\r",NULL);
    
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}
void gsmSendSms(char* mobNumber)
{
    sprintf(gsmcommandbuffer,"AT+CMGS=\"+%s\"\r",mobNumber);
    duSendData1(gsmcommandbuffer,strlen(gsmcommandbuffer));   
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

void gsmSendSmsData(char* msg)
{
    char ch=0x1A;
    sprintf(gsmcommandbuffer,"%s%c",msg,ch);
    duSendData1(gsmcommandbuffer,strlen(gsmcommandbuffer));
    guSendData(gsmcommandbuffer,strlen(gsmcommandbuffer));
}

gsmEventType gsmProcessReceiveMsg(char* Response)
{
    gsmEventType geGsmEventType;
    geGsmEventType = GSM_MESG_REC;
    char message[20] = {0};
    int i = 0;
    while(*Response != '\r')
    {
       message[i++] = *Response;
       Response++;
    }
    message[i] = '\0';
    strncpy(&command4[0],&message[0],3);
    strcpy(&arg4[0],&message[3]);
    commandParse(&command4[0],&arg4[0],GSM);
    return geGsmEventType;    
}