/*
CONCEPT BASED ON ( http://www.nologin.org/Downloads/Papers/remote-library-injection.pdf ) 
	> I DIDNT MANAGE TO FORCE NTOPENFILE TO RETURN A VALID FILEHANDLE WITH A NON EXISTANT FILE...
	ONLY WAY I FIGURE OUT IS BY POINTING TO A DUMMY MODULE ON HD.

CREDITS:
	> nologin( Concept )
	> Azorbix( Detours )
	> ntKid( Coder )
COOL PLACES:
	> http://www.gamedeception.net ( Almond Praliné )
	> http://www.uc-forum.com ( Almond Praliné )
*/

#ifdef _DEBUG
#error "KAMEHAMEHA HAS TO BE DONE IN RELEASE MODE"
#endif

#include <windows.h>
#include <string>

//Uncomment to hide from PEB ( i advise not to use this unless is really necessary... )
//#define HIDEMODULE

//STRUCT TO PASS TO TARGET PROCESS
struct DATA_T
{
	PWSTR _FileName;
	HANDLE _File, _Section, _Module;
	PVOID _Map, _FindStringMatchW, _LdrLoadDll, _NtOpenFile, _NtCreateSection, _NtMapViewOfSection, _NtUnmapViewOfSection, _myOpenFile, _myLdrLoadDll, _myCreateSection, _myMapViewOfSection, _myUnmapViewOfSection;
};

struct EXPORT_T
{
	PVOID _GetProcAddress;
	PSTR _Export;
	HMODULE _Module;
	FARPROC _Result;
};

BYTE m_FindStringMatchW[ 137 ] = //COMPARE UNICODE STRING
{
	0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C, 0x8B, 0x45, 0x08, 0x89, 0x45, 0xFC, 0x8B, 0x4D, 0x0C, 0x0F,
	0xB7, 0x11, 0x85, 0xD2, 0x75, 0x05, 0x8B, 0x45, 0x08, 0xEB, 0x6A, 0x8B, 0x45, 0xFC, 0x0F, 0xB7, 
	0x08, 0x85, 0xC9, 0x74, 0x5E, 0x8B, 0x55, 0xFC, 0x89, 0x55, 0xF4, 0x8B, 0x45, 0x0C, 0x89, 0x45, 
	0xF8, 0x8B, 0x4D, 0xF4, 0x0F, 0xB7, 0x11, 0x85, 0xD2, 0x74, 0x2E, 0x8B, 0x45, 0xF8, 0x0F, 0xB7, 
	0x08, 0x85, 0xC9, 0x74, 0x24, 0x8B, 0x55, 0xF4, 0x0F, 0xB7, 0x02, 0x8B, 0x4D, 0xF8, 0x0F, 0xB7, 
	0x11, 0x2B, 0xC2, 0x75, 0x14, 0x8B, 0x45, 0xF4, 0x83, 0xC0, 0x02, 0x89, 0x45, 0xF4, 0x8B, 0x4D, 
	0xF8, 0x83, 0xC1, 0x02, 0x89, 0x4D, 0xF8, 0xEB, 0xC8, 0x8B, 0x55, 0xF8, 0x0F, 0xB7, 0x02, 0x85, 
	0xC0, 0x75, 0x05, 0x8B, 0x45, 0xFC, 0xEB, 0x0D, 0x8B, 0x4D, 0xFC, 0x83, 0xC1, 0x02, 0x89, 0x4D, 
	0xFC, 0xEB, 0x98, 0x33, 0xC0, 0x8B, 0xE5, 0x5D, 0xC3
};

BYTE m_LdrLoadDll[ 80 ] = //MAKE SURE WE SUCCEEDED
{
	0x55, 0x8B, 0xEC, 0x51, 0x51, 0xC7, 0x45, 0xFC, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0x75, 0x14, 0xFF, 
	0x75, 0x10, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 0x08, 0x8B, 0x45, 0xFC, 0xFF, 0x50, 0x18, 0x89, 0x45, 
	0xF8, 0x83, 0x7D, 0xF8, 0x00, 0x7C, 0x22, 0x8B, 0x45, 0xFC, 0xFF, 0x30, 0x8B, 0x45, 0x10, 0xFF, 
	0x70, 0x04, 0x8B, 0x45, 0xFC, 0xFF, 0x50, 0x14, 0x59, 0x59, 0x85, 0xC0, 0x74, 0x0B, 0x8B, 0x45, 
	0xFC, 0x8B, 0x4D, 0x14, 0x8B, 0x09, 0x89, 0x48, 0x0C, 0x8B, 0x45, 0xF8, 0xC9, 0xC2, 0x10, 0x00  
};

