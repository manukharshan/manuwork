#include "ledindication.h"

eledindicationState geledindicationState;
eStatusindicationState geStatusindicationState;
bool Ledstatus;
bool homeledstatus=false;

void toggRedLed(void)
{
    if(Ledstatus)
    {
        REDLED = LEDON;
        Ledstatus = false;
    }
    else
    {
       REDLED = LEDOFF;
       Ledstatus = true;
    }
}

void toggleHoming(void)
{
    if(homeledstatus)
    {
       ORANGELED = LEDON;
       GREENLED = LEDOFF;
       homeledstatus = false;
    }
    else
    {
       ORANGELED = LEDOFF;
       GREENLED = LEDOFF;
       homeledstatus = true;
    }
}


void ledPinitialize(void)
{
    LEDINDICATION1 = 0;
    LEDINDICATION2 = 0;
    LEDINDICATION3 = 0;
    LEDINDICATION4 = 0;
    LEDINDICATION5 = 0;
    LEDINDICATION6 = 0;
    LEDINDICATION7 = 0;
    LEDINDICATION8 = 0;
    LEDINDICATION9 = 0;
    LEDINDICATION10 = 0;
    GREENLED = LEDOFF;
    ORANGELED = LEDOFF;
    REDLED = LEDOFF;
    YELLOWLED = LEDOFF;
}

void ledindicationTask(void)
{
  switch(geledindicationState)
  {
    case VALVEOPEN:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 1;
        LEDINDICATION6 = 1;
        LEDINDICATION7 = 1;
        LEDINDICATION8 = 1;
        LEDINDICATION9 = 1;
        LEDINDICATION10 = 1;
        break;
    }
    case VALVETENPERCLOSE:
    {
                
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 1;
        LEDINDICATION6 = 1;
        LEDINDICATION7 = 1;
        LEDINDICATION8 = 1;
        LEDINDICATION9 = 1;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVETWENTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 1;
        LEDINDICATION6 = 1;
        LEDINDICATION7 = 1;
        LEDINDICATION8 = 1;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVETHIRTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 1;
        LEDINDICATION6 = 1;
        LEDINDICATION7 = 1;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVEFOURTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 1;
        LEDINDICATION6 = 1;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVEFIFTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 1;
        LEDINDICATION6 = 0;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVESIXTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 1;
        LEDINDICATION5 = 0;
        LEDINDICATION6 = 0;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVESEVENTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 1;
        LEDINDICATION4 = 0;
        LEDINDICATION5 = 0;
        LEDINDICATION6 = 0;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVEEIGHTYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 1;
        LEDINDICATION3 = 0;
        LEDINDICATION4 = 0;
        LEDINDICATION5 = 0;
        LEDINDICATION6 = 0;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVENINETYPERCLOSE:
    {
        LEDINDICATION1 = 1;
        LEDINDICATION2 = 0;
        LEDINDICATION3 = 0;
        LEDINDICATION4 = 0;
        LEDINDICATION5 = 0;
        LEDINDICATION6 = 0;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
    case VALVECLOSE:
    {
        LEDINDICATION1 = 0;
        LEDINDICATION2 = 0;
        LEDINDICATION3 = 0;
        LEDINDICATION4 = 0;
        LEDINDICATION5 = 0;
        LEDINDICATION6 = 0;
        LEDINDICATION7 = 0;
        LEDINDICATION8 = 0;
        LEDINDICATION9 = 0;
        LEDINDICATION10 = 0;
        break;
    }
  }                
}

void taskStatusLedIndication(void)
{
  static int blinkfCount = 0;    
  switch(geStatusindicationState)
  {
      case VALVE_IDLE:
      {
          ORANGELED = LEDOFF;
          REDLED = LEDOFF;
          YELLOWLED = LEDOFF;
          GREENLED = LEDON;
          geStatusindicationState = VALVE_DEFAULT;
          break;
      }
      case VALVE_FAULT_BLINK:
      {
          blinkfCount++;
          if(blinkfCount>=1000)
          {
              toggRedLed();
              blinkfCount=0;
          }
          geStatusindicationState = VALVE_FAULT_BLINK;
          break;
      }
      case VALVE_HOME_BLINK:
      {
          blinkfCount++;
          if(blinkfCount>=1000)
          {
              toggleHoming ();
              blinkfCount = 0;
          }
          geStatusindicationState = VALVE_HOME_BLINK;           
          break;
      }
      case VALVE_DEFAULT:
      {
          break;
      }
  }
    
}

eStatusindicationState getStatusledindicationState(void)
{
    return geStatusindicationState;
}

void setStatusledindicationState(eStatusindicationState ledindicationState)
{
    geStatusindicationState = ledindicationState;
}


eledindicationState getledindicationstate(void)
{
    return geledindicationState;
}

void setledinidicationstate(eledindicationState ledindicationState)
{
    geledindicationState = ledindicationState;
}