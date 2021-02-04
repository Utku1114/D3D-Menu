#include "stdafx.h"
#include "Menu.h"
#include "Base.h"
#include "Pragma.h"
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "string.h"
#include <TlHelp32.h> //bozdum heralde bozulmuþ yarý yarýya
#include <Psapi.h>

#pragma warning(disable: 4244)
#pragma warning(disable: 4996) 

#define D3DAygýt LPDIRECT3DDEVICE9

using namespace std;

void D3DClass::PostReset(D3DAygýt Aygýt)
{
    font = new CD3DFont("Arial", 7, D3DFONT_CENTERED);
    font->InitDeviceObjects(Aygýt);
    font->RestoreDeviceObjects();
}
void D3DClass::PreReset(void)
{
    font->InvalidateDeviceObjects();
    font->DeleteDeviceObjects();
    delete font;
    font = NULL;
}
void D3DClass::Init()
{
	
    if(!Ayar)
	{
        X = 20; //Konum x
		Y = 5;  //Konum y
        WIDTH=200; 
        I_OFS=6;
        S_OFS=WIDTH-5;
        T_SPC=20;
        F_SPC=20;              
        I_SPC=20;
        I_CUR=0;
        ABOR=0;
        BDIR=0;
        Goster=true; 
        Ayar=true; 
		Menu.CSH = (DWORD)GetModuleHandleA("cshell.dll");
    }
	
}
char* D3DClass::oprintf (const char *fmt, ...)
{
    static char buffer[225] = "";
    va_list va_alist;
    va_start (va_alist, fmt);
    _vsnprintf (buffer,sizeof(buffer), fmt, va_alist);
    va_end (va_alist);
    return buffer;
}
void D3DClass::_SCEKLE(char *title, char *states,int type, int *var, int show, int when)
{
    if(show==when)
    {
        strcpy(items[NO].title,title);
        FieldAl(states,items[NO].state,*var+1);
        items[NO].type=type;
        items[NO].max=FieldBitir(states);
        items[NO].val=var;

        NO++;
    }
}

void D3DClass::Kategori(char *title, char *states,int *var)
{
    _SCEKLE(title,states,KATEGORI_S,var,0,0);
}

void D3DClass::Secenek(char *title, char *states,int *var,int show, int when)
{
    _SCEKLE(title,states,SECENEK,var,show,when);
}

void D3DClass::Yaz(char *title, char *states,int show,int when)
{
    _SCEKLE(title,states,YAZI,&H4CK.text,show,when);
}

int D3DClass::FieldBitir(char *str)
{
    char *ptr;
    int  no;
    for(no=1; (ptr=strchr(str,(char)'|'))!=NULL; no++)str=ptr+1;
    return no;
}

void D3DClass::FieldAl(char *str,char *dst,int no)
{
    char *ptr;
    int  i;
    for(i=1; (ptr=strchr(str,(char)'|'))!=NULL ; i++) 
    {
        if(i==no) break;
        str=ptr+1;
    }
    if(ptr)
    {
        i=(int)(ptr-str);
        strncpy(dst,str,i);
        dst[i]=0;
    }
    else
        strcpy(dst,str);
}

void D3DClass::ARGB(int x, int y, int w, int h, D3DCOLOR Renk, IDirect3DDevice9* Aygýt)
{
	if (!Aygýt)
		return;

	const DWORD D3D_FVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	struct Vertex
	{
		float x, y, z, ht;
		DWORD Renk;
	}
	V[4] =
	{
		{ (float)x, (float)(y + h), 0.0f, 0.0f, Renk },
		{ (float)x, (float)y, 0.0f, 0.0f, Renk },
		{ (float)(x + w), (float)(y + h), 0.0f, 0.0f, Renk },
		{ (float)(x + w), (float)y, 0.0f, 0.0f, Renk }
	};

	Aygýt->SetRenderState(D3DRS_LIGHTING, TRUE);
	Aygýt->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	Aygýt->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Aygýt->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	Aygýt->SetRenderState(D3DRS_FOGENABLE, false);
	Aygýt->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
    Aygýt->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    Aygýt->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    Aygýt->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	Aygýt->SetFVF(D3D_FVF);
	Aygýt->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));

	if (w < 0)w = 1;
	if (h < 0)h = 1;
	if (x < 0)x = 1;
	if (y < 0)y = 1;

	D3DRECT rec = { x, y, x + w, y + h };
	Aygýt->Clear(1, &rec, D3DCLEAR_TARGET, Renk, 0, 0);
}

