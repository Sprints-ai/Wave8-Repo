/*
 * ADC.c
 *
 *  Created on: Apr 25, 2020
 *      Author: K.Aladawy
 */

#include "ADC.h"

/************************************************************************
 ***************************** LOCAL MACROS *****************************
 ************************************************************************/
#define ADC_MODULE                            (*u32arr_BaseAddrArr[au8_Module]) /* Select Desired module */
#define NUM_OF_MODULES                        2u /*max ADC module*/
#define NUM_OF_SEQUENCER                      4u /*max sequencer number in each module*/
#define SEQUENCER_OFFSET_FACTOR               0x20u
#define SAMPLE_NUM_SHIFT_FACTOR               4u
#define GROUP_FACTOR                          10u /*a factor used to distinguish between module*/
#define D_BIT                                 0x01u /*D bit in ADCSSCTL reg mask*/
#define END_BIT                               0x02u /*END bit in ADCSSCTL reg mask*/
#define IE_BIT                                0x04u /*IE bit in ADCSSCTL reg mask*/
#define TS_BIT                                0x08u /*TS bit in ADCSSCTL reg mask*/
#define ONE_BIT                               0X1u
#define TEMP_VALUE_INITIAL_VALUE              0x0u /*variable initial value*/
#define TRIGGER_MASK_FACTOR                   4u
#define SAMPLE_SIZE_IN_BYTE                   4u /*size of conversion result in byte*/
#define SEQUENCER_0                           0u /*sequencer number*/
#define SEQUENCER_1                           1u /*sequencer number*/
#define SEQUENCER_2                           2u /*sequencer number*/
#define SEQUENCER_3                           3u /*sequencer number*/
#define BUFFER_SIZE_INITIAL_VALUE             0u /*variable initial value*/
#define INIT_LOOP_COUNTER                     0u /*variable initial value*/
#define SEQUENCER_0_MAX_SAMPLE                8u /*sequencer 0 max sample*/
#define SEQUENCER_1_2_MAX_SAMPLE              4u /*sequencer 1,2 max sample*/
#define SEQUENCER_3_MAX_SAMPLE                1u /*sequencer 3 max sample*/
#define SEQUENCER_NO_SAMPLE                   0u /*sequencer no sample*/
#define COMPLETE_CONVESION_BIT_INITIAL_VALUE  0x00u /*variable initial value*/
#define DATA_BUFFER_INITAIL_VALUE             0xFFFFFFFFu /*variable initial value*/
#define GROUP_INIT_INITIAL_VALUE              0x0u /*variable initial value*/
#define RESULT_BUFFER_SETUP_INITIAL_VALUE     0x0u /*variable initial value*/
#define GROUP_TRIGE_RSOURCE_INITIAL_VALUE     0xFFu /*variable initial value*/
#define GROUP_CONVERSION_RUN_INITIAL_VALUE    0x00u /*variable initial value*/
#define TRUE                                  1u
#define FALSE                                 0u


/************************************************************************
 **************************** MACRO FUNCTION ****************************
 ************************************************************************/
#define SET_BIT(REG,BIT)        do{(REG) |= (BIT);}while(0)
#define CLEAR_BIT(REG,BIT)      do{(REG) &= ~(BIT);}while(0)
#define TOGGLE_BIT(REG,BIT)     do{(REG) ^= (BIT);}while(0)
#define GET_BIT(REG,BIT)        ((REG) & (BIT))

/************************************************************************
 *************************** GLOBAL VARIABLES ***************************
 ************************************************************************/
static  ADC_Register_Type* u32arr_BaseAddrArr[NUM_OF_MODULES] = { ADC0,
                                                                  ADC1 };

static uint8_t gu8_GroupInit = GROUP_INIT_INITIAL_VALUE; /*0: not init, 1: init*/
static uint8_t gu8_ResultBufferSetup = RESULT_BUFFER_SETUP_INITIAL_VALUE; /*0: not init, 1: init*/
static uint8_t gu8_GroupTrigerSource = GROUP_TRIGE_RSOURCE_INITIAL_VALUE; /*0: H/W, 1: S/W*/
static uint8_t gu8_GroupConversionRun = GROUP_CONVERSION_RUN_INITIAL_VALUE; /*0:stop convesion, 1: startconversion */


/************************************************************************
 *********************** LOCAL FUNCTION PROTOTYPES **********************
 ************************************************************************/

/************************************************************************
 ******************** LOCAL FUNCTIONS IMPLEMENTATION ********************
 ************************************************************************/


