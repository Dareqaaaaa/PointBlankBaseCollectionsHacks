#include "stdafx.h"
#include "menu.h"
#include "variables.h"
#include "tools.h"
#include "xor.h"
#include "address.h"
#include "class.h"
#include "aimbot.h"
#include "esp.h"
#include "draw.h"
#include "main.h"

CHAR *OnOff  [] = { "[0/1]", "[1/1]" };
CHAR *Folder [] = { "[+]", "[-]" };
bool Create = false;

LPDIRECT3DDEVICE9 npDevice = NULL;
VOID StartMenu( LPDIRECT3DDEVICE9 pDevice )
{
	if( GetAsyncKeyState( VK_INSERT ) &1 )
		Show =! Show;
	
	if( Show && Menu.PFont )
	{
		Menu.DrawBox( 10, 35, 200, 23, BTBlack, Black, pDevice );
		Menu.DrawBorder( 10, 35, 200, 23, 1, Black, pDevice );

		Menu.DrawBox( 10, 60, 200, ( Current * 15 ), BBlack, Black, pDevice );
		Menu.DrawBorder( 10, 60, 200, ( Current * 15 ), 1, Black, pDevice );
		Menu.DrawD3DText( 30 + 13, 38, Menu_Titel, eMenu );

		Menu.DrawBorder( 10, 47 + ( D3DMenu * 15 ), 200, 13, 1, White, pDevice ); 

		Menu.DrawBox( 10, 62 + ( Current * 15 ), 200, 23, BTBlack, Black, pDevice );
		Menu.DrawBorder( 10, 62 + ( Current * 15 ), 200, 23, 1, Black, pDevice );
		Menu.DrawD3DText( 30 + 15, 65 + ( Current * 15 ), Menu_Titel, eSite );


		Current = 1;
		if( GetAsyncKeyState( VK_UP ) &1 )
			D3DMenu--;

		if( GetAsyncKeyState( VK_DOWN ) &1 )
			D3DMenu++;

		Menu.Additem( STR_esp,		1,  opt.esp.main, 1, Folder );
		if( opt.esp.main > 0 )
		{

			Menu.Additem( STR_espname,				1,			opt.esp.espname,				0, OnOff );
			Menu.Additem( STR_esphealth,			1,			opt.esp.esphp,					0, OnOff );
			Menu.Additem( STR_espbox,				1,			opt.esp.espbox,					0, OnOff );
			Menu.Additem( STR_espline,				1,			opt.esp.espline,				0, OnOff );
			Menu.Additem( STR_espdistance,			1,			opt.esp.espdistance,			0, OnOff );
		}

		Menu.Additem( STR_memory,		1,  opt.hack.main, 1, Folder );
		if( opt.hack.main > 0 )
		{

			Menu.Additem( STR_norecoil,				1,			opt.hack.recoil,				0, OnOff );
		}

		Menu.Additem( "[Options]",		1,  opt.options.main, 1, Folder );
		if( opt.options.main > 0 )
		{
			Menu.Additem( "Exit Game",				1,			opt.options.exit,				0, OnOff );
		}

		if( D3DMenu >= Current)
			D3DMenu = 1;
		else if( D3DMenu <= 0 )
			D3DMenu = Current - 1;
	}
}


HRESULT _stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!Create)
	{
		D3DXCreateFont( pDevice, 13, 0, 400, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,"Verdana", & Menu.PFont);
		Create = true;
	}

	if( Menu.PFont )
	{
		Menu.DrawD3DText(100, 100, Red, "DickHead");
		/*char txt[100];
		DWORD PPlayers = *(DWORD*)(0xE3EC70);
		if(PPlayers != NULL)
		{
			CGameCharaBasePH* Game = CGame.GetCharaByID(0);
			sprintf_s(txt, "Distance: [%d]", Game->getCurHP());
			Menu.DrawD3DText(100, 100, Red, txt);
		}*/
	} 
	return pEndScene(pDevice); 
}

 
void __cdecl nEndScene ( void )
{
     _asm pushad
	
	 npDevice = pRC->pRenderData->pDevice;

	 if (!Create)
	{
		D3DXCreateFont( npDevice, 13, 0, 400, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,"Verdana", & Menu.PFont);
		Create = true;
	}

	if( Menu.PFont )
	{
		char posxc[100], posyc[100], poszc[100];
		DWORD PPlayers = *(DWORD*)(0xE3EC70);
		if(PPlayers != NULL)
		{
			CallPlayerESP(npDevice);
			D3DXVECTOR3 PlayerPos;
			if(GetUserBone(PlayerPos, 0, 7))
			{
				sprintf_s(posxc, "PosX: [%0.2f]", PlayerPos.x);
				Menu.DrawD3DText(100, 100, Red, posxc);

				sprintf_s(posyc, "PosY: [%0.2f]", PlayerPos.y);
				Menu.DrawD3DText(100, 115, Red, posyc);

				sprintf_s(poszc, "PosZ: [%0.2f]", PlayerPos.z);
				Menu.DrawD3DText(100, 130, Red, poszc);
			}
		}
	}

     _asm popad
}
 
 
static DWORD hHooking           = NULL;
static DWORD hEndScene          = NULL;
 