void D3DClass::ARGB_KENAR_CIZ(int x, int y, int w, int h, int px, D3DCOLOR KenarRenk, IDirect3DDevice9* Aygýt)
{
	ARGB(x, (y + h - px), w, px, KenarRenk, Aygýt);
	ARGB(x, y, px, h, KenarRenk, Aygýt);
	ARGB(x, y, w, px, KenarRenk, Aygýt);
	ARGB((x + w - px), y, px, h, KenarRenk, Aygýt);
}

void D3DClass::MENU_OLUSTUR(int x, int y, int w, int h, D3DCOLOR Renk, D3DAygýt Aygýt)
{
	ARGB(x, y, w, h, 0xff000000, Aygýt);
	ARGB_KENAR_CIZ(x, y, w, h, 1, Renk, Aygýt);
	return;
}

void D3DClass::KENAR_OLUSTUR(int x, int y, int w, int h, D3DCOLOR Renk, D3DAygýt Aygýt)
{
	MENU_OLUSTUR(x, y, 1, h, Renk, Aygýt);
	MENU_OLUSTUR(x, y + h, w, 1, Renk, Aygýt);
	MENU_OLUSTUR(x, y, w, 1, Renk, Aygýt);
	MENU_OLUSTUR(x + w, y, 1, h + 1, Renk, Aygýt);
	return;
}



