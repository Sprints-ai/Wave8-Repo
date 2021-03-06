/*
* NVM.h
*
* Created: 29/04/2020 00:23:34
*  Author: sony
*/


#ifndef NVM_H_
#define NVM_H_
typedef enum {NVM_OK, NVM_NOK, NVM_BUSY}NVM_CheckType;
typedef void (*NvmActionDoneCbkPtrType)(void);
typedef struct
{
	unsigned char BlockId;
	unsigned char BlockLength;
	unsigned char* BlockRamAddress;
	NvmActionDoneCbkPtrType BlockWriteNotifPtr;
	NvmActionDoneCbkPtrType BlockReadNotifPtr;
}NVM_ConfigType;
typedef struct
{
	NvmActionDoneCbkPtrType WriteAllCallBack;
	NvmActionDoneCbkPtrType ReadAllCallback;
}NVM_GlobalCallbacksType;
void NVM_Init(void);
NVM_CheckType NVM_ReadAll(void);////data from physical -> mirror
NVM_CheckType NVM_WriteAll(void);//data from mirror -> physical
NVM_CheckType NVM_ReadBlock(unsigned char BlockId, unsigned char* DataPtr);//data from mirrror to user
NVM_CheckType NVM_WriteBlock(unsigned char BlockId, const unsigned char* DataPtr);//data from user to mirror
void NVM_Main(void);
void NVM_WriteBlockDoneNotif(void);
void NVM_ReadBlockDoneNotif(void);



#endif /* NVM_H_ */