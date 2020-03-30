/*
 * ICU_Cfg.h
 *
 * Created: 2/18/2020 9:58:09 AM
 *  Author: Reem
 */ 


#ifndef SWICU_CFG_H_
#define SWICU_CFG_H_

/********************************/
/*         Defines              */
/********************************/

#define	ICU_TIM_0              0
#define	ICU_TIM_1              1
#define	ICU_TIM_2              2

#define	ICU_DE_INT_0           0
#define	ICU_DE_INT_1           1
#define	ICU_DE_INT_2           2

/********************************/
/*  Register Bits definitions   */
/********************************/

#define MCUCSR_INT2_BIT		   6
#define GICR_INT2_BIT          5

/********************************/
/*      Configurations          */
/********************************/

#define SW_ICU_TIMER           ICU_TIM_0
#define DEI_ICU                ICU_DE_INT_2

#define DEI_ICU_PORT           GPIOB
#define DEI_ICU_PIN            BIT2




#endif /* SWICU_CFG_H_ */