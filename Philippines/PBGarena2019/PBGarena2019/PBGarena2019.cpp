// PBGarena2019.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

GarenaT * Garena = new GarenaT();

typedef  HRESULT(STDMETHODCALLTYPE *TSwapChainPresent)(IDirect3DSwapChain9* This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags);
TSwapChainPresent pSwapChainPresent = NULL;

HRESULT __stdcall hook_D3D9SwapChainPresent(IDirect3DSwapChain9 * This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags)
{
	IDirect3DDevice9 *pDevice;
	This->GetDevice(&pDevice);

	if (!Menu->Create)
	{
		D3DXCreateFontA(pDevice, 12, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &Menu->pFont);
		D3DXCreateLine(pDevice, &Menu->pLine);
		Menu->Create = true;
	}

	if (Menu->pFont != NULL)
		Menu->CreateMenu(pDevice);

	/*if (Garena->dwBase)
	{
		Function->CallESP(pDevice);
		Function->CallAimbot();
		Function->CallAimBullet();
	}*/

	pDevice->GetViewport(&Menu->Viewport);

	pDevice->Release();
	return pSwapChainPresent(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

unsigned __stdcall  GarenaT::InstallHook(LPVOID param)
{
	//Address->SetPointers();

	/*while (1)
	{
		dwBase = Utils->GetAddressByRecoil(Address->RecoilHorzAngle, Address->ADR_CHARACTERPOINTER);
		if (dwBase != -1)
			break;
	}
	dwBase = NULL;*/

	bool bStatus = Utils->GetSwapChainAddress(d3d9SwapChain, sizeof(d3d9SwapChain));
	if (bStatus)
		pSwapChainPresent = (TSwapChainPresent)DetourFunction((PBYTE)d3d9SwapChain[3], (PBYTE)hook_D3D9SwapChainPresent);
		
	/*do {
		dwBase = Utils->GetAddress(Address->ADR_CHARACTERPOINTER);
		if (!dwBase) Sleep(200);
	} while (!dwBase);

	dwBase = dwGetRealBase();*/

	do {
		if (!Utils->i3FrameworkDx) Utils->i3FrameworkDx = GetModuleHandleA(/*i3FrameworkDx.dll*/XorStr<0x9B, 18, 0xFE033128>("\xF2\xAF\xDB\xEC\xFE\xCD\xC4\xD5\xCC\xD6\xCE\xE2\xDF\x86\xCD\xC6\xC7" + 0xFE033128).s);
		if (!Utils->i3MathDx) Utils->i3MathDx = GetModuleHandleA(/*i3MathDx.dll*/XorStr<0x0C, 13, 0xF750A491>("\x65\x3E\x43\x6E\x64\x79\x56\x6B\x3A\x71\x7A\x7B" + 0xF750A491).s);
		if (!Utils->i3SceneDx) Utils->i3SceneDx = GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0x9A, 14, 0x8DDF9D84>("\xF3\xA8\xCF\xFE\xFB\xF1\xC5\xE5\xDA\x8D\xC0\xC9\xCA" + 0x8DDF9D84).s);
		if (!Utils->i3GfxDx) Utils->i3GfxDx = GetModuleHandleA(/*i3GfxDx.dll*/XorStr<0x92, 12, 0x707656D2>("\xFB\xA0\xD3\xF3\xEE\xD3\xE0\xB7\xFE\xF7\xF0" + 0x707656D2).s);
		Sleep(10);
	} while (!Utils->i3FrameworkDx || !Utils->i3MathDx || !Utils->i3SceneDx || !Utils->i3GfxDx);

	//Function->CallMemoryGame();

	return 1;
}