#include <stdio.h>
#include <stdlib.h>



#define ERROR_STATUS signed char

#define TEST_CASES 5

/*Errors Macros*/
#define SUMMITION_SUCCESSED 0
#define SUM_OVER_FLOW_ERROR -1
#define ADULT_CONTENT_16  -2
#define CONST_ADD_VALUE 1

signed char Testing___SUM_1(int Num1,int Num2);
signed char Sum1(int Num1,int Num2);

signed char Testing___SUM_2(unsigned char age,int Num1,int Num2);
signed char Sum2(unsigned char age,int Num1,int Num2);


signed char Testing___SUM_2_Integration_Test(unsigned char age,int Num1,int Num2);
int*Driver(void);

/*global pointer to be used int Sum_2_integration test Function to call Driver Function*/
long long int*PTR_To_Driver=NULL;


/*Array of Boudary Values of INT */
int Input_Array_Values[5]={2147483647,2147483646,0,-2147483647,-2147483648};
long long  int Expected_Results_Result[5]={2147483648,2147483647,1,-2147483646,-2147483647};

/*Array Of Expected Errors in each summition iteration*/
char Expected_Error_States[5]={SUM_OVER_FLOW_ERROR,SUMMITION_SUCCESSED,SUMMITION_SUCCESSED,SUMMITION_SUCCESSED,SUMMITION_SUCCESSED};
int Result;

/*Array of Boudary values of Unsigned Char AGE*/
/*Critical age point 16 Years */
int Ages_Array_Values[]={0,15,16,17,255};


