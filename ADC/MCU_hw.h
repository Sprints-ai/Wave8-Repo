#ifndef __MCU_HW_H__
#define __MCU_HW_H__

#include "../std_types.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*									TYPE DEF 															*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/***********************************PortRegister***********************************/

typedef struct
{
    uint32_t GPIODATA    ;
	uint8_t  REserved[0x3FC];
    uint32_t GPIODIR     ;
    uint32_t GPIOIS      ;
    uint32_t GPIOIBE     ;
    uint32_t GPIOIEV     ;
    uint32_t GPIOIM      ;
    uint32_t GPIORIS     ;
    uint32_t GPIOMIS     ;
    uint32_t GPIOICR     ;
    uint32_t GPIOAFSEL   ; /*offset : 0x420 -> 424 */

    uint8_t  Reserved_2[0xDC];
	
    uint32_t GPIODR2R    ; /*offset : 0x500 */
    uint32_t GPIODR4R    ;
    uint32_t GPIODR8R    ;
    uint32_t GPIOODR     ;
    uint32_t GPIOPUR     ;
    uint32_t GPIOPDR     ;
    uint32_t GPIOSLR     ;
    uint32_t GPIODEN     ;
    uint32_t GPIOLOCK    ;
    uint32_t GPIOCR      ;
    uint32_t GPIOAMSEL   ;
    uint32_t GPIOPCTL    ;
    uint32_t GPIOADCCTL  ;
    uint32_t GPIODMACTL  ;
}PORT_RegType;

/***********************************System Control Register ***********************************/

typedef union //done
{
	uint32_t u32_RCC_Register;
	struct
	{
    uint32_t MOSCDIS	:1; 
	uint32_t 			:3;
	uint32_t OSCSRC		:2; 
	uint32_t  XTAL		:5;
	uint32_t BYPASS		:1; 
	uint32_t			:1;
	uint32_t PWRDN		:1;
	uint32_t 			:3;
	uint32_t PWMDIV		:3;
	uint32_t USEPWMDIV	:1;
	uint32_t 			:1;
	uint32_t USESYSDIV	:1;
	uint32_t SYSDIV 	:4;
	uint32_t ACG 		:1;
	uint32_t    		:4;	
  
	}str_RCC_Bit_Reg;
	
}RCC_Reg_t;

typedef union//done
{
	uint32_t u32_RCC2_Register;
	struct
	{
   
    uint32_t 			:4;
	uint32_t OSCSRC2	:3; 
    uint32_t			:4;
	uint32_t BYPASS2	:1;
	uint32_t 			:1;
	uint32_t PWRDN2		:1;
	uint32_t USBPWRDN	:1;
	uint32_t 			:7;  
	uint32_t SYSDIV2LSB	:1;
	uint32_t SYSDIV2 	:6;
	uint32_t 			:1;
	uint32_t DIV400		:1;
	uint32_t USERCC2  	:1;
  
	}str_RCC2_Bit_Reg;
	
}RCC2_Reg_t;

typedef union //done
{
	uint32_t gu32_MISC_Reg;
	struct
	{
   
    uint32_t			:1;
	uint32_t BOR1MIS	:1;
	uint32_t 			:1;
	uint32_t MOFMIS		:1;
	uint32_t			:2;
	uint32_t PLLLMIS	:1;
	uint32_t USBPLLLMIS	:7;  
	uint32_t MOSCPUPMIS	:1;
	uint32_t 			:1;
	uint32_t VDDAMIS	:1;
    uint32_t BOR0MIS	:1;
    uint32_t		 	:20; 
  
	}gstr_MISC_Bit_Reg;
	
}MISC_Reg_t;

