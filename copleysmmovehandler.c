
#include "copleySmHandler.h"
#include "copleytransmithandler.h"
#include "events.h"
#include "app.h"
#include "string.h"
#include "stdlib.h"
#include "copleysmmovehandler.h"
#include "tcpiphandler.h"
#include "tcpiphandler.h"

#if 0
static copleyInitMoveStates geCopleyInitMoveState;
static copletMonitorMOveStates geCopleMonitorMoveStates;
static copleySmStates geCurrentMoveState;
static tcpipReceivePacket tcpIpMonitorReceivepacket;
static uint16_t uiTempCommand;



copleySmStates copleySMRelativeMovePosition0(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_0;
   
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_0,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
           
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_0,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
            geCurrentMoveState = eCopleyState;
            eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
            copleySMStateEntryActions(eCopleyState);
            geCopleMonitorMoveStates = MONITOR_MOVE_STATUS;
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_0,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
            geCurrentMoveState = eCopleyState;
            eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
            copleySMStateEntryActions(eCopleyState);
            geCopleMonitorMoveStates = MONITOR_MOVE_STATUS;
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    return eCopleyState;
}


copleySmStates copleySMRelativeMovePosition1(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_1;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_1,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_1,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_1,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    return eCopleyState;
}



copleySmStates copleySMRelativeMovePosition2(sysEvents *psSysEvt, bool *pbEventHandled)
{
      
   copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_2;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_2,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_2,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_2,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    } 
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition3(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_3;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_3,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_3,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_3,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition4(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_4;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_4,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_4,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_4,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition5(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_5;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_5,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_5,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_5,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition6(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_6;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_6,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_6,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_6,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition7(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_7;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_7,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_7,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_7,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition8(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_8;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_8,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_8,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_8,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    } 
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition9(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_9;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_9,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_9,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_9,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition10(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_10;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_10,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_10,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_10,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition11(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_11;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_11,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_11,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_11,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition12(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_12;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_12,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_12,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_12,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition13(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_13;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_13,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_13,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_13,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition14(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_14;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_14,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_14,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_14,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition15(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_15;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_15,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_15,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_15,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition16(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_16;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_16,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_16,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_16,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition17(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_17;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_17,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_17,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_17,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition18(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_18;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_18,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_18,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_18,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition19(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_19;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_19,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_19,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_19,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition20(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_20;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_20,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_20,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_20,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition21(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_21;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_21,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_21,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_21,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition22(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_22;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_22,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_22,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_22,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition23(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_23;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_23,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_23,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_23,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition24(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_24;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_24,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_24,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_24,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}

copleySmStates copleySMRelativeMovePosition25(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_RELATIVE_MOVE_POSITION_25;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_25,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_25,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_RELATIVE_MOVE_POSITION_25,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }    
    
    
    return eCopleyState;
}


copleySmStates copleySMAbsoluteMovePosition0(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_0;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_0,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_0,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_0,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }  
    
    
    return eCopleyState;
}


copleySmStates copleySMAbsoluteMovePosition1(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_1;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_1,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_1,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_1,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    return eCopleyState;
}



copleySmStates copleySMAbsoluteMovePosition2(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_2;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_2,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_2,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_2,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition3(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_3;
    
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_3,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_3,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_3,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition4(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_4;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_4,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_4,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_4,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition5(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_5;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_5,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_5,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_5,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition6(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_6;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_6,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_6,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_6,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition7(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_7;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_7,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_7,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_7,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition8(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_8;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_8,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_8,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_8,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition9(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_9;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_9,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_9,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_9,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition10(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_10;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_10,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_10,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_10,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition11(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_11;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_11,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_11,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_11,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition12(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_12;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_12,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_12,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_12,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition13(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_13;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_13,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_13,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_13,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition14(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_14;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_14,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_14,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_14,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition15(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_15;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_15,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_15,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_15,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition16(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_16;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_16,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_16,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_16,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition17(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_17;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_17,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_17,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_17,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition18(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_18;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_18,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_18,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_18,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition19(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_19;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_19,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_19,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_19,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition20(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_20;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_20,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_20,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_20,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition21(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_21;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_21,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_21,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_21,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition22(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_22;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_22,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_22,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_22,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition23(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_23;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_23,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_23,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_23,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition24(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_24;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_24,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_24,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_24,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}

copleySmStates copleySMAbsoluteMovePosition25(sysEvents *psSysEvt, bool *pbEventHandled)
{
   
    copleySmStates eCopleyState = COPLEY_SM_ABSOLUTE_MOVE_POSITION_25;
    if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
    {
        if(geCopleyInitMoveState != INIT_MOVE_END)
        {
            copleyInitMove(psSysEvt,pbEventHandled);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_25,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
        else
        {
            SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
            tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_25,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
        }
    }
    else if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        *pbEventHandled = true;
        tcpIPSendMesg(COPLEY_SM_ABSOLUTE_MOVE_POSITION_25,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
       
        
        if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
        {
            eCopleyState = COPLEY_SM_IDLE;
        }
        else
        {
             SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
        }
    }
    else
    {
        *pbEventHandled = false;
               
    }
    
    
    
    return eCopleyState;
}


copleySmStates copleySMMonitorMoveStatus(sysEvents *psSysEvt, bool *pbEventHandled)
{
    copleySmStates eCopleyState = COPLEY_SM_MONITOR_MOVE_STATUS;
    
    
    if(psSysEvt->eTypeEvent == COPLEY_MESSAGE)
    {
        
        switch (geCopleMonitorMoveStates)
        {
            case MONITOR_MOVE_STATUS:
            {
                
                tcpIPSendMesg(geCurrentMoveState,&psSysEvt->sCopleyData[0],psSysEvt->sTcpipRecvData.ucCommSel);
                
                if (('0' == psSysEvt->sCopleyData[2]) && ('\r' == psSysEvt->sCopleyData[3]))
                {
                    eCopleyState = COPLEY_SM_IDLE;
                }
                else
                {
                    DRV_USART0_WriteByte('G');
                    if(true == getTcpipMonitorReceiveEvent(&tcpIpMonitorReceivepacket))
                    {
                        DRV_USART0_WriteByte('G');
    
                        uiTempCommand = atoi(tcpIpMonitorReceivepacket.ucCommandByte);
    
                        if ((uiTempCommand < 500) && (uiTempCommand > 0))
                        {
                            
                            copleySMStateEntryActions(uiTempCommand);
                            geCopleMonitorMoveStates = REPORT_COMMANDS;
                            disposeTcpipMontorReceiveEvent();
                        }
                    }
                    else
                    {
                        SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
                    }
                }
     
                break;
            }
            case REPORT_COMMANDS:
            {
            
                tcpIPSendMesg(uiTempCommand,&psSysEvt->sCopleyData[0],tcpIpMonitorReceivepacket.ucCommSel);
                
                SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
                
                geCopleMonitorMoveStates = MONITOR_MOVE_STATUS;
                
                break;
            }
        }    
                
    }
    
    return eCopleyState;
}








void copleySetInitMoveState(copleyInitMoveStates eColeyInitMoveState)
{
    geCopleyInitMoveState = eColeyInitMoveState;
}

void copleyInitMove (sysEvents *psSysEvt, bool *pbEventHandled)
{
    
    switch (geCopleyInitMoveState)
    {
        
        case INIT_MOVE_COPLEY_PROFILE_RELATIVE_TRAP:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_SET_PROFILE_TYPE, (uint8_t *)"256");
                geCopleyInitMoveState = INIT_MOVE_COPLEY_SET_VELOCITY;
            }
            else
            {
                *pbEventHandled = false;
            }
          break;  
        }
        case INIT_MOVE_COPLEY_PROFILE_ABSOLUTE_TRAP:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_SET_PROFILE_TYPE, (uint8_t *)"0");
                geCopleyInitMoveState = INIT_MOVE_COPLEY_SET_VELOCITY;
            }
            else
            {
                *pbEventHandled = false;
            }
            break;
        }
        case INIT_MOVE_COPLEY_SET_VELOCITY:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_SET_VELOCITY, (uint8_t *)"10000");
                geCopleyInitMoveState = INIT_MOVE_COPLEY_SET_ACCEL_TIME;
            }
            else
            {
                *pbEventHandled = false;
            }
            break;

        }
        case INIT_MOVE_COPLEY_SET_ACCEL_TIME:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_SET_ACCEL_TIME, (uint8_t *)"200");
                geCopleyInitMoveState = INIT_MOVE_COPLEY_SET_DECL_TIME;
            }
            else
            {
                *pbEventHandled = false;
            }
            break;
           
        }
        case INIT_MOVE_COPLEY_SET_DECL_TIME:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_SET_DECEL_TIME, (uint8_t *)"200");
                geCopleyInitMoveState = INIT_MOVE_COPLEY_SET_DESIRED_STATE;
            }
            else
            {
                *pbEventHandled = false;
            }
            break;
        }
        case INIT_MOVE_COPLEY_SET_DESIRED_STATE:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_SET_DESIRED_STATE, (uint8_t *)"21");
                geCopleyInitMoveState = INIT_MOVE_COPLEY_START_MOVE;
            }
            else
            {
                *pbEventHandled = false;
            }
            break;
        }
        case INIT_MOVE_COPLEY_START_MOVE:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                *pbEventHandled = true;
                SendCommandToCopley(COPLEY_START_MOVE,(uint8_t *)NULL);
                geCopleyInitMoveState = INIT_MOVE_WAIT_END;
            }
            else
            {
                *pbEventHandled = false;
            }
            break;
        }
        case INIT_MOVE_WAIT_END:
        {
            if(psSysEvt->eTypeEvent == COPLEY_RESPONSE)
            {
                SendCommandToCopley(COPLEY_GET_STATUS,(uint8_t *)NULL);
                *pbEventHandled = true;
                geCopleyInitMoveState = INIT_MOVE_END;
            }
            else
            {
                *pbEventHandled = false;
            }
            
            break;
        }
        case INIT_MOVE_END:
        {
            break;
        }
        default:
        {
            break;
        }
        
    }
    
}

#endif