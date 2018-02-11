#include "monitorinoutpin.h"
#include "deviceDetails.h"

SysCirBuffer1 GSKeypadEvent;
eKeypadEvent gEKeypadEvent[KEY_ID_EVENT_MAX];
SKeyPressedEvent GSKeyPressedEvent[MAX_NO_OF_KEY];

void monitorinput(void)
{
  if ((JOGOPENVALVE_BTN == PRESS  && JOGCLOSEVALVE_BTN == RELEASE) ||(JOGOPENVALVE_BTN == RELEASE))
  {        
    switch(GSKeyPressedEvent[JOG_VALVE_OPEN].gEKeypadPressEvent)
    {
        case KEY_PRESSED:
           {
               if ((JOGOPENVALVE_BTN == RELEASE))
               {
                  GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter++;
                  
                  if(GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter >= DEBOUNCE_DELAY)
                  {
                     reportKeypadEvent(JOGOPENBUTTON_RELEASED);
                     GSKeyPressedEvent[JOG_VALVE_OPEN].uiContinuousPressDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_OPEN].gEKeypadPressEvent = KEY_RELEASED;
                  }
                }
               else
               {
                  GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter = 0U;
                  GSKeyPressedEvent[JOG_VALVE_OPEN].uiContinuousPressDelayCounter++;
                  if(GSKeyPressedEvent[JOG_VALVE_OPEN].uiContinuousPressDelayCounter >= CONTINUOUS_PRESS_DELAY)
                  {
                      GSKeyPressedEvent[JOG_VALVE_OPEN].uiContinuousPressDelayCounter = 0U;
                      //reportKeypadEvent(JOGOPENBUTTON_PRESSED);
                  }
               }
              break;
           } 
        case KEY_RELEASED:
           {
             if ((JOGOPENVALVE_BTN == PRESS))
               {
                  GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter++;
                  if(GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter >= DEBOUNCE_DELAY)
                  {
                     reportKeypadEvent(JOGOPENBUTTON_PRESSED);
                     GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_OPEN].uiContinuousPressDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_OPEN].gEKeypadPressEvent = KEY_PRESSED;
                  }
                }
             else
             {
                 GSKeyPressedEvent[JOG_VALVE_OPEN].uiDebounceCDelayCounter = 0U;
             }
            break;  
          }  
     }
  }
  if((JOGCLOSEVALVE_BTN == PRESS  && JOGOPENVALVE_BTN == RELEASE) ||(JOGCLOSEVALVE_BTN == RELEASE))
  {
    switch(GSKeyPressedEvent[JOG_VALVE_CLOSE].gEKeypadPressEvent)
    {
        case KEY_PRESSED:
           {
               if ((JOGCLOSEVALVE_BTN == RELEASE))
               {
                  GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter++;
                  
                  if(GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter >= DEBOUNCE_DELAY)
                  {
                     reportKeypadEvent(JOGCLOSEBUTTON_RELEASED);
                     GSKeyPressedEvent[JOG_VALVE_CLOSE].uiContinuousPressDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_CLOSE].gEKeypadPressEvent = KEY_RELEASED;
                  }
                }
               else
               {
                  GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter = 0U;
                  GSKeyPressedEvent[JOG_VALVE_CLOSE].uiContinuousPressDelayCounter++;
                  if(GSKeyPressedEvent[JOG_VALVE_CLOSE].uiContinuousPressDelayCounter >= CONTINUOUS_PRESS_DELAY)
                  {
                      GSKeyPressedEvent[JOG_VALVE_CLOSE].uiContinuousPressDelayCounter = 0U;
                      //reportKeypadEvent(JOGCLOSEBUTTON_PRESSED);
                  }
               }
              break;
           } 
        case KEY_RELEASED:
           {
             if ((JOGCLOSEVALVE_BTN == PRESS))
               {
                  GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter++;
                  if(GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter >= DEBOUNCE_DELAY)
                  {
                     reportKeypadEvent(JOGCLOSEBUTTON_PRESSED);
                     GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_CLOSE].uiContinuousPressDelayCounter = 0U;
                     GSKeyPressedEvent[JOG_VALVE_CLOSE].gEKeypadPressEvent = KEY_PRESSED;
                  }
                }
             else
             {
                 GSKeyPressedEvent[JOG_VALVE_CLOSE].uiDebounceCDelayCounter = 0U;
             }
            break;  
          }  
     }
  }
}

void reportKeypadEvent (eKeypadEvent eInputKeyPadEvent)
{
    
    gEKeypadEvent[GSKeypadEvent.uiInPtr] = eInputKeyPadEvent;
    GSKeypadEvent.uiInPtr++;
    GSKeypadEvent.uiProcessesCounter++;
    if (GSKeypadEvent.uiInPtr >= KEY_ID_EVENT_MAX )
    {
        GSKeypadEvent.uiInPtr = 0;
    }
    
}

bool getKeypadEvent (eKeypadEvent *KeyPadEvent)
{
    bool bRetVal = false;
    
    if (GSKeypadEvent.uiProcessesCounter > 0)
    {
        bRetVal = true;
        *KeyPadEvent = gEKeypadEvent[GSKeypadEvent.uiOutPtr];
    }
    return bRetVal;
}

void disposeKeypadEvent (void)
{
    GSKeypadEvent.uiOutPtr ++;
    if (GSKeypadEvent.uiOutPtr >= KEY_ID_EVENT_MAX )
    {
        GSKeypadEvent.uiOutPtr = 0;
    }
    GSKeypadEvent.uiProcessesCounter --;
}

void continuousMonitorKeypad(void)
{
    eKeypadEvent KeypadEvents;
    sDeviceCtrlState deviceCtrlState;
    deviceCtrlState = *getDeviceCtrlState();
    if(getKeypadEvent(&KeypadEvents))
    {
      if(LOCAL_MODE_SELECTED == deviceCtrlState.eValveCtrlState.eValveCtrlcommMod)
      {
        switch(KeypadEvents)
        {
            case JOGOPENBUTTON_RELEASED:
            {
                reportActionEvent(ACTIONVALVEEMERGENCYSTOP);
                break;
            }
            case JOGOPENBUTTON_PRESSED:
            {
//                setJogMod();
//                setCountToRun(JOGPOS);
//                reportActionEvent(ACTIONROTPOS);
                reportActionEvent(ACTIONVALVECLOSE);
                break;
            }
            case JOGCLOSEBUTTON_RELEASED:
            {
                reportActionEvent(ACTIONVALVEEMERGENCYSTOP);
                break;
            }
            case JOGCLOSEBUTTON_PRESSED:
            {
//                setJogMod();
//                setCountToRun(JOGNEG);
//                reportActionEvent(ACTIONROTPOS);
                reportActionEvent(ACTIONVALVEOPEN);
                break;
            }
         }
        disposeKeypadEvent(); 
      }
       else
        {
            disposeKeypadEvent();
        }
    }
   
}