void D3DClass::ShowMenu(D3DAygýt Aygýt)
{
    int    lm        =    GetAsyncKeyState(VK_LBUTTON)&1;
    int    rm        =    GetAsyncKeyState(VK_RBUTTON)&1;
    int    left    =    GetAsyncKeyState(VK_LEFT )&1;
    int    right    =    GetAsyncKeyState(VK_RIGHT)&1;
    int    up        =    GetAsyncKeyState(VK_UP   )&1;
    int    down    =    GetAsyncKeyState(VK_DOWN )&1;
    Init();
    if(GetAsyncKeyState(VK_INSERT)&1) 
	{
			Goster=(!Goster);
	}
	if (Goster)
	{
		NO = 0;
		Kategori("Render Settings", "+|-", &H4CK.Hileler.render);
		Secenek("Wall Hack", "Off|On", &H4CK.Hileler.wallhack, H4CK.Hileler.render,1);
		Secenek("Wireframe", "Off|On", &H4CK.Hileler.wireframe, H4CK.Hileler.render,1);
		Secenek("Crosshair", "Off|On", &H4CK.Hileler.crosshair, H4CK.Hileler.render,1);
		
		Kategori("Misc", "+|-",&H4CK.Miscs.main);
		Secenek("Name ESP", "Off|On", &H4CK.Hileler.nameesp, H4CK.Miscs.main,1);
		Secenek("No Recoil", "Off|On", &H4CK.Hileler.norecoil, H4CK.Miscs.main,1);
		Secenek("No Spread", "Off|On", &H4CK.Hileler.nospread, H4CK.Miscs.main,1);
		Secenek("No Fall Damage", "Off|On", &H4CK.Hileler.nofalldamage, H4CK.Miscs.main,1);
		Secenek("Unlimited Ammo", "Off|On", &H4CK.Hileler.unammo, H4CK.Miscs.main, 1);
		Secenek("Unlimited W.Ball", "Off|On", &H4CK.Hileler.unball, H4CK.Miscs.main, 1);
		Secenek("Rapid Fire", "Off|On", &H4CK.Hileler.rapidfire, H4CK.Miscs.main, 1);
		Secenek("No Delay Switch", "Off|On", &H4CK.Hileler.nodelay, H4CK.Miscs.main, 1);
		Secenek("Wall Shoot", "Off|On", &H4CK.Hileler.wallshot, H4CK.Miscs.main, 1);
		Secenek("Wolf Ability", "Off|On", &H4CK.Hileler.ability, H4CK.Miscs.main, 1);

		Kategori("Visual", "+|-", &H4CK.Visual.main);
		Secenek("Aimbot", "Fix", &H4CK.Hileler.aimbot, H4CK.Visual.main, 1);
		Secenek("Speed Hack", "Off|1x|2x|3x", &H4CK.Hileler.speedhack, H4CK.Visual.main, 1);
		Secenek("Jump Hack", "Off|1x|2x|3x", &H4CK.Hileler.jump, H4CK.Visual.main, 1);
		Secenek("Jump Speed", "Off|On", &H4CK.Hileler.jumpspeed, H4CK.Visual.main, 1);
		Secenek("No Gravity", "Off|On", &H4CK.Hileler.nogravity, H4CK.Visual.main, 1);
		Secenek("Respawn Where Die", "Off|On", &H4CK.Hileler.respawnwhere, H4CK.Visual.main, 1);
		Secenek("0 SP Slots", "Off|On", &H4CK.Hileler.zeroslots, H4CK.Visual.main, 1);
		Secenek("Inst. Respawn", "Off|On", &H4CK.Hileler.instrespawn, H4CK.Visual.main, 1);

		Kategori("Game", "+|-", &H4CK.Game.main);
		Secenek("Game Mode", "Off|Deathmatch|Wolf Hunt", &H4CK.Hileler.gamemode, H4CK.Game.main, 1);
		Secenek("Wolf Type", "Off|Power|Guardian|Ghost|Wild|Smart|Ghost2|Ice|Psy", &H4CK.Hileler.wolftype, H4CK.Game.main, 1);
		Secenek("Freeze All Player", "Off|On", &H4CK.Hileler.freeze, H4CK.Game.main,1 );

		Kategori("Credits", "+|-", &H4CK.Creditsler.main);
		Secenek("Version: 1.0", "",&H4CK.text,H4CK.Creditsler.main,1);
		Secenek("#Utku & Bingo", "",&H4CK.text,H4CK.Creditsler.main,1);

		MENU_OLUSTUR(X,MC_MSY,WIDTH,(NO*I_SPC),C_BOX,Aygýt);
		KENAR_OLUSTUR(X,MC_MSY,WIDTH,(NO*I_SPC),C_BORDER,Aygýt);

		MENU_OLUSTUR(X, Y+20, WIDTH, F_SPC, C_BOX, Aygýt);
		KENAR_OLUSTUR(X, Y+20, WIDTH, F_SPC, C_BORDER, Aygýt);
		font->DrawTextA(X + 100, Y+23, BLUE, "Blackjack Hack 1.0", 0x0001);
		 for(int no=0; no<NO; no++)
        {    
            D3DCOLOR text;

            text=(*(items[no].val)>0)?ACIK:KAPALI;

            if(items[no].type==KATEGORI)
                text=KATEGORI;

            if(I_CUR==no)
            {
                text=ORANGE;
			}

            font->DrawText(X+I_OFS,MC_ITEMY(no)+2,text,items[no].title,DT_SHADOW);
            font->DrawText(X+S_OFS,MC_ITEMY(no)+2,text,items[no].state,DT_RIGHT|DT_SHADOW);
        }

		 if(left && (*items[I_CUR].val)>0)
        {
            (*items[I_CUR].val)-=1;
        }

        if(right && (*items[I_CUR].val)<(items[I_CUR].max-1))
        {
            (*items[I_CUR].val)+=1;
        }

        if(up)
        {
            do {
                I_CUR=(I_CUR==0)?(NO-1):(I_CUR-1);
                if(ABOR>(-(I_SPC)))ABOR-=I_SPC;
            } while (items[I_CUR].type==YAZI);
        }

        if(down || items[I_CUR].type==YAZI)
        {
            do
            {
                I_CUR=(I_CUR+1)%NO;
                if(ABOR<(I_SPC))ABOR+=I_SPC;
            } while (items[I_CUR].type==YAZI);
        }

        if(I_CUR>NO)I_CUR=NO-1; 
    }
}