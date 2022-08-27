// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "utils.h"
#include "menu.h"
#include "function.h"

typedef  HRESULT(STDMETHODCALLTYPE *TSwapChainPresent)(IDirect3DSwapChain9* This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags);
TSwapChainPresent pSwapChainPresent = NULL;

HRESULT __stdcall hook_D3D9SwapChainPresent(IDirect3DSwapChain9 * This, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags)
{
	IDirect3DDevice9 *pDevice;
	This->GetDevice(&pDevice);

	if (!pMenu.Create)
	{
		pMenu.Init();
		pUtils.hD3DXCreateFont(pDevice, 12, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pMenu.pFont);
		pUtils.hD3DXCreateLine(pDevice, &pMenu.pLine);
		pMenu.Create = true;
	}

	if (pMenu.pFont != NULL)
		pMenu.CreateMenu(pDevice);


	pFunction.CallEsp(pDevice);
	pFunction.CallAimBullet(pDevice);
	pFunction.CallAimbot(pDevice);

	pDevice->GetViewport(&pMenu.Viewport);

	pDevice->Release();
	return pSwapChainPresent(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

INT InstallThread()
{
	pFunction.Init();
	void * d3d9SwapChain[20];
	bool bStatusHook = pUtils.GetSwapChainAddress(d3d9SwapChain, sizeof(d3d9SwapChain));
	if(bStatusHook)
		pSwapChainPresent = (TSwapChainPresent)pUtils.DetourCreate((PBYTE)d3d9SwapChain[3], (PBYTE)hook_D3D9SwapChainPresent, 5);

	pFunction.CallMemory();

	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InstallThread, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

