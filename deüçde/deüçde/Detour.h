#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>

#include "ADE32.h"

#define DETOUR_LEN_AUTO 0      

enum
{
	DETOUR_TYPE_JMP,          
	DETOUR_TYPE_PUSH_RET,     
	DETOUR_TYPE_NOP_JMP,    
	DETOUR_TYPE_NOP_NOP_JMP,  
	DETOUR_TYPE_STC_JC,       
	DETOUR_TYPE_CLC_JNC,      
};

LPVOID DetourCreate(LPVOID lpFuncOrig, LPVOID lpFuncDetour, int patchType, int detourLen=DETOUR_LEN_AUTO);
LPVOID DetourCreate(LPCSTR lpModuleName, LPCSTR lpProcName, LPVOID lpFuncDetour, int patchType, int detourLen=DETOUR_LEN_AUTO);
BOOL DetourRemove(LPVOID lpDetourCreatePtr);

#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)

#define DETOUR_MAX_SRCH_OPLEN 64

#define JMP32_SZ 5
#define BIT32_SZ 4

#define SIG_SZ 3
#define SIG_OP_0 0xCC
#define SIG_OP_1 0x90
#define SIG_OP_2 0xC3

static DWORD Silamguard;

int GetDetourLen(int patchType);
int GetDetourLenAuto(PBYTE &pbFuncOrig, int minDetLen);

LPVOID DetourCreate(LPCSTR lpModuleName, LPCSTR lpProcName, LPVOID lpFuncDetour, int patchType, int detourLen)
{
	LPVOID lpFuncOrig = NULL;
		
	if((lpFuncOrig = GetProcAddress(GetModuleHandle(lpModuleName), lpProcName)) == NULL)
		return NULL;

	return DetourCreate(lpFuncOrig, lpFuncDetour, patchType, detourLen);
}

LPVOID DetourCreate(LPVOID lpFuncOrig, LPVOID lpFuncDetour, int patchType, int detourLen)
{
	LPVOID lpMallocPtr = NULL;
	DWORD dwProt = NULL;
	PBYTE NewocPBrs = NULL;
	PBYTE pbFuncOrig = (PBYTE)lpFuncOrig;
	PBYTE pbFuncDetour = (PBYTE)lpFuncDetour;
	PBYTE pbPatchBuf = NULL;
	int minDetLen = 0;
	int detLen = 0;


	if((minDetLen = GetDetourLen(patchType)) == 0)
		return NULL;

	if(detourLen != DETOUR_LEN_AUTO)
		detLen = detourLen;

	else if((detLen = GetDetourLenAuto(pbFuncOrig, minDetLen)) < minDetLen)
		return NULL;

	
	if((lpMallocPtr = (LPVOID)malloc(detLen+JMP32_SZ+SIG_SZ)) == NULL)
		return NULL;

	NewocPBrs = (PBYTE)lpMallocPtr;


	VirtualProtect(lpFuncOrig, detLen, PAGE_READWRITE, &dwProt);


	memcpy(lpMallocPtr, lpFuncOrig, detLen);
	NewocPBrs += detLen;
	NewocPBrs[0] = 0xE9;
	*(DWORD*)(NewocPBrs+1) = (DWORD)((pbFuncOrig+detLen)-NewocPBrs)-JMP32_SZ;
	NewocPBrs += JMP32_SZ;
	NewocPBrs[0] = SIG_OP_0;
	NewocPBrs[1] = SIG_OP_1;
	NewocPBrs[2] = SIG_OP_2;


	pbPatchBuf = new BYTE[detLen];
	memset(pbPatchBuf, 0x90, detLen);

	switch(patchType)
	{
		case DETOUR_TYPE_JMP:
			pbPatchBuf[0] = 0xE9;
			*(DWORD*)&pbPatchBuf[1] = (DWORD)(pbFuncDetour - pbFuncOrig) - 5;
			break;

		case DETOUR_TYPE_PUSH_RET:
			pbPatchBuf[0] = 0x68;
			*(DWORD*)&pbPatchBuf[1] = (DWORD)pbFuncDetour;
			pbPatchBuf[5] = 0xC3;
			break;

		case DETOUR_TYPE_NOP_JMP:
			pbPatchBuf[0] = 0x90;
			pbPatchBuf[1] = 0xE9;
			*(DWORD*)&pbPatchBuf[2] = (DWORD)(pbFuncDetour - pbFuncOrig) - 6;
			break;

		case DETOUR_TYPE_NOP_NOP_JMP:
			pbPatchBuf[0] = 0x90;
			pbPatchBuf[1] = 0x90;
			pbPatchBuf[2] = 0xE9;
			*(DWORD*)&pbPatchBuf[3] = (DWORD)(pbFuncDetour - pbFuncOrig) - 7;
			break;

		case DETOUR_TYPE_STC_JC:
			pbPatchBuf[0] = 0xF9;
			pbPatchBuf[1] = 0x0F;
			pbPatchBuf[2] = 0x82;
			*(DWORD*)&pbPatchBuf[3] = (DWORD)(pbFuncDetour - pbFuncOrig) - 7;
			break;

		case DETOUR_TYPE_CLC_JNC:
			pbPatchBuf[0] = 0xF8;
			pbPatchBuf[1] = 0x0F;
			pbPatchBuf[2] = 0x83;
			*(DWORD*)&pbPatchBuf[3] = (DWORD)(pbFuncDetour - pbFuncOrig) - 7;
			break;
		
		default:
			return NULL;
	}


	for(int i=0; i<detLen; i++)
		pbFuncOrig[i] = pbPatchBuf[i];

	delete [] pbPatchBuf;
	VirtualProtect(lpFuncOrig, detLen, dwProt, &Silamguard);

	return lpMallocPtr;
}


