#include "StdAfx.h"
#include "utils.h"
#include "Xor.h"

utils pUtils;

utils::utils()
{
}


utils::~utils()
{
}

DWORD utils::MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect, dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);
	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}

BOOL utils::GetSwapChainAddress(void ** pTable, size_t Size)
{
	D3DPRESENT_PARAMETERS D3DPP = { 0 };
	D3DPP.Windowed = TRUE;
	D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DPP.hDeviceWindow = GetForegroundWindow();
	LPDIRECT3DDEVICE9 pDevice = NULL;

	LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return false;

	HRESULT hr = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DPP.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3DPP, &pDevice);
	if (FAILED(hr))
	{
		pD3D->Release();
		return false;
	}

	IDirect3DSwapChain9 * pSwapChain = nullptr;
	hr = pDevice->GetSwapChain(0, &pSwapChain);
	if (FAILED(hr))
	{
		pDevice->Release();
		pD3D->Release();
		return false;
	}

	void ** VTable = *reinterpret_cast<void***>(pSwapChain);
	memcpy(pTable, VTable, Size);

	pSwapChain->Release();
	pDevice->Release();
	pD3D->Release();

	return true;
}

DWORD utils::GetCirticalSectionAddress()
{
	HMODULE mhD3D = NULL;
	do
	{
		mhD3D = GetModuleHandle("d3d9.dll");
		Sleep(50);
	} while (!mhD3D);

	PIMAGE_DOS_HEADER DosHeader = (PIMAGE_DOS_HEADER)mhD3D;
	PIMAGE_NT_HEADERS NtHeader;
	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor;
	UINT Index;
	NtHeader = (PIMAGE_NT_HEADERS)(((PBYTE)DosHeader) + DosHeader->e_lfanew);
	if (NtHeader->Signature != IMAGE_NT_SIGNATURE) return 0;
	ImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(((PBYTE)DosHeader) + NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	__try {
		for (Index = 0; ImportDescriptor[Index].Characteristics != 0; Index++)
		{
			PSTR dllName = (PSTR)(((PBYTE)DosHeader) + ImportDescriptor[Index].Name);
			if (_strcmpi(dllName, "kernel32.dll") == 0)
			{
				PIMAGE_THUNK_DATA Thunk;
				PIMAGE_THUNK_DATA OrigThunk;
				if (!ImportDescriptor[Index].FirstThunk || !ImportDescriptor[Index].OriginalFirstThunk)
					return E_INVALIDARG;
				Thunk = (PIMAGE_THUNK_DATA)(((PBYTE)DosHeader) + ImportDescriptor[Index].FirstThunk);
				OrigThunk = (PIMAGE_THUNK_DATA)(((PBYTE)DosHeader) + ImportDescriptor[Index].OriginalFirstThunk);
				for (; OrigThunk->u1.Function != NULL; OrigThunk++, Thunk++)
				{
					if (OrigThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) continue;
					PIMAGE_IMPORT_BY_NAME importt = (PIMAGE_IMPORT_BY_NAME)(((PBYTE)DosHeader) + OrigThunk->u1.AddressOfData);
					if (strcmp("EnterCriticalSection", (char*)importt->Name) == 0)
					{
						return (DWORD)Thunk;
					}
				}
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		MessageBoxA(NULL, TEXT("Exception hit parsing imports"), TEXT("Error!"), MB_OK | MB_ICONINFORMATION); //
		return false;
	}
	return EXIT_SUCCESS;
}


BOOL utils::CheckWindowsVersion(DWORD dwMajorVersion, DWORD dwMinorVersion, DWORD dwProductType)
{
	OSVERSIONINFOEX VersionInfo;
	ZeroMemory(&VersionInfo, sizeof(OSVERSIONINFOEX));
	VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
	GetVersionEx((OSVERSIONINFO*)&VersionInfo);
	if (VersionInfo.dwMajorVersion == dwMajorVersion)
	{
		if (VersionInfo.dwMinorVersion == dwMinorVersion)
		{
			if (VersionInfo.wProductType == dwProductType)
			{
				return (TRUE);
			}
		}
	}
	return (FALSE);
}



DWORD utils::FindPatternD3D9(DWORD dwStartAddress, DWORD dwSize, BYTE *bMask, char * szMask, int codeOffset, BOOL extract)
{
	for (DWORD i = 0; i < dwSize; i++)
	{
		if (DataCompare((BYTE*)(dwStartAddress + i), bMask, szMask))
		{
			if (extract)
			{
				return *(DWORD*)(dwStartAddress + i + codeOffset);

			}
			else {

				return  (DWORD)(dwStartAddress + i + codeOffset);
			}
		}
	}
	return NULL;
}

DWORD utils::FindPattern(DWORD start, DWORD size, const char* sig, const char* mask) {
	BYTE* data = new BYTE[size];

	unsigned long bytesRead;
	if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)start, data, size, &bytesRead)) {
		return NULL;
	}

	for (DWORD i = 0; i < size; i++) {
		if (DataCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
			return start + i;
		}
	}
	return NULL;
}


