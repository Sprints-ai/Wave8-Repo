
/******************************************************************************************/
/*														NVIC registers																							*/
/******************************************************************************************/


#define BASEPRI *((uint32_t *)0x00000050) 


#define EN0 *((uint32_t *)0xE000E100)
#define EN1 *((uint32_t *)0xE000E104)
#define EN2 *((uint32_t *)0xE000E108)
#define EN3 *((uint32_t *)0xE000E10C)
#define EN4 *((uint32_t *)0xE000E110)



#define DIS0 *((uint32_t *)0xE000E180) 
#define DIS1 *((uint32_t *)0xE000E184)
#define DIS2 *((uint32_t *)0xE000E188)
#define DIS3 *((uint32_t *)0xE000E18C)
#define DIS4 *((uint32_t *)0xE000E190)


#define PEND0 *((uint32_t *)0xE000E200)
#define PEND1 *((uint32_t *)0xE000E204)
#define PEND2 *((uint32_t *)0xE000E208)
#define PEND3 *((uint32_t *)0xE000E20C) 
#define PEND4 *((uint32_t *)0xE000E210)


#define UNPEND0 *((uint32_t *)0xE000E280)
#define UNPEND1 *((uint32_t *)0xE000E284)
#define UNPEND2 *((uint32_t *)0xE000E288)
#define UNPEND3 *((uint32_t *)0xE000E28C)
#define UNPEND4 *((uint32_t *)0xE000E290)


#define PRI0  *((uint32_t *)0xE000E400)
#define PRI1  *((uint32_t *)0xE000E404)
#define PRI2  *((uint32_t *)0xE000E408)
#define PRI3  *((uint32_t *)0xE000E40C)
#define PRI4  *((uint32_t *)0xE000E410)
#define PRI5  *((uint32_t *)0xE000E414)
#define PRI6  *((uint32_t *)0xE000E418)
#define PRI7  *((uint32_t *)0xE000E41C)
#define PRI8  *((uint32_t *)0xE000E420)
#define PRI9  *((uint32_t *)0xE000E424)
#define PRI10 *((uint32_t *)0xE000E428)
#define PRI11 *((uint32_t *)0xE000E42C)
#define PRI12 *((uint32_t *)0xE000E430)
#define PRI13 *((uint32_t *)0xE000E434)
#define PRI14 *((uint32_t *)0xE000E438)
#define PRI15 *((uint32_t *)0xE000E43C)
#define PRI16 *((uint32_t *)0xE000E440)
#define PRI17 *((uint32_t *)0xE000E444)
#define PRI18 *((uint32_t *)0xE000E448)
#define PRI19 *((uint32_t *)0xE000E44C)
#define PRI20 *((uint32_t *)0xE000E450)
#define PRI21 *((uint32_t *)0xE000E454)
#define PRI22 *((uint32_t *)0xE000E458)
#define PRI23 *((uint32_t *)0xE000E45C)
#define PRI24 *((uint32_t *)0xE000E460)
#define PRI25 *((uint32_t *)0xE000E464)
#define PRI26 *((uint32_t *)0xE000E468)
#define PRI27 *((uint32_t *)0xE000E46C)
#define PRI28 *((uint32_t *)0xE000E470)
#define PRI29 *((uint32_t *)0xE000E474)
#define PRI30 *((uint32_t *)0xE000E478)
#define PRI31 *((uint32_t *)0xE000E47C)
#define PRI32 *((volatile uint32_t *)0xE000E480)
#define PRI33 *((volatile uint32_t *)0xE000E484)
#define PRI34 *((volatile uint32_t *)0xE000E488)

#define SWTRIG *((volatile uint32_t *)0x00000F00)

#define VTABLE *((volatile uint32_t *)0x00000D08)


#define APINT *((volatile uint32_t *)0xE000ED0C)


/******************************************************************************************/
/*														sys_clock registers																					*/
/******************************************************************************************/



#define RCC *(( volatile uint32_t *)0x400FE060)
#define RCC2 *((volatile uint32_t *)0x400FE070)

#define RIS *((volatile uint32_t *)0x400FE050)
	

#define RCGCWD 		*((volatile uint32_t *)0x400FE600)
#define RCGCTIMER *((volatile uint32_t *)0x400FE604)
#define RCGCGPIO 	*((volatile uint32_t *)0x400FE608)
#define RCGCDMA		*((volatile uint32_t *)0x400FE60C)
#define RCGCHIB		*((volatile uint32_t *)0x400FE614)
#define RCGCUART	*((volatile uint32_t *)0x400FE618)
#define RCGCSSI		*((volatile uint32_t *)0x400FE61C)
#define RCGCI2C		*((volatile uint32_t *)0x400FE620)
#define RCGCUSB		*((volatile uint32_t *)0x400FE628)
#define RCGCCAN		*((volatile uint32_t *)0x400FE634)
#define RCGCADC		*((volatile uint32_t *)0x400FE638)
#define RCGCACMP	*((volatile uint32_t *)0x400FE63C)
#define RCGCPWM		*((volatile uint32_t *)0x400FE640)
#define RCGCQEI		*((volatile uint32_t *)0x400FE644)
#define RCGCEEPROM *((volatile uint32_t *)0x400FE658)
#define RCGCWTIMER *((volatile uint32_t *)0x400FE65C)






