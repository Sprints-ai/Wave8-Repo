#include "../std_types.h"
#include "../registers.h"
#include "../../MCAL/PWM/PWM.h"
#include "PWM_TestCases.h"

#include <stdio.h>



#define OCR1A_NON_INVERTING_MODE (0x80)
#define OCR1B_NON_INVERTING_MODE (0x20)
#define PHASE_CORRECT_WG11_00BITS  (0x02)
#define PHASE_CORRECT_WG12_13BITS  (0x10)
#define WRITE_TO_TCCRA  (0xf3);
#define STOP_OCR1A   (0x3F)
#define STOP_OCR1B   (0xCF)
#define BIT4 0x10
#define BIT5 0x20
#define EXPECTED_PRESCALER_OUTPUT 2
#define INVALIDE_PWM_CH_ID 5
#define  ONE 1
#define  INFALIDE_PWM_PRESCALER 7

#define FRE_100_ICR_ (78)
#define TIMEr1_PRESCALER_1024 (0x0005)

extern uint8_t u8_PWM_CH_InitStatus;
extern uint8_t u8_PWM_CH1A_Prescaler;
extern uint8_t u8_PWM_CH1B_Prescaler;


static void PWM_Init_TestCase_0(void);
static void PWM_Init_TestCase_1(void);
static void PWM_Init_TestCase_2(void);
static void PWM_Init_TestCase_3(void);
static void PWM_Init_TestCase_4(void);
static void PWM_Init_TestCase_5(void);
static void (*PWM_Init_TestCasesFun[6])(void)={PWM_Init_TestCase_0,PWM_Init_TestCase_1,PWM_Init_TestCase_2,PWM_Init_TestCase_3,PWM_Init_TestCase_4,PWM_Init_TestCase_5};
extern void Test_PWM_InilFun(void);	


static void PWM_Start_TestCase_0(void);
static void PWM_Start_TestCase_1(void);

static void PWM_Start_TestCase_2(void);
static void PWM_Start_TestCase_3(void);
static void PWM_Start_TestCase_4(void);
static void (*PWM_Start_TestCasesFun[5])(void)={PWM_Start_TestCase_0,PWM_Start_TestCase_1,PWM_Start_TestCase_2,PWM_Start_TestCase_3,PWM_Start_TestCase_4};





static void PWM_Update_TestCase_0(void);
static void PWM_Update_TestCase_1(void);
static void PWM_Update_TestCase_2(void);
static void PWM_Update_TestCase_3(void);
static void PWM_Update_TestCase_4(void);
static void (*PWM_Update_TestCasesFun[5])(void)={PWM_Update_TestCase_0,PWM_Update_TestCase_1,PWM_Update_TestCase_2,PWM_Update_TestCase_3,PWM_Update_TestCase_4};


static void PWM_Stop_TestCase_0(void);
static void PWM_Stop_TestCase_1(void);
static void PWM_Stop_TestCase_2(void);
static void (*PWM_Stop_TestCasesFun[3])(void)={PWM_Stop_TestCase_0,PWM_Stop_TestCase_1,PWM_Stop_TestCase_2};

//// Test cases implementation  


static void PWM_Init_TestCase_0(void){
	
	uint8_t u8_ErrorStatus = 0;	
	printf("Test case 0: Passing NULL Pointer :");

	
	u8_ErrorStatus=Pwm_Init(NULL);
	
	if(u8_ErrorStatus== PWM_MODULE_ERROR_NUMBER + ERROR_NULL_PTR)
	
	printf(" PASS\n\n\n");
	
	else 
	
		printf(" Faild\n\n\n");
}

