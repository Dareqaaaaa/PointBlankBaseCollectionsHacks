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

void * utils::DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp;
	DWORD dwback;
	DWORD jumpto, newjump;
	VirtualProtect(src, len, PAGE_READWRITE, &dwback);
	if (src[0] == 0xE9)
	{
		jmp = (BYTE*)malloc(10);
		jumpto = (*(DWORD*)(src + 1)) + ((DWORD)src) + 5;
		newjump = (jumpto - (DWORD)(jmp + 5));
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = newjump;
		jmp += 5;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = (DWORD)(src - jmp);
	}
	else
	{
		jmp = (BYTE*)malloc(5 + len);
		memcpy(jmp, src, len);
		jmp += len;
		jmp[0] = 0xE9;
		*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	}
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

	for (int i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwback, &dwback);
	return (jmp - len);
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
	if (modBase.dwBase == 0 && modBase.dwSize == 0)
		modBase = GetBaseAddress();

	if (modi3SceneDx.dwBase == 0)
		modi3SceneDx.dwBase = (DWORD)GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0x9A, 14, 0x8DDF9D84>("\xF3\xA8\xCF\xFE\xFB\xF1\xC5\xE5\xDA\x8D\xC0\xC9\xCA" + 0x8DDF9D84).s);

	if (modi3GfxDx.dwBase == 0)
		modi3GfxDx.dwBase = (DWORD)GetModuleHandleA(/*i3GfxDx.dll*/XorStr<0x92, 12, 0x707656D2>("\xFB\xA0\xD3\xF3\xEE\xD3\xE0\xB7\xFE\xF7\xF0" + 0x707656D2).s);

	if (modi3FrameworkDx.dwBase == 0)
		modi3FrameworkDx.dwBase = (DWORD)GetModuleHandleA(/*i3FrameworkDx.dll*/XorStr<0x9B, 18, 0xFE033128>("\xF2\xAF\xDB\xEC\xFE\xCD\xC4\xD5\xCC\xD6\xCE\xE2\xDF\x86\xCD\xC6\xC7" + 0xFE033128).s);

	if (modi3MathDx.dwBase == 0)
		modi3MathDx.dwBase = (DWORD)GetModuleHandleA(/*i3MathDx.dll*/XorStr<0x0C, 13, 0xF750A491>("\x65\x3E\x43\x6E\x64\x79\x56\x6B\x3A\x71\x7A\x7B" + 0xF750A491).s);

	if (modD3DX43.dwBase == 0)
		modD3DX43.dwBase = (DWORD)LoadLibraryA(/*D3DX9_43.dll*/XorStr<0x43, 13, 0x38F51258>("\x07\x77\x01\x1E\x7E\x17\x7D\x79\x65\x28\x21\x22" + 0x38F51258).s);

	return &modBase;
}

HRESULT utils::hD3DXCreateLine(LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE*ppLine)
{
	oD3DXCreateLine pD3DXCreateLine = (oD3DXCreateLine)GetProcAddress((HMODULE)pUtils.modD3DX43.dwBase, /*D3DXCreateLine*/XorStr<0x18, 15, 0x5239BCF7>("\x5C\x2A\x5E\x43\x5F\x6F\x7B\x7E\x54\x44\x6E\x4A\x4A\x40" + 0x5239BCF7).s);
	return pD3DXCreateLine(pDevice, ppLine);
}

HRESULT utils::hD3DXCreateFont(IDirect3DDevice9 *pDevice, INT Height, UINT Width, UINT Weight, UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily, LPCTSTR pFacename, LPD3DXFONT *ppFont)
{
	oD3DXCreateFont pD3DXCreateFont = (oD3DXCreateFont)GetProcAddress((HMODULE)pUtils.modD3DX43.dwBase, /*D3DXCreateFontA*/XorStr<0x1D, 16, 0xF3084480>("\x59\x2D\x5B\x78\x62\x50\x46\x45\x51\x43\x61\x47\x47\x5E\x6A" + 0xF3084480).s);
	return pD3DXCreateFont(pDevice, Height, Width, Weight, MipLevels, Italic, CharSet, OutputPrecision, Quality, PitchAndFamily, pFacename, ppFont);
}

D3DXVECTOR3 * utils::hD3DXVec3Project(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DVIEWPORT9 *pViewport, CONST D3DXMATRIX *pProjection, CONST D3DXMATRIX *pView, CONST D3DXMATRIX *pWorld)
{
	oD3DXVec3Project pD3DXVec3Project = (oD3DXVec3Project)GetProcAddress((HMODULE)pUtils.modD3DX43.dwBase, /*D3DXVec3Project*/XorStr<0x8A, 16, 0xFBEC4148>("\xCE\xB8\xC8\xD5\xD8\xEA\xF3\xA2\xC2\xE1\xFB\xFF\xF3\xF4\xEC" + 0xFBEC4148).s);
	return pD3DXVec3Project(pOut, pV, pViewport, pProjection, pView, pWorld);
}