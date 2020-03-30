/*
 * ERROR.h
 *
 * Created: 3/29/2020 4:11:53 PM
 *  Author: Reem
 */ 


#ifndef ERROR_H_
#define ERROR_H_


/************************************************************************/
/*						 ERROR_STATUS defines                               */
/************************************************************************/
#define E_OK 0 // OK
#define E_NOK 1 // NOT OK

#define E_NULL_PTR                            -1
#define E_UNINITIALIZED_MODULE                -2
#define E_MULTIPLE_INITIALIZION               -3
#define E_STOP_WITHOUT_START                  -4
#define E_NOT_STARTED                         -4
#define E_INVALID_PARAMETER                   -5
#define E_MULTIPLE_START                      -6
#define E_MULTIPLE_STOP                       -7
#define E_FULL_BUFFER                         -8
#define E_TASK_DONE                            2



#endif /* ERROR_H_ */