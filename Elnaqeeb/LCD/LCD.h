/*
 * LCD.h
 *
 * Created: 3/14/2020 12:18:54 PM
 *  Author: Ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_

/************************************************************************/
/*                          General macros                              */
/************************************************************************/

#define ROW_0	(0)
#define ROW_1	(1)

#define COL_0	(0)
#define COL_1	(1)
#define COL_2	(2)
#define COL_3	(3)
#define COL_4	(4)
#define COL_5	(5)
#define COL_6	(6)
#define COL_7	(7)
#define COL_8	(8)
#define COL_9	(9)
#define COL_10	(10)
#define COL_11	(11)
#define COL_12	(12)
#define COL_13	(13)
#define COL_14	(14)
#define COL_15	(15)



/************************************************************************/
/*							LCD data types                              */
/************************************************************************/

/*LCD error handling data type*/
typedef sint8_t EnmLCDError_t;
#define OPERATION_SUCCESS	(-1)
#define NULL_PTR_ERROR		(-2)


/************************************************************************/
/*                        LCD Functions' prototypes                     */
/************************************************************************/

/*
 * Description: Initializing the LCD Module
 * @param(IN) : N/A
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_init(void);

/*
 * Description: Sending command to LCD
 * @param(IN) : LCD Command
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_sendCommand(uint8_t au8_cmd);

/*
 * Description: Displaying certain character over the LCD
 * @param(IN) : Character to be displayed
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_displayChar(uint8_t au8_data);

/*
 * Description: Displaying string(series of characters) over the LCD
 * @param(IN) : Pointer to string to be displayed
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_displayString(uint8_t* pu8_string);

/*
 * Description: Go to LCD certain  pixel (Row and Column intersection)
 * @param(IN) : Row of the LCD
 *				Column of the LCD
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_gotoRowColumn(uint8_t au8_row , uint8_t au8_col);

/*
 * Description: Displaying string in a certain LCD location
 * @param(IN) : Pointer to string to be displayed
 * 				Row of the LCD
 *				Column of the LCD
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_displayStringRowColumn(uint8_t* pu8_string , uint8_t au8_row , uint8_t au8_col);

/*
 * Description: Clearing the LCD
 * @param(IN) : N/A
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret LCD Error status
 */
EnmLCDError_t LCD_clear(void);

#endif /* LCD_H_ */