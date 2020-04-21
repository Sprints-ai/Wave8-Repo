#include "stdio.h"
#include "std_types.h"
#include "SOS.h"

/*
 * Testing SOS module
 */

/*Task paramaters*/
#define TASK_PRIORITY       (0)
#define TASK_CALLING_TYPE   (PERIODIC_CALLING)
#define TASK_PERIODICITY    (10)

/*Tasks code*/
void task1_func(void)
{
    return;
}

void task2_func(void)
{
    return;
}

/*Variable in returned error testing*/ 
EnmSOSError_t ret_err = 0;

/*Tasks definition*/
Task_ConfigType task1 = {TASK_PRIORITY,task1_func,TASK_CALLING_TYPE,TASK_PERIODICITY};
Task_ConfigType task2 = {TASK_PRIORITY,task2_func,TASK_CALLING_TYPE,TASK_PERIODICITY};

int main(void)
{
    printf("Testing SOS module:\n");
    printf("\n");
    printf("Testing SOS_Init function>>>>\n");
   
    /*
     * Test case 1:
     *  Initializing SOS module
     *  SUCCESS: Returns OperationSuccess
     *  FAILED : Other  
     */
    ret_err = SOS_Init();
    if(ret_err == OperationSuccess)
    {
        printf("Test case 1 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 1 : FAILED!\n");
    }

    /*
     * Test case 2:
     *  Multiple initialization of SOS module
     *  SUCCESS: Returns MultipleInit_Error
     *  FAILED : Other  
     */    
    ret_err = SOS_Init();
    if(ret_err == MultipleInit_Error)
    {
        printf("Test case 2 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 2 : FAILED!\n");
    }

    /*
     * Test case 3:
     *  De-Initialization of SOS module
     *  SUCCESS: Returns OperationSuccess
     *  FAILED : Other  
     */    
    ret_err = SOS_DeInit();
    if(ret_err == OperationSuccess)
    {
        printf("Test case 3 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 3 : FAILED!\n");
    }

    /*
     * Test case 4:
     *  Adding a task to SOS tasks buffer
     *  SUCCESS: Returns OperationSuccess
     *  FAILED : Other  
     */    
    ret_err = SOS_addTask(&task1);
    if(ret_err == OperationSuccess)
    {
        printf("Test case 4 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 4 : FAILED!\n");
    }

    /*
     * Test case 5:
     *  Exceeding SOS tasks buffer
     *  SUCCESS: Returns FullBuffer_Error
     *  FAILED : Other  
     */    
    ret_err = SOS_addTask(&task2);
    if(ret_err == FullBuffer_Error)
    {
        printf("Test case 5 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 5 : FAILED!\n");
    }

    /*
     * Test case 6:
     *  Passing NULL pointer to addTask function
     *  SUCCESS: Returns NullPtr_Error
     *  FAILED : Other  
     */    
    ret_err = SOS_addTask(NULL);
    if(ret_err == NullPtr_Error)
    {
        printf("Test case 6 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 6 : FAILED!\n");
    }

    /*
     * Test case 7:
     *  Passing NULL pointer to deleteTask function
     *  SUCCESS: Returns NullPtr_Error
     *  FAILED : Other  
     */    
    ret_err = SOS_deleteTask(NULL);
    if(ret_err == NullPtr_Error)
    {
        printf("Test case 7 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 7 : FAILED!\n");
    }

    /*
     * Test case 8:
     *  Deleting task from SOS tasks buffer
     *  SUCCESS: Returns OperationSuccess
     *  FAILED : Other  
     */    
    ret_err = SOS_deleteTask(&task1);
    if(ret_err == OperationSuccess)
    {
        printf("Test case 8 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 8 : FAILED!\n");
    }

    /*
     * Test case 9:
     *  Deleting task not found in SOS tasks buffer
     *  SUCCESS: Returns OperationSuccess
     *  FAILED : Other  
     */    
    ret_err = SOS_deleteTask(&task2);
    if(ret_err == Deleting_Without_Adding_Error)
    {
        printf("Test case 9 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 9 : FAILED!\n");
    }

    /*
     * Test case 10:
     *  Starting SOS scheduler
     *  SUCCESS: Returns OperationSuccess
     *  FAILED : Other  
     */    
    ret_err = SOS_run();
    if(ret_err == OperationSuccess)
    {
        printf("Test case 10: SUCCESS!\n");
    }
    else
    {
        printf("Test case 10: FAILED!\n");
    }

    return 0;
}