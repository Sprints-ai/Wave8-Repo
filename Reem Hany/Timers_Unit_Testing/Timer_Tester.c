#include "Timer_Tester.h"

int i=0,TimerChannels[]={0,1,2,3};
int TimerCounts[]={0,150,255,1024};

Timer_cfg_s ST_Timer_init_valid_test[]={
{TIMER_CH0, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},

{TIMER_CH0, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH1, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},

{TIMER_CH0, TIMER_MODE,           TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH0, COUNTER_RISING_MODE,  TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH0, COUNTER_FALLING_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},


{TIMER_CH0, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH0, TIMER_MODE, COUNTER_RISING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH0, TIMER_MODE, COUNTER_FALLING_MODE ,TIMER_PRESCALER_NO},

{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_NO_CLOCK},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_8},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_32},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_64},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_128},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_256},
{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_1024},


};

Timer_cfg_s ST_Timer_init_unvalid_test[]={
NULL,

{3, TIMER_MODE, TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},



{TIMER_CH0, 3,           TIMER_POLLING_MODE ,TIMER_PRESCALER_NO},



{TIMER_CH0, TIMER_MODE, 3 ,TIMER_PRESCALER_NO},


{TIMER_CH2, TIMER_MODE, TIMER_POLLING_MODE ,8},

};





