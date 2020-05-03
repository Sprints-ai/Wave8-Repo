#ifndef __SYS_CONTROL_Types_H__
#define __SYS_CONTROL_Types_H__

#include "../std_types.h"
/*
typedef uint8_t SystemControl_ClkGateFunction_t ;

#define Watchdog_Timer									0
#define General_Purpose_Timer_32_Bit					1
#define General_Purpose_Input_Output					2
#define Micro_Direct_Memory_Access						3
#define Hibernation										4
#define Universal_Asynchronous_Receiver_Transmitter		5
#define Synchronous_Serial_Interface					6
#define Inter_Integrated_Circuit						7
#define Universal_Serial_Bus 							8
#define Controller_Area_Network							9
#define Analog_to_Digital_Converter						10
#define Analog_Comparator								11
#define Pulse_Width_Modulator							12
#define Quadrature_Encoder_Interface					13
#define EEPROM											14
#define General_Purpose_Timer_64_Bit 					15

typedef uint8_t SystemControl_ClkGateModuleID_t ;

#define Watchdog_Timer0										0
#define Watchdog_Timer1										1
			
#define General_Purpose_Timer_32_Bit_Timer0					0
#define General_Purpose_Timer_32_Bit_Timer1					1
#define General_Purpose_Timer_32_Bit_Timer2					2
#define General_Purpose_Timer_32_Bit_Timer3					3
#define General_Purpose_Timer_32_Bit_Timer4					4
#define General_Purpose_Timer_32_Bit_Timer5					5
			
#define General_Purpose_Input_Output_PORT_A					0
#define General_Purpose_Input_Output_PORT_B     			1
#define General_Purpose_Input_Output_PORT_C     			2
#define General_Purpose_Input_Output_PORT_D     			3
#define General_Purpose_Input_Output_PORT_E     			4
#define General_Purpose_Input_Output_PORT_F     			5
			
#define Micro_Direct_Memory_Access_0						0
			
#define Hibernation_0										0

#define Universal_Asynchronous_Receiver_Transmitter_UART0	0
#define Universal_Asynchronous_Receiver_Transmitter_UART1	1
#define Universal_Asynchronous_Receiver_Transmitter_UART2   2
#define Universal_Asynchronous_Receiver_Transmitter_UART3   3
#define Universal_Asynchronous_Receiver_Transmitter_UART4   4
#define Universal_Asynchronous_Receiver_Transmitter_UART5   5
#define Universal_Asynchronous_Receiver_Transmitter_UART6	6
#define Universal_Asynchronous_Receiver_Transmitter_UART7	7
	
#define Synchronous_Serial_Interface_SSI_0					0	
#define Synchronous_Serial_Interface_SSI_1                  1
#define Synchronous_Serial_Interface_SSI_2                  2
#define Synchronous_Serial_Interface_SSI_3		            3

#define Inter_Integrated_Circuit_I2C_0						0
#define Inter_Integrated_Circuit_I2C_1                      1
#define Inter_Integrated_Circuit_I2C_2                      2
#define Inter_Integrated_Circuit_I2C_3                      3

#define Universal_Serial_Bus_0								0

#define Controller_Area_Network_CAN_0						0
#define Controller_Area_Network_CAN_1                       1

#define Analog_to_Digital_Converter_ADC_0					0
#define Analog_to_Digital_Converter_ADC_1                   1

#define Analog_Comparator_0									0

#define Pulse_Width_Modulator_PWM_0							0
#define Pulse_Width_Modulator_PWM_1                         1

#define Quadrature_Encoder_Interface_QEI_0					0
#define Quadrature_Encoder_Interface_QEI_1                  1

#define EEPROM_0											0

#define General_Purpose_Timer_64_Bit_Timer_0 				0
#define General_Purpose_Timer_64_Bit_Timer_1                1
#define General_Purpose_Timer_64_Bit_Timer_2                2
#define General_Purpose_Timer_64_Bit_Timer_3                3
#define General_Purpose_Timer_64_Bit_Timer_4 				4
#define General_Purpose_Timer_64_Bit_Timer_5 				5

typedef struct{
	
	SystemControl_ClkGateFunction_t		SystemControl_ClkGateFunction;
	SystemControl_ClkGateModuleID_t 	SystemControl_ClkGateModuleID;	
}SysCtr_Cfg_t;

*/


///////////////////second way ///////////////
#define Watchdog_Timer0																		0x00
#define Watchdog_Timer1																		0x01
						
#define General_Purpose_Timer_32_Bit_Timer0								0x08
#define General_Purpose_Timer_32_Bit_Timer1								0x09
#define General_Purpose_Timer_32_Bit_Timer2								0x0A
#define General_Purpose_Timer_32_Bit_Timer3								0x0B
#define General_Purpose_Timer_32_Bit_Timer4								0x0C
#define General_Purpose_Timer_32_Bit_Timer5								0x0D
			
#define General_Purpose_Input_Output_PORT_A								0x10
#define General_Purpose_Input_Output_PORT_B     					0x11
#define General_Purpose_Input_Output_PORT_C     					0x12
#define General_Purpose_Input_Output_PORT_D     					0x13
#define General_Purpose_Input_Output_PORT_E     					0x14
#define General_Purpose_Input_Output_PORT_F     					0x15
			
#define Micro_Direct_Memory_Access												0x18
			
#define Hibernation																				0x28

#define Universal_Asynchronous_Receiver_Transmitter_UART0	0x30
#define Universal_Asynchronous_Receiver_Transmitter_UART1	0x31
#define Universal_Asynchronous_Receiver_Transmitter_UART2 0x32
#define Universal_Asynchronous_Receiver_Transmitter_UART3 0x33
#define Universal_Asynchronous_Receiver_Transmitter_UART4 0x34
#define Universal_Asynchronous_Receiver_Transmitter_UART5 0x35
#define Universal_Asynchronous_Receiver_Transmitter_UART6	0x36
#define Universal_Asynchronous_Receiver_Transmitter_UART7	0x37
	
#define Synchronous_Serial_Interface_SSI_0								0x38	
#define Synchronous_Serial_Interface_SSI_1                0x39
#define Synchronous_Serial_Interface_SSI_2                0x3A
#define Synchronous_Serial_Interface_SSI_3		            0x3B

#define Inter_Integrated_Circuit_I2C_0										0x40
#define Inter_Integrated_Circuit_I2C_1                    0x41
#define Inter_Integrated_Circuit_I2C_2                    0x42
#define Inter_Integrated_Circuit_I2C_3                    0x43

#define Universal_Serial_Bus															0x50

#define Controller_Area_Network_CAN_0												0x68
#define Controller_Area_Network_CAN_1                       0x69

#define Analog_to_Digital_Converter_ADC_0										0x70
#define Analog_to_Digital_Converter_ADC_1                   0x71

#define Analog_Comparator																		0x78

#define Pulse_Width_Modulator_PWM_0													0x80
#define Pulse_Width_Modulator_PWM_1                         0x81

#define Quadrature_Encoder_Interface_QEI_0									0x88
#define Quadrature_Encoder_Interface_QEI_1                  0x89

#define EEPROM																							0xB0

#define General_Purpose_Timer_64_Bit_Timer_0 								0xB8
#define General_Purpose_Timer_64_Bit_Timer_1                0xB9
#define General_Purpose_Timer_64_Bit_Timer_2                0xBA
#define General_Purpose_Timer_64_Bit_Timer_3                0xBB
#define General_Purpose_Timer_64_Bit_Timer_4 								0xBC
#define General_Purpose_Timer_64_Bit_Timer_5 								0xBD


#endif
