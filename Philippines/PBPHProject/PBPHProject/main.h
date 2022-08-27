#pragma warning(disable:4996)

#define Green				D3DCOLOR_ARGB(255, 000, 255, 000)
#define Red					D3DCOLOR_ARGB(255, 255, 000, 000)
#define Blue				D3DCOLOR_ARGB(255, 000, 000, 255)
#define Orange				D3DCOLOR_ARGB(255, 255, 165, 000)
#define Yellow				D3DCOLOR_ARGB(255, 255, 255, 000)
#define Pink				D3DCOLOR_ARGB(255, 255, 192, 203)
#define Cyan				D3DCOLOR_ARGB(255, 000, 255, 255)
#define Purple				D3DCOLOR_ARGB(255, 160, 032, 240)
#define Black				D3DCOLOR_ARGB(255, 000, 000, 000) 
#define White				D3DCOLOR_ARGB(255, 255, 255, 255)
#define Grey				D3DCOLOR_ARGB(255, 112, 112, 112)
#define SteelBlue			D3DCOLOR_ARGB(255, 033, 104, 140)
#define LightSteelBlue		D3DCOLOR_ARGB(255, 201, 255, 255)
#define LightBlue			D3DCOLOR_ARGB(255, 026, 140, 306)
#define Salmon				D3DCOLOR_ARGB(255, 196, 112, 112)
#define Brown				D3DCOLOR_ARGB(255, 168, 099, 020)
#define Teal				D3DCOLOR_ARGB(255, 038, 140, 140)
#define Lime				D3DCOLOR_ARGB(255, 050, 205, 050)
#define ElectricLime		D3DCOLOR_ARGB(255, 204, 255, 000)
#define Gold				D3DCOLOR_ARGB(255, 255, 215, 000)
#define OrangeRed			D3DCOLOR_ARGB(255, 255, 069, 000)
#define GreenYellow			D3DCOLOR_ARGB(255, 173, 255, 047)
#define AquaMarine			D3DCOLOR_ARGB(255, 127, 255, 212)
#define SkyBlue				D3DCOLOR_ARGB(255, 000, 191, 255)
#define SlateBlue			D3DCOLOR_ARGB(255, 132, 112, 255)
#define Crimson				D3DCOLOR_ARGB(255, 220, 020, 060)
#define DarkOliveGreen		D3DCOLOR_ARGB(255, 188, 238, 104)
#define PaleGreen			D3DCOLOR_ARGB(255, 154, 255, 154)
#define DarkGoldenRod		D3DCOLOR_ARGB(255, 255, 185, 015)
#define FireBrick			D3DCOLOR_ARGB(255, 255, 048, 048)
#define DarkBlue			D3DCOLOR_ARGB(255, 000, 000, 204)
#define DarkerBlue			D3DCOLOR_ARGB(255, 000, 000, 153)
#define DarkYellow			D3DCOLOR_ARGB(255, 255, 204, 000)
#define LightYellow			D3DCOLOR_ARGB(255, 255, 255, 153)
#define DarkOutline			D3DCOLOR_ARGB(255, 37,   48,  52)
#define TBlack				D3DCOLOR_ARGB(180, 000, 000, 000) 
#define cGray				D3DCOLOR_ARGB(255, 200, 200, 200)
typedef UINT(__stdcall *threadFunc_t)(void*);

BOOL GetSwapChainAddress(void ** pTable, size_t Size)
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


// MODULE //

typedef struct _LDR_MODULE
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
}LDR_MODULE, *PLDR_MODULE;

typedef struct _PEB_LDR_DATA 
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
}PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB 
{
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	PPEB_LDR_DATA Ldr;
}PEB, *PPEB;

