/*
 * Processor.c
 *
 * Created: 4/3/2020 11:40:39 AM
 *  Author: Khaled
 */ 


#include "Processor.h"


#define WRITE_TO_SFR(REG,VALUE)         /*MOVE value to R0*/                                    \
                                        __asm__ ( "MOVT R0, #VALUE" );                          \
                                        /*Move from general register to special register*/      \
                                        __asm__ ( "MSR REG, R0" )                               \
                                         
                                    



void SVC_Handler (void)
{
    /*** CLEAR BIT 0 IN REG CONTROL USING GFR AND SFR*/
    /*Read CONTROL reg*/
    __asm__ ( "MRS R0, CONTROL" );
    
    /*clear bit 0*/
    __asm__ ( "AND R0, #0xFFFFFFFE" );
    
    /*write in CONTROL reg*/
    __asm__ ("MSR CONTROL , R0");
}


/*GLOBAL INTERRUPT*/
// /*PRIMASK REGSITER ENABLE AND DISABLE VALUES*/                                   
// #define PRIMASK_SET_VALUE       0x1
// #define PRIMASK_CLEAR_VALUE     0x0
// 
// /*BASEPRI REGSITER VALUES*/
// #define ALL_EXCEPTION_UNMASKED  0x00
// /*SET PRIMASK: Enable Global Interrupt*/
//    WRITE_TO_SFR(PRIMASK,PRIMASK_SET_VALUE); 

//    /*INITIALIZE BASEPRI: Enable Some Interrupt Priority*/
//    WRITE_TO_SFR(BASEPRI,ALL_EXCEPTION_UNMASKED);
