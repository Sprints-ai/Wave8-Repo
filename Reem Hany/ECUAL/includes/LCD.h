/*
 * LCD.h
 *
 * Created: 3/13/2020 5:49:20 PM
 *  Author: Reem
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../../Services/includes/std_types.h"
#include "../../Services/includes/common_macros.h"
#include "../../Services/includes/softwareDelay.h"
#include "../../MCAL/includes/DIO.h"

/******************************************************************************/
/*                           DEFINES                                          */
/******************************************************************************/
#define LCD_ERROR
#define LINE_1                             0
#define LINE_2                             1
#define LAST_LCD_COL                       15

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Initiates the LCD
 * 							
 */
extern ERROR_STATUS LCD_Init(void);

/**
 * Input: Command
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Send LCD Commands
 * 							
 */
extern ERROR_STATUS LCD_ExecuteCommand(uint8_t Command);

/**
 * Input: Data byte
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Send LCD data
 * 							
 */
extern ERROR_STATUS LCD_WriteData(uint8_t DataByte);

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: 			
 * Description: This function acts as the LCD Manager that synchronizes the  lcd functions
 * 							
 */
extern void LCD_Runnable(void);

/**
 * Input: 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: Clears LCD
 * 							
 */
extern ERROR_STATUS LCD_Clear(void);

/**
 * Input: row in the lcd (0/1) and col in the lcd 
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function used to re allocate the lcd cursor
 * 							
 */
extern ERROR_STATUS LCD_GoToXY(uint8_t row, uint8_t col);

/**
 * Input: Pointer to Data string
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function act as interface with the user to send data string
 * 							
 */
extern ERROR_STATUS DisplayData(uint8_t * Data);

/**
 * Input: Pointer to Data string
 * Output:
 * In/Out:			
 * Return: The error status of the function.			
 * Description: This function act as interface with the user to send data string
 * 							
 */
extern ERROR_STATUS ConvertToStr(uint8_t * Data);



#endif /* LCD_H_ */