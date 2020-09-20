#ifndef COMMON_MACRO_H_
#define COMMON_MACRO_H_
/************************************************************************/
/*				 INCLUDES			        */
/************************************************************************/




/************************************************************************/
/*				 FUNCTION LIKE MICRO			        */
/************************************************************************/

#define Set_BIT(REG,BIT_NUM)  REG|=(1<<BIT_NUM)

#define Clear_BIT(REG,BIT_NUM) REG&=~(1<<BIT_NUM)

#define TOGGEL_BIT(REG,BIT_NUM) REG^=(1<<BIT_NUM)

#define ROTATE_RIGHT(REG,BIT_NUM)   REG = (REG >> BIT_NUM) | (REG << (8-BIT_NUM)

#define  ROTATE_LEFT(REG,BIT_NUM)   REG = (REG << BIT_NUM) | (REG >> (8-BIT_NUM)

#define BIT_IS_SET(REG,BIT_NUM) (REG & (1<<BIT_NUM))

#define BIT_IS_CLEAR(REG,BIT_NUM) (!(REG & (1<<BIT_NUM)))
 

 
#endif