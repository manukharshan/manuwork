/* 
 * File:   actionHandler.h
 * Author: manu k harshan
 *
 * Created on 4 April, 2017, 12:25 PM
 */

#ifndef ACTIONHANDLER_H
#define	ACTIONHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "deviceDetails.h"
#include "defaultvalue.h"    
    
typedef enum
{
    ACTIONVALVEHOME,
    ACTIONVALVEOPEN,
    ACTIONVALVECLOSE,
    ACTIONVALVEEMERGENCYSTOP,
    ACTIONROTPOS,
    ACTIONROTNEG,
    ACTIONROTPOSHARDSTOP,
    ACTIONROTNEGHARDSTOP,        
    ACTIONCALIBRATE,
    ACTIONMAXEVENT,        
}eActionEvent;    
    
typedef enum
{
    ACTION_SM_IDLE,        
    ACTION_SM_HOME,
    ACTION_SM_ROTATE,        
    ACTION_SM_VALVEOPEN,
    ACTION_SM_VALVECLOSE,
    ACTION_SM_STOPMOTOR,
    ACTION_SM_HARDSTOPHOME,        
    ACTION_SM_MAX_STATE
}actionSmStates;

typedef struct
{
    eActionEvent geActionEvent;
}actionsysEvents;

typedef struct
{
    actionSmStates eactionSmStates;
    actionSmStates(*actionSmFuncitons)(actionsysEvents*,bool*);
}actionsmTable;

typedef enum
{
    MOTORPOSVELJOG = 0,
    MOTORNEGVELJOG,   
    MOTORPOSJOG,        
    MOTORSTOP,
    MOTORDISABLE,
    MOTORENABLE,
    MOTORHARDSTOP,
    MOTORMAXEVENT,
}eMotorEvent;

typedef enum
{
    MOTOR_HARD_NEGSTOP,
    MOTOR_HARD_NEGSTOP_STOP,
    MOTOR_HOMING_COMPLETE,        
}eMotortoHomeState;

typedef struct
{
    unsigned int tenPervalue;
    unsigned int twentyPervalue;
    unsigned int thirtyPervalue;
    unsigned int fourtyPervalue;
    unsigned int fiftyPervalue;
    unsigned int sixtyPervalue;
    unsigned int seventyPervalue;
    unsigned int eightyPervalue;
    unsigned int nintyPervalue;
    unsigned int hundredPervalue;
}epercentvalveclose;

typedef struct
{
    unsigned short int uiInPtr;
    unsigned short int uiOutPtr;
    unsigned short int uiProcessesCounter;
    
}SysCirBuffer2;

actionSmStates actionSmhandler(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionstateidle(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionstatehome(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionstaterotate(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionstatevalveopen(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionstatevalveclose(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionstopmotor(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);
actionSmStates actionhardstophome(actionsysEvents* psactionsysEvents,bool* psactionEventhandled);

actionSmStates motorControlAction(actionsysEvents* psactionsysEvents);

actionSmStates tasksetMotorToHome(void);

/*Function for Action Events*/
void reportActionEvent (eActionEvent eInputActionEvent);
bool getActionEvent (eActionEvent *ActionEvent);
void disposeActionEvent (void);

/*Function for Motor Events*/
void reportMotorEvent (eMotorEvent eInputMotorEvent);
bool getMotorEvent (eMotorEvent *MotorEvent);
void disposeMotorEvent (void);

epercentvalveclose gepercentvalveclose;



#ifdef	__cplusplus
}
#endif

#endif	/* ACTIONHANDLER_H */

