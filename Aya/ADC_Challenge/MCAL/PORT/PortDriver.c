/*
 * PortDriver.c
 *
 * Created: 4/8/2020 6:28:44 PM
 *  Author: Khaled
 */ 

/**********************************************************/
/************************ INCLUDES ************************/
/**********************************************************/
#include "PortDriver.h" 
 
/**********************************************************/
/****************** GPIO REGISTER MAPING ******************/
/**********************************************************/ 
typedef struct
{
    uint32_t GPIODATA         ;
    uint8_t  REserved[0x3FC]  ; /*offset: 0x04 -> 0x3FC*/
    uint32_t GPIODIR          ;
    uint32_t GPIOIS           ;
    uint32_t GPIOIBE          ;
    uint32_t GPIOIEV          ;
    uint32_t GPIOIM           ;
    uint32_t GPIORIS          ;
    uint32_t GPIOMIS          ;
    uint32_t GPIOICR          ;
    uint32_t GPIOAFSEL        ; 
    uint8_t  Reserved_2[0xDC] ; /*offset : 0x424 -> 0x500*/
    uint32_t GPIODR2R         ; 
    uint32_t GPIODR4R         ;
    uint32_t GPIODR8R         ;
    uint32_t GPIOODR          ;
    uint32_t GPIOPUR          ;
    uint32_t GPIOPDR          ;
    uint32_t GPIOSLR          ;
    uint32_t GPIODEN          ;
    uint32_t GPIOLOCK         ;
    uint32_t GPIOCR           ;
    uint32_t GPIOAMSEL        ;
    uint32_t GPIOPCTL         ;
    uint32_t GPIOADCCTL       ;
    uint32_t GPIODMACTL       ;
}PORT_RegType;

#define PORT_A      ( PORT_RegType*)BASE_ADDRESS_A
#define PORT_B      ( PORT_RegType*)BASE_ADDRESS_B
#define PORT_C      ( PORT_RegType*)BASE_ADDRESS_C
#define PORT_D      ( PORT_RegType*)BASE_ADDRESS_D
#define PORT_E      ( PORT_RegType*)BASE_ADDRESS_E
#define PORT_F      ( PORT_RegType*)BASE_ADDRESS_F

/**********************************************************/
/************************* MACROS *************************/
/**********************************************************/
#define NUM_OF_CHANNELS                                     8
#define NUM_OF_PORTS 6
																			   
#define CFG_ST_COUNTER_INITIAL_VALUE                        0
#define TEMP_VALUE_INITIAL_VALUE                            0 

#define BASE_ADDRESS_A                                      0x40004000
#define BASE_ADDRESS_B                                      0x40005000
#define BASE_ADDRESS_C                                      0x40006000
#define BASE_ADDRESS_D                                      0x40007000
#define BASE_ADDRESS_E                                      0x40024000
#define BASE_ADDRESS_F                                      0x40025000

#define EXT_INTERRUPT_DETECT_FACTOR                         10
#define EXT_INTERRUPT_LEVEL_DETECT                          2
#define EXT_INTERRUPT_EDGE_DETECT                           1

#define ANALOG_FUNCTION_VALUE                               20

#define GPIO_UNLOCK_VALUE                                   0x4C4F434B
#define GPIO_LOCK_VALUE                                     0X0125346D
/**********************************************************/
/******************** EXTERN VARIABLES ********************/
/**********************************************************/
extern PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS];

/**********************************************************/
/******************** GLOBAL VARIABLES ********************/
/**********************************************************/ 
 static volatile  PORT_RegType* U32ARR_BaseAddrArr[NUM_OF_PORTS] = { PORT_A,
                                                                     PORT_B,
                                                                     PORT_C,
                                                                     PORT_D,
                                                                     PORT_E,
                                                                     PORT_F };                                      