/************************************************************************
 ************************* APIS IMPLEMENTATION **************************
 ************************************************************************/

void Adc_Init( const Adc_ConfigType* ConfigPtr )
{
    uint8_t au8_SequencerNum = ConfigPtr->ADC_Sequencer % GROUP_FACTOR,
            au8_Module = (ConfigPtr->ADC_Sequencer)/GROUP_FACTOR,
            au8_GroupMask = (ONE_BIT << (au8_SequencerNum)) << (au8_Module * NUM_OF_SEQUENCER);
    uint32_t au32_TempValue = TEMP_VALUE_INITIAL_VALUE;

    if (NULL == ConfigPtr)
    {
#if (TEST_MODE)
        Printf("ADC_E_PARAMATER CONFIGRATION POINTER IS NULL ");
#endif
    }

    else
    {
        /* 1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
         * ADCACTSS register. Programming of the sample sequencers is allowed without having them
         * enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
         * event were to occur during the configuration process.
         */
        au32_TempValue =   ONE_BIT<<au8_SequencerNum; /*ASEN bit mask*/
        CLEAR_BIT(ADC_MODULE.ADCACTSS, au32_TempValue); /*Disable the sequencer*/


        /* 2. Configure the trigger event for the sample sequencer in the ADCEMUX register. */
        au32_TempValue = (uint32_t)((ConfigPtr->ADC_TriggerSource) << (au8_SequencerNum * TRIGGER_MASK_FACTOR)); /*Trigger event mask*/
        ADC_MODULE.ADCEMUX |= au32_TempValue; /*Select trigger event*/

        if (ADC_TRIGGER_SOURCE_PPROCESSOR == ConfigPtr->ADC_TriggerSource)
        {
            SET_BIT(gu8_GroupTrigerSource, au8_GroupMask); /*set trigger source flag (S/W)*/
        }
        else
        {
            CLEAR_BIT(gu8_GroupTrigerSource, au8_GroupMask); /*clear trigger source flag (H/W)*/
        }



        /* 3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
         * (ADCTSSEL) register to specify in which PWM module the generator is located. The default
         * register reset selects PWM module 0 for all generators.
         */


        /* 4. For each sample in the sample sequence, configure the corresponding input source in the
         * ADCSSMUXn register.
         */

        if (ADC_CHANNEL_TEMP_SENSOR != ConfigPtr->ADC_Channel) /*If the siganl source is input channel not on ship Temp. sensor*/
        {
            /*number of channel shifted left by number of sample in sequencer*/
            au32_TempValue = ((ConfigPtr->ADC_Channel) << ((ConfigPtr->ADC_SampleNum) * SAMPLE_NUM_SHIFT_FACTOR));
            /*Select module number (0,1), then select sequencer number (0,1,2,3), then select the register*/
            ADC_MODULE.SEQUENCER_ARR[au8_SequencerNum].ADCSSMUX |= au32_TempValue;
        }

        /* 5. For each sample in the sample sequence, configure the sample control bits in the corresponding
         * nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
         * is set. Failure to set the END bit causes unpredictable behavior.
         */
        au32_TempValue = TEMP_VALUE_INITIAL_VALUE; /*Clear Temp value to use it as a mask*/

        /*Select Temperature sensor or channel*/
        if (ADC_CHANNEL_TEMP_SENSOR == ConfigPtr->ADC_Channel)
        {
            SET_BIT(au32_TempValue, TS_BIT); /*Select the conversion from Temperature Sensor*/
        }
        else
        {
            CLEAR_BIT(au32_TempValue, TS_BIT); /*Select the conversion from I/O channel*/
        }

        /*Operation mode (polling or interrupt)*/
        if (ADC_OPERATION_MODE_INTERRUPT == ConfigPtr->ADC_OperationMode)
        {
            SET_BIT(au32_TempValue, IE_BIT); /*enable the interrupt*/
        }
        else if (ADC_OPERATION_MODE_POLLING == ConfigPtr->ADC_OperationMode)
        {
            CLEAR_BIT(au32_TempValue, IE_BIT); /*disable the interrupt*/
        }
        else
        {
            /*report error*/
        }

        /*Determine the end of sample*/
        if (ADC_END_OF_SAMPLE_ACTIVE == ConfigPtr->ADC_EndOfSample)
        {
            SET_BIT(au32_TempValue, END_BIT); /*this sample is the last sample of the sequence.*/
            SET_BIT(gu8_GroupInit, au8_GroupMask); /*set group init flag*/
        }
        else if (ADC_END_OF_SAMPLE_DEACTIVATE == ConfigPtr->ADC_EndOfSample)
        {
            CLEAR_BIT(au32_TempValue, END_BIT); /*Another sample in the sequence is the final sample.*/
        }
        else
        {
            /*report error*/
        }

        /*Determine sample mode (Single end, Differential)*/
        if (ADC_SAMPLE_MODE_SINGLE_END == ConfigPtr->ADC_SampleMode)
        {
            CLEAR_BIT(au32_TempValue, D_BIT); /*Select single end mode*/
        }
        else
        {
            SET_BIT(au32_TempValue, D_BIT); /*Select differential mode*/
        }

        /*mask value shifted left by number of sample in sequencer*/
        au32_TempValue = (uint32_t)(au32_TempValue << (ConfigPtr->ADC_SampleNum * SAMPLE_NUM_SHIFT_FACTOR));
        /*Select module number (0,1), then select sequencer number (0,1,2,3), then select the register*/
        ADC_MODULE.SEQUENCER_ARR[au8_SequencerNum].ADCSSCTL |= au32_TempValue;



        /* 6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register. */


        /* 7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
         * register.
         */
        au32_TempValue =  (uint32_t)(ONE_BIT<<(au8_SequencerNum));
        SET_BIT((ADC_MODULE.ADCACTSS), au32_TempValue); /*Enable the Sequencer*/
    }

}