static void PWM_Init_TestCase_1(void){
	
	uint8_t u8_ErrorStatus = 0;
	uint8_t u=0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	uint8_t u8_RegisterIndex=0;
	uint8_t  au8_ExpectedOuput[]={OCR1A_NON_INVERTING_MODE| PHASE_CORRECT_WG11_00BITS,PHASE_CORRECT_WG12_13BITS,BIT5,OCR1B_NON_INVERTING_MODE| PHASE_CORRECT_WG11_00BITS,PHASE_CORRECT_WG12_13BITS,BIT4};
	
	uint8_t * apu8_Register[]={&TCCR1A,&TCCR1B,&PORTD_DIR};
	uint8_t * apu8_Prescaler[]={&u8_PWM_CH1A_Prescaler,&u8_PWM_CH1B_Prescaler};
	
	gstr_Pwm_Cfg_t str_PwmCfg={PWM_CH1A,PWM_PRESCALER_8};
	u8_PWM_CH_InitStatus=0;
	printf("Test case 1: Passing valide argmement : \n\n");
	
	for(uint8_t PWMCH_ID=1;PWMCH_ID<3;PWMCH_ID++) 
	{	
		u=3*(PWMCH_ID-ONE);
		str_PwmCfg.u8_Channel = PWMCH_ID ;
		printf("%s",apu8_TestCaseName[PWMCH_ID-1]);
		
		u8_ErrorStatus=Pwm_Init(&str_PwmCfg);
		
		if((*apu8_Register[u8_RegisterIndex] == au8_ExpectedOuput[u] )&&(*apu8_Register[u8_RegisterIndex+1] == au8_ExpectedOuput[u+1]) &&(*apu8_Register[u8_RegisterIndex+2] == au8_ExpectedOuput[u+2]) &&(* apu8_Prescaler[PWMCH_ID-1] == EXPECTED_PRESCALER_OUTPUT) )
		{

			if(u8_ErrorStatus==E_OK)	
			{	
				printf(" PASS\n\n\n");
				
			}
			}
					
			else 
			{
				printf(" Faild %d\n\n\n",u8_ErrorStatus);
			}		
		
			u8_ErrorStatus = 0;
			TCCR1A = 0;
			TCCR1B = 0;
			PORTD_DIR = 0;
			u8_PWM_CH_InitStatus=0;
			
		}	
		
	}

static void PWM_Init_TestCase_2(void){
	
	uint8_t u8_ErrorStatus = 0;

	printf("Test case 2: Passing invalide PWM channel ID : ");

	gstr_Pwm_Cfg_t str_PwmCfg={INVALIDE_PWM_CH_ID,PWM_PRESCALER_8}; 
	
		u8_ErrorStatus=Pwm_Init(&str_PwmCfg);
		
		if(u8_ErrorStatus==PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL)
	
			printf(" PASS\n\n\n");
	
		else 
	
			printf(" Faild\n\n\n");
	}

static void PWM_Init_TestCase_3(void){ 
	
	uint8_t u8_ErrorStatus = 0;	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	 u8_PWM_CH_InitStatus = 0;
	printf("Test case 3: Passing invalide PWM prescaler :\n\n");  

	gstr_Pwm_Cfg_t str_PwmCfg={PWM_CH1A,INFALIDE_PWM_PRESCALER};  
	
		
	for(uint8_t PWMCH_ID=1;PWMCH_ID<3;PWMCH_ID++) 
	{
		printf("%s",apu8_TestCaseName[PWMCH_ID-1]);
		str_PwmCfg.u8_Channel = PWMCH_ID ;
		u8_ErrorStatus=Pwm_Init(&str_PwmCfg);
	
		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_Prescaler)
		
			printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  \n\n\n");
	}
}

static void PWM_Init_TestCase_4(void){
	
	uint8_t u8_ErrorStatus = 0;
	 u8_PWM_CH_InitStatus = 0;
	 
	printf("Test case 4 : Muiltiple Init. for smae PWM channel : \n\n"); 
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	
	gstr_Pwm_Cfg_t str_PwmCfg={PWM_CH1A,PWM_PRESCALER_8};
	for(uint8_t PWMCH_ID=1;PWMCH_ID<3;PWMCH_ID++) 
	{
		str_PwmCfg.u8_Channel = PWMCH_ID ;
		printf("%s",apu8_TestCaseName[PWMCH_ID-1]);
		Pwm_Init(&str_PwmCfg);
		u8_ErrorStatus=Pwm_Init(&str_PwmCfg);
		
		if(u8_ErrorStatus==PWM_MODULE_ERROR_NUMBER + ERROR_MULTIPLE_INIT)
		
		printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  \n\n\n");
	}
}