/**********************************************************/
/******************* APIS IMPLEMENTATION ******************/
/**********************************************************/                                    
void PortDriver_init (void)
{
    uint8_t                   au8_CfgStCounter  = CFG_ST_COUNTER_INITIAL_VALUE;
    uint32_t                  au32_TempValue    = TEMP_VALUE_INITIAL_VALUE;
    PortDriver_PortNumType    au8_PortNum       = NUM_OF_PORTS;
    PortDriver_ChannelNumType au8_ChannelOffset = NUM_OF_CHANNELS;        
    


        

    
    for(au8_CfgStCounter = CFG_ST_COUNTER_INITIAL_VALUE; au8_CfgStCounter < NUM_OF_ACTIVATED_CHANNELS; au8_CfgStCounter++)
    {
        au8_PortNum = PortDriver_CfgArr[au8_CfgStCounter].Channel / NUM_OF_CHANNELS;  /*determine the channel PORT*/

        au8_ChannelOffset = PortDriver_CfgArr[au8_CfgStCounter].Channel % NUM_OF_CHANNELS; /*determine the channel pin*/

        /*** UNLOCK GPIO AND COMMITTED ***/
        /*
         * GPIOLOCK reg protect some other gpio register from undesired access so to access this register unlock this register first (0x4C4F434B: UNLOCK, other value: LOCK)
         * GPIODIR reg bits 0:7, each bit represent pin commitment level  (0:UNCOMMITTED,  1:COMMITTED)
         */
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOLOCK = GPIO_UNLOCK_VALUE ; /*unlock gpio registers*/

        au32_TempValue = ( 1 << au8_ChannelOffset ); /*calculate commitment mask*/
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOCR |= au32_TempValue; /*enable commitment level to proper pin*/






        /*** CONFIGURE PIN DIRECTION ***/
        /*
         * GPIODIR reg bits 0:7, each bit represent pin direction in the port (0:INPUT,  1:OUTPUT)
         */

        au32_TempValue = ( (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Direction) << (au8_ChannelOffset));  /*calculate pin direction mask*/
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODIR |= au32_TempValue;  /*store pin direction in the proper bit in proper register*/






        /*** SELECT PIN FUNCTION(DIO / DIGITAL ALTERTNATIVE FUNCTION / ANALOG FUNCTION) ***/
        /*
         * GPIOAFSEL reg bits 0:7, each bit represent pin ALTERNATIVE function enable in the port (0:DIO,  1:ALTERNATIVE)
         * GPIOPCTL reg bits 0:31, each half-byte (4-bits) represent Pin ALTERNATIVE function, each pin has different value for different function
         * GPIODEN reg bits 0:7, each bit control pin digital configuration in the port (0:DISABLE. 1:ENABLE)
         * GPIOAMSEL reg bits 0:7, each bit control pin analog configuration in the port (0:DISABLE. 1:ENABLE)
         */
        /*check if the pin function is DIO*/
        if (PORTDRIVER_CHANNEL_FUNCTION_X_DIO == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Function)
        {
            /* clear proper bit in GPIOAFSEL register to select DIO function*/
            au32_TempValue = ~( 1 << au8_ChannelOffset );  /*calculate pin DIO function mask*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOAFSEL &= au32_TempValue; /*store pin DIO function value in the proper bit in proper GPIOAFSEL register*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODEN |= au32_TempValue; /*enable digital pin configuration */
        }
        /*check if the pin function is ANALOG*/ 
        else if (ANALOG_FUNCTION_VALUE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Function)
        {
            au32_TempValue = ( 1 << au8_ChannelOffset ); /*calculate pin ANALOG mask*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOAMSEL |= au32_TempValue; /*enable analog pin configuration */
				  	(*U32ARR_BaseAddrArr[au8_PortNum]).GPIOAFSEL |= au32_TempValue; /*store pin ADC function value in the proper bit in proper GPIOAFSEL*/

        }
        /*if the pin function is DIGITAL ALTERNATIVE*/
        else
        {
            /* set proper bit in GPIOAFSEL register to select ALTERNATIVE function*/
            au32_TempValue = ( 1 << au8_ChannelOffset );  /*calculate pin function mask*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOAFSEL |= au32_TempValue; /*store pin ALTERNATIVE function value in the proper bit in proper GPIOAFSEL register*/      
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODEN |= au32_TempValue; /*enable digital pin configuration */

            /* store proper value in proper field in GPIOPCTL register to select desired function*/
            au32_TempValue = ( 0xF << au8_ChannelOffset); /*calculate bits mask*/
            au32_TempValue |= (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPCTL; /*mask proper half-byte(4-bits)*/
            au32_TempValue &= (((PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Function) << au8_ChannelOffset) | 0xFFFFFFFF); /*store function value in proper bits*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPCTL = au32_TempValue; /*store function value in proper field in proper GPIOPCTL register*/
        }
        
        




        /*** CONFIGERATE PIN PROPERTIES ***/
        /*
         * GPIOR2R reg bits 0:7, each bit represent output pin current (0:N/A,  1:2mA)
         * GPIOR4R reg bits 0:7, each bit represent output pin current (0:N/A,  1:4mA)
         * GPIOR8R reg bits 0:7, each bit represent output pin current (0:N/A,  1:8mA)
         * GPIOODR reg bits 0:7, each bit represent pin attachment (0:N/A, 1:OPENED REAIN)
         * GPIOPDR reg bits 0:7, each bit represent pin attachment (0:N/A, 1:PULL DOWN RESISTOR)
         * GPIOPUR reg bits 0:7, each bit represent pin attachment (0:N/A, 1:PULL UP RESISTOR)
         * GPIOSLR reg bits 0:7, each bit represent pin slew rate configuration (0:disable, 1:enable)
         */
        /*select output current*/
        au32_TempValue = ( 1 << au8_ChannelOffset );  /*calculate pin mask*/

        switch (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Current_mA)
        {
            case PORTDRIVER_CHANNEL_CURRENT_mA_2:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODR2R |= au32_TempValue; /*configure the pin to 2 mA*/
            break;

            case PORTDRIVER_CHANNEL_CURRENT_mA_4:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODR4R |= au32_TempValue; /*configure the pin to 4 mA*/
            break;

            case PORTDRIVER_CHANNEL_CURRENT_mA_8:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIODR8R |= au32_TempValue; /*configure the pin to 8 mA*/
            break;

            default:
            break;

        }
        
        /*select pin pad*/
        switch (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Attachment)
        {
            case PORTDRIVER_CHANNEL_ATTACHMENT_NOTCONNECTED:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOODR &= ~(au32_TempValue) ; /*disable the pin open drain*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPDR &= ~(au32_TempValue) ; /*disable the pin pull-down resistor*/
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPUR &= ~(au32_TempValue) ; /*disable the pin pull-up resistor*/
            break;

            case PORTDRIVER_CHANNEL_ATTACHMENT_PULLUPRES:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPUR |= au32_TempValue ; /*enable the pin open drain*/
            break;
            
            case PORTDRIVER_CHANNEL_ATTACHMENT_PULLDOWNRES:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOPDR |= au32_TempValue ; /*enable the pin pull-down resistor*/
            break;
            
            case PORTDRIVER_CHANNEL_ATTACHMENT_OPENDRAIN:
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOODR |= au32_TempValue; /*enable the pin pull-up resistor*/

            /*enable/disable slew rate*/
            if (PORTDRIVER_CHANNEL_SLEWRATE_ENABLE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_SlewRate)
            {
                (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOSLR |= au32_TempValue; /*enable the pin slew rate*/
            }
            break;
            
            default:
            break;
        }

        
        



        /*** CONFIGURE INTERRUPT CONTROL ***/
        /* GPIOIM reg bits 0:7, each bit represent interrupt configuration (0:disable,  1:enable)
         * GPIOIS reg bits 0:7, each bit represent interrupt sense (0:edge,  1:level )
         * GPIOIBE reg bits 0:7, each bit represent interrupt both edge (0:single edge,  1:both edge)
         * GPIOIEV reg bits 0:7, each bit represent interrupt event (0:falling edge/low level, 1:raising edge/high level)
         */
        if (PORTDRIVER_CHANNEL_EXTI_DISABLE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
        {
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIM &= ~(au32_TempValue) ;/*disable pin interrupt*/
        }
        else
        {
            (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIM |= au32_TempValue ; /*enable pin interrupt*/

            if (EXT_INTERRUPT_EDGE_DETECT == (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti / EXT_INTERRUPT_DETECT_FACTOR))
            {
                (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIS &= ~(au32_TempValue); /*select interrupt edge trigger detection*/

                if(PORTDRIVER_CHANNEL_EXTI_BOTH_EDGE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                {
                    (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIBE |= au32_TempValue; /*select both edge detection*/
                }

                else
                {
                    (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIBE &= ~(au32_TempValue); /*select single edge detection*/

                    if(PORTDRIVER_CHANNEL_EXTI_RISIN_GEDGE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                    {
                        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIEV |= au32_TempValue; /*select rising edge detection*/
                    }

                    else if (PORTDRIVER_CHANNEL_EXTI_FALLIN_GEDGE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                    {
                        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIEV &= ~(au32_TempValue); /*select falling edge detection*/
                    }
                }

            } 
            else if (EXT_INTERRUPT_LEVEL_DETECT == (PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti / EXT_INTERRUPT_DETECT_FACTOR))
            {
                (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIS |= au32_TempValue;/*select interrupt level detection*/
                if(PORTDRIVER_CHANNEL_EXTI_HIGH_LEVEL_SENSE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                {
                    (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIEV |= au32_TempValue; /*select high level detection*/
                }

                else if (PORTDRIVER_CHANNEL_EXTI_LOW_LEVEL_SENSE == PortDriver_CfgArr[au8_CfgStCounter].PortDriver_Channel_Exti)
                {
                    (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOIEV &= ~(au32_TempValue); /*select low level detection*/
                }
            }
        }
        
        




        /*** LOCK GPIO AND UNCOMMITTED ***/
        /*
         * GPIOLOCK reg protect some other gpio register from undesired access so to access this register unlock this register first (0x4C4F434B: UNLOCK, other value: LOCK)
         * GPIODIR reg bits 0:7, each bit represent pin commitment level  (0:UNCOMMITTED,  1:COMMITTED)
         */
        au32_TempValue = ~( 1 << au8_ChannelOffset ); /*calculate non commitment mask*/
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOCR &= ~(au32_TempValue); /*disable commitment level to proper pin*/
        
        (*U32ARR_BaseAddrArr[au8_PortNum]).GPIOLOCK = GPIO_LOCK_VALUE ; /*lock gpio registers*/
        
        
   
    }
    

}
