#include "stdafx.h"

UtilsT * Utils = new UtilsT();

const char * UtilsT::bones[22] = 
{
	"Neck",			//0
	"Head",			//1
	"Spine1",		//2
	"Pelvis",		//3
	"L Clavicle",	//4
	"R Clavicle",	//5
	"L UpperArm",	//6
	"L Forearm",	//7
	"L Hand",		//8
	"L Thumb1",		//9
	"R UpperArm",	//10
	"R Forearm",	//11
	"R Hand",		//12
	"R Thumb1",		//13
	"L Thigh",		//14
	"L Calf",		//15
	"L Foot",		//16
	"L Toe",		//17
	"R Thigh",		//18
	"R Calf",		//19
	"R Foot",		//20
	"R Toe"			//21
};

DWORD UtilsT::GetAddressByRecoil(DWORD Ptr_Recoil, DWORD Ptr_Chara)
{
	DWORD retBaseAddress = 0;
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	uintptr_t address = 0;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	while (address < reinterpret_cast<uintptr_t>(si.lpMaximumApplicationAddress))
	{
		SIZE_T size = VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (!size)
			address += si.dwPageSize;

		if (mbi.Protect == PAGE_EXECUTE_READWRITE && mbi.RegionSize >= 10000000)
		{
			if (*(BYTE*)((DWORD)mbi.BaseAddress + Ptr_Recoil) == 0x52)
			{
				Function->CallMemory((DWORD)mbi.BaseAddress);
			}

			if (*(DWORD*)((DWORD)mbi.BaseAddress + Ptr_Chara))
			{
				return (DWORD)mbi.BaseAddress;
			}
		}
		address += mbi.RegionSize;
	}
	return -1;
}

DWORD UtilsT::GetAddress(DWORD Ptr_Chara)
{
	int timer = GetTickCount() + (1000 * 60);
	int counter = 0;
	DWORD retBaseAddress = 0;
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	uintptr_t address = 0;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	while (address < reinterpret_cast<uintptr_t>(si.lpMaximumApplicationAddress))
	{
		if (GetTickCount() > timer)
			break;

		SIZE_T size = VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<LPVOID>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (!size)
			address += si.dwPageSize;
		
		if (mbi.Protect == PAGE_EXECUTE_READWRITE && mbi.RegionSize >= 10000000)
		{
			if (*(DWORD*)((DWORD)mbi.BaseAddress + Ptr_Chara))
			{
				if(!retBaseAddress)
					retBaseAddress = (DWORD)mbi.BaseAddress;

				if (counter > 3)
					break;

				Garena->dwBaseArray[counter] = (DWORD)mbi.BaseAddress;
				counter++;

			}
		}
		address += mbi.RegionSize;
	}
	return retBaseAddress;
}

DWORD UtilsT::MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect, dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);
	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}

void UtilsT::WriteProtect(void *adress, void *bytes, int size)
{
	DWORD dwProtect;
	VirtualProtect((void*)adress, size, PAGE_EXECUTE_READWRITE, &dwProtect);
	memcpy((void *)adress, (PBYTE)bytes, size);
	VirtualProtect((void*)adress, size, dwProtect, &dwProtect);
}

void UtilsT::EraseHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;
	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);
	ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
	{
		for (i = 0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}

void UtilsT::HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]
			mov eax, [eax + 0Ch]
			mov dwPEB_LDR_DATA, eax

			InLoadOrderModuleList :
		mov esi, [eax + 0Ch]
			mov edx, [eax + 10h]

			LoopInLoadOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 18h]
			cmp ecx, hModule
			jne SkipA
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InMemoryOrderModuleList

			SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList

			InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]

			LoopInMemoryOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 10h]
			cmp ecx, hModule
			jne SkipB
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InInitializationOrderModuleList

			SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList

			InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]

			LoopInInitializationOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 08h]
			cmp ecx, hModule
			jne SkipC
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp Finished

			SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList

			Finished :
		popfd;
		popad;
	}
}

BOOL UtilsT::GetSwapChainAddress(void ** pTable, size_t Size)
{
	D3DPRESENT_PARAMETERS D3DPP = { 0 };
	D3DPP.Windowed = TRUE;
	D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DPP.hDeviceWindow = GetForegroundWindow();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
	{
		//printf("Direct3DCreate9 failed: 0x%X", (DWORD)GetLastError());
		return false;
	}

	HRESULT hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DPP.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3DPP, &pDevice);
	if (FAILED(hr))
	{
		//printf("CreateDevice failed: 0x%X", (DWORD)hr);
		pD3D->Release();
		return false;
	}

	IDirect3DSwapChain9 * pSwapChain = nullptr;
	hr = pDevice->GetSwapChain(0, &pSwapChain);
	if (FAILED(hr))
	{
		//printf("GetSwapChain failed: 0x%X", (DWORD)hr);
		pDevice->Release();
		pD3D->Release();
		return false;
	}

	void ** VTable = *reinterpret_cast<void***>(pSwapChain);
	memcpy(pTable, VTable, Size);

	//printf("IDirect3DSwapChain9::Present 0x%p\n", VTable[3]);

	pSwapChain->Release();
	pDevice->Release();
	pD3D->Release();

	return true;
}


VOID UtilsT::WriteJump(DWORD dwFunction, DWORD dwAddress)
{
	BYTE DetourBytes[5] = { 0xE9,0x00,0x00,0x00,0x00 };
	*(DWORD*)(&DetourBytes[1]) = (dwFunction - dwAddress) - 0x5;
	WriteMemory((LPVOID)dwAddress, (LPBYTE)DetourBytes, 5);
}

VOID UtilsT::WriteMemory(LPVOID lpAddress, LPBYTE lpBuffer, DWORD dwLengh)
{
	LPBYTE pAddress = (LPBYTE)lpAddress;
	LPBYTE pBuffer = (LPBYTE)lpBuffer;
	MEMORY_BASIC_INFORMATION MBI;
	VirtualQuery(lpAddress, &MBI, sizeof(MBI));
	VirtualProtect(MBI.BaseAddress, MBI.RegionSize, PAGE_EXECUTE_READWRITE, &MBI.Protect);
	while (dwLengh-- > 0)
	{
		*pAddress++ = *pBuffer++;
	}
	VirtualProtect(MBI.BaseAddress, MBI.RegionSize, MBI.Protect, &MBI.Protect);
	FlushInstructionCache(GetCurrentProcess(), lpAddress, dwLengh);
}