DWORD utils::FindPatternArray(DWORD start, DWORD size, const char* mask, int count, ...) {
	char* sig = new char[count + 1];
	va_list ap;
	va_start(ap, count);
	for (int i = 0; i < count; i++) {
		char read = va_arg(ap, char);
		sig[i] = read;
	}
	va_end(ap);
	sig[count] = '\0';
	return FindPattern(start, size, sig, mask);
}

bool utils::DataCompare(const BYTE* pData, const BYTE* pMask, const char* pszMask) {
	for (; *pszMask; ++pszMask, ++pData, ++pMask) {
		if (*pszMask == 'x' && *pData != *pMask) {
			return false;
		}
	}
	return (*pszMask == NULL);
}

void utils::HideModule(HINSTANCE hModule)
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

PModule utils::GetModule(char* moduleName) {
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do {
		if (!strcmp(mEntry.szModule, (LPSTR)moduleName)) {
			CloseHandle(module);

			PModule mod = { (DWORD)mEntry.hModule, mEntry.modBaseSize };
			return mod;
		}
	} while (Module32Next(module, &mEntry));

	PModule mod = { (DWORD)false, (DWORD)false };
	return mod;
}

PModule utils::GetBaseAddress()
{
	PModule mod = { (DWORD)false, (DWORD)false };
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
			mod.dwBase = (DWORD)mbi.BaseAddress;
			mod.dwSize = (DWORD)mbi.RegionSize;
		}
		address += mbi.RegionSize;
	}
	return mod;
}

PModule* utils::GetClientModule() 
{
	modBase = GetBaseAddress();
	modCheatBlocker = GetModule(/*cb.cbm*/XorStr<0x32, 7, 0x9ED461FC>("\x51\x51\x1A\x56\x54\x5A" + 0x9ED461FC).s);
	modi3SceneDx.dwBase = (DWORD)GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0x9A, 14, 0x8DDF9D84>("\xF3\xA8\xCF\xFE\xFB\xF1\xC5\xE5\xDA\x8D\xC0\xC9\xCA" + 0x8DDF9D84).s);
	modi3GfxDx.dwBase = (DWORD)GetModuleHandleA(/*i3GfxDx.dll*/XorStr<0x92, 12, 0x707656D2>("\xFB\xA0\xD3\xF3\xEE\xD3\xE0\xB7\xFE\xF7\xF0" + 0x707656D2).s);
	modi3FrameworkDx.dwBase = (DWORD)GetModuleHandleA(/*i3FrameworkDx.dll*/XorStr<0x9B, 18, 0xFE033128>("\xF2\xAF\xDB\xEC\xFE\xCD\xC4\xD5\xCC\xD6\xCE\xE2\xDF\x86\xCD\xC6\xC7" + 0xFE033128).s);
	modi3MathDx.dwBase = (DWORD)GetModuleHandleA(/*i3MathDx.dll*/XorStr<0x0C, 13, 0xF750A491>("\x65\x3E\x43\x6E\x64\x79\x56\x6B\x3A\x71\x7A\x7B" + 0xF750A491).s);
	modD3DX43.dwBase = (DWORD)LoadLibraryA(/*D3DX9_43.dll*/XorStr<0x43, 13, 0x38F51258>("\x07\x77\x01\x1E\x7E\x17\x7D\x79\x65\x28\x21\x22" + 0x38F51258).s);
	modKernel32.dwBase = (DWORD)LoadLibraryA(/*Kernel32.dll*/XorStr<0x55, 13, 0x34541291>("\x1E\x33\x25\x36\x3C\x36\x68\x6E\x73\x3A\x33\x0C" + 0x34541291).s);
	return &modBase;
}

BOOL utils::hGetThreadContext(HANDLE hThread, LPCONTEXT lpContext)
{
	oGetThreadContext pGetThreadContext = (oGetThreadContext)GetProcAddress((HMODULE)modKernel32.dwBase, /*GetThreadContext*/XorStr<0xF9, 17, 0x1E0E6423>("\xBE\x9F\x8F\xA8\x95\x8C\x9A\x61\x65\x41\x6C\x6A\x71\x63\x7F\x7C" + 0x1E0E6423).s);
	return pGetThreadContext(hThread, lpContext);
}

