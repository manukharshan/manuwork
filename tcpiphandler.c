#ifdef TCP_SERVER

#include "tcpiphandler.h"
#include "events.h"
#include "app.h"
#include "tcp.h"
#include "datatypeconversion.h"
#include "copleySmHandler.h"
#include "sys_devcon_cache.h"
#include "tcpip/src/tcpip_private.h"
/*Definitions*/
#define TCPIP_RECEIVE_BUF_SIZE 500
#define LEN_TCP_RX_CMD 40
#define LEN_UDP_RX_CMD 40
tcpipReceivePacket gsTcpipReceive[TCPIP_RECEIVE_BUF_SIZE];
tcpipReceivePacket gsMonitorReceive[TCPIP_RECEIVE_BUF_SIZE];
eventPtr gsTcpipReceiveEvent;
eventPtr gsMonitorReceiveEvent;
tcpipReceivePacket receiveData;
uint8_t command[4];
uint8_t arg[40];

static uint8_t gucTCmdBuf[LEN_TCP_RX_CMD];
static uint16_t guiIndex = 0;



void initTCPHandler (void)
{
    gsTcpipReceiveEvent.uiProcessCtr = 0;
    gsTcpipReceiveEvent.uiOutPtr = 0;
    gsTcpipReceiveEvent.uiInPtr = 0;
    gsMonitorReceiveEvent.uiProcessCtr = 0;
    gsMonitorReceiveEvent.uiOutPtr = 0;
    gsMonitorReceiveEvent.uiInPtr = 0;
}

void tcpipHandlerTask() 
{  
    uint8_t ucTempBuf;  
    if (TCPIP_TCP_IsConnected(appData.tcpServerSocket) && TCPIP_TCP_GetIsReady(appData.tcpServerSocket)) 
    {
        TCPIP_TCP_Get(appData.tcpServerSocket,&ucTempBuf);
        gucTCmdBuf[guiIndex] = ucTempBuf;
        if(gucTCmdBuf[guiIndex]=='\r')
        {
            guiIndex = 0;
            memmove(&gsTcpipReceive[gsTcpipReceiveEvent.uiInPtr].ucCommandByte[0],&gucTCmdBuf[0],LEN_TCP_RX_CMD);
            gsTcpipReceive[gsTcpipReceiveEvent.uiInPtr].ucCommSel = TCP_IP;
            gsTcpipReceiveEvent.uiInPtr ++;
            if (gsTcpipReceiveEvent.uiInPtr >= TCPIP_RECEIVE_BUF_SIZE)
            {
                gsTcpipReceiveEvent.uiInPtr = 0;
            }
            gsTcpipReceiveEvent.uiProcessCtr ++;
        }
        else
        {
            guiIndex ++;
        }
    }
    
}

void udpHandlerTask() 
{
    uint8_t ucTempBuf[30];    
    if (TCPIP_UDP_IsConnected(appData.udpServerSocket) && TCPIP_UDP_GetIsReady(appData.udpServerSocket)) 
    {
        TCPIP_UDP_ArrayGetRaw(appData.udpServerSocket, &ucTempBuf[0], LEN_UDP_RX_CMD);        
        memmove(&gsTcpipReceive[gsTcpipReceiveEvent.uiInPtr].ucCommandByte[0],&ucTempBuf[0],LEN_UDP_RX_CMD);
        gsTcpipReceive[gsTcpipReceiveEvent.uiInPtr].ucCommSel = UDP;
        gsTcpipReceiveEvent.uiInPtr ++;
        if (gsTcpipReceiveEvent.uiInPtr >= TCPIP_RECEIVE_BUF_SIZE)
        {
            gsTcpipReceiveEvent.uiInPtr = 0;
        }
        gsTcpipReceiveEvent.uiProcessCtr ++;
    }
}

bool getTcpipReceiveEvent(tcpipReceivePacket *psTcpipReceive) 
{
    bool bRetVal = true;
    if (gsTcpipReceiveEvent.uiProcessCtr > 0) {
        *psTcpipReceive = gsTcpipReceive[gsTcpipReceiveEvent.uiOutPtr];
    } else 
    {
        bRetVal = false;
    }
    return bRetVal;
}