typedef union    //done
{
	uint32_t gu32_RIS_Reg;
	struct
	{
    
    uint32_t			:1;
	uint32_t BOR1RIS	:1;
	uint32_t 			:1;
	uint32_t MOFRIS		:1;
	uint32_t			:2;
	uint32_t PLLLRIS	:1;
	uint32_t USBPLLLRIS	:7;  
    uint32_t MOSCPUPRIS	:1;
    uint32_t 			:1;
 	uint32_t VDDARIS	:1;
	uint32_t BOR0RIS	:1;
    uint32_t		 	:20; 

	
	}gstr_RIS_Bit_Reg;
	
}RIS_Reg_t;

        
typedef struct {
	uint32_t RCGCWD     ;        	  					//0
	uint32_t RCGCTIMER  ;        		  				//1
	uint32_t RCGCGPIO	;							  				//2
	uint32_t RCGCDMA	;												//3
  uint32_t Reserved0;//610->614	
	uint32_t RCGCHIB 	;												//5
	uint32_t RCGCUART	;												//6
	uint32_t RCGCSSI 	;												//7
	uint32_t RCGCI2C 	;												//8
	uint32_t Reserved1;//624-628  //9
	uint32_t RCGCUSB	;												//10
  uint32_t Reserved2[2];	//62C -> 634 
	uint32_t RCGCCAN 	;												//13
	uint32_t RCGCADC 	;												//14
	uint32_t RCGCACMP 	;											//15
	uint32_t RCGCPWM  	;											//16
	uint32_t RCGCQEI    ;											//17
	uint32_t Reserved3[4];//648 -> 658
	uint32_t RCGCEEPROM ;											//22
    uint32_t RCGCWTIMER ;										//23
} ClkGate_Reg_t;


/***********************************Flash Memory Register***********************************/

typedef union    //done
{
	uint32_t gu32_EEDONE_Reg;
	struct
	{
	uint32_t WORKING	:1;
	uint32_t 			:1;  
    uint32_t WKERASE	:1;
    uint32_t WKCOPY		:1;
	uint32_t NOPERM		:1;
	uint32_t WRBUSY		:1;
    uint32_t		 	:26; 

	}gstr_EEDONE_Bit_Reg;
	
}EEDONE_Reg_t;

/*********************************** ADC Register ***********************************/
typedef struct {
	
uint32_t ADCACTSS 		 ;	
uint32_t ADCRIS 		 ;
uint32_t ADCIM 			 ; 
uint32_t ADCISC 		 ;
uint32_t ADCOSTAT 		 ;
uint32_t ADCEMUX		 ;
uint32_t ADCUSTAT 		 ;
uint32_t ADCTSSEL 		 ;
uint32_t ADCSSPRI 		 ;
uint32_t ADCSPC 		 ;
uint32_t ADCPSSI         ;
uint32_t Reserved1		 ;
uint32_t ADCSAC 		 ;
uint32_t ADCDCISC 		 ;
uint32_t ADCCTL 	     ;
uint32_t Reserved2		 ;	
uint32_t ADCSSMUX0		 ;
uint32_t ADCSSCTL0 	     ;
uint32_t ADCSSFIFO0 	 ;
uint32_t ADCSSFSTAT0 	 ;
uint32_t ADCSSOP0 		 ;
uint32_t ADCSSDC0        ;
uint32_t reserved3[0x2]	 ;    /*offset : 0x058 -> 0x060 */	
uint32_t ADCSSMUX1 	     ;
uint32_t ADCSSCTL1 	     ;
uint32_t ADCSSFIFO1 	 ;
uint32_t ADCSSFSTAT1 	 ;
uint32_t ADCSSOP1		 ;
uint32_t ADCSSDC1        ;
uint32_t reserved4[0x2]	 ;   /*offset : 0x078 -> 0x080 */			
uint32_t ADCSSMUX2 	     ;
uint32_t ADCSSCTL2 	     ;
uint32_t ADCSSFIFO2 	 ;
uint32_t ADCSSFSTAT2	 ;
uint32_t ADCSSOP2 	     ;
uint32_t ADCSSDC2        ;
uint32_t reserved5[0x2]	 ;   /*offset : 0x098 -> 0x0A0 */	
uint32_t ADCSSMUX3       ;
uint32_t ADCSSCTL3       ;
uint32_t ADCSSFIFO3      ;
uint32_t ADCSSFSTAT3     ;
uint32_t ADCSSOP3 	     ;
uint32_t ADCSSDC3        ;
uint32_t reserved6[0x312];  /*offset : 0x0B8 -> 0xD00 */	
uint32_t ADCDCRIC        ;
uint32_t reserved7[0x3F] ; /*offset : 0xD04 -> 0xE00 */	
uint32_t ADCDCCTL0       ;
uint32_t ADCDCCTL1       ;
uint32_t ADCDCCTL2       ;
uint32_t ADCDCCTL3       ;
uint32_t ADCDCCTL4       ;
uint32_t ADCDCCTL5       ;
uint32_t ADCDCCTL6       ;
uint32_t ADCDCCTL7       ;
uint32_t reserved8[0x8]	 ;	 /*offset : 0xE20 -> 0xE40 */	
uint32_t ADCDCCMP0       ;
uint32_t ADCDCCMP1       ;
uint32_t ADCDCCMP2       ;
uint32_t ADCDCCMP3  	 ;
uint32_t ADCDCCMP4 	     ;
uint32_t ADCDCCMP5       ;
uint32_t ADCDCCMP6       ;
uint32_t ADCDCCMP7       ;
uint32_t reserved9[0x58] ;	/*offset : 0xE60 -> 0x0FC0 */	
uint32_t ADCPP 	         ;
uint32_t ADCPC 	         ;
uint32_t ADCCC 	         ;

} ADC_Reg_t;