BYTE m_OpenFile[ 89 ] = //GET FILE HANDLE FROM FILE NAME
{
	0x55, 0x8B, 0xEC, 0x51, 0x51, 0xC7, 0x45, 0xFC, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0x75, 0x1C, 0xFF, 
	0x75, 0x18, 0xFF, 0x75, 0x14, 0xFF, 0x75, 0x10, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 0x08, 0x8B, 0x45, 
	0xFC, 0xFF, 0x50, 0x1C, 0x89, 0x45, 0xF8, 0x83, 0x7D, 0xF8, 0x00, 0x7C, 0x25, 0x8B, 0x45, 0xFC, 
	0xFF, 0x30, 0x8B, 0x45, 0x10, 0x8B, 0x40, 0x08, 0xFF, 0x70, 0x04, 0x8B, 0x45, 0xFC, 0xFF, 0x50, 
	0x14, 0x59, 0x59, 0x85, 0xC0, 0x74, 0x0B, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0x08, 0x8B, 0x09, 0x89, 
	0x48, 0x04, 0x8B, 0x45, 0xF8, 0xC9, 0xC2, 0x18, 0x00 
};

BYTE m_CreateSection[ 77 ] = //GET SECTION HANDLE FROM FILE HANDLE
{
	0x55, 0x8B, 0xEC, 0x51, 0x51, 0xC7, 0x45, 0xFC, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0x75, 0x20, 0xFF, 
	0x75, 0x1C, 0xFF, 0x75, 0x18, 0xFF, 0x75, 0x14, 0xFF, 0x75, 0x10, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 
	0x08, 0x8B, 0x45, 0xFC, 0xFF, 0x50, 0x20, 0x89, 0x45, 0xF8, 0x83, 0x7D, 0xF8, 0x00, 0x7C, 0x16, 
	0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0x20, 0x3B, 0x48, 0x04, 0x75, 0x0B, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 
	0x08, 0x8B, 0x09, 0x89, 0x48, 0x08, 0x8B, 0x45, 0xF8, 0xC9, 0xC2, 0x1C, 0x00 
};

BYTE m_MapViewOfSection[ 93 ] = //FORCE SYSTEM IMAGE REBASE FROM SECTION HANDLE
{
	0x55, 0x8B, 0xEC, 0x51, 0x51, 0xC7, 0x45, 0xFC, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0x75, 0x2C, 0xFF, 
	0x75, 0x28, 0xFF, 0x75, 0x24, 0xFF, 0x75, 0x20, 0xFF, 0x75, 0x1C, 0xFF, 0x75, 0x18, 0xFF, 0x75, 
	0x14, 0xFF, 0x75, 0x10, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 0x08, 0x8B, 0x45, 0xFC, 0xFF, 0x50, 0x24, 
	0x89, 0x45, 0xF8, 0x83, 0x7D, 0xF8, 0x00, 0x7C, 0x1D, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 0x08, 0x3B, 
	0x48, 0x08, 0x75, 0x12, 0x8B, 0x45, 0x10, 0x8B, 0x4D, 0xFC, 0x8B, 0x49, 0x10, 0x89, 0x08, 0xB8, 
	0x03, 0x00, 0x00, 0x40, 0xEB, 0x03, 0x8B, 0x45, 0xF8, 0xC9, 0xC2, 0x28, 0x00
};