int main()
{/* local Variables for Actual and Expected Summition States and to save Expected and Actual Result for further Check*/
   signed char Check_Test=SUMMITION_SUCCESSED;
   long long int Expected_Result=0;
   signed char Actual_Error_State=SUMMITION_SUCCESSED;
   int Actual_Result=0;
   signed char Expected_Error_state=SUMMITION_SUCCESSED;

    /*Testing Function1 Unit_Test for SUM1*/
    /*LAB#_1*/
    /* 5 Test Cases*/
   for(char i=0;i<TEST_CASES;i++){
             printf("****************************This is Unit Test for SUMMITION MODULE***************************************\n*******************************************_API_NO#_1_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n\n-FUNCTION NAME:SUM_1_UNIT_TEST\n-INPUT1: =(%d)______INPUT2: =(%d) \n",i+1,Input_Array_Values[i],CONST_ADD_VALUE);
             Check_Test=Testing___SUM_1(Input_Array_Values[i],CONST_ADD_VALUE);
             Expected_Result=Expected_Results_Result[i];
              Actual_Error_State=Check_Test;
              Actual_Result=Result;
              Expected_Error_state=Expected_Error_States[i];

              switch(i){
          case 3:
             if(Actual_Result==Expected_Result&&Actual_Error_State==Expected_Error_state)
                {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
             {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              break;

              case 4:
             if(Actual_Result==Expected_Result&&Actual_Error_State==Expected_Error_state)
                {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
             {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              break;

              default:
                if(Actual_Result<=Expected_Result&&Actual_Error_State==Expected_Error_state)
                    {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
                {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              }
   }

    /*Testing Function1 Unit_Test for SUM2*/
    /*LAB#_2*/
    /* 5 Test Cases*/
   for(char i=0;i<TEST_CASES;i++){
             printf("****************************This is Unit Test for SUMMITION MODULE***************************************\n*******************************************_API_NO#_2_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n\n-FUNCTION NAME:SUM_2_UNIT_TEST\n-Age: =(%d)______INPUT2: =(%d)______INPUT3: =(%d) \n",i+1,Ages_Array_Values[i],Input_Array_Values[i],CONST_ADD_VALUE);
             Check_Test=Testing___SUM_2(Ages_Array_Values[i],Input_Array_Values[i],CONST_ADD_VALUE);
             Expected_Result=Expected_Results_Result[i];
              Actual_Error_State=Check_Test;
              Actual_Result=Result;
              Expected_Error_state=Expected_Error_States[i];
              switch(i){
          case 3:
             if(Actual_Result==Expected_Result&&Actual_Error_State==Expected_Error_state)
                {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
             {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              break;

              case 4:
             if(Actual_Result==Expected_Result&&Actual_Error_State==Expected_Error_state)
                {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
             {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              break;

              default:
                  Expected_Error_state=ADULT_CONTENT_16;
                if(Actual_Result<=Expected_Result&&Actual_Error_State==Expected_Error_state)
                    {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
                {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              }
   }

/*/*Testing Function1 Integration_Test_Using Function_Driver for SUM2*/
    /*LAB#_2*/
    /* 5 Test Cases*/

      for(char i=0;i<TEST_CASES;i++){
             printf("****************************This is Unit Test for SUMMITION MODULE***************************************\n*******************************************_API_NO#_3_**************************************************\n*****************************************TEST_CASE_NO#_%d***********************************************\n\n-FUNCTION NAME:SUM_2_Integration_Test_With_Function_Driver\n-Age: =(%d)______INPUT2: =(%d)______INPUT3: =(%d) \n",i+1,Ages_Array_Values[i],Input_Array_Values[i],CONST_ADD_VALUE);
             Check_Test=Testing___SUM_2_Integration_Test(Ages_Array_Values[i],Input_Array_Values[i],CONST_ADD_VALUE);
             Expected_Result=PTR_To_Driver[i];
              Actual_Error_State=Check_Test;
              Actual_Result=Result;
              Expected_Error_state=Expected_Error_States[i];

              switch(i){
          case 3:
             if(Actual_Result==Expected_Result&&Actual_Error_State==Expected_Error_state)
                {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
             {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              break;

              case 4:
             if(Actual_Result==Expected_Result&&Actual_Error_State==Expected_Error_state){
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
                {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              break;


              default:
                  Expected_Error_state=ADULT_CONTENT_16;
                if(Actual_Result<=Expected_Result&&Actual_Error_State==Expected_Error_state)
                    {
                  printf("Expected_RESULT=(%lld)______Expected_Error_States=(%d)\n",Expected_Result,Expected_Error_state);
             printf("Actual_RESULT=(%d)______Actual_Error_States=(%d)\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE PASSED\n\n\n");
             }
             else
                {
                printf("Expected Output:Expected_RESULT=%lld________Expected_Error_States=%d\n",Expected_Result,Expected_Error_state);
             printf("Actual Output:Actual_RESULT=%d_________Actual_Error_States=%d\n",Actual_Result,Actual_Error_State);
                printf("TEST CASE FAILLED\n\n\n");
             }
              }
   }
    return 0;
}


ERROR_STATUS Sum1(int Num1,int Num2){
    ERROR_STATUS Check_Error_State=SUMMITION_SUCCESSED;
     Result=Num1+Num2;
    if(Result<Num1||Result<Num2&&Num1>=0&&Num2>=0){
       Check_Error_State=SUM_OVER_FLOW_ERROR;
   } else{
    Check_Error_State=SUMMITION_SUCCESSED;
    }
    return Check_Error_State;
}

signed char Testing___SUM_1(int Num1,int Num2){
    signed char Test_API_1=SUMMITION_SUCCESSED;
    Test_API_1=Sum1(Num1,Num2);
    return Test_API_1;
}


signed char Sum2(unsigned char age,int Num1,int Num2){
     ERROR_STATUS Check_Error_State=SUMMITION_SUCCESSED;
     if(age>16){
        Check_Error_State=Sum1(Num1,Num2);
        }
     else{
        Check_Error_State=ADULT_CONTENT_16;
     }
    return Check_Error_State;
}

signed char Testing___SUM_2(unsigned char age,int Num1,int Num2){
   signed char Test_API_2=SUMMITION_SUCCESSED;
    Test_API_2=Sum2(age,Num1,Num2);
    return Test_API_2;
}

int*Driver(void){
static long long  int D_Expected_Results_Result[5]={2147483648,2147483647,1,-2147483646,-2147483647};
return D_Expected_Results_Result;
}

signed char Testing___SUM_2_Integration_Test(unsigned char age,int Num1,int Num2){
    PTR_To_Driver=Driver();
   signed char Test_API_3=SUMMITION_SUCCESSED;
    Test_API_3=Sum2(age,Num1,Num2);
    return Test_API_3;
}