void Testing_Timer_Init(){

int index = 0;

     /********************Testing timer Init ****************************/

    printf("\n.................Check on valid cases.................\n\n");
    printf("\nCheck on Not NULL pointer.................\n\n");
for(index=0;index<18;index++)
{

    printf("Test Case NO# %d: ",(index+1));
    if(Timer_Init(&ST_Timer_init_valid_test[index]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

    if(index==0)
     printf("\nCheck on Timer Channels.................\n\n");
     if(index==3)
     printf("\nCheck on Timer Mode.................\n\n");
    if(index==6)
     printf("\nCheck on Timer interrupt.................\n\n");
    if(index==9)
     printf("\nCheck on Timer prescaler.................\n\n");


}




   printf("\n.................Check on unvalid cases.................\n\n");
    printf("\nCheck on NULL pointer.................\n\n");
for(index=0;index<5;index++)
{

    printf("Test Case NO# %d: ",(index+1));
    if(Timer_Init(&ST_Timer_init_unvalid_test[index]) == 0){
        printf("Failed\n");
    }
    else{
        printf("Passed\n");
    }

    if(index==0)
     printf("\nCheck on Timer Channels.................\n\n");
     if(index==1)
     printf("\nCheck on Timer Mode.................\n\n");
    if(index==2)
     printf("\nCheck on Timer interrupt.................\n\n");
    if(index==3)
     printf("\nCheck on Timer prescaler.................\n\n");


}

printf("\n\n");
}



void Testing_TimerStart_TimerChannels(){
     /********************Testing timer start****************************/
    /********************Check on Timer Channels************************/

    printf("\nCheck on Timer Channels.................\n\n");

    printf("Test Case NO#1: ");
    if(Timer_Start(TimerChannels[0],0) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

    printf("Test Case NO#2: ");
  //  printf("Expected Output: %d\n",0);
    //printf("Your is Output: %d\n",Timer_Start(TimerChannels[0],0));
    if(Timer_Start(TimerChannels[1],0) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

    printf("Test Case NO#3: ");
  //  printf("Expected Output: %d\n",0);
    //printf("Your is Output: %d\n",Timer_Start(TimerChannels[0],0));
    if(Timer_Start(TimerChannels[2],0) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#4: ");
  //  printf("Expected Output: %d\n",0);
    //printf("Your is Output: %d\n",Timer_Start(TimerChannels[0],0));
    if(Timer_Start(TimerChannels[3],0) == 1){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

}

void Testing_TimerStart_TimerCounts(){
    printf("\nCheck on Timer Channels.................\n\n");
    /************Timer 0***********************/
    printf("Test Case NO#1: ");
    if(Timer_Start(TimerChannels[0],TimerCounts[0]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#2: ");
    if(Timer_Start(TimerChannels[0],TimerCounts[1]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#3: ");
    if(Timer_Start(TimerChannels[0],TimerCounts[2]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#4: ");
    if(Timer_Start(TimerChannels[0],TimerCounts[3]) == 1){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }




    /************Timer 1***********************/
     printf("Test Case NO#5: ");
    if(Timer_Start(TimerChannels[2],TimerCounts[0]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#6: ");
    if(Timer_Start(TimerChannels[1],TimerCounts[1]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#7: ");
    if(Timer_Start(TimerChannels[1],TimerCounts[2]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#8: ");
    if(Timer_Start(TimerChannels[1],TimerCounts[3]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

    /************Timer 2***********************/
     printf("Test Case NO#9: ");
    if(Timer_Start(TimerChannels[2],TimerCounts[0]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#10: ");
    if(Timer_Start(TimerChannels[2],TimerCounts[1]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#11: ");
    if(Timer_Start(TimerChannels[2],TimerCounts[2]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#12: ");
    if(Timer_Start(TimerChannels[2],TimerCounts[3]) == 1){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
}

void Testing_TimerStop_NoOfChannels(){
     /********************Testing timer start****************************/
    /********************Check on Timer Channels************************/

    printf("\nCheck on Timer Channels.................\n\n");
    printf("Test Case NO#1: ");
  //  printf("Expected Output: %d\n",0);
    //printf("Your is Output: %d\n",Timer_Start(TimerChannels[0],0));
    if(Timer_Stop(TimerChannels[0]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

    printf("Test Case NO#2: ");
    if(Timer_Stop(TimerChannels[1]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

    printf("Test Case NO#3: ");
    if(Timer_Stop(TimerChannels[2]) == 0){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }
    printf("Test Case NO#4: ");
    if(Timer_Stop(TimerChannels[3]) == 1){
        printf("Passed\n");
    }
    else{
        printf("Failed\n");
    }

}



 void Timer_GetValue_Test()
{

    uint16_t Timer_Value=0;
    uint16_t *PTimer_Value;
    PTimer_Value=NULL;//&Timer_Value;
    uint8_t Ret_value=8;


    printf("First test case is to insert a NULL Pointer\n ");
    /*NOTE THAT:this case may cause the program to crash if you ant to check other cases you have to hash the line below*/
    Ret_value=Timer_GetValue(TIMER_0, PTimer_Value);
    if(Ret_value==ZERO)
    {
        printf("Test Case #1 PASSED\n ");
    }
    else
    {
        printf("Test Case #1 NOT PASSED \n");
    }

    printf("\nSecond test case is to insert a non NULL Pointer\n ");
    PTimer_Value=&Timer_Value;
    Ret_value=Timer_GetValue(TIMER_0, &Timer_Value);
    if(Ret_value==0)
    {
        printf("Test Case #2 PASSED\n ");
    }
    else
    {
        printf("Test Case #2 NOT PASSED \n");
    }
    printf("\nThird test case is to insert an invalid Channel number\n ");
    Ret_value=Timer_GetValue(4, &Timer_Value);
    if(Ret_value==1)
    {
        printf("Test Case #3 PASSED\n ");
    }
    else
    {
        printf("Test Case #3 NOT PASSED \n");
    }

    printf("\nFourth test case is to insert a valid Channel number\n ");
    Ret_value=Timer_GetValue(TIMER_1, &Timer_Value);
    if(Ret_value==0)
    {
        printf("Test Case #4 PASSED\n ");
    }
    else
    {
        printf("Test Case #4 NOT PASSED \n");
    }


}
void Timer_GetStatus_Test()
{
    uint16_t Timer_Value=0;
    uint16_t *PTimer_Value;
    PTimer_Value=NULL;//&Timer_Value;
    uint8_t Ret_value=8;

    printf("\nFirst test case is to insert a NULL Pointer\n ");
    /*NOTE THAT:this case may cause the program to crash if you ant to check other cases you have to hash the line below*/
    Ret_value=Timer_GetStatus(TIMER_0, PTimer_Value);
    if(Ret_value==ZERO)
    {
        printf("Test Case #1 PASSED\n ");
    }
    else
    {
        printf("Test Case #1 NOT PASSED \n");
    }

    printf("\nSecond test case is to insert a non NULL Pointer\n ");
    PTimer_Value=&Timer_Value;
    Ret_value=Timer_GetStatus(TIMER_0, &Timer_Value);
    if(Ret_value==0)
    {
        printf("Test Case #2 PASSED\n ");
    }
    else
    {
        printf("Test Case #2 NOT PASSED \n");
    }
    printf("\nThird test case is to insert an invalid Channel number\n ");
    Ret_value=Timer_GetStatus(4, &Timer_Value);
    if(Ret_value==1)
    {
        printf("Test Case #3 PASSED\n ");
    }
    else
    {
        printf("Test Case #3 NOT PASSED \n");
    }

    printf("\nFourth test case is to insert a valid Channel number\n ");
    Ret_value=Timer_GetStatus(TIMER_1, &Timer_Value);
    if(Ret_value==0)
    {
        printf("Test Case #4 PASSED\n ");
    }
    else
    {
        printf("Test Case #4 NOT PASSED \n");
    }


}



