

#ifndef E15_ARM_REPO_CONFIG_NVIC_CFG_H_
#define E15_ARM_REPO_CONFIG_NVIC_CFG_H_

#include "../utils/Std_Types.h"

#define NVIC_PRI_GRP_XXX            4
#define NVIC_PRI_GRP_XXY            5
#define NVIC_PRI_GRP_XYY            6
#define NVIC_PRI_GRP_YYY            7

#define NVIC_CHOSEN_GRP_SUB         NVIC_PRI_GRP_XYY

/*TODO Configure Number of Enabled Interrupts*/
#define NVIC_NUM_OF_ENABLED_INT                     5


#endif /* E15_ARM_REPO_CONFIG_NVIC_CFG_H_ */
