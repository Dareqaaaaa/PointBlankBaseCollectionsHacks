#include <Windows.h>
#include <fstream>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include "XOR.h"
#include "main.h"

DWORD retMyDIP;
void D3Dfunktionen(LPDIRECT3DDEVICE9 pDevice)
{
	IDirect3DVertexBuffer9* pStreamData = NULL;
	UINT iOffsetInBytes, iStride;
	pDevice->GetStreamSource(0, &pStreamData, &iOffsetInBytes, &iStride);
}

__declspec(naked) HRESULT WINAPI MyDIP()
{
	static LPDIRECT3DDEVICE9 pDevice;

	__asm
	{
		MOV EDI, EDI
		PUSH EBP
		MOV EBP, ESP
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOV pDevice, EAX
	}

	__asm
	{
		JMP retMyDIP
	}
}


void Hook()
{
	DWORD hD3D = NULL;
	do {
		hD3D = (DWORD)LoadLibrary(ed3d9);
		if (!hD3D) Sleep(200);
	} while (!hD3D);

	DWORD *vtbl;

	DWORD adr = FindPattern(hD3D, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	if (adr)
	{
		memcpy(&vtbl, (void*)(adr + 2), 4);
		retMyDIP = vtbl[147] + 0x5;
		MakeJMP((PBYTE)vtbl[147], (DWORD)MyDIP, 0x5);

	}
}

extern "C"
{
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
	{
		switch (fdwReason)
		{
		case DLL_PROCESS_ATTACH:
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Hook, 0, 0, 0);
			break;
		}
		return true;
	}
}