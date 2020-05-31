 /* Story1.c
 *
 * Created: 4/12/2020 9:25:45 AM
 *  Author: Khaled
 */
 
 #include "Story1.h"

/* value to achieve 1s periodicity for blinking task */
 #define ONE_SEC        1000


/* static Function Prototype*/
static void Story1_BlinkingTask (void *pvParameters);
static void Story1_InitTask (void *pvParameters);

/* initiate init task handle*/
static TaskHandle_t Story1_InitTaskHandle; 
 
/*main story 1 function*/
 void Story1 (void)
 {
     
     /*
      * Description: Create task to initialize the system (led)
      * Input: Pointer to task 
      *        Task name
      *        Task stack depth
      *        No i/p parameter 
      * Input/Output: Task handle address to use it to suspend the task
      */
     xTaskCreate (Story1_InitTask, "LED Init", 37, NULL, 2,&Story1_InitTaskHandle);

     
     /*
      * Description: Create task to achieve led blinking functionality
      * Input: Pointer to task 
      *        Task name
      *        Task stack depth
      *        No i/p parameter 
      * Input/Output: No need to task handle
      */
     xTaskCreate (Story1_BlinkingTask, "LED Blinking", 30, NULL, 1,NULL);
     

      /*Start Scheduler*/
      vTaskStartScheduler();
 }

 /* system initialization task which initialize the led module */
 void Story1_InitTask (void *pvParameters)
 {
    
  
    while (1)
    {
        /* initialize the led module */
        Led_Init(LED_0);

        /* suspend the task after finishing the initialization */
        vTaskSuspend( Story1_InitTaskHandle );
        
    }
    
 }
 
 /* blinking functionality task */
 void Story1_BlinkingTask (void *pvParameters)
 {
    /* reference tick for periodicity function */
    TickType_t xLastWakeTime;

    /* periodicity value */
    const TickType_t xFrequency = ONE_SEC;
    
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    
    while(1)
    {
        // Wait for the next cycle.
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
        
        /* toggle the led to achieve task functionality */
        Led_Toggle(LED_0);
    }
 }