PVOID utils::hAddVectoredExceptionHandler(ULONG First, PVECTORED_EXCEPTION_HANDLER Handler)
{
	oAddVectoredExceptionHandler pAddVectoredExceptionHandler = (oAddVectoredExceptionHandler)GetProcAddress((HMODULE)modKernel32.dwBase, /*AddVectoredExceptionHandler*/XorStr<0x3F, 28, 0xBFE4CEF0>("\x7E\x24\x25\x14\x26\x27\x31\x29\x35\x2D\x2D\x0F\x33\x2F\x28\x3E\x3B\x39\x3E\x3C\x1B\x35\x3B\x32\x3B\x3D\x2B" + 0xBFE4CEF0).s);
	return pAddVectoredExceptionHandler(First, Handler);
}

HANDLE utils::hOpenThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId)
{
	oOpenThread pOpenThread = (oOpenThread)GetProcAddress((HMODULE)modKernel32.dwBase, /*OpenThread*/XorStr<0xF7, 11, 0x8FB955D0>("\xB8\x88\x9C\x94\xAF\x94\x8F\x9B\x9E\x64" + 0x8FB955D0).s);
	return pOpenThread(dwDesiredAccess, bInheritHandle, dwThreadId);
}

DWORD utils::hSuspendThread(HANDLE hThread)
{
	oSuspendThread pSuspendThread = (oSuspendThread)GetProcAddress((HMODULE)modKernel32.dwBase, /*SuspendThread*/XorStr<0xE6, 14, 0x0AFA0948>("\xB5\x92\x9B\x99\x8F\x85\x88\xB9\x86\x9D\x95\x90\x96" + 0x0AFA0948).s);
	return pSuspendThread(hThread);
}
DWORD utils::hResumeThread(HANDLE hThread)
{
	oResumeThread pResumeThread = (oResumeThread)GetProcAddress((HMODULE)modKernel32.dwBase, /*ResumeThread*/XorStr<0x7A, 13, 0xF07E5105>("\x28\x1E\x0F\x08\x13\x1A\xD4\xE9\xF0\xE6\xE5\xE1" + 0xF07E5105).s);
	return pResumeThread(hThread);
}

BOOL utils::hCloseHandle(HANDLE hObject)
{
	oCloseHandle pCloseHandle = (oCloseHandle)GetProcAddress((HMODULE)modKernel32.dwBase, /*CloseHandle*/XorStr<0xC9, 12, 0x7330D56D>("\x8A\xA6\xA4\xBF\xA8\x86\xAE\xBE\xB5\xBE\xB6" + 0x7330D56D).s);
	return pCloseHandle(hObject);
}

BOOL  utils::hThread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte)
{
	oThread32First pThread32First = (oThread32First)GetProcAddress((HMODULE)modKernel32.dwBase, /*Thread32First*/XorStr<0x5C, 14, 0xB59EB5C8>("\x08\x35\x2C\x3A\x01\x05\x51\x51\x22\x0C\x14\x14\x1C" + 0xB59EB5C8).s);
	return pThread32First(hSnapshot, lpte);
}

BOOL  utils::hThread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte)
{
	oThread32Next pThread32Next = (oThread32Next)GetProcAddress((HMODULE)modKernel32.dwBase, /*Thread32Next*/XorStr<0xD6, 13, 0xA2F26F4C>("\x82\xBF\xAA\xBC\xBB\xBF\xEF\xEF\x90\xBA\x98\x95" + 0xA2F26F4C).s);
	return pThread32Next(hSnapshot, lpte);
}

BOOL utils::hSetThreadContext(HANDLE hThread, const LPCONTEXT lpContext)
{
	oSetThreadContext pSetThreadContext = (oSetThreadContext)GetProcAddress((HMODULE)modKernel32.dwBase, /*SetThreadContext*/XorStr<0xA5, 17, 0x2DCBCF0B>("\xF6\xC3\xD3\xFC\xC1\xD8\xCE\xCD\xC9\xED\xC0\xDE\xC5\xD7\xCB\xC0" + 0x2DCBCF0B).s);
	return pSetThreadContext(hThread, lpContext);
}

HANDLE utils::hCreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID)
{
	oCreateToolhelp32Snapshot pCreateToolhelp32Snapshot = (oCreateToolhelp32Snapshot)GetProcAddress((HMODULE)modKernel32.dwBase, /*CreateToolhelp32Snapshot*/XorStr<0x2B, 25, 0x0B619DBD>("\x68\x5E\x48\x4F\x5B\x55\x65\x5D\x5C\x58\x5D\x53\x5B\x48\x0A\x08\x68\x52\x5C\x4E\x4C\x28\x2E\x36" + 0x0B619DBD).s);
	return pCreateToolhelp32Snapshot(dwFlags, th32ProcessID);
}