static void PWM_Init_TestCase_5(void){
	
	uint8_t u8_ErrorStatus = 0;
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	u8_PWM_CH_InitStatus = 0;
	
	printf("Test case 5:Muiltiple Init. for different timer channel : \n\n"); 
	
	gstr_Pwm_Cfg_t str_PwmCfg={PWM_CH1A,PWM_PRESCALER_8};
	for(uint8_t PWMCH_ID=1;PWMCH_ID<3;PWMCH_ID++) 
	{
		str_PwmCfg.u8_Channel = PWMCH_ID ;
		printf("%s",apu8_TestCaseName[PWMCH_ID-1]);
		u8_ErrorStatus=Pwm_Init(&str_PwmCfg);
		
		if(u8_ErrorStatus==E_OK)
		
		printf(" PASS\n\n\n");
		
		else 
		
			printf(" Faild  \n\n\n" );
	}
	
}

extern void Test_PWM_InilFun(void){
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST PWM INIT FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 6 ; Test_Case_Stage ++ )
	{
		PWM_Init_TestCasesFun[Test_Case_Stage]();
		
	}
}


/////


static void PWM_Start_TestCase_0(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	
	
	uint8_t * apu8_Register[]={(uint8_t *)&OCR1A,(uint8_t *)&OCR1B,(uint8_t *)&TCCR1,(uint8_t *)&ICR1};
	
	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t PWM_CH_ID = 1;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		
		u8_ErrorStatus=Pwm_Start(PWM_CH_ID,50,FREQ_100_);
			
		if((* apu8_Register[PWM_CH_ID-1]==39) && (* apu8_Register[2]==TIMEr1_PRESCALER_1024)&&(* apu8_Register[3]==FRE_100_ICR_))
		{
			if(u8_ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild   \n\n\n");
		}
		TCCR1=0;
		ICR1=0;
	}
	
static void PWM_Start_TestCase_1(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
		
	printf("Test case 1: Passing invalide PWM channel : ");
		
	u8_ErrorStatus=Pwm_Start(5,50,FREQ_100_);
		
	if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
}
	
static void PWM_Start_TestCase_2(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
		
	printf("Test case 2: Passing invalide duty cycle parametar : \n\n");
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Start(PWM_CH_ID,150,FREQ_100_);
			
		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR)
		
			printf(" PASS\n\n\n");

		
		else 
		
			printf(" Faild \n\n\n");
		}
}

static void PWM_Start_TestCase_3(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
		
	printf("Test case 3: Passing invalide duty cycle parametar : \n\n");
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Start(PWM_CH_ID,50,70);
			
		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR)
		
			printf(" PASS\n\n\n");

		
		else 
		
			printf(" Faild \n\n\n");
		}
}

static void PWM_Start_TestCase_4(void){
	
	uint8_t u8_ErrorStatus = 0;
		u8_PWM_CH_InitStatus = 0 ;

	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	printf("Test case 4 : calling start without init :\n\n");
	
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Start(PWM_CH_ID,50,FREQ_100_);

		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}

extern void Test_PWM_StartFun(void){ 
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST PWM Start FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 5 ; Test_Case_Stage ++ )
	{
		PWM_Start_TestCasesFun[Test_Case_Stage]();
		
	}
}

///



static void PWM_Update_TestCase_0(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	
	
	uint8_t * apu8_Register[]={(uint8_t *)&OCR1A,(uint8_t *)&OCR1B,(uint8_t *)&ICR1};
	
	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t PWM_CH_ID = 1;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		
		u8_ErrorStatus=Pwm_Update(PWM_CH_ID,50,FREQ_100_);
			
		if((* apu8_Register[PWM_CH_ID-1]==39) && (* apu8_Register[2]==FRE_100_ICR_))
		{
			if(u8_ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		}
			
			else 
			
				printf(" Faild   \n\n\n");
		}
		
		ICR1=0;
	}
