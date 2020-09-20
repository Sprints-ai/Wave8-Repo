#include "LCDTesting.h"
#include "LCD.h"

void LCD_InitTesting(void)
{
    /***********************************/
    /* Happy Scenario:
     * Only one initialization
     * Expected Output is E_OK
    */
    /***********************************/
    ERROR_STATUS ERR;
    ERR = LCD_Init();
    if(ERR == E_OK)
    {
        printf("Expected Output: 0\n");
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: 0\n");
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }


     /*
     * Multiple initialization
     * Expected Output is LCD_ERROR + E_MULTIPLE_INITIALIZION
    */
    /***********************************/

    ERR = LCD_Init();
    ERR = LCD_Init();
    if(ERR == LCD_ERROR + E_MULTIPLE_INITIALIZION)
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_MULTIPLE_INITIALIZION));
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_MULTIPLE_INITIALIZION));
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }
}

void LCD_ExecuteCommandTesting(void)
{
    ERROR_STATUS ERR;
    /*
     * Uninitialized Module
     * Expected Output is LCD_ERROR + E_MULTIPLE_INITIALIZION
    */
    /***********************************/

    ERR = LCD_ExecuteCommand(0x00);

    if(ERR == LCD_ERROR + E_UNINITIALIZED_MODULE)
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }

    /*
     * Initialized Module
     * Expected Output is E_OK
    */
    /***********************************/
    LCD_Init();
    ERR = LCD_ExecuteCommand(0x00);

    if(ERR == E_OK)
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }
     /*
     * Invalid Command
     * Expected Output is E_INVALID_PARAMETER
    */
    /***********************************/

    ERR = LCD_ExecuteCommand(0xFF);

    if(ERR == E_INVALID_PARAMETER)
    {
        printf("Expected Output: %d\n",E_INVALID_PARAMETER);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",E_INVALID_PARAMETER);
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");
    }
}

void LCD_WriteDataTesting(void)
{
    ERROR_STATUS ERR;
    /*
     * Uninitialized Module
     * Expected Output is LCD_ERROR + E_MULTIPLE_INITIALIZION
    */
    /***********************************/

    ERR = LCD_WriteData(0x00);

    if(ERR == LCD_ERROR + E_UNINITIALIZED_MODULE)
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }

    /*
     * Initialized Module
     * Expected Output is E_OK
    */
    /***********************************/
    LCD_Init();
    ERR = LCD_WriteData(0x00);

    if(ERR == E_OK)
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }
}

void LCD_GoToXTesting(void){
    ERROR_STATUS ERR;
    /*
     * Uninitialized Module
     * Expected Output is LCD_ERROR + E_MULTIPLE_INITIALIZION
    */
    /***********************************/

    ERR = LCD_GoToXY(0,0);

    if(ERR == LCD_ERROR + E_UNINITIALIZED_MODULE)
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }

    /*
     * Initialized Module
     * Expected Output is E_OK
    */
    /***********************************/
    LCD_Init();
   ERR = LCD_GoToXY(0,0);


    if(ERR == E_OK)
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }

     /*
     * Initialized Module
     * Expected Output is E_OK
    */
    /***********************************/

   ERR = LCD_GoToXY(5,5);


    if(ERR == LCD_ERROR + E_INVALID_PARAMETER)
    {
        printf("Expected Output: %d\n",LCD_ERROR + E_INVALID_PARAMETER);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",LCD_ERROR + E_INVALID_PARAMETER);
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }

}

void LCD_DisplayDataTesting(void){
    ERROR_STATUS ERR;
     /*
     * Uninitialized Module
     * Expected Output is LCD_ERROR + E_MULTIPLE_INITIALIZION
    */
    /***********************************/

    ERR = DisplayData("Hii");

    if(ERR == LCD_ERROR + E_UNINITIALIZED_MODULE)
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",(LCD_ERROR + E_UNINITIALIZED_MODULE));
        printf("Your Output: %d\n",ERR);
        printf("Test case: failed\n");

    }

    /*
     * Initialized Module
     * Expected Output is E_OK
    */
    /***********************************/
    LCD_Init();
    ERR = DisplayData("Hi");

    if(ERR == E_OK)
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",E_OK);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");
    }

    /*
     * NULL PTR
     * Expected Output is E_OK
    */
    /***********************************/
    LCD_Init();
    ERR = DisplayData(NULL);

    if(ERR == LCD_ERROR + E_NULL_PTR)
    {
        printf("Expected Output: %d\n",LCD_ERROR + E_NULL_PTR);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");

    }
    else
    {
        printf("Expected Output: %d\n",LCD_ERROR + E_NULL_PTR);
        printf("Your Output: %d\n",ERR);
        printf("Test case: Passed\n");
    }

}