void HideModule (HINSTANCE hModule)
{
	PEB* peb;
	LDR_MODULE* ldr;
	
	peb = (PEB*)__readfsdword(0x30);
	
	ldr = (LDR_MODULE*)peb->Ldr->InLoadOrderModuleList.Flink;

	while(ldr->BaseAddress != 0)
	{
		if(ldr->BaseAddress == hModule)
		{
			if(ldr->InLoadOrderModuleList.Blink != 0)
				(ldr->InLoadOrderModuleList.Blink)->Flink = ldr->InLoadOrderModuleList.Flink;	
			
			if(ldr->InLoadOrderModuleList.Blink != 0)
				(ldr->InLoadOrderModuleList.Flink)->Blink = ldr->InLoadOrderModuleList.Blink;
			
			if(ldr->InInitializationOrderModuleList.Blink != 0)
				(ldr->InInitializationOrderModuleList.Blink)->Flink = ldr->InInitializationOrderModuleList.Flink;
			
			if(ldr->InInitializationOrderModuleList.Flink != 0)
				(ldr->InInitializationOrderModuleList.Flink)->Blink = ldr->InInitializationOrderModuleList.Blink;

			if(ldr->InMemoryOrderModuleList.Flink != 0)
				(ldr->InMemoryOrderModuleList.Blink)->Flink = ldr->InMemoryOrderModuleList.Flink;

			if(ldr->InMemoryOrderModuleList.Flink != 0)
				(ldr->InMemoryOrderModuleList.Flink)->Blink = ldr->InMemoryOrderModuleList.Blink;
		}
		ldr = (LDR_MODULE*)ldr->InLoadOrderModuleList.Flink;
	}
}

void EraseHeaders (HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH;
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if(!hModule) return;

	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	ersize = sizeof(IMAGE_DOS_HEADER);
	if(VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect))
	{
		for(i=0; i < ersize; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if(pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect))
	{
		for(i=0; i < ersize; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}

void ErasePEHeader (HINSTANCE hModule)
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)hModule, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
	ZeroMemory((PVOID)hModule, 4096);
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, NULL);
	FlushInstructionCache(GetCurrentProcess(), (LPCVOID)mbi.BaseAddress, mbi.RegionSize);
}

HANDLE CreateStealthThread(threadFunc_t pThreadFunc, void *pArgument) // by Ende! //
{
   BYTE *pK32     = (BYTE*)GetModuleHandle(eKernel32);
   BYTE *pPopRet  = nullptr;
   DWORD oldProt;

   auto rva2va = [&](DWORD dwVA)
   { 
      return (void*)((uintptr_t)pK32 + dwVA);
   };

   void *pWriteTarget = nullptr;

   auto pMz          = (IMAGE_DOS_HEADER*)pK32;
   auto pNt          = (IMAGE_NT_HEADERS32*)rva2va(pMz->e_lfanew);
   auto pCurSection  = (IMAGE_SECTION_HEADER*)((uintptr_t)pNt + sizeof(IMAGE_NT_HEADERS32));

   for(int i=0; i<pNt->FileHeader.NumberOfSections; ++i)
   {
      if(memcmp(".text", pCurSection->Name, 5) == 0)
      {
         pWriteTarget = (void*)((uintptr_t)rva2va(pCurSection->VirtualAddress) + pCurSection->Misc.VirtualSize - 6);
         break;
      }
      ++pCurSection;
   }

   if(!pWriteTarget) return NULL;

   uint8_t shellcode[] = "\x68\x00\x00\x00\x00\xC2";
   *(threadFunc_t*)(shellcode + 1) = pThreadFunc;
   
   VirtualProtect(pWriteTarget, 6, PAGE_EXECUTE_READWRITE, &oldProt);
   memcpy(pWriteTarget, shellcode, 6);
   VirtualProtect(pWriteTarget, 6, oldProt, &oldProt);

   return CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)pWriteTarget, pArgument, NULL, nullptr);
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

	for(int i = 5; i < len; i++) 
		src[i] = 0x90;

	VirtualProtect((PBYTE)src, len, dwBack, &dwBack);
	return(jmp - len);
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