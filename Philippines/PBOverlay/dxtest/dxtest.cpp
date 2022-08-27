// dxtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
int _tmain(int argc, _TCHAR* argv[])
{
	Debug->Log(L"Hack Initiated.");
	while (true)
	{
		Overlay->RefreshOverlay();
	}
	return 0;
}
*/

int StartRoutine()
{
	do {
		Globals->Base.Address = Utils->EnumRegions(GetCurrentProcess(), Function->ADR_CHECK);
		if(!Globals->Base.Address) Sleep(200);
	} while (!Globals->Base.Address);

	Debug->Log(L"Hack Initiated.");
	while (true)
	{
		Overlay->RefreshOverlay();
	}
	return 0;
}

BOOL WINAPI DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		//HideModule(hinstDLL);
		//MessageBox(0, "Hooked", "TURUE", 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartRoutine, 0, 0, 0);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}