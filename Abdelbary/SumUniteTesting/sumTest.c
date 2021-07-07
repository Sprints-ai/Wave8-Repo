
#include <stdio.h>
#define E_OK 	0
#define E_NOK	-1
#define MAX_INIT	100
#define ERR_STATUS	int
ERR_STATUS sum(int a , int b,int* sum)
{
ERR_STATUS u8_funStatus = E_OK;

if(MAX_INIT-b < a)
u8_funStatus = E_NOK;
else
{
*sum = a+b;
}
return u8_funStatus;
}

int main(void)
{
int a[][3] = {{5,5,E_OK},{0,0,E_OK},{MAX_INIT,MAX_INIT-5,E_NOK}};
int s = 0;
for(int i =0 ; i < 3 ;i++)
{
int expRet = sum(a[i][0],a[i][1],&s);
printf("testCase %d : expected_output %d , actual_output %d  ",i,a[i][2],expRet);
if(expRet == a[i][2])
printf("PASSED\n");
else
printf("FAILD\n");
}
return 0; 
}