static void PWM_Update_TestCase_1(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
		
	printf("Test case 1: Passing invalide PWM channel : ");
		
	u8_ErrorStatus=Pwm_Update(5,50,FREQ_100_);
		
	if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
}
static void PWM_Update_TestCase_2(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
		
	printf("Test case 2: Passing invalide duty cycle parametar : \n\n");
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Update(PWM_CH_ID,150,FREQ_100_);
			
		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR)
		
			printf(" PASS\n\n\n");

		
		else 
		
			printf(" Faild \n\n\n");
		}
}
static void PWM_Update_TestCase_3(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
		
	printf("Test case 3: Passing invalide duty cycle parametar : \n\n");
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Update(PWM_CH_ID,50,70);
			
		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PARAMETAR)
		
			printf(" PASS\n\n\n");

		
		else 
		
			printf(" Faild \n\n\n");
		}
}

static void PWM_Update_TestCase_4(void){
	
	uint8_t u8_ErrorStatus = 0;
		u8_PWM_CH_InitStatus = 0 ;

	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	printf("Test case 4 : calling Updata without init :\n\n");
	
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Update(PWM_CH_ID,50,FREQ_100_);

		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}

extern void Test_PWM_UpdateFun(void){ 
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Pwm Update FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 5 ; Test_Case_Stage ++ )
	{
		PWM_Update_TestCasesFun[Test_Case_Stage]();
		
	}
}




static void PWM_Stop_TestCase_0(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
	
	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	
	
	//uint8_t * apu8_Register[]={(uint8_t *)&TCCR1A,(uint8_t *)&TCCR1A};
	
	printf("Test case 0: Passing valide argmement: \n\n");
	
	for(uint8_t PWM_CH_ID = 1;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		
		u8_ErrorStatus=Pwm_Stop(PWM_CH_ID);
			
		//if((* apu8_Register[PWM_CH_ID-1]==0))
		//{
			if(u8_ErrorStatus==E_OK)
			
			printf(" PASS\n\n\n");
		//}
			
			else 
			
				printf(" Faild   \n\n\n");
		}
		
		//ICR1=0;
	}
static void PWM_Stop_TestCase_1(void){
	
	uint8_t u8_ErrorStatus = 0;
	
	u8_PWM_CH_InitStatus = 3 ;
		
	printf("Test case 1: Passing invalide PWM channel : ");
		
	u8_ErrorStatus=Pwm_Stop(5);
		
	if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_INVALIDE_PWM_CHANNEL)
	
		printf(" PASS\n\n\n");

	
	else 
	
		printf(" Faild \n\n\n");
}
static void PWM_Stop_TestCase_2(void){
	
	uint8_t u8_ErrorStatus = 0;
	u8_PWM_CH_InitStatus = 0 ;

	uint8_t * apu8_TestCaseName[]={"FOR TIMER_CH_1A : ","FOR TIMER_CH_1B : "};
	printf("Test case 2 : calling Updata without init :\n\n");
	
	for(uint8_t PWM_CH_ID = 1 ;PWM_CH_ID < 3;PWM_CH_ID ++) 
	{
		printf("%s",apu8_TestCaseName[PWM_CH_ID-1]);
		u8_ErrorStatus=Pwm_Stop(PWM_CH_ID);

		if(u8_ErrorStatus == PWM_MODULE_ERROR_NUMBER + ERROR_UNILTILZED_PWM )
		
			printf(" PASS\n\n\n");
	
		
		else 
		
			printf(" Faild \n\n\n");
		}
	}
extern void Test_PWM_StopFun(void){ 
	
	char Test_Case_Stage=0;
	
	printf("\n                      TEST Pwm Stop FUNCTION\n\n");
	
	for( ; Test_Case_Stage < 3 ; Test_Case_Stage ++ )
	{
		PWM_Stop_TestCasesFun[Test_Case_Stage]();
		
	}
}

	