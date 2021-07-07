#include "../std_types.h"
#include "../registers.h"
#include "../../MCAL/Timer/Timer.h"
#include<stdio.h>
#include "Timer_TestCases.h"
#define INVALIDE_TIMER_CH_ID 5
#define INVALIDE_TIMER_MODE 4
#define INFALIDE_TIMER_PRESCALER 9  
#define INFALIDE_TIMER_INT_MODE  9
#define TIMER0_TOV0_BIT 0x01
#define TIMER1_TOV1_BIT 0x04
#define TIMER2_TOV2_BIT 0x40

extern uint8_t u8_TimerInitFLag;
extern uint8_t gu8_PrescalerTimer0;
extern uint8_t gu8_PrescalerTimer1;
extern uint8_t gu8_PrescalerTimer2;
void TimerTOV(void){
	
}

/////////////////					Test cases prototype 					///////////////////////////


/// Inti Function //
static void Timer_Init_TestCase_0(void);
static void Timer_Init_TestCase_1(void);
static void Timer_Init_TestCase_2(void);
static void Timer_Init_TestCase_3(void);
static void Timer_Init_TestCase_4(void);
static void Timer_Init_TestCase_5(void);
static void Timer_Init_TestCase_6(void);
static void Timer_Init_TestCase_7(void);
static void Timer_Init_TestCase_8(void);
static void (*Timer_Init_TestCasesFun[9])(void)={Timer_Init_TestCase_0,Timer_Init_TestCase_1,Timer_Init_TestCase_2,Timer_Init_TestCase_3,Timer_Init_TestCase_4,Timer_Init_TestCase_5,Timer_Init_TestCase_6,Timer_Init_TestCase_7,Timer_Init_TestCase_8};



/// start Function // 

static void Timer_Start_TestCase_0(void);
static void Timer_Start_TestCase_1(void);
static void Timer_Start_TestCase_2(void);
static void Timer_Start_TestCase_3(void);
static void (*Timer_Start_TestCasesFun[4])(void)={Timer_Start_TestCase_0,Timer_Start_TestCase_1,Timer_Start_TestCase_2,Timer_Start_TestCase_3};





   /// Stop Funcion ///
static void Timer_Stop_TestCase_0(void);
static void Timer_Stop_TestCase_1(void);
static void Timer_Stop_TestCase_2(void);
static void (*Timer_Stop_TestCasesFun[3])(void)={Timer_Stop_TestCase_0,Timer_Stop_TestCase_1,Timer_Stop_TestCase_2};




 /// Get value Function /// 
static void Timer_GetValue_TestCase_0(void);
static void Timer_GetValue_TestCase_1(void);
static void Timer_GetValue_TestCase_2(void);
static void Timer_GetValue_TestCase_3(void);
static void (*Timer_GetValue_TestCasesFun[4])(void)={Timer_GetValue_TestCase_0,Timer_GetValue_TestCase_1,Timer_GetValue_TestCase_2,Timer_GetValue_TestCase_3};



  /// Set value ///

static void Timer_SetValue_TestCase_0(void);
static void Timer_SetValue_TestCase_1(void);
static void Timer_SetValue_TestCase_2(void);
static void Timer_SetValue_TestCase_3(void);
static void (*Timer_SetValue_TestCasesFun[4])(void)={Timer_SetValue_TestCase_0,Timer_SetValue_TestCase_1,Timer_SetValue_TestCase_2,Timer_SetValue_TestCase_3};

 /// Get status Function ///

static void Timer_GetStatus_TestCase_0(void);
static void Timer_GetStatus_TestCase_1(void);
static void Timer_GetStatus_TestCase_2(void);
static void Timer_GetStatus_TestCase_3(void);
static void (*Timer_GetStatus_TestCasesFun[4])(void)={Timer_GetStatus_TestCase_0,Timer_GetStatus_TestCase_1,Timer_GetStatus_TestCase_2,Timer_GetStatus_TestCase_3};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////// 		Test cases implementation ////////////////////////////////////////


