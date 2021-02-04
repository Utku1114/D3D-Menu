#include "Base.h"
#include "Menu.h"
#include "Detour.h"
#include <iostream>
#include <TlHelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

#pragma comment( lib, "psapi.lib" )
#define D3DparamX		, UINT paramx
#define D3DparamvalX	, paramx
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
int SumStride;



ID3DXLine *pLine;

using namespace std;

UCHAR
szFileSys[255],
szVolNameBuff[255];

DWORD
dwMFL,
dwSysFlags,
dwSerial;

IDirect3DVertexBuffer9* Stream_Data;
UINT OffsetInBytes;
UINT m_Stride;
bool Color = false;

LPDIRECT3DTEXTURE9    texYellow, texRed, texGreen, texBlue, texBlack, texWhite, texPink, texOrange, texLightBlue, texCyan, texPurple, texSteelBlue, texLightSteelBlue, texSalmon, texBrown, texTeal, texLime, texElectricLime, texGold, texOrangeRed, texGreenYellow, texAquaMarine, texSkyBlue, texSlateBlue, texCrimson, texDarkOliveGreen, texPaleGreen, texDarkGoldenRod, texFireBrick, texDarkBlue, texDarkerBlue, texDarkYellow, texLightYellow;

cBase Base;
D3DClass Menu;
Hileler_S H4CK;

HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
    if(FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
        return E_FAIL;
    
    WORD colour16 = ((WORD)((colour32>>28)&0xF)<<12)
	            	|(WORD)(((colour32>>20)&0xF)<<8)
	             	|(WORD)(((colour32>>12)&0xF)<<4)
                 	|(WORD)(((colour32>>4)&0xF)<<0);

    D3DLOCKED_RECT d3dlr;    
    (*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
    WORD *pDst16 = (WORD*)d3dlr.pBits;

    for(int xy=0; xy < 8*8; xy++)
        *pDst16++ = colour16;

    (*ppD3Dtex)->UnlockRect(0);

    return S_OK;
}

void PreReset( D3DAygýt Aygýt )
{
	Menu.PreReset();
	return;
}

void PostReset( D3DAygýt Aygýt )
{
	Menu.PostReset(Aygýt);
	return;
}

typedef HRESULT ( WINAPI* oReset )( D3DAygýt Aygýt, D3DPRESENT_PARAMETERS* pPresentationParameters );
oReset pReset;

HRESULT APIENTRY myReset( D3DAygýt Aygýt, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	PreReset( Aygýt );
	HRESULT hRet = pReset( Aygýt, pPresentationParameters );
	
	if( SUCCEEDED( hRet ) )
	{
		PostReset( Aygýt );
	}
	return hRet;
}
typedef HRESULT (WINAPI* oDrawIndexedPrimitive) (D3DAygýt Aygýt, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
oDrawIndexedPrimitive pDrawIndexedPrimitive;

HANDLE Process = OpenProcess(PROCESS_ALL_ACCESS,0, GetCurrentProcessId());

HRESULT WINAPI  myDrawIndexedPrimitive(D3DAygýt Aygýt, D3DPRIMITIVETYPE pType D3DparamX ,UINT nMinIndex, UINT nNumVertices, UINT nStartIndex, UINT nPrimitiveCount )
{
	if(Aygýt->GetStreamSource(0,&Stream_Data,&OffsetInBytes,&m_Stride) == D3D_OK) 
		Stream_Data->Release();
	DWORD dwOldZEnable = D3DZB_TRUE;
		
	if(!Color)
	{
	 GenerateTexture(Aygýt, &texGreen , D3DCOLOR_ARGB(255,0,255,0));
     GenerateTexture(Aygýt, &texRed , D3DCOLOR_ARGB(255,255,0,0));
     GenerateTexture(Aygýt, &texBlue , D3DCOLOR_ARGB(255,0,0,255));
     GenerateTexture(Aygýt, &texOrange , D3DCOLOR_ARGB(255,255,165,0));
     GenerateTexture(Aygýt, &texYellow , D3DCOLOR_ARGB(255,255,255,0));
     GenerateTexture(Aygýt, &texPink , D3DCOLOR_ARGB(255,255,192,203));
     GenerateTexture(Aygýt, &texCyan , D3DCOLOR_ARGB(255,0,255,255));
     GenerateTexture(Aygýt, &texPurple , D3DCOLOR_ARGB(255,160,32,240));
     GenerateTexture(Aygýt, &texBlack , D3DCOLOR_ARGB(255,0,0,0));
     GenerateTexture(Aygýt, &texWhite , D3DCOLOR_ARGB(255,255,255,255));
     GenerateTexture(Aygýt, &texSteelBlue , D3DCOLOR_ARGB(255,33,104,140));
     GenerateTexture(Aygýt, &texLightSteelBlue, D3DCOLOR_ARGB(255,201,255,255));
     GenerateTexture(Aygýt, &texLightBlue , D3DCOLOR_ARGB(255,26,140,306));
     GenerateTexture(Aygýt, &texSalmon , D3DCOLOR_ARGB(255,196,112,112));
     GenerateTexture(Aygýt, &texBrown , D3DCOLOR_ARGB(255,168,99,20));
     GenerateTexture(Aygýt, &texTeal , D3DCOLOR_ARGB(255,38,140,140));
     GenerateTexture(Aygýt, &texLime , D3DCOLOR_ARGB(255,50,205,50));
     GenerateTexture(Aygýt, &texElectricLime , D3DCOLOR_ARGB(255,204,255,0));
     GenerateTexture(Aygýt, &texGold , D3DCOLOR_ARGB(255,255, 215, 0));
     GenerateTexture(Aygýt, &texOrangeRed , D3DCOLOR_ARGB(255,255,69,0));
     GenerateTexture(Aygýt, &texGreenYellow , D3DCOLOR_ARGB(255,173,255,47));
     GenerateTexture(Aygýt, &texAquaMarine , D3DCOLOR_ARGB(255,127,255,212));
     GenerateTexture(Aygýt, &texSkyBlue , D3DCOLOR_ARGB(255,0,191,255));
     GenerateTexture(Aygýt, &texSlateBlue , D3DCOLOR_ARGB(255,132, 112, 255));
     GenerateTexture(Aygýt, &texCrimson , D3DCOLOR_ARGB(255,220,20,60));
     GenerateTexture(Aygýt, &texDarkOliveGreen, D3DCOLOR_ARGB(255,188,238,104 ));
     GenerateTexture(Aygýt, &texPaleGreen , D3DCOLOR_ARGB(255,154,255, 154));
     GenerateTexture(Aygýt, &texDarkGoldenRod , D3DCOLOR_ARGB(255,255, 185, 15 ));
     GenerateTexture(Aygýt, &texFireBrick , D3DCOLOR_ARGB(255,255,48,48));
     GenerateTexture(Aygýt, &texDarkBlue , D3DCOLOR_ARGB(255,0,0,204));
     GenerateTexture(Aygýt, &texDarkerBlue , D3DCOLOR_ARGB(255,0,0,153));
     GenerateTexture(Aygýt, &texDarkYellow , D3DCOLOR_ARGB(255,255,204,0));
     GenerateTexture(Aygýt, &texLightYellow , D3DCOLOR_ARGB(255,255,255,153));
	Color = true;
	}
	if(H4CK.Hileler.wallhack == 1)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				DWORD dwReEnableZB = D3DZB_TRUE;
				Aygýt->GetRenderState(D3DRS_ZENABLE, &dwReEnableZB); 
				Aygýt->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE); 
				Aygýt->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
		}
	}
	//Off|Red|Green|Blue|Cyan|Orange|Yellow
	if(H4CK.Hileler.chams == 1)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				Aygýt->SetRenderState(D3DRS_ZENABLE, false);
				Aygýt->SetTexture(0, texRed);
				pDrawIndexedPrimitive(Aygýt, pType D3DparamvalX, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
				Aygýt->SetTexture(0, texRed);
				Aygýt->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(H4CK.Hileler.chams == 2)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				Aygýt->SetRenderState(D3DRS_ZENABLE, false);
				Aygýt->SetTexture(0, texGreen);
				pDrawIndexedPrimitive(Aygýt, pType D3DparamvalX, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
				Aygýt->SetTexture(0, texGreen);
				Aygýt->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(H4CK.Hileler.chams == 3)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				Aygýt->SetRenderState(D3DRS_ZENABLE, false);
				Aygýt->SetTexture(0, texBlue);
				pDrawIndexedPrimitive(Aygýt, pType D3DparamvalX, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
				Aygýt->SetTexture(0, texBlue);
				Aygýt->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(H4CK.Hileler.chams == 4)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				Aygýt->SetRenderState(D3DRS_ZENABLE, false);
				Aygýt->SetTexture(0, texCyan);
				pDrawIndexedPrimitive(Aygýt, pType D3DparamvalX, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
				Aygýt->SetTexture(0, texCyan);
				Aygýt->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(H4CK.Hileler.chams == 5)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				Aygýt->SetRenderState(D3DRS_ZENABLE, false);
				Aygýt->SetTexture(0, texOrange);
				pDrawIndexedPrimitive(Aygýt, pType D3DparamvalX, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
				Aygýt->SetTexture(0, texOrange);
				Aygýt->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(H4CK.Hileler.chams == 6)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
				Aygýt->SetRenderState(D3DRS_ZENABLE, false);
				Aygýt->SetTexture(0, texYellow);
				pDrawIndexedPrimitive(Aygýt, pType D3DparamvalX, nMinIndex, nNumVertices, nStartIndex, nPrimitiveCount);
				Aygýt->SetTexture(0, texYellow);
				Aygýt->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(H4CK.Hileler.wireframe == 1)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
			Aygýt->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
	}
	if(H4CK.Hileler.xray == 1)
	{
		if((m_Stride == 20) || (m_Stride == 44 || m_Stride == 32 || m_Stride == 50 || m_Stride == 52 || m_Stride == 40))
		{
			Aygýt->Clear(0,NULL,D3DCLEAR_TARGET,0x00000000,1.0f,0);
			Aygýt->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		}
	}
	D3DCOLOR xcolor;

	switch (H4CK.Hileler.crosshair == 1){
	case 0: xcolor = D3DCOLOR_ARGB(255, 0, 0, 255);
		break;
	case 1: xcolor = D3DCOLOR_ARGB(255, 0, 0, 255);
		break;
	case 2: xcolor = D3DCOLOR_ARGB(255, 0, 255, 0);
		break;
	case 3: xcolor = D3DCOLOR_ARGB(255, 255, 0, 0);
		break;
	}
	if (H4CK.Hileler.crosshair == 1 > 0){

		int size = 20, strong = 2;
		D3DVIEWPORT9 viewP;
		Aygýt->GetViewport(&viewP);
		int iCenterX = (viewP.Width / 2) - 1;
		int iCenterY = (viewP.Height / 2) - 1;
		if (iCenterX < 20 && iCenterY < 20)
		{
			iCenterX = (GetSystemMetrics(0) / 2);
			iCenterY = (GetSystemMetrics(1) / 2);
		}
		D3DRECT rec2 = { iCenterX - size, iCenterY, iCenterX + size, iCenterY + strong };
		D3DRECT rec3 = { iCenterX, iCenterY - size, iCenterX + strong, iCenterY + size };
		Aygýt->Clear(1, &rec2, D3DCLEAR_TARGET, xcolor, 0, 0);
		Aygýt->Clear(1, &rec3, D3DCLEAR_TARGET, xcolor, 0, 0);
	}
	if(H4CK.Hileler.nameesp == 1)
	{
		DWORD Ptr = Menu.CSH + 0x34E950;
		DWORD Value = 2251829620;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4, NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x34E950;
		DWORD Value = 2251829621;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4, NULL);
	}
	if(H4CK.Hileler.norecoil == 1)
	{
		DWORD Ptr = Menu.CSH + 0x860F3;
		DWORD Value = 2665025140;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x860F3;
		DWORD Value = 2665025141;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.nospread == 1)
	{
		DWORD Ptr = Menu.CSH + 0x11AF5E;
		DWORD Value = 2257258100;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x11AF5E;
		DWORD Value = 2257258101;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.unammo == 1)
	{
		DWORD Ptr = Menu.CSH + 0x120420;
		DWORD Value = 2114045827;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x120420;
		DWORD Value = 2126546278;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.rapidfire == 1)
	{
		DWORD Ptr = Menu.CSH + 0x11CF5B;
		DWORD Value = 1574503796;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x11CF5B;
		DWORD Value = 1574503797;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.nodelay == 1)
	{
		DWORD Ptr = Menu.CSH + 0x1173C5;
		DWORD Value = 6951147;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x1173C5;
		DWORD Value = 6951029;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.wallshot == 1)
	{
		DWORD Ptr = Menu.BIN + 0x4D361;
		DWORD Value = 5;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.BIN + 0x4D361;
		DWORD Value = 1967244534;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.ability == 1)
	{
		DWORD Ptr = Menu.CSH + 0x5531D;
		DWORD Value = 28312949;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x5531D;
		DWORD Value = 28312948;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.jump == 1)
	{
		DWORD Ptr = Menu.CSH + 0x3F4154;
		DWORD Value = 1065353216;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.jump == 2) {
		DWORD Ptr = Menu.CSH + 0x3F4154;
		DWORD Value = 1072064102;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.jump == 3) {
		DWORD Ptr = Menu.CSH + 0x3F4154;
		DWORD Value = 1075419546;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if (H4CK.Hileler.jump == 0) {
		DWORD Ptr = Menu.CSH + 0x3F4154;
		DWORD Value = 1062165545;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.jumpspeed == 1)
	{
		DWORD Ptr = Menu.CSH + 0xF716E;
		DWORD Value = 25920527;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0xF716E;
		DWORD Value = 25920783;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.aimbot == 1)
	{
		DWORD Ptr = Menu.CSH + 0x1F94D;
		DWORD Value = 1;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x1F94D;
		DWORD Value = 0;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.aimbot == 1)
	{
		DWORD Ptr = Menu.CSH + 0x28A44C;
		DWORD Value = 3196063092;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x28A44C;
		DWORD Value = 3196063093;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.nogravity == 1)
	{
		DWORD Ptr = Menu.CSH + 0xF4BFD;
		DWORD Value = 5;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0xF4BFD;
		DWORD Value = 1967244534;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.respawnwhere == 1)
	{
		DWORD Ptr = Menu.CSH + 0xF2A85;
		DWORD Value = 3897951979;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0xF2A85;
		DWORD Value = 3897951860;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.zeroslots == 1)
	{
		DWORD Ptr = Menu.CSH + 0x1851E3;
		DWORD Value = 3071218292;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x1851E3;
		DWORD Value = 3071218293;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.unball == 1)
	{
		DWORD Ptr = Menu.CSH + 0x68EDAC;
		DWORD Value = 1;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x68EDAC;
		DWORD Value = 2;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.instrespawn == 1)
	{
		DWORD Ptr = Menu.CSH + 0x7CD40;
		DWORD Value = 1574503796;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0x7CD40;
		DWORD Value = 1574503797;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.nofalldamage == 1)
	{
		DWORD Ptr = Menu.CSH + 0xF5E21;
		DWORD Value = 2654543220;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0xF5E21;
		DWORD Value = 2654543221;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.speedhack == 1)
	{
		DWORD Ptr = Menu.CSH + 0xA8781;
		DWORD Value = 98110580;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else {
		DWORD Ptr = Menu.CSH + 0xA8781;
		DWORD Value = 98110581;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}
	if(H4CK.Hileler.gamemode == 1)
	{
		DWORD Ptr = Menu.CSH + 0x60ABAC;
		DWORD Value = 4;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.gamemode == 2) {
		DWORD Ptr = Menu.CSH + 0x60ABAC;
		DWORD Value = 20;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	}

	if(H4CK.Hileler.wolftype == 1)
	{
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 1;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 2) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 2;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 3) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 3;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 4) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 4;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 5) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 5;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 6) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 6;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 7) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 7;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 8) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 8;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.wolftype == 9) {
		DWORD Ptr = Menu.CSH + 0x68ECE8;
		DWORD Value = 9;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} 
	if(H4CK.Hileler.freeze == 1) {
		DWORD Ptr = Menu.OBJ + 0x40EA7;
		DWORD Value = 1574503796;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} else if(H4CK.Hileler.freeze == 0) {
		DWORD Ptr = Menu.OBJ + 0x40EA7;
		DWORD Value = 1967244534;
		WriteProcessMemory(Process, (LPVOID)Ptr, &Value, 4,NULL);
	} 
	     	return pDrawIndexedPrimitive(Aygýt,pType D3DparamvalX,nMinIndex,nNumVertices,nStartIndex,nPrimitiveCount);
}


