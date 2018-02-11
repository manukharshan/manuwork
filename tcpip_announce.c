/*******************************************************************************
  TCPIP Announce Client and Server

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    - Provides device hostname and IP address discovery on a local 
      Ethernet subnet (same broadcast domain)
    - Reference: None.  Hopefully AN833 in the future.
*******************************************************************************/

/*******************************************************************************
File Name:  tcpip_announce.c
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_STACK_USE_ANNOUNCE)

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_ANNOUNCE



typedef struct
{
    UDP_SOCKET          skt;    // associated socket
}TCPIP_ANNOUNCE_DCPT;

    
static TCPIP_ANNOUNCE_DCPT announceDcpt;

typedef enum
{
    ANNOUNCE_FIELD_TRUNCATED = 0x01,
    ANNOUNCE_FIELD_MAC_ADDR,
    ANNOUNCE_FIELD_MAC_TYPE,
    ANNOUNCE_FIELD_HOST_NAME,
    ANNOUNCE_FIELD_IPV4_ADDRESS,
    ANNOUNCE_FIELD_IPV6_UNICAST,
    ANNOUNCE_FIELD_IPV6_MULTICAST,
    ANNOUNCE_FIELD_IPV6_DEFAULT_ROUTER,
    ANNOUNCE_FIELD_IPV6_DEFAULT_GATEWAY,
    ANNOUNCE_FIELD_DEVICE_ID,
    ANNOUNCE_FIELD_CONNECTION_STATUS,
} ANNOUNCE_FIELD_PAYLOAD;

static const uint8_t announceFieldTerminator[] = "\r\n";

#if defined (TCPIP_STACK_USE_DHCP_CLIENT)
static TCPIP_DHCP_HANDLE announceDHCPHandler = NULL;
#endif

#if defined (TCPIP_STACK_USE_IPV6)
static IPV6_HANDLE announceIPV6Handler = NULL;
#endif

static int                  announceIfs = 0;            // number of interfaces running on
static int                  announceInitCount = 0;      // module initialization count
static const void*          announceMemH = 0;           // memory handle

static uint32_t             announceRequestMask = 0;    // request mask per interface: bit x for interface x

static tcpipAsyncHandle       announceAsyncSendHandle = 0;  // asynchronous handle
static tcpipAsyncHandle       announceAsyncHandle = 0;      // asynchronous handle

static uint8_t tcpServerIP[15] = {0};
// prototypes
static void             _TCPIP_AnnounceCleanup(void);

static void             ANNOUNCE_Notify(TCPIP_NET_HANDLE hNet, uint8_t evType, const void * param);

static uint8_t guiConnectionStatus = 0;
// implementation; API functions

bool TCPIP_ANNOUNCE_Init(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const TCPIP_ANNOUNCE_MODULE_CONFIG* announceData)
{
    UDP_SOCKET  s;
    bool        initFail = false;

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {   // interface restart
        return true;
    }
    
    // stack init    
    while(announceInitCount == 0)
    {   // first time we're run
        initFail = true;
        // store the memory allocation handle
        announceMemH = stackCtrl->memH;
        announceIfs = stackCtrl->nIfs;
        announceRequestMask = 0;
#if defined (TCPIP_STACK_USE_DHCP_CLIENT)
        announceDHCPHandler = TCPIP_DHCP_HandlerRegister(0, (TCPIP_DHCP_EVENT_HANDLER)ANNOUNCE_Notify, NULL);
        if (announceDHCPHandler == NULL)
        {
            break;
        }
#endif
#if defined (TCPIP_STACK_USE_IPV6)
        announceIPV6Handler = TCPIP_IPV6_HandlerRegister(0, (IPV6_EVENT_HANDLER)ANNOUNCE_Notify, NULL);
        if (announceIPV6Handler == NULL)
        {
            break;
        }
#endif

        announceAsyncSendHandle = _TCPIPStackAsyncHandlerRegister(TCPIP_ANNOUNCE_Send, TCPIP_ANNOUNCE_SendTaskPending, 0);
        if(announceAsyncSendHandle == 0)
        {
            break;
        }

        announceAsyncHandle = _TCPIPStackAsyncHandlerRegister(TCPIP_ANNOUNCE_Task, 0, TCPIP_ANNOUNCE_TASK_RATE); 
        if(announceAsyncHandle == 0)
        {
            break;
        }
        // initstatus
        announceDcpt.skt = INVALID_UDP_SOCKET;

        // Open a UDP socket for inbound and outbound transmission
        // Allow receive on any interface 
        s = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, TCPIP_ANNOUNCE_PORT, 0);

        if(s == INVALID_UDP_SOCKET)
        {
            break;
        }
        announceDcpt.skt = s;

        if(!TCPIP_UDP_RemoteBind(s, IP_ADDRESS_TYPE_IPV4, TCPIP_ANNOUNCE_PORT,  0))
        {
            break;
        }

        if(!TCPIP_UDP_OptionsSet(s, UDP_OPTION_STRICT_PORT, (void*)true))
        {
            break;
        }

        initFail = false;
        break;
    }

    if(initFail)    
    {
        _TCPIP_AnnounceCleanup();
        return false;
    }
    
    announceInitCount++;

    return true;
}

void TCPIP_ANNOUNCE_DeInit(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{

    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT) // stack shut down
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_DOWN) // interface down

    if(announceInitCount > 0)
    {   // we're up and running
        if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_DOWN)
        {
            announceRequestMask &= ~(1 << stackCtrl->netIx);
        }
        else if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
        {   // whole stack is going down
            if(--announceInitCount == 0)
            {   // all closed
                // release resources
                _TCPIP_AnnounceCleanup();
                announceMemH = 0;
            }
        }
    }

}






void TCPIP_ANNOUNCE_Send(void)
{
    UDP_SOCKET  announceSocket;
    uint16_t    dataLen;
    uint16_t    minimumDataLen;
    uint16_t    txLen;
    bool truncated;
    TCPIP_NET_IF *pNetIf;
    const char* interfaceName;
    ANNOUNCE_FIELD_PAYLOAD payloadType;
    int         netIx;
    uint16_t terminatorLen = strlen ((const char *)announceFieldTerminator);

#if defined (TCPIP_STACK_USE_IPV6)
    IPV6_INTERFACE_CONFIG*  pIpv6Config;
    IPV6_ADDR_STRUCT * addressPointer;
    IPV6_HEAP_NDP_DR_ENTRY *defaultRouter;
    IPV6_ADDR *pGatewayAddr;
#endif

    // create the socket
    announceSocket = TCPIP_UDP_ClientOpen(IP_ADDRESS_TYPE_IPV4, TCPIP_ANNOUNCE_PORT, 0);

    if (announceSocket == INVALID_UDP_SOCKET)
    {   // keep the request pending, we'll try next time
        return;
    }

    for(netIx = 0; netIx < announceIfs; netIx++)
    {
        uint16_t noOfNet = TCPIP_STACK_NumberOfNetworksGet();
//        DRV_USART0_WriteByte((uint8_t)announceIfs);
//        DRV_USART0_WriteByte((uint8_t)noOfNet);
        // reply to the request on the interface it arrived on
        if((announceRequestMask & (1 << netIx)) != 0)
        {
            pNetIf = (TCPIP_NET_IF*)TCPIP_STACK_IndexToNet(netIx);

            if(TCPIP_STACK_NetworkIsLinked(pNetIf))
            {   // reply only if this interface is up and running

                TCPIP_UDP_SocketNetSet (announceSocket, pNetIf);
                TCPIP_UDP_BcastIPV4AddressSet(announceSocket, UDP_BCAST_NETWORK_DIRECTED, pNetIf);

#if defined (TCPIP_STACK_USE_IPV6)
                pIpv6Config = TCPIP_IPV6_InterfaceConfigGet(pNetIf);
#endif

                interfaceName = TCPIP_STACK_MACIdToString(pNetIf->macId);

                truncated = false;

                dataLen = ((terminatorLen + 1) * 4) + sizeof (IPV4_ADDR) + sizeof (TCPIP_MAC_ADDR);

                dataLen += strlen(interfaceName); 
                dataLen += strlen((char *)pNetIf->NetBIOSName);

                minimumDataLen = dataLen + 1 + terminatorLen;


#if defined (TCPIP_STACK_USE_IPV6)
                addressPointer = (IPV6_ADDR_STRUCT *)pIpv6Config->listIpv6UnicastAddresses.head;

                while(addressPointer != NULL)
                {
                    dataLen += sizeof (IPV6_ADDR) + 1 + terminatorLen;
                    addressPointer = addressPointer->next;
                }

                addressPointer = (IPV6_ADDR_STRUCT *)pIpv6Config->listIpv6MulticastAddresses.head;

                while(addressPointer != NULL)
                {
                    dataLen += sizeof (IPV6_ADDR) + 1 + terminatorLen;
                    addressPointer = addressPointer->next;
                }

                defaultRouter = pIpv6Config->currentDefaultRouter;
                while(defaultRouter != NULL)
                {
                    dataLen += sizeof (IPV6_ADDR) + 1 + terminatorLen;
                    defaultRouter = defaultRouter->next;
                }
                // For IPV6 gateway address
                dataLen += sizeof (IPV6_ADDR) + 1 + terminatorLen;
#endif

                if (dataLen > TCPIP_ANNOUNCE_MAX_PAYLOAD)
                {
                    dataLen = TCPIP_ANNOUNCE_MAX_PAYLOAD;
                }

                if ((txLen = TCPIP_UDP_TxPutIsReady(announceSocket, dataLen)) < dataLen)
                {
                    truncated = true;
                    if ((txLen = TCPIP_UDP_TxPutIsReady(announceSocket, minimumDataLen)) < minimumDataLen)
                    {
                        TCPIP_UDP_Close (announceSocket);
                        return;
                    }
                }

                // Put Mac Address
                payloadType = ANNOUNCE_FIELD_MAC_ADDR;
                TCPIP_UDP_Put (announceSocket, payloadType);
                TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)&pNetIf->netMACAddr, sizeof (TCPIP_MAC_ADDR));
                TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);

                if (truncated)
                {
                    payloadType = ANNOUNCE_FIELD_TRUNCATED;
                    TCPIP_UDP_Put (announceSocket, payloadType);
                    TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                }

                // Put Mac Type
                payloadType = ANNOUNCE_FIELD_MAC_TYPE;
                TCPIP_UDP_Put (announceSocket, payloadType);
                TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)interfaceName, strlen (interfaceName));
                TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);

                // Put Host Name
                payloadType = ANNOUNCE_FIELD_HOST_NAME;
                TCPIP_UDP_Put (announceSocket, payloadType);
                TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)&pNetIf->NetBIOSName, strlen((char*)pNetIf->NetBIOSName));
                TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);

                // Put IPv4 Address
                payloadType = ANNOUNCE_FIELD_IPV4_ADDRESS;
                TCPIP_UDP_Put (announceSocket, payloadType);
                TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)&pNetIf->netIPAddr, sizeof (IPV4_ADDR));
                TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                
#if defined DAVIS_ANNOUNCE_PACK                
                payloadType = ANNOUNCE_FIELD_DEVICE_ID;
                TCPIP_UDP_Put (announceSocket, payloadType);
                TCPIP_UDP_ArrayPut(announceSocket,DEVICE_ID,strlen(DEVICE_ID));
                TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                
                payloadType = ANNOUNCE_FIELD_CONNECTION_STATUS;
                TCPIP_UDP_Put (announceSocket, payloadType);
                TCPIP_UDP_ArrayPut(announceSocket,&guiConnectionStatus,sizeof(uint8_t));
                TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
#endif   
                
#if defined (TCPIP_STACK_USE_IPV6)

                // Put IPv6 unicast addresses
                minimumDataLen = sizeof (IPV6_ADDR) + 1 + terminatorLen;

                addressPointer = (IPV6_ADDR_STRUCT *)pIpv6Config->listIpv6UnicastAddresses.head;

                payloadType = ANNOUNCE_FIELD_IPV6_UNICAST;

                while(addressPointer != NULL && (TCPIP_UDP_TxPutIsReady(announceSocket, minimumDataLen) >= minimumDataLen))
                {
                    TCPIP_UDP_Put (announceSocket, payloadType);
                    TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)&addressPointer->address, sizeof (IPV6_ADDR));
                    TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                    addressPointer = addressPointer->next;
                }

                // Put IPv6 multicast listeners    
                addressPointer = (IPV6_ADDR_STRUCT *)pIpv6Config->listIpv6MulticastAddresses.head;

                payloadType = ANNOUNCE_FIELD_IPV6_MULTICAST;

                while(addressPointer != NULL && (TCPIP_UDP_TxPutIsReady(announceSocket, minimumDataLen) >= minimumDataLen))
                {
                    TCPIP_UDP_Put (announceSocket, payloadType);
                    TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)&addressPointer->address, sizeof (IPV6_ADDR));
                    TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                    addressPointer = addressPointer->next;
                }
                
                defaultRouter = pIpv6Config->currentDefaultRouter;
                payloadType = ANNOUNCE_FIELD_IPV6_DEFAULT_ROUTER;
                while(defaultRouter != NULL && (TCPIP_UDP_TxPutIsReady(announceSocket, minimumDataLen) >= minimumDataLen))
                {
                    TCPIP_UDP_Put (announceSocket, payloadType);
                    TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)&defaultRouter->neighborInfo->remoteIPAddress, sizeof (IPV6_ADDR));
                    TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                    defaultRouter = defaultRouter->next;
                }

                pGatewayAddr = (IPV6_ADDR*)TCPIP_STACK_NetDefaultIPv6GatewayGet(pNetIf);
                if(pGatewayAddr)
                {
                    payloadType = ANNOUNCE_FIELD_IPV6_DEFAULT_GATEWAY;
                    TCPIP_UDP_Put (announceSocket, payloadType);
                    TCPIP_UDP_ArrayPut(announceSocket, (const uint8_t *)pGatewayAddr, sizeof (IPV6_ADDR));
                    TCPIP_UDP_ArrayPut (announceSocket, announceFieldTerminator, terminatorLen);
                }

#endif

                TCPIP_UDP_Flush (announceSocket);
            }

            announceRequestMask &= ~(1 << netIx);   // clear requests on this interface
        }
    }


    TCPIP_UDP_Close (announceSocket);
}

bool TCPIP_ANNOUNCE_SendTaskPending (void)
{
    return announceRequestMask != 0;
}

void TCPIP_ANNOUNCE_Task(void)
{
    uint8_t         discQuery[20];
    UDP_SOCKET      s;
    UDP_SOCKET_INFO sktInfo;
    
    s = announceDcpt.skt;

	while(true)
	{   // consume all queued packets
        if(!TCPIP_UDP_GetIsReady(s))
        {
            return;
        }
			
        // See if this is a discovery query or reply
        TCPIP_UDP_ArrayGet(s, discQuery,20);
        if(discQuery[0] == 'D')
        {   // We received a discovery request, reply
//            tcpServerIP = &discQuery[2];
            TCPIP_UDP_SocketInfoGet(s, &sktInfo);
            // fake a legitimate DHCP event on that interface	
            ANNOUNCE_Notify (sktInfo.hNet, DHCP_EVENT_BOUND, NULL);
        }
#if defined DAVIS_ANNOUNCE_PACK 
        if(discQuery[0] == 'S')
        {
            uint8_t devId[2] = DEVICE_ID;
            uint16_t index = 0;
            if (discQuery[1] == devId[0] && discQuery[2] == devId[1])
            {
                if (guiConnectionStatus == 0)
                {
//                    memcpy(tcpServerIP,)
                   // while (discQuery[index + 3] != NULL && index <20)
 				while ((discQuery[index + 3] != '\r') && (index < 15)&& (discQuery[index + 3] != NULL))
                    {
                        tcpServerIP[index] = discQuery[index + 3];
                        index ++;
                    }
                    guiConnectionStatus = 1;
                }
                TCPIP_UDP_SocketInfoGet(s, &sktInfo);
                ANNOUNCE_Notify (sktInfo.hNet, DHCP_EVENT_BOUND, NULL);
            }
        }
#endif
        TCPIP_UDP_Discard(s);
	}	

}
#if defined DAVIS_ANNOUNCE_PACK  
uint8_t getConnectionStatus()
{
    return guiConnectionStatus;
}

uint8_t * getTcpServerIP()
{
    return &tcpServerIP[0];
}
#endif
// local functions

static void ANNOUNCE_Notify(TCPIP_NET_HANDLE hNet, uint8_t evType, const void * param)
{
    if(announceMemH)
    {
        if(evType == DHCP_EVENT_BOUND || evType == DHCP_EVENT_CONN_LOST || evType == DHCP_EVENT_SERVICE_DISABLED)
        {
            TCPIP_NET_IF* pNetIf = _TCPIPStackHandleToNet(hNet);
            announceRequestMask |= (1 << pNetIf->netIfIx);
        }
    }
}

static void _TCPIP_AnnounceCleanup(void)
{
#if defined   ( TCPIP_STACK_USE_DHCP_CLIENT)
    if (announceDHCPHandler != NULL)
    {
        TCPIP_DHCP_HandlerDeRegister(announceDHCPHandler);
        announceDHCPHandler = NULL;
    }
#endif
#if defined (TCPIP_STACK_USE_IPV6)
    if (announceIPV6Handler != NULL)
    {
        TCPIP_IPV6_HandlerDeregister(announceIPV6Handler);
        announceIPV6Handler = NULL;
    }
#endif
    if(announceAsyncSendHandle != 0)
    {
        _TCPIPStackAsyncHandlerDeRegister(announceAsyncSendHandle);
        announceAsyncSendHandle = 0;
    }

    if(announceAsyncHandle != 0)
    {
        _TCPIPStackAsyncHandlerDeRegister(announceAsyncHandle);
        announceAsyncHandle = 0;
    }

    if(announceDcpt.skt != INVALID_UDP_SOCKET)
    {
        TCPIP_UDP_Close(announceDcpt.skt);
	        announceDcpt.skt = INVALID_UDP_SOCKET;
    }

    announceRequestMask = 0;
    announceIfs = 0;

}

#endif //#if defined(TCPIP_STACK_USE_ANNOUNCE)