#ifdef HIDEMODULE
BYTE m_UnmapViewOfSection[ 42 ] = //TRY TO PREVENT SECTION DESTRUCTION UPON FREELIBRARY
{
	0x55, 0x8B, 0xEC, 0x51, 0xC7, 0x45, 0xFC, 0xEE, 0xEE, 0xEE, 0xEE, 0x8B, 0x45, 0xFC, 0x8B, 0x4D, 
	0x0C, 0x3B, 0x48, 0x10, 0x75, 0x04, 0x33, 0xC0, 0xEB, 0x0C, 0xFF, 0x75, 0x0C, 0xFF, 0x75, 0x08, 
	0x8B, 0x45, 0xFC, 0xFF, 0x50, 0x28, 0xC9, 0xC2, 0x08, 0x00 
};
#endif

BYTE m_GetProcAddress[ 30 ] = //GET REMOTE PROCESS ADDRESS
{
	0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0xFF, 0x70, 0x04, 0x8B, 0x45, 0x08, 0xFF, 0x70, 0x08, 0x8B, 
	0x45, 0x08, 0xFF, 0x10, 0x8B, 0x4D, 0x08, 0x89, 0x41, 0x0C, 0x5D, 0xC2, 0x04, 0x00 
};

static INT m_DecoyModuleSize = 28672,
		   m_FindStringMatchSize = 137,
		   m_LdrLoadDllSize = 80,
		   m_OpenFileSize = 89, 
		   m_CreateSectionSize = 77, 
		   m_MapViewOfSectionSize = 93,
		   m_UnmapViewOfSectionSize = 42,
		   m_GetProcAddressSize = 30,
		   m_DataSize = sizeof( DATA_T ),
		   m_ExportSize = sizeof( EXPORT_T );

PVOID WriteStreamSections( HANDLE _Process, PBYTE _Stream, SIZE_T& _StreamSize ) //WRITE HEADER AND SECTIONS TO VICTIM PROCESS
{
	PIMAGE_DOS_HEADER _Dos = ( PIMAGE_DOS_HEADER )_Stream;

	if( _Dos == NULL || _Dos->e_magic != IMAGE_DOS_SIGNATURE )
		return NULL;

	PIMAGE_NT_HEADERS _Nt = ( PIMAGE_NT_HEADERS )&_Stream[ _Dos->e_lfanew ];

	if( _Nt == NULL || _Nt->Signature != IMAGE_NT_SIGNATURE )
		return NULL;

	PVOID _Base = VirtualAllocEx( _Process, NULL, _Nt->OptionalHeader.SizeOfImage, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE );

	if( _Base == NULL )
		return NULL;

	if( WriteProcessMemory( _Process, _Base, _Stream, _Nt->OptionalHeader.SizeOfHeaders, NULL ) == FALSE )
	{
		VirtualFreeEx( _Process, _Base, _Nt->OptionalHeader.SizeOfImage, MEM_RELEASE );
		return NULL;
	}

	PIMAGE_SECTION_HEADER _Section = IMAGE_FIRST_SECTION( _Nt );

	if( _Section == NULL )
	{
		VirtualFreeEx( _Process, _Base, _Nt->OptionalHeader.SizeOfImage, MEM_RELEASE );
		return NULL;
	}

	for( INT i = 0; i < _Nt->FileHeader.NumberOfSections; i++ )
	{
		if( WriteProcessMemory( _Process, ( PVOID )( ( ULONG )_Base + _Section[ i ].VirtualAddress ), ( PVOID )( ( ULONG )_Stream + _Section[ i ].PointerToRawData ), _Section[ i ].SizeOfRawData, NULL ) == FALSE )
		{
			VirtualFreeEx( _Process, _Base, _Nt->OptionalHeader.SizeOfImage, MEM_RELEASE );
			return NULL;
		}
	}

	_StreamSize = _Nt->OptionalHeader.SizeOfImage;

	return _Base;
}

