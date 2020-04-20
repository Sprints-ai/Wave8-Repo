
#include <stdio.h>
#include "ICU.h"

#define ICU_JUNK_MODE   (7)

/*ICU_Init API Test*/
void ICU_init_test()
{

    Icu_cfg_s st_Icu_init;
    st_Icu_init.ICU_Ch_No = ICU_CH2;
    st_Icu_init.ICU_Ch_Timer = ICU_TIMER_CH0;

    /*1st test:
    *Description: Everything done as expected
    *Expected Output : E_OK
    *Output : E_OK
    */

    printf("%d",Icu_Init(&st_Icu_init));

    /*2ndt test:
    *Description: inserting unimplemented channel or wrong one
    *Expected Output : ERROR
    *Output : ERROR
    */

    st_Icu_init.ICU_Ch_No = ICU_CH1;
    printf("%d",Icu_Init(&st_Icu_init));

    /*3rd test:
    *Description: Multiple init
    *Expected output:Errror
    *Output: Error
    */

    printf("%d",Icu_Init(&st_Icu_init));
    printf("%d",Icu_Init(&st_Icu_init));

    /*4th test
    *Description: Inserting wrong timer_channel
    *Expected out : Error
    *Output: Error
    */

   st_Icu_init.ICU_Ch_Timer = 8;

   printf("%d",Icu_Init(&st_Icu_init));
   
}

/*Icu_Read API Test*/
void ICU_Read_Test()
{
    uint32_t au32_IcuTestVar = 200;
    Icu_cfg_s st_Icu_init;
    st_Icu_init.ICU_Ch_No = ICU_CH2;
    st_Icu_init.ICU_Ch_Timer = ICU_TIMER_CH0;

    /*first test case
    *Description : Everything done as expected
    *Expected Out : E_OK
    *Output: E_OK
    */

    Icu_Init(&st_Icu_init);
    printf("%d",Icu_ReadTime(ICU_CH2,ICU_FALE_TO_RISE,&au32_IcuTestVar));

    /*2nd test case
    *Description : wrong init
    *Expected Out : ERROR
    *Output: ERROR not initialized
    */

   st_Icu_init.ICU_Ch_No = ICU_CH0;

    Icu_Init(&st_Icu_init);
    printf("%d",Icu_ReadTime(ICU_CH2,ICU_FALE_TO_RISE,&au32_IcuTestVar));

   /*3rd test case
    *Description : wrong mode
    *Expected Out : ERROR
    *Output: ERROR
    */

   Icu_Init(&st_Icu_init);
   printf("%d",Icu_ReadTime(ICU_CH2,ICU_JUNK_MODE,&au32_IcuTestVar));

}


int main()
{
    
    ICU_Read_Test();
    return 0;
}