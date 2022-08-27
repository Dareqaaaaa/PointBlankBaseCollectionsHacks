#pragma once
#include "stdafx.h"

struct UtilsT
{
public:
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
		int espdistance;
		int espname;
	}esp;

	struct saimbot
	{
		int main;
		int smooth;
		int fov;
		int draw;
		int key;
		int target;
	}aimbot;

	struct saimbullet
	{
		int main;
		int draw;
		int target;
	}aimbullet;

	struct smemory
	{
		int norecoil;
		int nospread;
		int opk;
		int fastshot;
		int fastreloadknife;
		int fastreload;
		int fastswitch;
		int extrahp;
		int fastrespawn;
		int nofalldamage;
		int rapidfire;
		int ghostmode;
	}memory;

public:
	HMODULE i3FrameworkDx;
	HMODULE i3MathDx;
	HMODULE i3SceneDx;
	HMODULE i3GfxDx;
public:
	static const char * bones[22];
public:
	DWORD GetAddress(DWORD Ptr_Chara);
	DWORD GetAddressByRecoil(DWORD Ptr_Recoil, DWORD Ptr_Chara);
	DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget);
	void WriteProtect(void *adress, void *bytes, int size);
	void EraseHeaders(HINSTANCE hModule);
	void HideModule(HINSTANCE hModule);
	BOOL GetSwapChainAddress(void ** pTable, size_t Size);
	VOID WriteMemory(LPVOID lpAddress, LPBYTE lpBuffer, DWORD dwLengh);
	VOID WriteJump(DWORD dwFunction, DWORD dwAddress);

	template<typename T>
	static T ReadMem(SIZE_T address)
	{
		T buffer;
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}
public:
	UtilsT()
	{
		i3FrameworkDx = GetModuleHandleA(/*i3FrameworkDx.dll*/XorStr<0x9B, 18, 0xFE033128>("\xF2\xAF\xDB\xEC\xFE\xCD\xC4\xD5\xCC\xD6\xCE\xE2\xDF\x86\xCD\xC6\xC7" + 0xFE033128).s);
		i3MathDx = GetModuleHandleA(/*i3MathDx.dll*/XorStr<0x0C, 13, 0xF750A491>("\x65\x3E\x43\x6E\x64\x79\x56\x6B\x3A\x71\x7A\x7B" + 0xF750A491).s);
		i3SceneDx = GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0x9A, 14, 0x8DDF9D84>("\xF3\xA8\xCF\xFE\xFB\xF1\xC5\xE5\xDA\x8D\xC0\xC9\xCA" + 0x8DDF9D84).s);
		i3GfxDx = GetModuleHandleA(/*i3GfxDx.dll*/XorStr<0x92, 12, 0x707656D2>("\xFB\xA0\xD3\xF3\xEE\xD3\xE0\xB7\xFE\xF7\xF0" + 0x707656D2).s);
	}
};

extern UtilsT * Utils;