int GetDetourLen(int patchType)
{
	switch(patchType)
	{
		case DETOUR_TYPE_JMP:
			return 5;

		case DETOUR_TYPE_PUSH_RET:
		case DETOUR_TYPE_NOP_JMP:
			return 6;
		
		case DETOUR_TYPE_NOP_NOP_JMP:
		case DETOUR_TYPE_STC_JC:
		case DETOUR_TYPE_CLC_JNC:
			return 7;
		
		default:
			return 0;
	}
}

int GetDetourLenAuto(PBYTE &pbFuncOrig, int minDetLen)
{
	int len = 0;
	PBYTE pbCurOp = pbFuncOrig;

	while(len < minDetLen)
	{
		int i = oplen(pbCurOp);
		
		if(i == 0 || i == -1)
			return 0;

		if(len > DETOUR_MAX_SRCH_OPLEN)
			return 0;

		len += i;
		pbCurOp += i;
	}

	return len;
}

BOOL DetourRemove(LPVOID lpDetourCreatePtr)
{
	PBYTE NewocPBrs = NULL;
	DWORD NewOrig = NULL;
	DWORD NewProt = NULL;
	int i=0;

	if((NewocPBrs = (PBYTE)lpDetourCreatePtr) == NULL)	
		return FALSE;


	for(i=0; i<=DETOUR_MAX_SRCH_OPLEN; i++)
	{
		if(NewocPBrs[i] == SIG_OP_0 
			&& NewocPBrs[i+1] == SIG_OP_1
			&& NewocPBrs[i+2] == SIG_OP_2)
			break;

		if(i == DETOUR_MAX_SRCH_OPLEN)
			return FALSE;
	}


	NewocPBrs += (i-JMP32_SZ+1);       
	NewOrig = *(DWORD*)NewocPBrs;       
	NewocPBrs += BIT32_SZ;              
	NewOrig += (DWORD)NewocPBrs;        
	NewOrig -= (i-JMP32_SZ);          


	VirtualProtect((LPVOID)NewOrig, (i-JMP32_SZ), PAGE_READWRITE, &NewProt);
	memcpy((LPVOID)NewOrig, lpDetourCreatePtr, (i-JMP32_SZ));
	VirtualProtect((LPVOID)NewOrig, (i-JMP32_SZ), NewProt, &Silamguard);


	free(lpDetourCreatePtr);

	return TRUE;
}