void disposeTcpipReceiveEvent() 
{
    gsTcpipReceiveEvent.uiOutPtr++;
    if (gsTcpipReceiveEvent.uiOutPtr >= TCPIP_RECEIVE_BUF_SIZE)
    {
        gsTcpipReceiveEvent.uiOutPtr = 0;
    }
    gsTcpipReceiveEvent.uiProcessCtr--;
}

void processTcpipData(void)
{
    int i = 0,j=0;
    if(getTcpipReceiveEvent(&receiveData))
    {
        memcpy(&command[0],&(receiveData.ucCommandByte[0]),3);
        i=3;
        while(receiveData.ucCommandByte[i] != '\r')
        {
            arg[j++] = receiveData.ucCommandByte[i++];
        }
        arg[j]='\0';
        command[3]='\0';
        //command purse function
        commandParse(&command[0],&arg[0],receiveData.ucCommSel);
        disposeTcpipReceiveEvent();
    }
}

//bool tcpIPSendMesg(mainSmStates eCopleySmStats, uint8_t ucCopleyData[], uint8_t ucCommandChannel) 
//{
//    bool bRetVal = true;
//    uint8_t ucTCPIPPutBuffer[100];
//    uint16_t uiIndex;
//    unsignedIntToString((uint16_t) eCopleySmStats, DIGIT_3, &ucTCPIPPutBuffer[0]);
//    memset(&ucTCPIPPutBuffer[3], ':', 1U);
//    uiIndex = 0U;
//
//    if (ucCopleyData != NULL) 
//    {
//        while (ucCopleyData[uiIndex] != '\r') 
//        {
//            ucTCPIPPutBuffer[uiIndex + 4U] = ucCopleyData[uiIndex];
//            uiIndex++;
//        }
//
//        ucTCPIPPutBuffer[uiIndex + 4U] = ucCopleyData[uiIndex];
//    }
//
//    uiIndex = uiIndex + 4U + 1U;
//
//    if (ucCommandChannel == TCP_IP) 
//    {
//        TCPIP_TCP_ArrayPut(appData.tcpServerSocket, (uint8_t *) ucTCPIPPutBuffer, uiIndex);
//    } 
//    else 
//    {
//        bRetVal = sendResposneViaUDP(ucTCPIPPutBuffer, uiIndex);
//    }
//
//    return bRetVal;
//
//}

bool sendResposneViaUDP(uint8_t ucUDPResponse[], uint16_t uiSize) 
{
    bool bRetval = true;
    TCPIP_NET_IF *pNetIf;
    uint16_t uiTempSocket;
    uint8_t ucUDpCommandFormat[50];
    uint16_t uiUDPPacketSize; 
    memmove(&ucUDpCommandFormat[0],&ucUDPResponse[0],uiSize); 
    uiUDPPacketSize = uiSize;
    uiTempSocket = TCPIP_UDP_ClientOpen(IP_ADDRESS_TYPE_IPV4, appData.udpPort, 0);

    if (uiTempSocket == INVALID_UDP_SOCKET) { // keep the request pending, we'll try next time
        return false;
    }
    pNetIf = (TCPIP_NET_IF*)TCPIP_STACK_IndexToNet(0);

    if(TCPIP_STACK_NetworkIsLinked(pNetIf))
    {   // reply only if this interface is up and running

        TCPIP_UDP_SocketNetSet (uiTempSocket, pNetIf);
        TCPIP_UDP_BcastIPV4AddressSet(uiTempSocket, UDP_BCAST_NETWORK_DIRECTED, pNetIf);
        if ((TCPIP_UDP_IsConnected(uiTempSocket))&&(TCPIP_UDP_PutIsReady(uiTempSocket))) 
        {
            TCPIP_UDP_ArrayPutRaw(uiTempSocket, &ucUDpCommandFormat[0], uiUDPPacketSize);

            TCPIP_UDP_Flush(uiTempSocket);

            TCPIP_UDP_Close(uiTempSocket);
        } 
        else 
        {
            bRetval = false;
        }
    }
    else 
    {
        bRetval = false;
    }
    return bRetval;
}


#endif