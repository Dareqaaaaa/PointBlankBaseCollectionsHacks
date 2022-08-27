#include <windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <tlhelp32.h>
#include <process.h>
#include <stdint.h>
#include <string>


#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

using namespace std;

LPD3DXFONT pFont;
DWORD dwBaseAddress = NULL;

#include "XOR.h"
#include "tools.h"
#include "main.h"
#include "menu.h"
#include "int.h"
#include "adressen.h"
#include "class.h"
#include "esp.h"
#include "aimbot.h"
#include "memory.h"

bool Create = false;
char *opt_OnOff[]   = {"[OFF]", "[ON]"};

void CreateMenu (LPDIRECT3DDEVICE9 pDevice)
{
	if(GetAsyncKeyState(VK_INSERT)&1) 
		Show = !Show;

	if(Show)
	{
		if(GetAsyncKeyState(VK_UP)&1)
			MenuSelection--;

		if(GetAsyncKeyState(VK_DOWN)&1) 
			MenuSelection++;

		DrawBox(pDevice, 20, 11, 190, 20, 1, D3DCOLOR_ARGB(220,96,144,242), D3DCOLOR_ARGB(220,5,5,5));
		cWriteText(110, 14, D3DCOLOR_ARGB(255, 000, 255, 000), "PB INDO");
		DrawBox(pDevice, 20, 34, 190, ( Current * 15 ), 1, D3DCOLOR_ARGB(220,50,50,50), D3DCOLOR_ARGB(220,5,5,5));

		DrawBorder(pDevice, 20, 26 + ( MenuSelection * 15 ), 190, 15, 1, D3DCOLOR_ARGB(255, 255, 255, 255));

		DrawBox(pDevice, 20, 35 + ( Current * 15) , 190, 18, 1, D3DCOLOR_ARGB(220,96,144,242), D3DCOLOR_ARGB(220,5,5,5));
		cWriteText(110, 38 + ( Current * 15 ), D3DCOLOR_ARGB(255, 000, 255, 000), eSite);

		Current = 1;
		Kategorie(pDevice, STR_aimbot);


		if(MenuSelection >= Current)
			MenuSelection = 1;

		if(MenuSelection < 1)
			MenuSelection = Current;
	}
}
 

typedef  HRESULT(STDMETHODCALLTYPE *TSwapChainPresent)(IDirect3DSwapChain9* This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags);
TSwapChainPresent pSwapChainPresent = NULL;

HRESULT __stdcall hook_D3D9SwapChainPresent(IDirect3DSwapChain9 * This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags)
{
	IDirect3DDevice9 *pDevice;
	This->GetDevice(&pDevice);

	if (!Create)
	{
		D3DXCreateFontA(pDevice, 12, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFont);
		Create = true;
	}

	if (pFont == NULL)
		pFont->OnLostDevice();
	if (pFont != NULL)
		CreateMenu(pDevice);

	pDevice->Release();
	return pSwapChainPresent(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

void InstallHook()
{
	DWORD hD3D;
	do
	{
		hD3D = (DWORD)GetModuleHandle(ed3d9);
		Sleep(100);
	}while(!hD3D);

	void** d3d9SwapChain;
	bool bStatus = GetSwapChainAddress(d3d9SwapChain, sizeof(d3d9SwapChain));
	if (bStatus)
		pSwapChainPresent = (TSwapChainPresent)CreateDetour((PBYTE)d3d9SwapChain[3], (PBYTE)hook_D3D9SwapChainPresent, 5, 0xE9);

	return;
}

BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		EraseHeaders(hinstDLL);
		HideModule(hinstDLL);
		CreateStealthThread((threadFunc_t)InstallHook,0);
		break;
	}
	return true;
}