Std_ReturnType Adc_SetupResultBuffer( Adc_SequencerType Group, Adc_ValueGroupType* DataBufferPtr )
{
    Std_ReturnType Error = FALSE;
    uint8_t au8_BufferNumOfElement = BUFFER_SIZE_INITIAL_VALUE,
            au8_InitLoopCounter = INIT_LOOP_COUNTER,
            au8_Sequencer = Group % GROUP_FACTOR,
            au8_Module = Group / GROUP_FACTOR,
            au8_GroupMask = (ONE_BIT << (au8_Sequencer)) << (au8_Module * NUM_OF_SEQUENCER);

    if (NULL == DataBufferPtr)
    {
        Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E_PARAMATER BUFFER POINTER IS NULL ");
#endif
    }
    else
    {
        au8_BufferNumOfElement = sizeof(DataBufferPtr) / SAMPLE_SIZE_IN_BYTE;

        /*Check Buffer size compatibility with the Group*/
        if (SEQUENCER_0 == au8_Sequencer)
        {
            if ( (SEQUENCER_0_MAX_SAMPLE < au8_BufferNumOfElement) || (SEQUENCER_NO_SAMPLE == au8_BufferNumOfElement) )
            {
                Error |= TRUE;
#if (TEST_MODE)
                Printf("ADC_E NON COMPATIBLE SIZE ERROR");
#endif
            }
            else
            {
                Error |= TRUE;
            }
        }
        else if ( (SEQUENCER_1 == au8_Sequencer) || (SEQUENCER_2 == au8_Sequencer) )
        {
            if ( (SEQUENCER_1_2_MAX_SAMPLE < au8_BufferNumOfElement) || (SEQUENCER_NO_SAMPLE == au8_BufferNumOfElement) )
            {
                Error |= TRUE;
#if (TEST_MODE)
                Printf("ADC_E NON COMPATIBLE SIZE ERROR");
#endif
            }
            else
            {
                Error |= FALSE;
            }
        }
        else if (SEQUENCER_3 == au8_Sequencer)
        {
            if (SEQUENCER_3_MAX_SAMPLE != au8_BufferNumOfElement)
            {
                Error |= TRUE;
#if (TEST_MODE)
                Printf("ADC_E NON COMPATIBLE SIZE ERROR");
#endif
            }
            else
            {
                Error |= FALSE;
            }
        }
        else
        {
            Error |= TRUE;
#if (TEST_MODE)
                Printf("ADC_E PARAMTER GROUP ID NON-EXISTING ERROR");
#endif
        }



        if(FALSE == Error)
        {
            /*initialize the Buffer*/
            for (au8_InitLoopCounter = INIT_LOOP_COUNTER; au8_InitLoopCounter < au8_BufferNumOfElement; au8_InitLoopCounter++)
            {
                DataBufferPtr[au8_InitLoopCounter] = DATA_BUFFER_INITAIL_VALUE; /*initialize Result Buffer by Constant Value */
            }

            SET_BIT(gu8_ResultBufferSetup, au8_GroupMask);/*set result buffer setup flag*/
        }

    }

    return Error;
}