/////////////////////////////////////////////////////////////////////////////////////////////
/* 							DEFINE 															*/
/////////////////////////////////////////////////////////////////////////////////////////////


/************************************NVIC REGISTER ***********************************/

#define EN0_REG						*((reg_type32_t )0xE000E100)
#define EN1_REG						*((reg_type32_t )0xE000E104)
#define EN2_REG						*((reg_type32_t )0xE000E108)
#define EN3_REG						*((reg_type32_t )0xE000E10C)
#define EN4_REG						*((reg_type32_t )0xE000E110)

#define DIS0_REG					*((reg_type32_t )0xE000E180)
#define DIS1_REG					*((reg_type32_t )0xE000E184)
#define DIS2_REG					*((reg_type32_t )0xE000E188)
#define DIS3_REG					*((reg_type32_t )0xE000E18C)
#define DIS4_REG					*((reg_type32_t )0xE000E190)

#define PEND0_REG					*((reg_type32_t )0xE000E200)
#define PEND1_REG					*((reg_type32_t )0xE000E204)
#define PEND2_REG					*((reg_type32_t )0xE000E208)
#define PEND3_REG					*((reg_type32_t )0xE000E20C)
#define PEND4_REG					*((reg_type32_t )0xE000E210)

#define UNPEND0_REG					*((reg_type32_t )0xE000E280)
#define UNPEND1_REG					*((reg_type32_t )0xE000E284)
#define UNPEND2_REG					*((reg_type32_t )0xE000E288)
#define UNPEND3_REG					*((reg_type32_t )0xE000E28C)
#define UNPEND4_REG					*((reg_type32_t )0xE000E290)

#define ACTIVE0_REG					*((reg_type32_t )0xE000E300)
#define ACTIVE1_REG					*((reg_type32_t )0xE000E304)
#define ACTIVE2_REG					*((reg_type32_t )0xE000E308)
#define ACTIVE3_REG					*((reg_type32_t )0xE000E30C)
#define ACTIVE4_REG					*((reg_type32_t )0xE000E310)


#define PRI0_REG					*((reg_type32_t )0xE000E400)
#define PRI1_REG					*((reg_type32_t )0xE000E404)
#define PRI2_REG					*((reg_type32_t )0xE000E408)
#define PRI3_REG					*((reg_type32_t )0xE000E40C)

#define PRI4_REG					*((reg_type32_t )0xE000E410)
#define PRI5_REG					*((reg_type32_t )0xE000E414)
#define PRI6_REG					*((reg_type32_t )0xE000E418)
#define PRI7_REG					*((reg_type32_t )0xE000E41C)

