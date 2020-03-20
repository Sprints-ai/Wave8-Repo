/*
 * common_macros.h
 *
 * Created: 17/02/2020 11:35:08 ص
 *  Author: TOSHIBA
 */ 


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* ERROR_GANDLING_STATUS */



#define CLEAR_BIT(REG,BIT)          (REG&=~(BIT))
#define SET_BIT(REG,BIT)            (REG|=(BIT))
#define READ_BIT(REG,BIT)           (REG&(BIT))
#define SET_MASK(number,Mask)       ((number)|=(Mask))




#endif /* COMMON_MACROS_H_ */