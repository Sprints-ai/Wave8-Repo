#include "Questions.h"

uint8 st1[]="Q1: 1+1=2 ? ";
uint8 st2[]="Q2  1+2=3 ? ";
uint8 st3[]="Q3  1+3=7 ? ";
uint8 st4[]="Q4  1+4=0 ? ";

uint8  Yes_res_str[]="n#Yes:";
uint8  No_res_str[]=" n#No:";
uint8 report_res[]="n#of Corct Ans:";

volatile uint8 Count_Yes=0;
volatile uint8 Count_No=0;

volatile uint8 Semaphore=1;

volatile uint8 index=0;

uint8 count_res=0;
uint8 user_ans[4];
	 
void __vector_2(void)
{
	user_ans[index]=YES;
	Count_Yes++;
	Semaphore++;
	index++;
}


void __vector_3(void)
{
	user_ans[index]=NO;
	Count_No++;
	Semaphore++;
	index++;
}


void Question_1(void){
	if(Semaphore==1){
		LCD_displayString(&st1);
		SOS_Delete_Task(Question_1);
	}
	
}

void Question_2(void){
	if(Semaphore==2){
		LCD_clearScreen();
		LCD_displayString(&st2);
		SOS_Delete_Task(Question_2);
	}
}

void Question_3(void){
	if(Semaphore==3){
		LCD_clearScreen();
		LCD_displayString(&st3);
		SOS_Delete_Task(Question_3);
	}
}
void Question_4(void){
	if(Semaphore==4){
		LCD_clearScreen();
		LCD_displayString(&st4);
		SOS_Delete_Task(Question_4);
	}
}
void Result(void){
	if(Semaphore==5){
		uint8 arr[4]={YES,YES,NO,NO};
		LCD_clearScreen();
		LCD_displayString(&Yes_res_str);
		LCD_displayInteger(Count_Yes);
		LCD_displayString(&No_res_str);
		LCD_displayInteger(Count_No);
		LCD_goToRowColumn(1,0);
	   LCD_displayString(&report_res);
		for(uint8 i=0;i<4;i++){
			if(arr[i]==user_ans[i]){
				count_res++;
			}
		}
		LCD_displayInteger(count_res);
		SOS_Delete_Task(Result);
	}
}