typedef HRESULT(WINAPI* oEndScene)(D3DAygýt Aygýt);
oEndScene pEndScene;

long _stdcall myEndScene( D3DAygýt Aygýt )
{
		PostReset(Aygýt);
		Menu.ShowMenu(Aygýt);
		PreReset(Aygýt);
	return pEndScene( Aygýt );
}
void *D3Ddiscover(void *tbl, int size)
{
	HWND				  hWnd;
	void				  *pInterface=0 ;
	D3DPRESENT_PARAMETERS d3dpp; 

	if ((hWnd=CreateWindowEx(NULL,WC_DIALOG,"",WS_OVERLAPPED,0,0,50,50,NULL,NULL,NULL,NULL))==NULL) return 0;
	ShowWindow(hWnd, SW_HIDE);

	LPDIRECT3D9	pD3D;
	D3DAygýt	pD3Ddev;
	if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION))!=NULL) 

	{
	    ZeroMemory(&d3dpp, sizeof(d3dpp));
	    d3dpp.Windowed         = TRUE;
		d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	    d3dpp.hDeviceWindow    = hWnd;
	    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	    d3dpp.BackBufferWidth  = d3dpp.BackBufferHeight = 600;
		pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&pD3Ddev);
		if (pD3Ddev)  {
		    pInterface = (PDWORD)*(DWORD *)pD3Ddev;
			memcpy(tbl,(void *)pInterface,size);
			pD3Ddev->Release();
		}
		pD3D->Release();
	}
	DestroyWindow(hWnd);
	return pInterface;
}


int __stdcall D3D(void)
{

	HINSTANCE	hD3D;
	DWORD		vTable[105];
	hD3D=0;
	do {
		hD3D = GetModuleHandle("d3d9.dll");
		if (!hD3D) Sleep(100);
	} while(!hD3D);


	if (D3Ddiscover((void *)&vTable[0],420)==0) return 0;
	{
		
		while(1)
		{
		
			if(memcmp((void*)vTable[82],(void*)(PBYTE)"\x8B\xFF",2)== 0)
		{
			pEndScene = (oEndScene) DetourCreate((PBYTE) vTable[42], (PBYTE)myEndScene,5);
			pDrawIndexedPrimitive = (oDrawIndexedPrimitive)DetourCreate((PBYTE)vTable[82], (PBYTE)myDrawIndexedPrimitive, 5);
		}
	Sleep(50);
	}
	return 0;
	}

}

int __stdcall DllMain(HMODULE Modül, DWORD Sonuç, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(Modül);
	if (Sonuç == 1)
	{  
	    CreateThread(0, 0, (PTHREAD_START_ROUTINE)D3D, 0, 0, 0);
	}	
	return 1;
}