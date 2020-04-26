#include <stdio.h>
#include <stdlib.h>
#include "Mock_Timer.h"

uint8_t test_Scinarios_INIT(uint8_t test_Case_Num);
int main(void){
	printf( "%d\n",test_Scinarios_INIT(1));
	printf( "%d\n",test_Scinarios_INIT(2));
	printf( "%d\n",test_Scinarios_INIT(3));
	printf( "%d\n",test_Scinarios_INIT(4));
	printf( "%d\n",test_Scinarios_INIT(5));
	printf( "%d\n",test_Scinarios_INIT(6));
	printf( "%d\n",test_Scinarios_INIT(7));
	/**************************************************************************************/
	printf( "%d\n",test_Scinarios_INIT(8));
	printf( "%d\n",test_Scinarios_INIT(9));
	printf( "%d\n",test_Scinarios_INIT(10));
	printf( "%d\n",test_Scinarios_INIT(11));
	printf( "%d\n",test_Scinarios_INIT(12));
	/******************************************************************************************/
	printf( "%d\n",test_Scinarios_INIT(13));
	printf( "%d\n",test_Scinarios_INIT(14));
	printf( "%d\n",test_Scinarios_INIT(15));
	printf( "%d\n",test_Scinarios_INIT(16));
	printf( "%d\n",test_Scinarios_INIT(17));
	/***************************************************************************************/
	printf( "%d\n",test_Scinarios_INIT(18));
	
	return 0;
}

uint8_t test_Scinarios_INIT(uint8_t test_Case_Num){
uint8_t ret=0;
switch(test_Case_Num){
	case 1:
	ret=Timer_Init(&Timer_Configuration2);
	ret=Timer_Start(TIMER_CH2,5);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	break;
	case 2:	
	ret=Timer_Init(&testcase2);
	ret=Timer_Start(TIMER_CH2,5);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	printf("TCNT2=%d     ",TCNT2);
	break;
	case 3:
	ret=Timer_Init(&testcase3);
	ret=Timer_Start(TIMER_CH2,5);
	printf("TCNT2=%d     ",TCNT2);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	break;
	case 4:
	ret=Timer_Init(&testcase4);
	ret=Timer_Start(TIMER_CH2,5);
	printf("TCNT2=%d     ",TCNT2);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	break;
	case 5:
	ret=Timer_Init(&testcase5);
	ret=Timer_Start(TIMER_CH2,5);printf("TCNT2=%d     ",TCNT2);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	break;
	case 6:
	ret=Timer_Init(&testcase6);
	ret=Timer_Start(TIMER_CH2,5);printf("TCNT2=%d     ",TCNT2);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	break;
	case 7:
	ret=Timer_Init(&testcase7);
	ret=Timer_Start(TIMER_CH2,5);
	printf("TCNT2=%d     ",TCNT2);
	printf("TCCR2=%d   ",TCCR2);printf("TIMSK=%#X   ",TIMSK);printf("ASSR=%d\n\n",ASSR);
	break;
	case 8:
	ret=Timer_Init(&testcase8);
	ret=Timer_Start(TIMER_CH0,5);
	printf("TCNT0=%d     ",TCNT0);
	printf("TCCR0=%d   ",TCCR0);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 9:
	ret=Timer_Init(&testcase9);
	ret=Timer_Start(TIMER_CH0,5);
		printf("TCNT0=%d     ",TCNT0);
	printf("TCCR0=%d   ",TCCR0);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 10:
	ret=Timer_Init(&testcase10);
	ret=Timer_Start(TIMER_CH0,5);
		printf("TCNT0=%d     ",TCNT0);
	printf("TCCR0=%d   ",TCCR0);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 11:
	ret=Timer_Init(&testcase11);
	ret=Timer_Start(TIMER_CH0,5);
		printf("TCNT0=%d     ",TCNT0);
	printf("TCCR0=%d   ",TCCR0);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 12:
	ret=Timer_Init(&testcase12);
	ret=Timer_Start(TIMER_CH0,5);
		printf("TCNT0=%d     ",TCNT0);
	printf("TCCR0=%d   ",TCCR0);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 13:
	ret=Timer_Init(&testcase13);
	ret=Timer_Start(TIMER_CH1,5);
	printf("TCNT1=%d     ",TCNT1);
	printf("TCCR1=%d   ",TCCR1);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 14:
	ret=Timer_Init(&testcase14);
	ret=Timer_Start(TIMER_CH1,5);
	printf("TCNT1=%d     ",TCNT1);
	printf("TCCR1=%d   ",TCCR1);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 15:
	ret=Timer_Init(&testcase15);
	ret=Timer_Start(TIMER_CH1,5);
	printf("TCNT1=%d     ",TCNT1);
	printf("TCCR1=%d   ",TCCR1);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 16:
	ret=Timer_Init(&testcase16);
	ret=Timer_Start(TIMER_CH1,5);
	printf("TCNT1=%d     ",TCNT1);
	printf("TCCR1=%d   ",TCCR1);printf("TIMSK=%#X\n\n",TIMSK);
	break;
	case 17:
	ret=Timer_Init(&testcase17);
	ret=Timer_Start(TIMER_CH1,5);
	printf("TCNT1=%d     ",TCNT1);
	printf("TCCR1=%d   ",TCCR1);printf("TIMSK=%#X\n\n",TIMSK);
	break;	
	case 18:
	ret=Timer_Init(0);
	break;
}
return ret;
}