#define PRI8_REG					*((reg_type32_t )0xE000E420)
#define PRI9_REG					*((reg_type32_t )0xE000E424)
#define PRI10_REG					*((reg_type32_t )0xE000E428)
#define PRI11_REG					*((reg_type32_t )0xE000E42C)

#define PRI12_REG					*((reg_type32_t )0xE000E430)
#define PRI13_REG					*((reg_type32_t )0xE000E434)
#define PRI14_REG					*((reg_type32_t )0xE000E438)
#define PRI15_REG					*((reg_type32_t )0xE000E43C)

#define PRI16_REG					*((reg_type32_t )0xE000E440)
#define PRI17_REG					*((reg_type32_t )0xE000E444)
#define PRI18_REG					*((reg_type32_t )0xE000E448)
#define PRI19_REG					*((reg_type32_t )0xE000E44C)

#define PRI20_REG					*((reg_type32_t )0xE000E450)
#define PRI21_REG					*((reg_type32_t )0xE000E454)
#define PRI22_REG					*((reg_type32_t )0xE000E458)
#define PRI23_REG					*((reg_type32_t )0xE000E45C)

#define PRI24_REG					*((reg_type32_t )0xE000E460)
#define PRI25_REG					*((reg_type32_t )0xE000E464)
#define PRI26_REG					*((reg_type32_t )0xE000E468)
#define PRI27_REG					*((reg_type32_t )0xE000E46C)

#define PRI28_REG					*((reg_type32_t )0xE000E470)
#define PRI29_REG					*((reg_type32_t )0xE000E474)
#define PRI30_REG					*((reg_type32_t )0xE000E478)
#define PRI31_REG					*((reg_type32_t )0xE000E47C)

#define PRI32_REG					*((reg_type32_t )0xE000E480)
#define PRI33_REG					*((reg_type32_t )0xE000E484)
#define PRI34_REG					*((reg_type32_t )0xE000E488)


#define SWTRIG_REG					*((reg_type32_t )0xE000EF00)

/* **************************************************************************************************** */

#define INTCTRL_REG					*((reg_type32_t )0xE000ED04)
#define VTABLE_REG					*((reg_type32_t )0xE000ED08)
#define APINT_REG					*((reg_type32_t )0xE000ED0C)



/***********************************PortRegister***********************************/
					// FOR APB//
					
#define BASE_ADDRESS_A   0x40004000
#define BASE_ADDRESS_B   0x40005000
#define BASE_ADDRESS_C   0x40006000
#define BASE_ADDRESS_D   0x40007000
#define BASE_ADDRESS_E   0x40024000
#define BASE_ADDRESS_F   0x40025000
        

#define  ACTINATING_PORT(PORT_BASE_ADDR)     (*((volatile PORT_RegType* const)PORT_BASE_ADDR))



/*********************************** System Control Register ***********************************/


#define RCC_REG			(*((volatile RCC_Reg_t *const)(0x400FE060)))

#define RCC2_REG			(*((volatile RCC2_Reg_t*const)(0x400FE070)))
												
#define RIS_REG			(*((volatile RIS_Reg_t *const)(0x400FE050)))
												
#define MISC_REG			(*((volatile MISC_Reg_t*const)(0x400FE058)))

#define ClkGate_Reg		(*((volatile ClkGate_Reg_t*const)(0x400FE600)))	

#define RCGCWD_REG					(*(( reg_type32_t )(0x400FE600)))
/*********************************** Flash Memory Register ***********************************/

#define EEDONE_Reg		(*((volatile EEDONE_Reg_t *const)(0x400AF018)))


/*********************************** ADC Register ***********************************/


#define ADC_REG(ADCx_BASE_ADDERSS) (*((volatile ADC_Reg_t*const)ADCx_BASE_ADDERSS))
#define ADC0_BASE_ADDRESS 0x40038000
#define ADC1_BASE_ADDRESS 0x40039000

#endif

