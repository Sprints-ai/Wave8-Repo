/*
 * Story3.c
 *
 * Created: 4/12/2020 4:40:48 PM
 *  Author: Khaled
 */ 
#include "Story3.h"


#define WATCH                       4
#define CONTROL                     5
#define LED_STOP                    6
#define LED_100                     7
#define LED_400                     8

#define DELAY_400MS_FACTOR          4
#define COUNT_INITIAL_VALUE         0
#define BLINKING_TASK_FREQ          100
#define SENSE_2SEC                  2000
#define SENSE_4SEC                  4000
#define INIT_TASK_DEPTH_STACK       40
#define CONTROL_TASK_DEPTH_STACK    40
#define INIT_TASK_PRIORTY            2
#define CONTROL_TASK_PRIORTY         1


/* local function prototypes */
static void Story3_ControlTask (void *pvParameters);
static void Story3_InitTask (void *pvParameters);

/* initiate init task handle*/
TaskHandle_t Story3_InitTaskHandle;

void Story3 (void)
{
    
    /*
     * Description: Create task to initialize the system (led and push bottom)
     * Input: Pointer to task 
     *        Task name
     *        Task stack depth
     *        No i/p parameter 
     *
     * Input/Output: Task handle address to use it to suspend the task
     */
    xTaskCreate (Story3_InitTask, "Init", INIT_TASK_DEPTH_STACK, NULL, INIT_TASK_PRIORTY,&Story3_InitTaskHandle);

    /*
     * Description: Create task to initialize the system (led)
     * Input: Pointer to task 
     *        Task name
     *        Task stack depth
     *        No i/p parameter 
     * Input/Output: No need to task handle
     */
    xTaskCreate (Story3_ControlTask, "control", CONTROL_TASK_DEPTH_STACK, NULL, CONTROL_TASK_PRIORTY,NULL);
    

    /*Start Scheduler*/
    vTaskStartScheduler();
}

/* system initialization task which initialize the led module and push bottom module */
void Story3_InitTask (void *pvParameters)
{
    
    
    while (1)
    {
        /* led module initialize */
        Led_Init(LED_0);

        /* push bottom module initialize */
        pushButtonInit(BTN_1);

        /* suspend the task after finishing the initialization */
        vTaskSuspend( Story3_InitTaskHandle );
        
    }
    
}

void Story3_ControlTask (void *pvParameters)
{
    /* reference tick for periodicity function */
    TickType_t xLastWakeTime;

    /* periodicity value */
    const TickType_t Story3_BlinkingFrequency = BLINKING_TASK_FREQ;

    /* variables used calculate the pressed time  */
    TickType_t au16_TimeStart   = NOT_INITIALIZED,
               au16_TimerStop   = NOT_INITIALIZED,
               au16_PressedTime = NOT_INITIALIZED;  
    
        
    static uint8_t au8_ButtonStatus = NOT_INITIALIZED,
                   au8_Control      = WATCH, 
                   au8_Decision     = LED_STOP, 
                   au8_Count        = NOT_INITIALIZED;
    
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    while(1)
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, Story3_BlinkingFrequency );
        
        switch(au8_Control)
        {
            case WATCH:
            /* get push button status (pressed or released) */
            pushButtonGetStatus (BTN_1, &au8_ButtonStatus);
            
            if (Pressed == au8_ButtonStatus)
            {
                /* if the PB pressed get the tick counter value */
                au16_TimeStart = xTaskGetTickCount();    

                /* switch the function statue to control status*/
                au8_Control = CONTROL;
            }
            break;

            case CONTROL:
            /* get push button status (pressed or released) */
            pushButtonGetStatus (BTN_1, &au8_ButtonStatus);
            

            if (Released == au8_ButtonStatus)
            {
                /* if the PB released get the tick counter value */
                au16_TimerStop = xTaskGetTickCount();

                /* calculate the pressed time by using preses tick count and release tick count */
                au16_PressedTime = au16_TimerStop - au16_TimeStart;
                
                if (au16_PressedTime < SENSE_2SEC)
                {
                    /* if the PB pressed less than 2sec switch led decision to stop */
                    au8_Decision = LED_STOP;              
                }
                else if (au16_PressedTime > SENSE_4SEC)
                {
                    /* if the PB pressed more than 4sec switch led decision to LED toggle each 100ms */
                    au8_Decision = LED_100;               
                }
                else
                {
                    /* if the PB pressed more than 2sec and less than 4sec switch led decision to led toggle each 400 ms*/
                    au8_Decision = LED_400;               
                }
                /* switch the function statue to watch status */
                au8_Control = WATCH;
            }
            break;
        }

        switch (au8_Decision)
        {
            case LED_STOP:
            /* turn the led off*/
            Led_Off(LED_0); 
            break;
            
            case LED_100:
            /* toggle the led each time (100 ms) */
            Led_Toggle(LED_0); 
            break;

            case LED_400:
            /* toggle the led each 4 times (400ms) */
            au8_Count ++;
            if (au8_Count == DELAY_400MS_FACTOR)
            {
                Led_Toggle(LED_0); 
                au8_Count = COUNT_INITIAL_VALUE;
            }
            break;
            
        }
        
    }
}

