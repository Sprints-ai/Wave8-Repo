/*
* EEPROM_INT.h
*
* Created: 28/04/2020 23:25:12
*  Author: sony
*/


#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_

/*
* Register bit manipulation
*/
#define SET_BIT(REG,BIT)		REG |= (1<<BIT)
#define CLEAR_BIT(REG,BIT)		REG &= ~(1<<BIT)
#define TOGGLE_BIT(REG,BIT)		REG ^= (1<<BIT)
#define GET_BIT(REG,BIT)		((REG >> BIT) & 0x01)

/*
 * Internal EEPROM Registers 
 */
#define EECR      (*(volatile unsigned char*)(0x3C))
#define EEDR      (*(volatile unsigned char*)(0x3D))
#define EEARL     (*(volatile unsigned char*)(0x3E))
#define EEARH     (*(volatile unsigned char*)(0x3F))

/*Store program memory control register*/
#define SPMCR     (*(volatile unsigned char*)(0x57))

/*Status register*/
#define SREG      (*(volatile unsigned char*)(0x5F))

/**********************************************************************************************************************************/

/*
 * Internal EEPROM Used data types
 */

/*Enum indicating Internal EEPROM status*/
typedef enum {EEINT_OK, EEINT_NOK, EEINT_BUSY}EEINT_CheckType;

/*Pinter used in call back operation*/
typedef void (*EEINT_CbkFunPtrType)(void);

/*Configuration structure used in Internal EEPROM Configurations*/
typedef struct
{
	EEINT_CbkFunPtrType WriteDoneCbkPtr;
	EEINT_CbkFunPtrType ReadDoneCbkPtr;
}EEINT_ConfigType;

/**********************************************************************************************************************************/

/*
 * Internal EEPROM Functions' prototypes 
 */

/*
 * Description: Internal EEPROM module initialization.
 * @param(IN) : N/A
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret: N/A
 */
void EEINT_Init(void);

/*
 * Description: Handles internal EEPROM data write request.
 * @param(IN) : Start address to begin writing from
 *              Pointer to the data that will be written
 *              Length of the data
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret: Internal EEPROM status
 */
EEINT_CheckType EEINT_ReqWrite(unsigned char StartAddress, const unsigned char* DataPtr, unsigned char Length);

/*
 * Description: Handles internal EEPROM data read request.
 * @param(IN) : Start address to begin reading from
 *              Length of the data
 * @param(OUT): Pointer to the date that will be read
 * @param(I/O): N/A
 * @ret: Internal EEPROM status
 */
EEINT_CheckType EEINT_ReqRead(unsigned char StartAddress,unsigned char* DataPtr,unsigned char Length);

/*
 * Description: Handles internal EEPROM data read/write operations.
 * @param(IN) : N/A
 * @param(OUT): N/A
 * @param(I/O): N/A
 * @ret: N/A
 */
void EEINT_Main(void);

#endif /* EEPROM_INT_H_ */