#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include "Font.h"
#include <time.h>
#include <TlHelp32.h>
#include <stdlib.h>
#define D3DparamX		, UINT paramx
#define D3DparamvalX	, paramx
#define D3DAygýt LPDIRECT3DDEVICE9
#pragma comment( lib, "psapi.lib" )
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma once

#define ITEM_ARRAY 64 

#define MC_MAXX                    (X)                                               
#define MC_FCTR(x,y)            ((x))                                              
/*#define MC_ITEMY(index)            (Y+(index*I_SPC)+T_SPC+(T_SPC/2))                  
#define MC_MSY                    (Y+T_SPC+(T_SPC/2))    */                    

#define MC_ITEMY(index)            (Y+(index*I_SPC)+T_SPC+(T_SPC))                  
#define MC_MSY                    (Y+T_SPC+(T_SPC))    

class D3DClass
{
public:
	
	DWORD CSH, BIN, OBJ;
	D3DPRESENT_PARAMETERS d3dpp;

	struct sitem{
            char title[50];        
            char state[50];       
            int     type;         
            int  max;          
            int  no;           
            int     *val;          
    }items[ITEM_ARRAY];
	enum COLORS{  // Normal Colors
        WHITE    =    D3DCOLOR_ARGB(255,255,255,255),
        RED        =    D3DCOLOR_ARGB(255,225,0,0),
        GREEN    =    D3DCOLOR_ARGB(255,124,252,0),
        BLUE    =    D3DCOLOR_ARGB(255,30,144,255),
        BLACK    =    D3DCOLOR_ARGB(255,0,0,0),
        PURPLE    =    D3DCOLOR_ARGB(255,125,0,255),
        GREY    =    D3DCOLOR_ARGB(255,128,128,128),
		TEAL = D3DCOLOR_ARGB(255,0,128,128),
        YELLOW  =    D3DCOLOR_ARGB(255,255,255,0),
        ORANGE    =    D3DCOLOR_ARGB(255,255,125,0),
		VIOLET = D3DCOLOR_ARGB(255,199,21,133),
		DEEPBLUE = D3DCOLOR_ARGB(255,0,191,255)
    };
	enum I_COLORS{  // Item Colors
        KAPALI     =   WHITE, //D3DCOLOR_ARGB(255,255,255,255),
        ACIK     =  D3DCOLOR_ARGB(255,0,191,255),// D3DCOLOR_ARGB(191,255,0,0),
        KATEGORI     = WHITE, //  D3DCOLOR_ARGB(255,220,20,60),
    };
	enum BK_COLORS{ // BackGround Colors
        C_BOX    = D3DCOLOR_ARGB(25, 0, 0, 0),// D3DCOLOR_ARGB(2,31,100,0),
        C_BORDER = D3DCOLOR_ARGB(255,0,191,255),// D3DCOLOR_ARGB(161,226,255,0)
    };
	enum I_TYPES{
        YAZI = 0,
        SECENEK = 1,
        KATEGORI_S  = 2
    };
	   struct MenuSt_t
    {
    	int x , y;
    	int NumberOfItems;
    	bool Gorunur_B , AyarYap;
    };
	CD3DFont *font;
    int  X,Y;              
    int  M_DRAG;    
    int  WIDTH;           
    int  I_OFS,S_OFS;    
    int  I_SPC,I_TSPC;  
    int  T_SPC,F_SPC;    
    int  NO;           
    int  I_CUR;     
    bool Goster;        
    bool Ayar;      
     
    int  ABOR;            
    int  BTEX,BDIR;   
    char*    oprintf (const char *fmt, ...);
    void    PostReset(D3DAygýt Aygýt);
    void    PreReset(void);
    void    ShowMenu(D3DAygýt Aygýt);
    void    ShowBox(D3DAygýt Aygýt);


	void ARGB(int x, int y, int w, int h,  D3DCOLOR Renk, IDirect3DDevice9* Aygýt);
	void ARGB_KENAR_CIZ(int x, int y, int w, int h, int px, D3DCOLOR KenarRenk, IDirect3DDevice9* Aygýt);
	void MENU_OLUSTUR(int x, int y, int w, int h, D3DCOLOR Renk, D3DAygýt Aygýt);
	void KENAR_OLUSTUR(int x, int y, int w, int h, D3DCOLOR Renk, D3DAygýt Aygýt);

private:
	void    Kategori(char *title, char *states, int *var);
    void    Secenek(char *title, char *states,int *var, int show, int when);
    void    Yaz(char *title, char *states,int show, int when);
    void    _SCEKLE(char *title, char *states,int type, int *var, int show, int when);

	void    FieldAl(char * str,char *dst,int no);
    int       FieldBitir(char * str);

    void    Init(void);
};
extern D3DClass Menu;


struct MenuSt_t
    {
        int x , y;
        int NumberOfItems;
        bool IsVisble , Load;
    };

struct Hileler_S
{
	int text; 
        struct Hile_S
		{
			int render;
			int chams;
			int wallhack;
			int wireframe;
			int xray;
			int crosshair;
			int nameesp;
			int norecoil;
			int nospread;
			int unammo;
			int rapidfire;
			int nodelay;
			int wallshot;
			int ability;
			int jump;
			int jumpspeed;
			int aimbot;
			int nogravity;
			int respawnwhere;
			int zeroslots;
			int unball;
			int instrespawn;
			int nofalldamage;
			int speedhack;
			int gamemode;
			int wolftype;
			int freeze;
		}Hileler;
		struct Creditsler_S
		{
			int main;
			int yazý;
		}Creditsler;
		struct Misc {
			int main;
		}Miscs;

		struct Visual {
			int main;
		}Visual;

		struct Game {
			int main;
		}Game;
};
extern Hileler_S H4CK;