#if(START_GROUP_CONVERSIO)
void Adc_StartGroupConversion( Adc_SequencerType Group )
{
    uint8_t au8_Temp = TEMP_VALUE_INITIAL_VALUE,
            au8_Error = FALSE,
            au8_Sequencer = Group % GROUP_FACTOR,
            au8_Module = Group / GROUP_FACTOR,
            au8_GroupMask = (ONE_BIT << (au8_Sequencer)) << (au8_Module * NUM_OF_SEQUENCER);

    /*** CHECK THE GROUP ID ***/
    if ( (NUM_OF_SEQUENCER <= au8_Sequencer) || (NUM_OF_MODULES <= au8_Module) )
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E_PARAMTER GROUP ID NON-EXISTING ERROR");
#endif
    }

    /*** CHECK THE GROUP INITIALIZED ***/
    au8_Temp = GET_BIT(gu8_GroupInit, au8_GroupMask); /*get group init flag */
    if( FALSE == au8_Temp)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T INITIALIZED ");
#endif
    }

    /*** CHECK THE RESULT BUFFER SETUP ***/
    au8_Temp = GET_BIT(gu8_ResultBufferSetup, au8_GroupMask); /*get result buffer setup flag */
    if( FALSE == au8_Temp)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP BUFFER IS NOT INITIALIZED ");
#endif
    }

    /*** CHECK THE EVENT TRIGGER SOURCE ***/
    au8_Temp = GET_BIT(gu8_GroupTrigerSource, au8_GroupMask); /*get event trigger source flag*/
    if( FALSE == au8_Temp)/* if the source is H/W */
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T SOFTWARE TRIGGER ");
#endif
    }

    /*** CHECK PRE START ***/
    au8_Temp = GET_BIT(gu8_GroupConversionRun, au8_GroupMask); /*get group run conversion flag */
    if( FALSE != au8_Temp)/* if the group already start */
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP IS ALREADY STARTED CONVERSION ");
#endif
    }

    if (FALSE == au8_Error)
    {
        /*** START CONVERSION ***/
        SET_BIT(ADC_MODULE.ADCPSSI, (ONE_BIT << au8_Sequencer));
        SET_BIT(gu8_GroupConversionRun, au8_GroupMask); /*set group run conversion flag*/
    }
}
#endif



#if(STOP_GROUP_CONVERSIO)
void Adc_StopGroupConversion( Adc_SequencerType Group )
{
    uint8_t au8_Temp = TEMP_VALUE_INITIAL_VALUE,
            au8_Error = FALSE,
            au8_Sequencer = Group % GROUP_FACTOR,
            au8_Module = Group / GROUP_FACTOR,
            au8_GroupMask = (ONE_BIT << (au8_Sequencer)) << (au8_Module * NUM_OF_SEQUENCER);

    /*** CHECK THE GROUP ID ***/
    if ( (NUM_OF_SEQUENCER <= au8_Sequencer) || (NUM_OF_MODULES <= au8_Module) )
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E_PARAMTER GROUP ID NON-EXISTING ERROR");
#endif
    }

    /*** CHECK THE GROUP INITIALIZED ***/
    au8_Temp = GET_BIT(gu8_GroupInit, au8_GroupMask); /*get group init flag */
    if( FALSE == au8_Temp)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T INITIALIZED ");
#endif
    }

    /*** CHECK THE EVENT TRIGGER SOURCE ***/
    au8_Temp = GET_BIT(gu8_GroupTrigerSource, au8_GroupMask); /*get event trigger source flag*/
    if( FALSE == au8_Temp)/* if the source is H/W */
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T SOFTWARE TRIGGER ");
#endif
    }

    /*** CHECK PRE STOP ***/
    au8_Temp = GET_BIT(gu8_GroupConversionRun, au8_GroupMask); /*get group run conversion flag */
    if( FALSE == au8_Temp)/* if the group already stop */
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T STARTED CONVERSION ");
#endif
    }

    if (FALSE == au8_Error)
    {
        /*** STOP CONVERSION ***/
        CLEAR_BIT(ADC_MODULE.ADCPSSI, (ONE_BIT << au8_Sequencer));
        CLEAR_BIT(gu8_GroupConversionRun, au8_GroupMask); /*set group start conversion flag*/
    }
}
#endif