/// Inti Function //
static void Timer_Init_TestCase_0(void){
	
	char ErrorStatus = 0;	
	printf("Test case 0: Passing NULL Pointer :");

	
	ErrorStatus=Timer_Init(NULL);
	
	if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR)
	
	printf(" PASS\n\n\n");
	
	else 
	
		printf(" Faild\n\n\n");
}
static void Timer_Init_TestCase_1(void){
	
	char ErrorStatus = 0;
	uint8_t u=0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0\n","FOR TIMER_CH_1\n ","FOR TIMER_CH_2\n","		INT_mode : ","		Polling_Mode : "};
	
	uint8_t  au8_ExpectedOuput[]={0x00,0x01,0x00,0x01,0x0000,0x04,0,0x0001,0x00,0x40,0,0x01};
	
	uint8_t * apu8_Register[]={&TCCR0,(uint8_t *)&TCCR1,&TCCR2,&TIMSK};
	uint8_t * apu8_Prescaler[]={&gu8_PrescalerTimer0,&gu8_PrescalerTimer1,&gu8_PrescalerTimer2};
	void(* apTimer_INT_Mode[2])(void)={TimerTOV,NULL};
	
	gstrTimerConfig_t  TimerConfig={TIMER_CH_0,TIMER_MODE,TIMER_PRESCALER_NO,TIMER_MODE_POOLING,NULL};
	
	printf("Test case 1: Passing valide argmement : \n");
	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{	
		u=4*TimerCH_ID;
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		for (uint8_t u8_Timer_INT_Modes =1;u8_Timer_INT_Modes<3;u8_Timer_INT_Modes++)
		{
			printf("%s",apu8_TestCaseName[3+u8_Timer_INT_Modes-1]);
			TimerConfig.u8_Timer_INT_Mode = u8_Timer_INT_Modes-1;
			TimerConfig.p_TOV_INT = apTimer_INT_Mode[u8_Timer_INT_Modes-1];
			ErrorStatus = Timer_Init(&TimerConfig);
			
			if(*apu8_Register[TimerCH_ID] == au8_ExpectedOuput[u] &&(*apu8_Register[3] == au8_ExpectedOuput[u+u8_Timer_INT_Modes])&&(au8_ExpectedOuput[u+3]==* apu8_Prescaler[TimerCH_ID]) )
			{

				if(ErrorStatus==E_OK)	
				{	
					printf(" PASS\n\n\n");
					
				}
			}
					
			else 
			{
				printf(" Faild \n\n\n");
			}		
		
			ErrorStatus = 0;
			u8_TimerInitFLag=0;
			
		}	
		*apu8_Register[3]=0;
	}
}	
static void Timer_Init_TestCase_2(void){
	
	char ErrorStatus = 0;	
	gstrTimerConfig_t  TimerConfig={TIMER_CH_1,TIMER_MODE,TIMER_PRESCALER_NO,TIMER_MODE_INT,NULL};
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	printf("Test case 2: Passing NULL Pointer to t CBF  (INT_MODE):\n\n");

	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		ErrorStatus=Timer_Init(&TimerConfig);
		
		if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR)
		
		printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild \n\n\n");
	}
}
static void Timer_Init_TestCase_3(void){
	
	char ErrorStatus = 0;

	printf("Test case 3: Passing invalide timer channel ID : ");

	gstrTimerConfig_t  TimerConfig={INVALIDE_TIMER_CH_ID,TIMER_MODE,TIMER_PRESCALER_NO,TIMER_MODE_POOLING,NULL};
	
		ErrorStatus=Timer_Init(&TimerConfig);
		
		if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL)
	
			printf(" PASS\n\n\n");
	
		else 
	
			printf(" Faild\n\n\n");
	}
