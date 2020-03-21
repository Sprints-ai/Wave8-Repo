
#ifndef TEST_H
#define TEST_H

#include "Services/SOS_Config.h"

/**
 * Description: Tests the SOS_Init function
 * Test Cases :
 *				1- passing invalid parameter in the configuration struct
 *				expected output 202 which maps to module ID + Invalid parameter error ID
 *
 *				2- reinitializing SOS
 *				expected output 204 which maps to module ID + module already initialized
 *
 *				3- witting a valid code
 *				expected output 0 which maps to no error
 */
void SOS_Init_Test(void);

/**
 * Description: Tests the SOS_DeInit function
 * Test Cases :
 *				1- de_initializing SOS before initializing it
 *				expected output 203 which maps to module ID + module not initialized
 *
 *				2- writing a valid code
 *				expected output 0 which maps to no error
 *
 */
void SOS_DeInit_Test(void);

/**
 * Description: Tests the SOS_Start_Timer function
 * Test Cases :
 *				1- starting SOS without initialization
 *				expected output 203 which maps to module ID + module not initialized
 *
 *				2-passing a null pointer as the function pointer
 *				expected output 201 which maps to module ID + NULL pointer error
 *				
 *				3- writing a valid code
 *				expected output 0 which maps to no error
 *
 *				4- adding a new value after the buffer is full
 *				expected output 207 which maps to module ID + buffer is full
 *
 */
void SOS_Start_Timer_Test(void);

/**
 * Description: Tests the SOS_Stop_Timer function
 * Test Cases :
 *				1- stopping a task that's not started (does not exist in the buffer)
 *				expected output 202 which maps to module ID + invalid parameter error
 *
 *				
 *				2- writing a valid code (stopping a task that exists in the buffer)
 *				expected output 0 which maps to no error
 *
 */
void SOS_Stop_Timer_Test(void);

/**
 * Description: Tests the SOS_Dispatch function
 * Test Cases :
 *				1- dispatching before initializing the SOS
 *				expected output 203 which maps module ID + module not initialized
 *
 *				2-dispatching before starting any task (buffer is empty)
 *				expected output 0 which maps to no error
 *
 *				3- writing a valid code 
 *				expected output 0 which maps to no error
 *
 */
void SOS_Dispatch_Test(void);

#endif  /* TEST_H */