Std_ReturnType Adc_ReadGroup( Adc_SequencerType Group, Adc_ValueGroupType* DataBufferPtr )
{
    uint8_t au8_Temp = TEMP_VALUE_INITIAL_VALUE,
            au8_Error = FALSE,
            au8_Sequencer = Group % GROUP_FACTOR,
            au8_Module = Group / GROUP_FACTOR,
            au8_GroupMask = (ONE_BIT << (au8_Sequencer)) << (au8_Module * NUM_OF_SEQUENCER);
    uint32_t au32_CompleteConvesionBit = COMPLETE_CONVESION_BIT_INITIAL_VALUE;

    /*** CHECK THE GROUP ID ***/
    if ( (NUM_OF_SEQUENCER <= au8_Sequencer) || (NUM_OF_MODULES <= au8_Module) )
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E_PARAMTER GROUP ID NON-EXISTING ERROR");
#endif
    }

    /*** CHECK THE GROUP INITIALIZED ***/
    au8_Temp = GET_BIT(gu8_GroupInit, au8_GroupMask); /*get group init flag */
    if( FALSE == au8_Temp)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T INITIALIZED ");
#endif
    }

    /*** CHECK THE RESULT BUFFER SETUP ***/
    au8_Temp = GET_BIT(gu8_ResultBufferSetup, au8_GroupMask); /*get result buffer setup flag */
    if( FALSE == au8_Temp)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP BUFFER IS NOT INITIALIZED ");
#endif
    }

    /*** CHECK PRE START ***/
    au8_Temp = GET_BIT(gu8_GroupConversionRun, au8_GroupMask); /*get group run conversion flag */
    if( FALSE == au8_Temp)/* if the group stop conversion */
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP IS ALREADY STARTED CONVERSION ");
#endif
    }

    /*** CHECK DATA BUFFER POINTER ***/
    if (NULL == DataBufferPtr)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E_PARAMATER BUFFER POINTER IS NULL ");
#endif
    }

    /*** CHECK IF THE CONVERSION COMPLETE ***/
    au32_CompleteConvesionBit = GET_BIT(ADC_MODULE.ADCRIS, (ONE_BIT << (au8_Sequencer))); /*get conversion complete flag*/
    if(FALSE == au32_CompleteConvesionBit)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E CONVERSION ISN'T COMPLETE YET");
#endif
    }


    if (FALSE == au8_Error)
    {     
	    *DataBufferPtr = ADC_MODULE.SEQUENCER_ARR[au8_Sequencer].ADCSSFIFO; /*read conversion result*/
        CLEAR_BIT(ADC_MODULE.ADCISC, (ONE_BIT << (au8_Sequencer))); /*clear conversion complete flag*/
    }

    return au8_Error;
}



Adc_StatusType Adc_GetGroupStatus( Adc_SequencerType Group )
{
    uint8_t au8_Temp = TEMP_VALUE_INITIAL_VALUE,
            au8_Error = FALSE,
            au8_ReturnValue,
            au8_Sequencer = Group % GROUP_FACTOR,
            au8_Module = Group / GROUP_FACTOR,
            au8_GroupMask = (ONE_BIT << (au8_Sequencer)) << (au8_Module * NUM_OF_SEQUENCER);
    uint32_t au32_CompleteConvesionBit = COMPLETE_CONVESION_BIT_INITIAL_VALUE;

    /*** CHECK THE GROUP ID ***/
    if ( (NUM_OF_SEQUENCER <= au8_Sequencer) || (NUM_OF_MODULES <= au8_Module) )
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E_PARAMTER GROUP ID NON-EXISTING ERROR");
#endif
    }

    /*** CHECK THE GROUP INITIALIZED ***/
    au8_Temp = GET_BIT(gu8_GroupInit, au8_GroupMask); /*get group init flag */
    if( FALSE == au8_Temp)
    {
        au8_Error |= TRUE;
#if (TEST_MODE)
        Printf("ADC_E GROUP ISN'T INITIALIZED ");
#endif
    }

    if (FALSE == au8_Error)
    {
        /*** CHECK IF THE CONVERSION COMPLETE ***/
        au32_CompleteConvesionBit = GET_BIT(ADC_MODULE.ADCRIS, (ONE_BIT << (au8_Sequencer))); /*get conversion complete flag*/
        if(FALSE == au32_CompleteConvesionBit)
        {
            /*** CHECK CONVERSION RUN ***/
            au8_Temp = GET_BIT(gu8_GroupConversionRun, au8_GroupMask); /*get group run conversion flag */
            if( FALSE == au8_Temp)/* if the group stop */
            {
                au8_ReturnValue = ADC_IDLE;
            }
            else
            {
                au8_ReturnValue = ADC_BUSY;
            }
        }
        else
        {
            au8_ReturnValue = ADC_COMPLETED;
        }
    }
    else
    {
        au8_ReturnValue = ADC_IDLE;
    }


    return au8_ReturnValue;
}



















