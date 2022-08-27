#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <winbase.h>
#include <fstream>
#include <winbase.h>
#include <winternl.h>
#include <time.h>
#pragma warning(disable: 4996)

using namespace std;
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
DWORD FindPatternPointer( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] );
DWORD GetSizeofCode( const char* szModuleName );
DWORD GetSizeofCode( const char* szModuleName ) 
{ 
	HMODULE hModule = GetModuleHandleA( szModuleName ); 
	if ( !hModule ) return NULL; 
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
	if( !pDosHeader ) return NULL; 
	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
	if( !pNTHeader ) return NULL; 
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
	if( !pOptionalHeader ) return NULL; 
	return pOptionalHeader->SizeOfCode; 
}

DWORD FindPatternPointer( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] ) 
{ 
	unsigned int i = NULL; 
	int iLen = strlen( pszMask ) - 1; 
	for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ) 
	{ 
		if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ) 
		{ 
			if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
		} 
		else i = NULL; 
	} return NULL; 
}
/*------------------------------------------- Declaration hModule ------------------------------------------------------*/
LPTSTR PBSTR			= "PointBlank.exe";
LPTSTR PBi3Gfxx			= "i3GfxDx.dll";
LPTSTR PBi3Iptx			= "i3InputDx.dll";
LPTSTR PBi3Fmxx			= "i3FrameworkDx.dll";

/*------------------------------------------- Declaration DWORD ------------------------------------------------------*/
DWORD DwStartAddress, DwStartGfx, DwStartScn, DwStartFmx, DwStartNxCha, DwSize, DwSizei3Fmx, DwSizeNxCha;
DWORD dwSizePlayer, dwPlayerBase, dwBaseAmmo, dwPlayerHealth, dwAllHealth, dwNameESP, dwNoRecoil, dwHorzAngle2, dwVertAngle1, dwVertAngle2, dwSetWeapon, dwNetPlayerSize, dwNetPlayerOffset, dwWeaponCheck;
DWORD ResultPlayerBase, ResultPlayerBase2, ResultHealthBase2, ResultBaseAmmo2, ResultGameContext2, ResultCheckAmmo,  ResultESP1;


/******************************Declaration ESP DWORD**********************************/
DWORD dwESPPlayerSize, dwESPPlayerPos;
DWORD ResultESPPlayerSize, ResultESPPlayerPos;
/*------------------------------------------- Declaration AutoLogger ------------------------------------------------------*/

void SearchPatterns(void)
{
Sleep(100);
DwStartAddress = 0x400000;
do {
DwStartAddress = (DWORD)GetModuleHandle(PBSTR);
//Sleep(100);
	}while(!DwStartAddress);
DwSize = 0xA00000;
DwSizei3Fmx = GetSizeofCode(PBi3Fmxx);


		dwPlayerBase		= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x56","xx????????xxxxxxxxxxxxxxx");
		//dwAllHealth			= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5D\xC2\x04\x00\x8B","xx????x????xxxxx");
		dwPlayerHealth		= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x8B\x0D\x00\x00\x00\x00\x83\xF8\x0F\x77\x00\x8B\xD0\x69\xD2","xx????xxxx?xxxx");
		dwNameESP			= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x75\x58\x68\x00\x00\x00\x00\x8D\x4D\xD8\xE8\x00\x00\x00\x00","xxx????xxxx????");
		dwESPPlayerSize		= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x68\x00\x00\x00\x00\x8D\x96\x00\x00\x00\x00\x52\xC6\x45\xFC\x02","x????xx????xxxxx");
		dwESPPlayerPos		= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x8D\x86\x00\x00\x00\x00\x50\xC6\x45\xFC\x01\xE8\x00\x00\x00\x00","xx????xxxxxx????");
		 //dwWeaponCheck		= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x55\x8B\xEC\x83\xEC\x00\xC7\x45\xFC\x00\x00\x00\x00\xEB\x00\x8B\x45\xFC","xxxxx?xxx????x?xxx");
		 //dwSetWeapon		= FindPatternPointer(DwStartAddress,DwSize,(PBYTE)"\x55\x8B\xEC\x83\xEC\x00\x89\x4D\x00\x83\x7D\x08\x00\x74\x00\x83\x7D\x00\x00\x75\x00","xxxxx?xx?xxx?x?xx??x?");
		 
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPlayerBase+0x2), &ResultPlayerBase, sizeof(ResultPlayerBase), NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPlayerHealth+0x2), &ResultHealthBase2, sizeof(ResultHealthBase2), NULL);		


		/**ESP**/
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwESPPlayerSize+0x1), &ResultESPPlayerSize, sizeof(ResultESPPlayerSize), NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwESPPlayerPos+0x2), &ResultESPPlayerPos, sizeof(ResultESPPlayerPos), NULL);

		ResultPlayerBase2 = ResultPlayerBase;
		ResultGameContext2 = ResultPlayerBase2 + 0x300;
		ResultESPPlayerPos = ResultESPPlayerPos + 0xB8;
		ResultESP1 = dwNameESP;
	//return (0);
}