typedef void ( WINAPI * EnterCriticalSection_t ) ( LPCRITICAL_SECTION lpCriticalSection );
EnterCriticalSection_t  pEnterCriticalSection;
void WINAPI nEnterCriticalSection ( LPCRITICAL_SECTION lpCriticalSection )
{
    _asm
    {
        MOV EAX, [EBP+0x4]
        MOV hHooking, EAX
    }

    if ( hHooking == hEndScene )
    {
        __asm call [nEndScene]
    }
    return pEnterCriticalSection(lpCriticalSection);
}
 
 
unsigned __stdcall Start ( LPVOID lpArg )
{     
            DWORD hD3D,hCriticalSection;
            do
            {
                 hD3D = (DWORD)GetModuleHandle(ed3d9);
                 Sleep(100);
            }    while(!hD3D);
 
 
            MEMORY_BASIC_INFORMATION D3D9Info;
            VirtualQuery((void*)(hD3D+0x1000),&D3D9Info,sizeof(D3D9Info));
 
            hCriticalSection = Tools.FindPattern((DWORD)D3D9Info.BaseAddress,D3D9Info.RegionSize,(PBYTE)"\x74\x07\x00\xFF\x15\x00\x00\x00\x00\x8D\x00\x00","xx?xx????x??",5,true);
            if ( !hCriticalSection )
            {
                exit(1);
            }
 
            if ( !hEndScene )
                hEndScene = Tools.FindPattern((DWORD)D3D9Info.BaseAddress,D3D9Info.RegionSize,(PBYTE)"\x57\xFF\x15\x00\x00\x00\x00\xF6\x46\x00\x00\x89\x5D\xFC\x75\x0E\x8B\x86\x00\x00\x00\x00\xA8\x01\xC6\x45\x00\x00\x75\x24","xxx????xx??xxxxxxx????xxxx??xx",7,false); // Win XP
            if ( !hEndScene )                
               hEndScene = Tools.FindPattern((DWORD)D3D9Info.BaseAddress,D3D9Info.RegionSize,(PBYTE)"\x57\xFF\x15\x00\x00\x00\x00\xE9\x00\x00\x00\x00\x39\x5F\x18\x74\x07\x57\xFF\x15\x00\x00\x00\x00\xB8\x00\x00\x00\x00\x8B\x4D\xF4\x64\x89\x0D\x00\x00\x00\x00\x59\x5F\x5E\x5B\x8B\xE5\x5D\xC2\x04\x00\x68\xAD\x06\x00\x00","xxx????x????xxxxxxxx????x????xxxxxx????xxxxxxxxxxxxx??",7,false); // Vista Win7
            if ( !hEndScene )
               hEndScene = Tools.FindPattern((DWORD)D3D9Info.BaseAddress,D3D9Info.RegionSize,(PBYTE)"\x33\xC0\xE8\x00\x00\x00\x00\xC2\x04\x00\x8B\xDF\xEB\x8E\x53\xFF\x15\x00\x00\x00\x00\xEB\x90","xxx????xxxxxxxxxx????xx",21,false);// Win8 8.0 + 8.1                
            if ( !hEndScene )
            {
                exit(1);
            }
 
            if ( hEndScene )
            {
               DWORD dwBack;
               VirtualProtect((void*)(hCriticalSection),4,PAGE_EXECUTE_READWRITE,&dwBack);
               pEnterCriticalSection       = (EnterCriticalSection_t) *(DWORD*)(hCriticalSection);
               *(DWORD*)(hCriticalSection) = (DWORD)nEnterCriticalSection;
               VirtualProtect((void*)(hCriticalSection),4,dwBack,&dwBack);
              return EXIT_SUCCESS;
            }
 
     return EXIT_FAILURE;
}

void JhemWrite(void *adress,void *bytes,int size)
{
	DWORD dwProtect;
	VirtualProtect((void*)adress,size,PAGE_EXECUTE_READWRITE,&dwProtect);
	memcpy((void *)adress,(PBYTE)bytes,size); 
	VirtualProtect((void*)adress,size,dwProtect,&dwProtect); 
}

unsigned __stdcall StartBypapss ( LPVOID lpArg )
{
	for(;;)
	{
		JhemWrite((void*)0x4AFEE0, (void*)"\x90\x90\x90", 3);
		JhemWrite((void*)0x4AFF80, (void*)"\xC3", 1);
		JhemWrite((void*)0xC19A74, (void*)"\x00", 1);
		JhemWrite((void*)0xC19AAC, (void*)"\x00", 1);
		JhemWrite((void*)0xC19AB8, (void*)"\x00", 1);
		JhemWrite((void*)0xC19BB4, (void*)"\x00", 1);
		JhemWrite((void*)0xC19BDC, (void*)"\x00", 1);
		JhemWrite((void*)0xC19BF4, (void*)"\x00", 1);
	}
	return 0;
}

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		_beginthreadex(0, 0, StartBypapss, 0, 0, 0);
	}
	return TRUE;
}