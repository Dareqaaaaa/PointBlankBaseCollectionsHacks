#include "stdafx.h"

class CTools
{
public:

	BOOL  bCompare ( const BYTE* pData, const BYTE* bMask, const char* szMask )
	{
		for ( ;*szMask; ++szMask, ++pData, ++bMask )
		{
			if ( *szMask == 'x' && *pData != *bMask )
				 return 0;
		}
		return (*szMask) == NULL;
	}
 
	DWORD FindPattern ( DWORD dwStartAddress,DWORD dwSize, BYTE *bMask, char * szMask, int codeOffset, BOOL extract )
	{ 
		for ( DWORD i = 0; i < dwSize; i++ )
		{
			if ( this->bCompare((BYTE*)(dwStartAddress + i),bMask,szMask) )
			{
				if ( extract )  
				{
					return *(DWORD*)(dwStartAddress+i+codeOffset);
 
				} else {
 
					return  (DWORD)(dwStartAddress+i+codeOffset);
				}
			}
		}
		return NULL;
	}

	void *DetourFunc(BYTE *src, const BYTE *dst, const int len)
	{
		BYTE *jmp = (BYTE*)malloc(len+5);
		DWORD dwback;
		VirtualProtect(src, len, PAGE_READWRITE, &dwback);
		memcpy(jmp, src, len);	jmp += len;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;
		src[0] = 0xE9;
		*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;
		VirtualProtect(src, len, dwback, &dwback);
		return (jmp-len);
	}

	HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
	{
		if(FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
			return E_FAIL;
    
		WORD colour16 = ((WORD)((colour32>>28)&0xF)<<12)
	            		|(WORD)(((colour32>>20)&0xF)<<8)
	             		|(WORD)(((colour32>>12)&0xF)<<4)
                 		|(WORD)(((colour32>>4)&0xF)<<0);

		D3DLOCKED_RECT d3dlr;    
		(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
		WORD *pDst16 = (WORD*)d3dlr.pBits;

		for(int xy=0; xy < 8*8; xy++)
			*pDst16++ = colour16;

		(*ppD3Dtex)->UnlockRect(0);

		return S_OK;
	}

	void HideModule(HINSTANCE hModule)
	{
			DWORD dwPEB_LDR_DATA = 0;
			_asm
			{
			pushad;
			pushfd;
			mov eax, fs:[30h];
			mov eax, [eax+0Ch];
			mov dwPEB_LDR_DATA, eax;
			mov esi, [eax+0Ch];
			mov edx, [eax+10h];
			LoopInLoadOrderModuleList:
					lodsd;
					mov esi, eax;
					mov ecx, [eax+18h];
					cmp ecx, hModule;
					jne SkipA
					mov ebx, [eax]
					mov ecx, [eax+4]
					mov [ecx], ebx
					mov [ebx+4], ecx
					jmp InMemoryOrderModuleList
			SkipA:
					cmp edx, esi
					jne LoopInLoadOrderModuleList
	InMemoryOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+14h]
			mov edx, [eax+18h]
			LoopInMemoryOrderModuleList:
					lodsd
					mov esi, eax
					mov ecx, [eax+10h]
					cmp ecx, hModule
					jne SkipB
					mov ebx, [eax]
					mov ecx, [eax+4]
					mov [ecx], ebx
					mov [ebx+4], ecx
					jmp InInitializationOrderModuleList
			SkipB:
					cmp edx, esi
					jne LoopInMemoryOrderModuleList
	InInitializationOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+1Ch]
			mov edx, [eax+20h]
			LoopInInitializationOrderModuleList:
					lodsd
					mov esi, eax      
					mov ecx, [eax+08h]
					cmp ecx, hModule      
					jne SkipC
					mov ebx, [eax]
					mov ecx, [eax+4]
					mov [ecx], ebx
					mov [ebx+4], ecx
					jmp Finished
			SkipC:
					cmp edx, esi
					jne LoopInInitializationOrderModuleList
			Finished:
					popfd;
					popad;
			}
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
			for ( i=0; i < ersize; i++ )
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
}Tools;