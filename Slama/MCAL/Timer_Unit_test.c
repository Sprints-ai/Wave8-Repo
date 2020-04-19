
#include <stdio.h>
#include "timer.h"

void timer_init_test()
{
  /*1st test case:
  *Descript: Everything done as expected
  *Expected output : E_OK
  *Output : E_OK
  */

    Timer_cfg_s st_timer_init;
    st_timer_init.Timer_Cbk_ptr = NULL;
    st_timer_init.Timer_CH_NO = TIMER_CH1;
    st_timer_init.Timer_INT_Mode = TIMER_POLLING_MODE;
    st_timer_init.Timer_Mode = TIMER_MODE;
    st_timer_init.Timer_Prescaler = TIMER_NO_CLOCK;

    
    printf("%d",Timer_Init(&st_timer_init));

    /*2nd test case:
    *Descript : Enter any wrong config value
    *expected output : ERROR
    *output: ERROR
    */

   st_timer_init.Timer_CH_NO = 10;
   printf("%d",Timer_Init(&st_timer_init));

}

void timer_start_test()
{
    Timer_cfg_s st_timer_init;
    st_timer_init.Timer_Cbk_ptr = NULL;
    st_timer_init.Timer_CH_NO = TIMER_CH1;
    st_timer_init.Timer_INT_Mode = TIMER_POLLING_MODE;
    st_timer_init.Timer_Mode = TIMER_MODE;
    st_timer_init.Timer_Prescaler = TIMER_NO_CLOCK;

    /*1st test:
    *Description: Everything done as expected
    *Expected Output: E_OK
    *Output : E_OK
    */

    Timer_Init(&st_timer_init);
    printf("%d",Timer_Start(TIMER_CH1,100));

    /*2nd test:
    *Description: starting without init
    *Expected Output: ERROR_TIMER_NOT_START
    *Output : ERROR_TIMER_NOT_START
    */

    printf("%d",Timer_Start(TIMER_CH1,100));

    /*3rd Test:
    *Description: Start with wrong values
    *Expected out :Error Wrong Value
    *Output : ERROR_INVALID_VALUES
    */

   st_timer_init.Timer_CH_NO = TIMER_CH0;
   Timer_Init(&st_timer_init);
   printf("%d",Timer_Start(TIMER_CH0,700));

   /*4th test:
   *Description: Inserting invalid channel number
   *Expected out :ERROR_INVALID_CHANNEL
   *Output: Invalid channel or not init channel
   */

    printf("%d",Timer_Start(4,700));

}

void timer_stop_test()
{
    Timer_cfg_s st_timer_init;
    st_timer_init.Timer_Cbk_ptr = NULL;
    st_timer_init.Timer_CH_NO = TIMER_CH1;
    st_timer_init.Timer_INT_Mode = TIMER_POLLING_MODE;
    st_timer_init.Timer_Mode = TIMER_MODE;
    st_timer_init.Timer_Prescaler = TIMER_NO_CLOCK;

    /*1st test:
    *Description: Everything done as expected
    *Expected Output: E_OK
    *Output : E_OK
    */

   Timer_Init(&st_timer_init);

   printf("%d",Timer_Stop(TIMER_CH1));

   /*2nd test:
    *Description: inseting not init or wrong channel
    *Expected Output: ERROR
    *Output : ERROR
    */

   printf("%d",Timer_Stop(TIMER_CH0));

}
int main()
{
    timer_stop_test();

    return 0;
}