static void Timer_Init_TestCase_4(void){
	
	char ErrorStatus = 0;	
	printf("Test case 4: Passing invalide timer mode  : \n\n"); 
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};


	gstrTimerConfig_t  TimerConfig={TIMER_CH_1,INVALIDE_TIMER_MODE,TIMER_PRESCALER_NO,TIMER_MODE_POOLING,NULL};
	
	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		ErrorStatus=Timer_Init(&TimerConfig);
	
		if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_Mode)
		
			printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  %d \n\n\n",ErrorStatus);
	 }
	
	
}
static void Timer_Init_TestCase_5(void){ 
	
	char ErrorStatus = 0;	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};

	printf("Test case 5: Passing invalide timer prescaler :\n\n");  

	gstrTimerConfig_t  TimerConfig={TIMER_CH_1,TIMER_MODE,INFALIDE_TIMER_PRESCALER,TIMER_MODE_POOLING,NULL};
	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		ErrorStatus=Timer_Init(&TimerConfig);
	
		if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler)
		
			printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  %d \n\n\n",ErrorStatus);
	}
	
	
		
	
}
static void Timer_Init_TestCase_6(void){
	
	char ErrorStatus = 0;	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};

	printf("Test case 6: Passing invalide timerINT mode : \n\n"); 

	gstrTimerConfig_t  TimerConfig={TIMER_CH_1,TIMER_MODE,TIMER_PRESCALER_NO,INFALIDE_TIMER_INT_MODE,NULL};
	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		ErrorStatus=Timer_Init(&TimerConfig);
		
		if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_INT_MODE)
		
			printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  %d \n\n\n",ErrorStatus);
	}
	
	
}
static void Timer_Init_TestCase_7(void){
	
	char ErrorStatus = 0;
	 u8_TimerInitFLag=0;
	 
	printf("Test case 7:Muiltiple Init. for smae timer channel : \n\n"); 
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	gstrTimerConfig_t  TimerConfig={TIMER_CH_1,TIMER_MODE,TIMER_PRESCALER_NO,TIMER_MODE_POOLING,NULL};
	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		Timer_Init(&TimerConfig);
		ErrorStatus=Timer_Init(&TimerConfig);
		
		if(ErrorStatus==TIMER_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT)
		
		printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  %d \n\n\n",ErrorStatus);
	}
}
static void Timer_Init_TestCase_8(void){
	
	char ErrorStatus = 0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	 u8_TimerInitFLag=0;
	 
	printf("Test case 8:Muiltiple Init. for different timer channel : \n\n"); 
	
	gstrTimerConfig_t  TimerConfig={TIMER_CH_1,TIMER_MODE,TIMER_PRESCALER_NO,TIMER_MODE_POOLING,NULL};
	for(uint8_t TimerCH_ID=0;TimerCH_ID<3;TimerCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		TimerConfig.u8_TimerCh = TimerCH_ID ;
		ErrorStatus=Timer_Init(&TimerConfig);
		
		if(ErrorStatus==E_OK)
		
		printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild \n\n\n");
	}
	
}
extern void Test_Timer_InilFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Timer INIT FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 9 ; Test_Case_Stage ++ )
	{
		Timer_Init_TestCasesFun[Test_Case_Stage]();
		
	}
}


/// start Function //   
static void Timer_Start_TestCase_0(void){
	
	char ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
	
	uint8_t u8_RegisterIndex=0;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	uint16_t  au8EnterValue[]={255,65535,255};
	
	uint8_t * apu8_Register[]={&TCCR0,&TCNT0,(uint8_t *)(&TCCR1),(uint8_t *)&TCNT1,&TCCR2,&TCNT2};

	gu8_PrescalerTimer0 = 0x01;
	
	gu8_PrescalerTimer1 = 0x0001;
	
	gu8_PrescalerTimer2 = 0x01;
	
	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
		u8_RegisterIndex = 2 * TimerCH_ID;
		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_Start(TimerCH_ID,au8EnterValue[TimerCH_ID]);
			
		if((* apu8_Register[u8_RegisterIndex]==0x01) && (* apu8_Register[u8_RegisterIndex+1]==0))
		{
			if(ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild \n\n\n");
		}
	}
static void Timer_Start_TestCase_1(void){
	
	char ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
		
	printf("Test case 1: Passing invalide timer channel : ");
		
	ErrorStatus=Timer_Start(INVALIDE_TIMER_CH_ID,255);
		
	if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
		}
static void Timer_Start_TestCase_2(void){
	
	uint8_t ErrorStatus = 0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	u8_TimerInitFLag = 0x07;
		
	printf("Test case 2: Passing invalide parametar : \n\n");
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID +=2) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		ErrorStatus=Timer_Start(TimerCH_ID,256);
			
		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR)
		
			printf(" PASS\n\n\n");

		
		else 
		
			printf(" Faild \n\n\n");
		}
}
static void Timer_Start_TestCase_3(void){
	
	uint8_t ErrorStatus = 0;
	u8_TimerInitFLag = 0;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	uint16_t  au8EnterValue[]={255,65535,255};
	printf("Test case 3: calling start without init :\n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_Start(TimerCH_ID,au8EnterValue[TimerCH_ID]);
			

		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}
extern void Test_Timer_StartFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Timer Start FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 4 ; Test_Case_Stage ++ )
	{
		Timer_Start_TestCasesFun[Test_Case_Stage]();
		
	}
}


