
#include "processor.h"


static PROCESSOR_ModeType REQUIRED_MODE =PROCESSOR_ModeNonPrivilege;

void PROCESSOR_switchMode(PROCESSOR_ModeType Mode)
{
  

    REQUIRED_MODE=Mode;
    __asm(" SVC #1");

}

/*TODO: Put the following function address in Vector table */
void PROCESSOR_SvcHandler(void)
{
    switch(REQUIRED_MODE)
    {
    case PROCESSOR_ModePrivilege:
        __asm(" MOV R0, #0");
        __asm(" MSR CONTROL, R0");
        break;
    case PROCESSOR_ModeNonPrivilege:
        __asm(" MOV R0, #1");
        __asm(" MSR CONTROL, R0");
        break;
    default:
        break;
    }


}

void PROCESSOR_enableGlobalInt(void)
{
    PROCESSOR_switchMode(PROCESSOR_ModePrivilege);
    __asm("    cpsie   i\n");
    PROCESSOR_switchMode(PROCESSOR_ModeNonPrivilege);
}

void PROCESSOR_disableGlobalInt(void)
{
    PROCESSOR_switchMode(PROCESSOR_ModePrivilege);
    __asm("    cpsid   i\n");
    PROCESSOR_switchMode(PROCESSOR_ModeNonPrivilege);
}
