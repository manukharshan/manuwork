#include <xc.h>
#include "copleySmHandler.h"
#include "copleytransmithandler.h"
#include "events.h"
#include "app.h"
#include "string.h"
#include "stdlib.h"
#include "tcpiphandler.h"
#include "tcpiphandler.h"
#include "timerfunctions.h"
#include "monitorinoutpin.h"

//extern char messagePacket[64];
static uint32_t guiTimeoutCounter_1 = 0U;
bool milliSecondflag = false;

void interruptsetup(void) 
{
// Unlock MCU assignment to use PPS
//  SystemUnlock();
  CFGCONbits.IOLOCK=0;            // unlock configuration
  CFGCONbits.PMDLOCK=0;
  
  // Assign external interrupts
  // Bit assignments are listed on page 146 of the datasheet
  INT1Rbits.INT1R = 0b0110; // Define RPC2 as INT1 (MX220 pin D3)

  // Lock PPS facility again
  CFGCONbits.IOLOCK=1; // relock configuration
  CFGCONbits.PMDLOCK=1;
//  SystemLock();
     
  // Interrupt setup
  IEC0bits.INT1IE=0; // disable this interrupt
  INTCONbits.INT1EP=0; // edge polarity for this interrupt ( rising edge )
//  IPC1bits.INT1IP=1; // interrupt priority
//  IPC1bits.INT1IS=1; // interrupt sub priority
  IEC0bits.INT1IE=1; // enable this interrupt
}

void timerISRcallback (void)
{
    timerOperation();
    //continuousMonitorPowerStatus();
    monitorinput();
        
     guiTimeoutCounter_1 ++;
//     millisecondcheck = true;
     if (guiTimeoutCounter_1 == 1000)
     {
        guiTimeoutCounter_1 = 0U;
     }
    milliSecondflag = true; 
}


void timerOperation(void)
 { 
      uint8_t count =0;
         
     for(count =0;count<MAX_TIMER;count++)
     {
         if(timer_array[count].timer_on == 1)
         {
          timer_array[count].msec_timer++;
          if(timer_array[count].msec_timer >= timer_array[count].timer_time)
          {
             timer_array[count].timeout_flag = 1;
             timer_array[count].timer_on= 0;
             timer_array[count].msec_timer = 0;
          }
         }
         else
         {
            timer_array[count].msec_timer = 0; 
         }
     }
         
 }
void startTimer(SOFT_TIMER *timer_data,uint16_t timeMs)
{
    if(timer_data->timer_on == 0)
    {
     timer_data->timeout_flag=0;
     timer_data->timer_time = timeMs;
     timer_data->timer_on=1;
     timer_data->msec_timer = 0;
    }
}

void stopTimer(SOFT_TIMER *timer_data)
{
    timer_data->timeout_flag=0;
    timer_data->timer_on=0;
    timer_data->msec_timer = 0;
}
uint8_t getTimeOutOccur(SOFT_TIMER *timer_data)
{
    return timer_data->timeout_flag;
}