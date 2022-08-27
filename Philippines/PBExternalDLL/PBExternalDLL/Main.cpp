#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include <windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <tlhelp32.h>
#include <iostream>
#include <process.h>
#include <stdint.h>
#include <string>
#include <detours.h>

LPD3DXFONT pFont;
ID3DXLine *pLine;
D3DVIEWPORT9 Viewport;
bool Create = false;
DWORD dwBaseAddress = NULL;
DWORD dwi3Skeleton = NULL;
void * d3d9SwapChain[20];

typedef  HRESULT(STDMETHODCALLTYPE *TSwapChainPresent)(IDirect3DSwapChain9* This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags);
TSwapChainPresent pSwapChainPresent = NULL;

#include "Menu.h"
#include "Utils.h"
#include "Address.h"
#include "Aimbot.h"
#include "ESP.h"

const char *opt_OnOff[] = { "[OFF]", "[ON]" };
const char *opt_BoneKey[] = { "[SHIFT]", "[LBUTTON]", "[AUTO]" };
const char *opt_BoneTarget[] = { "[Head]", "[Neck]", "[Body]" };
const char *opt_BoneOption[] = { "[Recommended]", "[Normal]", "[Big]" };

void CreateMenu(LPDIRECT3DDEVICE9 pDevice)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		Show = !Show;

	if (Show)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
			MenuSelection--;

		if (GetAsyncKeyState(VK_DOWN) & 1)
			MenuSelection++;

		DrawBox(pDevice, 20, 11, 190, 20, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 14, Green, "POINTBLANK RAML");
		DrawBox(pDevice, 20, 34, 190, (Current * 15), 1, D3DCOLOR_ARGB(220, 50, 50, 50), D3DCOLOR_ARGB(220, 5, 5, 5));

		DrawBorder(pDevice, 20, 26 + (MenuSelection * 15), 190, 15, 1, White);

		DrawBox(pDevice, 20, 35 + (Current * 15), 190, 18, 1, D3DCOLOR_ARGB(220, 96, 144, 242), D3DCOLOR_ARGB(220, 5, 5, 5));
		cWriteText(110, 38 + (Current * 15), Green, "WWW.RANDOM.NET");

		Current = 1;

		Kategorie(pDevice, "[Aimbot]");
		AddItem(pDevice, "Enable Aimbot", opt.aimbot.main, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Smooth", opt.aimbot.smooth, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Fov", opt.aimbot.fov, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Draw", opt.aimbot.draw, opt_OnOff, 1);
		AddItem(pDevice, "Aimbot Key", opt.aimbot.key, opt_BoneKey, 2);

		Kategorie(pDevice, "[ESP]");
		AddItem(pDevice, "ESP Box", opt.esp.espbox, opt_OnOff, 1);
		AddItem(pDevice, "ESP Line", opt.esp.espline, opt_OnOff, 1);
		AddItem(pDevice, "ESP Health", opt.esp.esphealth, opt_OnOff, 1);
		AddItem(pDevice, "ESP Skeleton", opt.esp.espbone, opt_OnOff, 1);

		if (MenuSelection >= Current)
			MenuSelection = 1;

		if (MenuSelection < 1)
			MenuSelection = Current;
	}
}

bool espbone = false;

HRESULT __stdcall hook_D3D9SwapChainPresent(IDirect3DSwapChain9 * This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags)
{
	IDirect3DDevice9 *pDevice;
	This->GetDevice(&pDevice);

	if (!Create)
	{
		D3DXCreateFontA(pDevice, 12, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFont);
		Create = TRUE;
	}

	//if (pFont != NULL)
		//CreateMenu(pDevice);

	pDevice->GetViewport(&Viewport);

	if (dwBaseAddress != NULL)
	{
		auto pLocal = GameObject.GetCharaByID(GetMyIndex());
		if (pLocal)
		{
			for (int i = 0; i < 16; i++)
			{
				D3DXVECTOR3 vWorld, vScreen;
				if (GetBoneMatrix(vWorld, bones[1], i))
				{
					if (ADDXW2S(pDevice, vWorld, vScreen))
					{
						ESP.ESPDrawSkeleton(i, White, pDevice);
					}
				}
			}
		}

		//CallESP(pDevice);
		//CallAimbot(pDevice);
	}

	pDevice->Release();
	return pSwapChainPresent(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

unsigned __stdcall InstallHook(LPVOID param)
{
	
	bool bSuccess = GetAddress(d3d9SwapChain, sizeof(d3d9SwapChain));
	if (bSuccess)
	{
		pSwapChainPresent = (TSwapChainPresent)DetourFunction((BYTE*)d3d9SwapChain[3], (BYTE*)hook_D3D9SwapChainPresent);
	}
	return 1;
}

unsigned int __stdcall MyThread(void * pArgs)
{
	do {
		dwBaseAddress = EnumRegions(GetCurrentProcess(), ADR_CHARACTERPOINTER);
		if (!dwBaseAddress) Sleep(200);
	} while (!dwBaseAddress);

	return 1;
}

BOOL WINAPI DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		EraseHeaders(hinstDLL);
		HideModule(hinstDLL);
		_beginthreadex(0, 0, InstallHook, 0, 0, 0);
		_beginthreadex(0, 0, MyThread, 0, 0, 0);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}