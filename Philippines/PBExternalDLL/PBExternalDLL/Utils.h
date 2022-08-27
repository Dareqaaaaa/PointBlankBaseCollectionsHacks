struct copt
{
	struct sinfo
	{
		int main;
	}info;

	struct sd3d
	{
		int main;
		int crosshair;
	}d3d;

	struct sesp
	{
		int main;
		int espbone;
		int espline;
		int espbox;
		int esphealth;
	}esp;

	struct saimbot
	{
		int main;
		int smooth;
		int fov;
		int draw;
		int key;
	}aimbot;
}opt;

DWORD EnumRegions(HANDLE hProcess, DWORD ADR_CHARACTERPOINTER, DWORD falseBase = NULL)
{
	DWORD retBaseAddress = 0;
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	uintptr_t address = 0;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	while (address < reinterpret_cast<uintptr_t>(si.lpMaximumApplicationAddress))
	{
		SIZE_T size = VirtualQueryEx(hProcess, reinterpret_cast<LPVOID>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (size)
		{
			if (mbi.Protect == PAGE_EXECUTE_READWRITE && mbi.RegionSize >= 10000000)
			{
				BYTE ADR_Char = *(DWORD*)((DWORD)mbi.BaseAddress + ADR_CHARACTERPOINTER);
				if(ADR_Char)
				{
					if (falseBase == (DWORD)mbi.BaseAddress)
						continue;

					retBaseAddress = (DWORD)mbi.BaseAddress;
					break;
				}
			}
			address += mbi.RegionSize;
		}
		else {
			address += si.dwPageSize;
		}
	}
	return retBaseAddress;
}
DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect, dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);
	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}
void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*pAddress = 0xE9;
	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
	for (DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
	return;
}
void *CreateDetour(PBYTE src, const BYTE *dst, const int len, DWORD Type)
{
	BYTE *jmp = (BYTE*)malloc(len + 5);
	DWORD dwBack;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
	memcpy(jmp, src, len);
	jmp += len;
	jmp[0] = (BYTE)Type;
	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	src[0] = (BYTE)Type;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

	for (int i = 5; i < len; i++)
		src[i] = 0x90;

	VirtualProtect((PBYTE)src, len, dwBack, &dwBack);
	return(jmp - len);
}
void EraseHeaders(HINSTANCE hModule)
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
void HideModule(HINSTANCE hModule)
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

BOOL GetAddress(void ** pTable, size_t Size)
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