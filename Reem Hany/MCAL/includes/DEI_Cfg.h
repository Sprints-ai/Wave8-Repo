/*
 * DEI_Cfg.h
 *
 * Created: 3/29/2020 9:03:10 PM
 *  Author: Reem
 */ 


#ifndef DEI_CFG_H_
#define DEI_CFG_H_


/********************************/
/*  Register Bits definitions   */
/********************************/

#define MCUCSR_INT2_BIT		   6

#define MCUCR_INT0A_BIT        0
#define MCUCR_INT0B_BIT        1

#define MCUCR_INT1A_BIT        2
#define MCUCR_INT1B_BIT        3

#define GICR_INT0_BIT          6
#define GICR_INT1_BIT          7
#define GICR_INT2_BIT          5

/********************************/
/*      Configurations          */
/********************************/
#define DEI_INT0_PORT      GPIOD
#define DEI_INT0_PIN       BIT2

#define DEI_INT1_PORT      GPIOD
#define DEI_INT1_PIN       BIT3

#define DEI_INT2_PORT      GPIOB
#define DEI_INT2_PIN       BIT2


#endif /* DEI_CFG_H_ */