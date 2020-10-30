/******************************************************************************/
#ifndef CO_SCH_H
#include "CO_SCH.h"
#endif
/******************************************************************************/
#define ENDED 0
/******************************************************************************/
TASK_t CO_SCH_Task[CO_SCH_MAX_TASKS];
/******************************************************************************/
void CO_SCH_Delete_Task(const u8_t ID){
     if(ID < CO_SCH_MAX_TASKS && CO_SCH_Task[ID].pTask != NULL_PTR){
        CO_SCH_Task[ID].pTask = NULL_PTR;
        CO_SCH_Task[ID].Run = 0;
        CO_SCH_Task[ID].Delay = 0;
        CO_SCH_Task[ID].Period = 0;
     }
     else{
        /* Error: Undefined Task */
     }
}
/******************************************************************************/
void CO_SCH_Init(void){
     u8_t Id;
     for(Id = 0; Id < CO_SCH_MAX_TASKS; Id++){
         CO_SCH_Delete_Task(Id);
     }
     /* To Do: Init Timer Here */
}
/******************************************************************************/
void CO_SCH_Add_Task(void (*const PTASK)(void),
                     const u8_t DELAY,
                     const u8_t PERIOD){

     static u8_t Id = 0;
     if(Id < CO_SCH_MAX_TASKS){
        CO_SCH_Task[Id].pTask = PTASK;
        CO_SCH_Task[Id].Delay = 1 + DELAY;
        CO_SCH_Task[Id].Period = PERIOD;
        CO_SCH_Task[Id].Run = 0;
        CO_SCH_Task[Id].Id = Id;
        Id++;
     }
     else{
        /* Error: Scheduler is Fulled */
     }
}
/******************************************************************************/
void CO_SCH_Dispatch_Tasks(void){
     u8_t Id;
     for(Id = 0; Id < CO_SCH_MAX_TASKS; Id++){
        if(CO_SCH_Task[Id].Run > 0){
           CO_SCH_Task[Id].pTask();
           CO_SCH_Task[Id].Run--;
           if(0 == CO_SCH_Task[Id].Period){
              CO_SCH_Delete_Task(Id);
           }
        }
        else{
           /* Task is not Ready */
        }
     }
}
/******************************************************************************/
void CO_SCH_Update_Tasks(void){
     u8_t Id;
     for(Id = 0; Id < CO_SCH_MAX_TASKS; Id++){
         if(CO_SCH_Task[Id].pTask != NULL_PTR){
            CO_SCH_Task[Id].Delay--;
            if(ENDED == CO_SCH_Task[Id].Delay){
               CO_SCH_Task[Id].Run++;
               CO_SCH_Task[Id].Delay = CO_SCH_Task[Id].Period;
            }
            else{
               /* Task is not Ready */
            }
         }
         else{
            /* Error: Undefined Task */
         }
     }
}
/******************************************************************************/
void CO_SCH_Start(void){
     /* To Do: Enable Interrupt Here */
}
/******************************************************************************/
void CO_SCH_Sleep(void){
     /* To Do: */
}