/// Stop Funcion ///


static void Timer_Stop_TestCase_0(void){
	
	char ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
		
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	
	uint8_t * apu8_Register[]={&TCCR0,(uint8_t *)(&TCCR1),&TCCR2};

	TCCR0 = 0x01;
	
	TCCR1 = 0x0001;
	
	TCCR2 = 0x01;
	
	printf("Test case 0: Passing valide argument: \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_Stop(TimerCH_ID);
			
		if((* apu8_Register[TimerCH_ID]==0x00))
		{
			if(ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild \n\n\n");
		}
	}
static void Timer_Stop_TestCase_1(void){
	
	char ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
		
	printf("Test case 1: Passing invalide timer channel : ");
		
	ErrorStatus=Timer_Stop(INVALIDE_TIMER_CH_ID);
		
	if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
		}
static void Timer_Stop_TestCase_2(void){
	
	uint8_t ErrorStatus = 0;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	u8_TimerInitFLag = 0;

	
	printf("Test case 2: calling stop without init :\n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_Stop(TimerCH_ID);
			

		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}
extern void Test_Timer_StopFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Timer Stop FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 3 ; Test_Case_Stage ++ )
	{
		Timer_Stop_TestCasesFun[Test_Case_Stage]();
		
	}
}


 
/// Get value Function ///


static void Timer_GetValue_TestCase_0(void){
	
	uint8_t ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
	
	uint16_t u16_actualValue=0;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	TCNT0=55;
	TCNT1=55;
	TCNT2=55;
	

	
	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
	
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_GetValue(TimerCH_ID,&u16_actualValue);
			
		if(u16_actualValue == 55)
		{
			if(ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild \n\n\n");
		u16_actualValue=0;
	}
	}

static void Timer_GetValue_TestCase_1(void){
	
	char ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	printf("Test case 1: Passing NULL Pointer (value): \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
	
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_GetValue(TimerCH_ID,NULL);
			
		
			if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR  )
			
				printf(" PASS\n\n\n");
		
			
			else 
			
				printf(" Faild \n\n\n");
	
	}
	}

static void Timer_GetValue_TestCase_2(void){
	
	char ErrorStatus = 0;
	uint16_t u16_actualValue=0;
	
	u8_TimerInitFLag = 0x07;
		
	printf("Test case 2: Passing invalide timer channel : ");
		
	ErrorStatus=Timer_GetValue(INVALIDE_TIMER_CH_ID,& u16_actualValue);
		
	if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
		}

static void Timer_GetValue_TestCase_3(void){
	
	uint8_t ErrorStatus = 0;
	uint16_t u16_actualValue=0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	u8_TimerInitFLag = 0;

	
	printf("Test case 3: calling stop without init :\n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_GetValue(TimerCH_ID,& u16_actualValue);
			

		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}

extern void Test_Timer_GetValueFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Timer GetValue FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 4 ; Test_Case_Stage ++ )
	{
		Timer_GetValue_TestCasesFun[Test_Case_Stage]();
		
	}
}


/// Set value Function ///