/******************************************************************************************/
/*														GPIO regiters 																				*/
/******************************************************************************************/
#define GPIO_PORT_A_APB  0x40004000
#define GPIO_PORT_A_AHB	 0x40058000
#define GPIO_PORT_B_APB  0x40005000
#define GPIO_PORT_B_AHB  0x40059000
#define GPIO_PORT_C_APB  0x40006000
#define GPIO_PORT_C_AHB  0x4005A000
#define GPIO_PORT_D_APB  0x40007000
#define GPIO_PORT_D_AHB  0x4005B000
#define GPIO_PORT_E_APB  0x40024000
#define GPIO_PORT_E_AHB  0x4005C000
#define GPIO_PORT_F_APB  0x40025000
#define GPIO_PORT_F_AHB  0x4005D000



#define GPIODATA_OFFSET              0x000
#define GPIODIR_OFFSET               0x400
#define GPIOIS_OFFSET                0x404
#define GPIOIBE_OFFSET               0x408
#define GPIOIEV_OFFSET               0x40C
#define GPIOIM_OFFSET                0x410
#define GPIORIS_OFFSET               0x414
#define GPIOMIS_OFFSET               0x418
#define GPIOICR_OFFSET               0x41C
#define GPIOAFSEL_OFFSET             0x420  
#define GPIODR2R_OFFSET              0x500 
#define GPIODR4R_OFFSET              0x504 
#define GPIODR8R_OFFSET              0x508 
#define GPIOODR_OFFSET               0x50C
#define GPIOPUR_OFFSET               0x510
#define GPIOPDR_OFFSET               0x514
#define GPIOSLR_OFFSET               0x518
#define GPIODEN_OFFSET               0x51C
#define GPIOLOCK_OFFSET              0x520 
#define GPIOCR_OFFSET                0x524
#define GPIOAMSEL_OFFSET             0x528  
#define GPIOPCTL_OFFSET              0x52C 
#define GPIOADCCTL_OFFSET            0x530   
#define GPIODMACTL_OFFSET            0x534   
#define GPIOPeriphID4_OFFSET         0xFD0      
#define GPIOPeriphID5_OFFSET         0xFD4      
#define GPIOPeriphID6_OFFSET         0xFD8      
#define GPIOPeriphID7_OFFSET         0xFDC      
#define GPIOPeriphID0_OFFSET         0xFE0      
#define GPIOPeriphID1_OFFSET         0xFE4      
#define GPIOPeriphID2_OFFSET         0xFE8      
#define GPIOPeriphID3_OFFSET         0xFEC  
#define GPIOPCellID0_OFFSET          0xFF0
#define GPIOPCellID1_OFFSET          0xFF4 
#define GPIOPCellID2_OFFSET          0xFF8 
#define GPIOPCellID3_OFFSET          0xFFC

#define GPIODIR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIODIR_OFFSET))
#define GPIOIS(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOIS_OFFSET))
#define GPIOIBE(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOIBE_OFFSET))
#define GPIOIEV(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOIEV_OFFSET))
#define GPIOIM(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOIM_OFFSET))
#define GPIORIS(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIORIS_OFFSET))
#define GPIOMIS(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOMIS_OFFSET))

#define GPIOICR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOICR_OFFSET))
#define GPIOAFSEL(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIOAFSEL_OFFSET))
#define GPIODR2R(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIODR2R_OFFSET))
#define GPIODR4R(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIODR4R_OFFSET))
#define GPIODR8R(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIODR8R_OFFSET))
#define GPIOODR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOODR_OFFSET))
#define GPIOPUR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOPUR_OFFSET))
#define GPIOPDR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOPDR_OFFSET))
#define GPIOSLR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOSLR_OFFSET))
#define GPIODEN(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIODEN_OFFSET))
#define GPIOLOCK(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIOLOCK_OFFSET))
#define GPIOCR(BASE_ADDRESS)					*((volatile uint32_t*)(BASE_ADDRESS + GPIOCR_OFFSET))
#define GPIOAMSEL(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIOAMSEL_OFFSET))
#define GPIOPCTL(BASE_ADDRESS)				*((volatile uint32_t*)(BASE_ADDRESS + GPIOPCTL_OFFSET))
#define GPIOADCCTL(BASE_ADDRESS)			*((volatile uint32_t*)(BASE_ADDRESS + GPIOADCCTL_OFFSET))
#define GPIODMACTL(BASE_ADDRESS)			*((volatile uint32_t*)(BASE_ADDRESS + GPIODMACTL_OFFSET))




#define RCGCWTIMER *((volatile uint32_t *)0x400FE65C)










