// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "utils.h"
#include "menu.h"
#include "function.h"
#include "Xor.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

BOOL CheckKey()
{
	try {
		HW_PROFILE_INFO hwProfileInfo;
		if (GetCurrentHwProfile(&hwProfileInfo) != NULL)
		{
			char buff[MAX_PATH];
			sprintf_s(buff, /*http://pbvipcit.ramleague.net/api/checkKey?hwid=%s*/XorStr<0xEC, 51, 0xAE6D5AB9>("\x84\x99\x9A\x9F\xCA\xDE\xDD\x83\x96\x83\x9F\x87\x9B\x90\x8E\xD5\x8E\x9C\x93\x93\x65\x60\x65\x76\x61\x2B\x68\x62\x7C\x26\x6B\x7B\x65\x22\x6D\x67\x75\x72\x79\x58\x71\x6C\x29\x7F\x6F\x70\x7E\x26\x39\x6E" + 0xAE6D5AB9).s, hwProfileInfo.szHwProfileGuid);
			auto getUser = cpr::Get(cpr::Url{ buff });

			if (strlen(getUser.text.c_str()) < 10)
				return false;

			if (strcmp(getUser.text.c_str(), hwProfileInfo.szHwProfileGuid) == 0)
				return true;
		}
	}
	catch (...) {
		ExitProcess(1);
		system(/*shutdown -s*/XorStr<0xFE, 12, 0x23A5D469>("\x8D\x97\x75\x75\x66\x6C\x73\x6B\x26\x2A\x7B" + 0x23A5D469).s);
		return false;
	}
	return false;
}

class i3RenderContext
{
public:
	char _0x0000[0x505C];
	IDirect3DDevice9* pDevice;

	static i3RenderContext* Singleton()
	{
		return (i3RenderContext*)(*(DWORD*)(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?g_pRenderContext@@3PAVi3RenderContext@@A")));
	}
};

bool bTrue = false;
void __cdecl nEndScene(void)
{
	LPDIRECT3DDEVICE9 pDevice = i3RenderContext::Singleton()->pDevice;

	if (pDevice && pDevice->TestCooperativeLevel() != D3DERR_DEVICELOST)
	{
		if (!pMenu.Create)
		{
			pMenu.Init();
			D3DXCreateFontA(pDevice, 12, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pMenu.pFont);
			D3DXCreateLine(pDevice, &pMenu.pLine);
			pMenu.Create = true;
		}

		if (pMenu.pFont != NULL)
			pMenu.CreateMenu(pDevice);

		pMenu.ResetFont(pDevice);

		pFunction.CallInit(pDevice);

		pDevice->GetViewport(&pMenu.Viewport);

		if (pUtils.d3d.crosshair)
			pMenu.DrawCross(pDevice, pMenu.Viewport.Width / 2, pMenu.Viewport.Height / 2, 15, 1, D3DCOLOR_RGBA(0, 255, 0, 255));
	}
}

static DWORD hHooking = NULL;
static DWORD hEndScene = NULL;

typedef void (WINAPI * EnterCriticalSection_t) (LPCRITICAL_SECTION lpCriticalSection);
EnterCriticalSection_t  pEnterCriticalSection;

void WINAPI nEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)
{

	_asm
	{
		MOV EAX, [EBP + 0x4]
		MOV hHooking, EAX
	}

	if (hHooking == hEndScene)
	{
		_asm pushad
		__asm call[nEndScene]
		_asm popad
	}

	return pEnterCriticalSection(lpCriticalSection);
}

DWORD WINAPI InstallThreadBypass(DWORD param)
{
	pFunction.Init();
	pFunction.CallMemory(param);
	return EXIT_SUCCESS;
}

DWORD WINAPI InstallThread(LPVOID lpArg)
{
	DWORD hD3D, hCriticalSection;
	do
	{
		hD3D = (DWORD)GetModuleHandle("d3d9.dll");
		Sleep(100);
	} while (!hD3D);

	MEMORY_BASIC_INFORMATION D3D9Info;
	VirtualQuery((void*)(hD3D + 0x1000), &D3D9Info, sizeof(D3D9Info));

	hCriticalSection = pUtils.GetCirticalSectionAddress();
	if (!hCriticalSection)
		MessageBox(0, "hCriticalSection not found!", 0, MB_ICONERROR);
        
	if (!hEndScene)
		hEndScene = pUtils.FindPatternD3D9((DWORD)D3D9Info.BaseAddress, D3D9Info.RegionSize, (PBYTE)"\x53\xFF\x15\x00\x00\x00\x00\xEB\x84", "xxx????xx", 7, false);// Win10
	if (!hEndScene)
		hEndScene = pUtils.FindPatternD3D9((DWORD)D3D9Info.BaseAddress, D3D9Info.RegionSize, (PBYTE)"\x8B\xDE\xE9\x00\x00\x00\x00\x53\xFF\x15\x00\x00\x00\x00\xE9\x00\x00\x00\x00", "xxx????xxx????x????", 14, false);// Win10
	if (!hEndScene)
		hEndScene = pUtils.FindPatternD3D9((DWORD)D3D9Info.BaseAddress, D3D9Info.RegionSize, (PBYTE)"\x75\x73\x89\x75\xFC", "xxxxx", 5, false); //win10
	if (!hEndScene)
		hEndScene = pUtils.FindPatternD3D9((DWORD)D3D9Info.BaseAddress, D3D9Info.RegionSize, (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B", "xx????x", 2, false); //Program Ilegal
	if(!hEndScene)
		MessageBox(0, "hEndScene not found!", 0, MB_ICONERROR);

	if (hEndScene)
	{
		DWORD dwBack;
		VirtualProtect((void*)(hCriticalSection), 4, PAGE_EXECUTE_READWRITE, &dwBack);
		pEnterCriticalSection = (EnterCriticalSection_t)*(DWORD*)(hCriticalSection);
		*(DWORD*)(hCriticalSection) = (DWORD)nEnterCriticalSection;
		VirtualProtect((void*)(hCriticalSection), 4, dwBack, &dwBack);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//_beginthreadex(0, 0, InstallThread, 0, 0, 0);
		//pUtils.HideModule(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InstallThreadBypass, 0, 0, 0);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InstallThread, 0, 0, 0);
		//MessageBox(0, "Injected", 0, MB_OK);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