static void Timer_SetValue_TestCase_0(void){
	
	uint8_t ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
	
	uint16_t u16_TestValue=55;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	uint8_t * apu8_Register[]={&TCNT0,(uint8_t *)&TCNT1,&TCNT2};

	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_SetValue(TimerCH_ID,u16_TestValue);
			
		if((* apu8_Register[TimerCH_ID]==55) )
		{
			if(ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild \n\n\n");
		}
	}

static void Timer_SetValue_TestCase_1(void){
		

	uint8_t ErrorStatus = 0;
	uint16_t u16_TestValue=55;
	
	u8_TimerInitFLag = 0x07;
		
	printf("Test case 1: Passing invalide timer channel : ");
		
	ErrorStatus=Timer_SetValue(INVALIDE_TIMER_CH_ID,u16_TestValue);
		
	if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
		}

static void Timer_SetValue_TestCase_2(void){
	
	uint8_t ErrorStatus = 0;
	uint16_t u16_TestValue=265;

	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	u8_TimerInitFLag = 0x07;
		
	printf("Test case 2: Passing invalide parametar : \n\n");
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID +=2) 
	{
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		ErrorStatus=Timer_SetValue(TimerCH_ID,u16_TestValue);
			
		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR)
		
			printf(" PASS\n\n\n");

		
		else 
		
			printf(" Faild \n\n\n");
		}
}

static void Timer_SetValue_TestCase_3(void){
	
	uint8_t ErrorStatus = 0;
	uint16_t u16_TestValue=55;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	u8_TimerInitFLag = 0;
	printf("Test case 3: calling start without init :\n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_SetValue(TimerCH_ID,u16_TestValue);
			

		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}

extern void Test_Timer_SetValueFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Timer SetValue FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 4 ; Test_Case_Stage ++ )
	{
		Timer_SetValue_TestCasesFun[Test_Case_Stage]();
		
	}
}

/// Get status Function ///

static void Timer_GetStatus_TestCase_0(void){
	
	uint8_t ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
	
	uint8_t u8_actualValue=0;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	uint8_t  apu8_Register[]={TIMER0_TOV0_BIT,TIMER1_TOV1_BIT,TIMER2_TOV2_BIT};
	TIFR=TIMER0_TOV0_BIT|TIMER1_TOV1_BIT|TIMER2_TOV2_BIT;
	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
	
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_GetStatus(TimerCH_ID,&u8_actualValue);
		if(u8_actualValue == apu8_Register[TimerCH_ID] )
		{
			if(ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild \n\n\n");
		u8_actualValue=0;
	}
	}

static void Timer_GetStatus_TestCase_1(void){
	
	uint8_t ErrorStatus = 0;
	
	uint8_t u8_actualValue=0;

	u8_TimerInitFLag = 0x07;
		
	printf("Test case 1: Passing invalide timer channel : ");
		
	ErrorStatus=Timer_GetStatus(INVALIDE_TIMER_CH_ID,&u8_actualValue);
		
	if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_INVALIDE_TIMER_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
		}

static void Timer_GetStatus_TestCase_2(void){
	
	char ErrorStatus = 0;
	
	u8_TimerInitFLag = 0x07;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	
	printf("Test case 2: Passing NULL Pointer (value): \n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{
	
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_GetStatus(TimerCH_ID,NULL);
			
		
			if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_NULL_PTR  )
			
				printf(" PASS\n\n\n");
		
			
			else 
			
				printf(" Faild \n\n\n");
	
	}
	}

static void Timer_GetStatus_TestCase_3(void){
	
	uint8_t ErrorStatus = 0;
	uint8_t u8_actualValue=0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_0 : ","FOR TIMER_CH_1 : ","FOR TIMER_CH_2 : "};
	u8_TimerInitFLag = 0;

	
	printf("Test case 3: calling GetStatus without init :\n\n");
	
	for(uint8_t TimerCH_ID = 0;TimerCH_ID < 3;TimerCH_ID ++) 
	{		
		printf("%s",apu8_TestCaseName[TimerCH_ID]);
		
		ErrorStatus=Timer_GetStatus(TimerCH_ID,&u8_actualValue);
			

		if(ErrorStatus == TIMER_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_TIMER )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}

extern void Test_Timer_GetStatusFun(void){ 
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Timer GetStatus FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 4 ; Test_Case_Stage ++ )
	{
		Timer_GetStatus_TestCasesFun[Test_Case_Stage]();
		
	}
}