BOOL AllocDecoy( HANDLE _Process, DATA_T& _Data, ULONG _Address )//ALLOCATE AND WRITE OUR FUNCTIONS TO VICTIM PROCESS
{
	if( ( _Data._FindStringMatchW = VirtualAllocEx( _Process, NULL, m_FindStringMatchSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
		return FALSE;

	if( WriteProcessMemory( _Process, _Data._FindStringMatchW, m_FindStringMatchW, m_FindStringMatchSize, NULL ) == FALSE )
		return FALSE;

	*( PULONG )( m_LdrLoadDll + 0x8 ) = _Address;

	if( ( _Data._myLdrLoadDll = VirtualAllocEx( _Process, NULL, m_LdrLoadDllSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
		return FALSE;

	if( WriteProcessMemory( _Process, _Data._myLdrLoadDll, m_LdrLoadDll, m_LdrLoadDllSize, NULL ) == FALSE )
		return FALSE;

	*( PULONG )( m_OpenFile + 0x8 ) = _Address;

	if( ( _Data._myOpenFile = VirtualAllocEx( _Process, NULL, m_OpenFileSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
		return FALSE;

	if( WriteProcessMemory( _Process, _Data._myOpenFile, m_OpenFile, m_OpenFileSize, NULL ) == FALSE )
		return FALSE;

	*( PULONG )( m_CreateSection + 0x8 ) = _Address;

	if( ( _Data._myCreateSection = VirtualAllocEx( _Process, NULL, m_CreateSectionSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
		return FALSE;

	if( WriteProcessMemory( _Process, _Data._myCreateSection, m_CreateSection, m_CreateSectionSize, NULL ) == FALSE )
		return FALSE;

	*( PULONG )( m_MapViewOfSection + 0x8 ) = _Address;

	if( ( _Data._myMapViewOfSection = VirtualAllocEx( _Process, NULL, m_MapViewOfSectionSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
		return FALSE;

	if( WriteProcessMemory( _Process, _Data._myMapViewOfSection, m_MapViewOfSection, m_MapViewOfSectionSize, NULL ) == FALSE )
		return FALSE;
#ifdef HIDEMODULE
	*( PULONG )( m_UnmapViewOfSection + 0x7 ) = _Address;

	if( ( _Data._myUnmapViewOfSection = VirtualAllocEx( _Process, NULL, m_UnmapViewOfSectionSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
		return FALSE;

	if( WriteProcessMemory( _Process, _Data._myUnmapViewOfSection, m_UnmapViewOfSection, m_UnmapViewOfSectionSize, NULL ) == FALSE )
		return FALSE;
#endif
	return TRUE;
}

VOID FreeDecoy( HANDLE _Process, DATA_T& _Data )//RELEASE OUR ALLOCATED FUNCTIONS ON VICTIM PROCESS
{
	if( _Data._FindStringMatchW )
		VirtualFreeEx( _Process, _Data._FindStringMatchW, m_FindStringMatchSize, MEM_RELEASE );

	if( _Data._myLdrLoadDll )
		VirtualFreeEx( _Process, _Data._myLdrLoadDll, m_LdrLoadDllSize, MEM_RELEASE );

	if( _Data._myOpenFile )
		VirtualFreeEx( _Process, _Data._myOpenFile, m_OpenFileSize, MEM_RELEASE );

	if( _Data._myCreateSection )
		VirtualFreeEx( _Process, _Data._myCreateSection, m_CreateSectionSize, MEM_RELEASE );

	if( _Data._myMapViewOfSection )
		VirtualFreeEx( _Process, _Data._myMapViewOfSection, m_MapViewOfSectionSize, MEM_RELEASE );
#ifdef HIDEMODULE
	if( _Data._myUnmapViewOfSection )
		VirtualFreeEx( _Process, _Data._myUnmapViewOfSection, m_UnmapViewOfSectionSize, MEM_RELEASE );
#endif
}

PVOID SetDetourPtr( HANDLE _Process, PBYTE _Source, INT _Len )//BASED ON AZORBIX DETOURS
{
	PVOID _Ptr = VirtualAllocEx( _Process, NULL, _Len + 5, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE );

	if( _Ptr == NULL )
		return NULL;

	MEMORY_BASIC_INFORMATION _Info;

	if( VirtualQueryEx( _Process, ( PVOID )_Source, &_Info, sizeof( MEMORY_BASIC_INFORMATION ) ) == NULL )
		return NULL;

	if( VirtualProtectEx( _Process, _Info.BaseAddress, _Info.RegionSize, PAGE_EXECUTE_READWRITE, &_Info.Protect ) == FALSE )
		return NULL;

	if( WriteProcessMemory( _Process, _Ptr, _Source, _Len, NULL ) == FALSE )
		return NULL;

	if( VirtualProtectEx( _Process, _Info.BaseAddress, _Info.RegionSize, _Info.Protect, new ULONG ) == FALSE )
		return NULL;

	if( FlushInstructionCache( _Process, _Info.BaseAddress,_Info.RegionSize ) == FALSE )
		return NULL;

	ULONG _Delta = ( ULONG )_Ptr + _Len, _Address = ( ULONG )( ( ULONG )_Source + _Len - _Delta ) - 5;

	BYTE _Jump[ 5 ] = { 0xE9, ( ( _Address ) & 0xFF ), ( ( _Address >> 8 )& 0xFF ), ( ( _Address >> 16 ) & 0xFF ), ( ( _Address >> 24 ) & 0xFF ) };

	if( WriteProcessMemory( _Process, ( PVOID )_Delta, _Jump, 5, NULL ) == FALSE )
		return NULL;

	return _Ptr;
}

BOOL ApplyDetour( HANDLE _Process, PBYTE _Source, PBYTE _Dest, INT _Len )//BASED ON AZORBIX DETOURS
{
	MEMORY_BASIC_INFORMATION _Info;

	if( VirtualQueryEx( _Process, ( PVOID )_Source, &_Info, sizeof( MEMORY_BASIC_INFORMATION ) ) == NULL )
		return FALSE;

	if( VirtualProtectEx( _Process, _Info.BaseAddress, _Info.RegionSize, PAGE_EXECUTE_READWRITE, &_Info.Protect ) == FALSE )
		return FALSE;

	ULONG _Address = ( ULONG )( ( ULONG )_Dest - ( ULONG )_Source ) - 5;

	BYTE _Jump[ 5 ] = { 0xE9, ( ( _Address ) & 0xFF ), ( ( _Address >> 8 )& 0xFF ), ( ( _Address >> 16 ) & 0xFF ), ( ( _Address >> 24 ) & 0xFF ) };

	if( WriteProcessMemory( _Process, _Source, _Jump, 5, NULL ) == FALSE )
		return FALSE;

	if( VirtualProtectEx( _Process, _Info.BaseAddress, _Info.RegionSize, _Info.Protect, new ULONG ) == FALSE )
		return FALSE;

	if( FlushInstructionCache( _Process, _Info.BaseAddress,_Info.RegionSize ) == FALSE )
		return FALSE;

	return TRUE;
}

BOOL RestoreDetour( HANDLE _Process, PBYTE _Source, PBYTE _Dest, INT _Len )//BASED ON AZORBIX DETOURS
{
	MEMORY_BASIC_INFORMATION _Info;

	if( VirtualQueryEx( _Process, ( PVOID )_Source, &_Info, sizeof( MEMORY_BASIC_INFORMATION ) ) == NULL )
		return FALSE;

	if( VirtualProtectEx( _Process, _Info.BaseAddress, _Info.RegionSize, PAGE_EXECUTE_READWRITE, &_Info.Protect ) == FALSE )
		return FALSE;

	if( WriteProcessMemory( _Process, _Source, _Dest, _Len, NULL ) == FALSE )
		return FALSE;

	LONG _Address = ( ULONG )( ( ULONG )_Source - ( ULONG )_Dest ) - 5;

	BYTE _Jump[ 5 ] = { 0xE9, ( ( _Address ) & 0xFF ), ( ( _Address >> 8 )& 0xFF ), ( ( _Address >> 16 ) & 0xFF ), ( ( _Address >> 24 ) & 0xFF ) };

	if( WriteProcessMemory( _Process, _Dest, _Jump, 5, NULL ) == FALSE )
		return FALSE;

	if( VirtualProtectEx( _Process, _Info.BaseAddress, _Info.RegionSize, _Info.Protect, new ULONG ) == FALSE )
		return FALSE;

	if( FlushInstructionCache( _Process, _Info.BaseAddress,_Info.RegionSize ) == FALSE )
		return FALSE;

	return TRUE;
}	


template <int XORSTART, int BUFLEN, int XREFKILLER>

class XorStr
{
private:
	XorStr();
public:
	char s[BUFLEN];

	XorStr(const char * xs);

	~XorStr()
	{
		for (int i = 0; i < BUFLEN; i++)
			s[i] = 0;
	}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART, BUFLEN, XREFKILLER>::XorStr(const char * xs)
{
	int xvalue = XORSTART;
	int i = 0;

	for (; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = 0;
}

static std::string m_ClientKey(/*http://www.ramleague.net/*/XorStr<0x2F, 26, 0xF1074B76>("\x47\x44\x45\x42\x09\x1B\x1A\x41\x40\x4F\x17\x48\x5A\x51\x51\x5B\x5E\x27\x34\x27\x6D\x2A\x20\x32\x68" + 0xF1074B76).s), m_ServerKey(/*http://www.ramleague.net/pointblank-vip/*/XorStr<0x93, 41, 0x82703241>("\xFB\xE0\xE1\xE6\xAD\xB7\xB6\xED\xEC\xEB\xB3\xEC\xFE\xCD\xCD\xC7\xC2\xC3\xD0\xC3\x89\xC6\xCC\xDE\x84\xDC\xC2\xC7\xC1\xC4\xD3\xDE\xD2\xDA\xDE\x9B\xC1\xD1\xC9\x95" + 0x82703241).s);
VOID myDecode(PBYTE _Byte, INT _Size, std::string _ClientKey, std::string _ServerKey)
{
	BYTE _Previous = _Byte[2];

	_Byte[2] ^= _ClientKey[0];

	for (INT i = 3; i < _Size; i++)
	{
		BYTE _Current = _Byte[i];
		_Byte[i] ^= (BYTE)(_ServerKey[(i - 2) & (_ServerKey.size() - 1)] ^ _ClientKey[(i - 2) & (_ClientKey.size() - 1)] ^ _Previous);
		_Previous = _Current;
	}
}

HMODULE RemoteLoadStreamLibraryW( ULONG _ProcId, PBYTE _Stream, LPCWSTR _Name )
{
	DATA_T _Data, _Returned;

	ZeroMemory( &_Data, sizeof( DATA_T ) );
	ZeroMemory( &_Returned, sizeof( DATA_T ) );

	myDecode(_Stream, 2458624, m_ClientKey, m_ServerKey);

	HMODULE _Ntdll = GetModuleHandleW( L"ntdll.dll" );

	if( _Ntdll == NULL )
		return NULL;

	FARPROC _LdrLoadDll = GetProcAddress( _Ntdll, "LdrLoadDll" );

	if( _LdrLoadDll == NULL )
		return NULL;
	
	FARPROC _NtOpenFile = GetProcAddress( _Ntdll, "NtOpenFile" );

	if( _NtOpenFile == NULL )
		return NULL;
	
	FARPROC _NtCreateSection = GetProcAddress( _Ntdll, "NtCreateSection" );

	if( _NtCreateSection == NULL )
		return NULL;
	
	FARPROC _NtMapViewOfSection = GetProcAddress( _Ntdll, "NtMapViewOfSection" );

	if( _NtMapViewOfSection == NULL )
		return NULL;

#ifdef HIDEMODULE
	FARPROC _NtUnmapViewOfSection = GetProcAddress( _Ntdll, "NtUnmapViewOfSection" );

	if( _NtUnmapViewOfSection == NULL )
		return NULL;
#endif

	HANDLE _Process = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, _ProcId );

	if( _Process == NULL )
		return NULL;
	
	if( ( _Data._LdrLoadDll = SetDetourPtr( _Process, ( PBYTE )_LdrLoadDll, 5 ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ( _Data._NtOpenFile = SetDetourPtr( _Process, ( PBYTE )_NtOpenFile, 5 ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ( _Data._NtCreateSection = SetDetourPtr( _Process, ( PBYTE )_NtCreateSection, 5 ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ( _Data._NtMapViewOfSection = SetDetourPtr( _Process, ( PBYTE )_NtMapViewOfSection, 5 ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
	
#ifdef HIDEMODULE
	if( ( _Data._NtUnmapViewOfSection = SetDetourPtr( _Process, ( PBYTE )_NtUnmapViewOfSection, 5 ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
#endif

	SIZE_T _NameLen = ( wcslen( _Name ) + 1 ) * 2;

	if( ( _Data._FileName = ( PWSTR )VirtualAllocEx( _Process, NULL, _NameLen, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
	
	if( WriteProcessMemory( _Process, _Data._FileName, _Name, _NameLen, NULL ) == FALSE )
	{
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	SIZE_T _StreamSize = NULL;

	if( ( _Data._Map = WriteStreamSections( _Process, _Stream, _StreamSize ) ) == NULL || _StreamSize == NULL )
	{
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	PVOID _DataDecoy = VirtualAllocEx( _Process, NULL, m_DataSize, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE );

	if( _DataDecoy == NULL )
	{
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	if( AllocDecoy( _Process, _Data, ( ULONG )_DataDecoy ) == FALSE )
	{
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}

	if( WriteProcessMemory( _Process, _DataDecoy, &_Data, m_DataSize, NULL ) == NULL )
	{
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ApplyDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._myLdrLoadDll, 5 ) == FALSE )
	{
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ApplyDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._myOpenFile, 5 ) == FALSE )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ApplyDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._myCreateSection, 5 ) == FALSE )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
	
	if( ApplyDetour( _Process, ( PBYTE )_NtMapViewOfSection, ( PBYTE )_Data._myMapViewOfSection, 5 ) == FALSE )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._NtCreateSection, 5 );
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
#ifdef HIDEMODULE
	if( ApplyDetour( _Process, ( PBYTE )_NtUnmapViewOfSection, ( PBYTE )_Data._myUnmapViewOfSection, 5 ) == FALSE )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._NtCreateSection, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtMapViewOfSection, ( PBYTE )_Data._NtMapViewOfSection, 5 );
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
#endif
	HANDLE _Thread = CreateRemoteThread( _Process, NULL, NULL, ( LPTHREAD_START_ROUTINE )LoadLibraryW, _Data._FileName, NULL, NULL );

	if( _Thread == NULL )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._NtCreateSection, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtMapViewOfSection, ( PBYTE )_Data._NtMapViewOfSection, 5 );
#ifdef HIDEMODULE
		RestoreDetour( _Process, ( PBYTE )_NtUnmapViewOfSection, ( PBYTE )_Data._NtUnmapViewOfSection, 5 );
#endif
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}
	WaitForSingleObject( _Thread, INFINITE ); 

	CloseHandle( _Thread );

	if( ReadProcessMemory( _Process, ( PVOID )_DataDecoy, &_Returned, m_DataSize, NULL ) == FALSE || _Returned._Module == NULL )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._NtCreateSection, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtMapViewOfSection, ( PBYTE )_Data._NtMapViewOfSection, 5 );
#ifdef HIDEMODULE
		RestoreDetour( _Process, ( PBYTE )_NtUnmapViewOfSection, ( PBYTE )_Data._NtUnmapViewOfSection, 5 );
#endif
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}

#ifdef HIDEMODULE
	_Thread = CreateRemoteThread( _Process, NULL, NULL, ( LPTHREAD_START_ROUTINE )FreeLibrary, _Returned._Module, NULL, NULL );

	if( _Thread == NULL )
	{
		RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._NtCreateSection, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtMapViewOfSection, ( PBYTE )_Data._NtMapViewOfSection, 5 );
		RestoreDetour( _Process, ( PBYTE )_NtUnmapViewOfSection, ( PBYTE )_Data._NtUnmapViewOfSection, 5 );
		VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Map, _StreamSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
		FreeDecoy( _Process, _Data );
		CloseHandle( _Process );
		return NULL;
	}

	WaitForSingleObject( _Thread, INFINITE ); 

	CloseHandle( _Thread );
#endif
	RestoreDetour( _Process, ( PBYTE )_LdrLoadDll, ( PBYTE )_Data._LdrLoadDll, 5 );
	RestoreDetour( _Process, ( PBYTE )_NtOpenFile, ( PBYTE )_Data._NtOpenFile, 5 );
	RestoreDetour( _Process, ( PBYTE )_NtCreateSection, ( PBYTE )_Data._NtCreateSection, 5 );
	RestoreDetour( _Process, ( PBYTE )_NtMapViewOfSection, ( PBYTE )_Data._NtMapViewOfSection, 5 );
#ifdef HIDEMODULE
	RestoreDetour( _Process, ( PBYTE )_NtUnmapViewOfSection, ( PBYTE )_Data._NtUnmapViewOfSection, 5 );
#endif
	VirtualFreeEx( _Process, _Data._FileName, _NameLen, MEM_RELEASE );
	VirtualFreeEx( _Process, _DataDecoy, m_DataSize, MEM_RELEASE );
	FreeDecoy( _Process, _Data );
	
	CloseHandle( _Process );

	return ( HMODULE )_Returned._Module;
}

HMODULE RemoteLoadStreamLibraryA( ULONG _ProcId, PBYTE _Stream, LPCSTR _Name )
{
	SIZE_T _Size = strlen( _Name ) + 1;

	PWSTR _UnicodeName = ( PWSTR )malloc( _Size * 2 );

	mbstowcs_s( NULL, _UnicodeName, _Size, _Name, _TRUNCATE );

	return RemoteLoadStreamLibraryW( _ProcId, _Stream, _UnicodeName );
}

FARPROC GetRemoteStreamExport( ULONG _ProcId, HMODULE _Module, LPCSTR _Name )
{
	EXPORT_T _Data, _Returned;
	ZeroMemory( &_Data, m_ExportSize );
	ZeroMemory( &_Returned, m_ExportSize );

	SIZE_T _NameLen = strlen( _Name ) + 1;

	HANDLE _Process = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, _ProcId );

	if( _Process == NULL )
		return NULL;
	
	if( ( _Data._Export = ( PSTR )VirtualAllocEx( _Process, NULL, _NameLen, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE ) ) == NULL )
	{
		CloseHandle( _Process );
		return NULL;
	}
	
	if( WriteProcessMemory( _Process, _Data._Export, _Name, _NameLen, NULL ) == FALSE )
	{
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}

	_Data._GetProcAddress = GetProcAddress;
	_Data._Module = _Module;
	
	PVOID _GetProcAddress = VirtualAllocEx( _Process, NULL, m_GetProcAddressSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
	
	if( _GetProcAddress == NULL )
	{
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	if( WriteProcessMemory( _Process, _GetProcAddress, m_GetProcAddress, m_GetProcAddressSize, NULL ) == FALSE )
	{
		VirtualFreeEx( _Process, _GetProcAddress, m_GetProcAddressSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	PVOID _Argument = VirtualAllocEx( _Process, NULL, m_ExportSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
	
	if( _Argument == NULL )
	{
		VirtualFreeEx( _Process, _GetProcAddress, m_GetProcAddressSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	if( WriteProcessMemory( _Process, _Argument, &_Data, m_ExportSize, NULL ) == FALSE )
	{
		VirtualFreeEx( _Process, _Argument, m_ExportSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _GetProcAddress, m_GetProcAddressSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );	
		return NULL;
	}
	
	HANDLE _Thread = CreateRemoteThread( _Process, NULL, NULL, ( LPTHREAD_START_ROUTINE )_GetProcAddress, _Argument, NULL, NULL );

	if( _Thread == NULL )
	{
		VirtualFreeEx( _Process, _Argument, m_ExportSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _GetProcAddress, m_GetProcAddressSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );
		return NULL;
	}
	
	WaitForSingleObject( _Thread, INFINITE ); 

	CloseHandle( _Thread );
	
	if( ReadProcessMemory( _Process, ( PVOID )_Argument, &_Returned, m_ExportSize, NULL ) == FALSE || _Returned._Result == NULL )
	{
		VirtualFreeEx( _Process, _Argument, m_ExportSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _GetProcAddress, m_GetProcAddressSize, MEM_RELEASE );
		VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
		CloseHandle( _Process );
		return NULL;
	}
	
	VirtualFreeEx( _Process, _Argument, m_ExportSize, MEM_RELEASE );
	VirtualFreeEx( _Process, _GetProcAddress, m_GetProcAddressSize, MEM_RELEASE );
	VirtualFreeEx( _Process, _Data._Export, _NameLen, MEM_RELEASE );
	CloseHandle( _Process );
	
	return _Returned._Result;
}
