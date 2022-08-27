// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"


unsigned __stdcall MainThread(LPVOID param)
{
	Garena->InstallHook(param);
	return 0;
}


BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		//Misc.EraseHeaders(hDll);
		//Misc.HideModule(hDll);
		_beginthreadex(0, 0, MainThread, 0, 0, 0);
	}
	return TRUE;
}