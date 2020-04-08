#include "stdio.h"
#include "std_types.h"
#include "LCD.h"

/*Demo cmd of the LCD*/
#define LCD_CMD     (0XFF)

/*
 * Testing LCD module
 */

/*Variable used in error detection*/
EnmLCDError_t ret_err = 0;

int main(void)
{
    printf("Testing LCD module:\n");
    printf("\n");
    printf("Testing LCD_init function>>>>\n");
   
    /*
     * Test case 1:
     *  Initializing LCD module.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */
    ret_err = LCD_init();
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 1 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 1 : FAILED!\n");
    }

    /*
     * Test case 2:
     *  Sending command to the LCD.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */    
    ret_err = LCD_sendCommand(LCD_CMD);
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 2 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 2 : FAILED!\n");
    }

    /*
     * Test case 3:
     *  Displaying certain character over the LCD.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */    
    ret_err = LCD_displayChar('A');
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 3 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 3 : FAILED!\n");
    }

    /*
     * Test case 4:
     *  Displaying series of chracters (String) over the LCD.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */    
    ret_err = LCD_displayString("This is LCD Test");
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 4 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 4 : FAILED!\n");
    }

    /*
     * Test case 5:
     *  Passing NULL address (Empty string) for the LCD.
     *  SUCCESS: Returns NULL_PTR_ERROR
     *  FAILED : Other  
     */    
    ret_err = LCD_displayString(NULL);
    if(ret_err == NULL_PTR_ERROR)
    {
        printf("Test case 5 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 5 : FAILED!\n");
    }

    /*
     * Test case 6:
     *  Passing certain row and column so that LCD can begin writing data from them.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */    
    ret_err = LCD_gotoRowColumn(ROW_0 , COL_0);
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 6 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 6 : FAILED!\n");
    }

    /*
     * Test case 7:
     *  Passing string to the LCD with specified Row and Column to begin writing the string from.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */    
    ret_err = LCD_displayStringRowColumn("This is LCD Testing", ROW_0 , COL_0);
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 7 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 7 : FAILED!\n");
    }

    /*
     * Test case 8:
     *  Sending empty string(NULL)to LCD with specified row and column.
     *  SUCCESS: Returns NULL_PTR_ERROR
     *  FAILED : Other  
     */    
    ret_err = LCD_displayStringRowColumn(NULL, ROW_0 , COL_0);
    if(ret_err == NULL_PTR_ERROR)
    {
        printf("Test case 8 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 8 : FAILED!\n");
    }

    /*
     * Test case 9:
     *  Clearing the LCD.
     *  SUCCESS: Returns OPERATION_SUCCESS
     *  FAILED : Other  
     */    
    ret_err = LCD_clear();
    if(ret_err == OPERATION_SUCCESS)
    {
        printf("Test case 9 : SUCCESS!\n");
    }
    else
    {
        printf("Test case 9 : FAILED!\n");
    }


    return 0;
}