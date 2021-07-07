/*
 * BCM_test.h
 *
 * Created: 3/24/2020 4:47:54 PM
 *  Author: mahmo
 */ 


#ifndef BCM_TEST_H_
#define BCM_TEST_H_
#include "../../ServiceLayer/BCM/BCM.h"
#include "../Tester/stubFunction.h"
#include "../Tester/tester.h"
/*

ERROR_STATUS BCM_init(gstr_BCM_cfg_t* bcm_cfg );
ERROR_STATUS BCM_setup(gstr_BCM_Task_cfg_t* str_BCM_TaskCfg);
ERROR_STATUS BCM_RX_dispatcher();
ERROR_STATUS BCM_TX_dispatcher();
*/

void BCM_Module_Test(void);
void BCM_init_test(void);
void BCM_setup_test(void);
void BCM_RX_dispatcher_test(void);
void BCM_TX_dispatcher_test(void);



#endif /* BCM_TEST_H_ */