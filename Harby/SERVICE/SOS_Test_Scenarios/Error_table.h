/*
 * Error_table.h
 *
 * Created: 25-Feb-20 5:22:48 PM
 *  Author: ahmed
 */ 


#ifndef ERROR_TABLE_H_
#define ERROR_TABLE_H_


/************************************************************************/
/*							INIT DEFINES                                */
/************************************************************************/
#define ERROR_NULL_PTR_INIT			(-1)
#define ERROR_MULTIPLE_MODULE_INIT	(-2)
#define INVALID_INIT_PARAMETER		(-3)

/************************************************************************/
/*							START DEFINES                               */
/************************************************************************/
#define ERROR_NULL_PTR_START			(-4)
#define ERROR_MULTIPLE_MODULE_START		(-5)
#define ERROR_START_FULL_BUFFER			(-6)
#define ERROR_MODULE_NOT_INIT			(-11)
#define ERROR_INVALID_START_PARAMETERS	(-12)
/************************************************************************/
/*							DISPATCH DEFINES                            */
/************************************************************************/
#define ERROR_DISPATCH_NO_TASKS	(-7)

/************************************************************************/
/*							STOP DEFINES                                */
/************************************************************************/
#define ERROR_MODULES_STOPPED_BEFORE	(-8)
#define ERROR_MODULE_DIDNOT_START		(-9)
#define ERROR_MODULE_PRIORITY_USED		(-10)

#endif /* ERROR_TABLE_H_ */
