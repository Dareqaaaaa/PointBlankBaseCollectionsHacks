#include "stdafx.h"

UtilsT* Utils = new UtilsT();

inline bool UtilsT::IsHandleValid(HANDLE h) 
{ 
	return h != INVALID_HANDLE_VALUE; 
}
inline BOOL UtilsT::ProperlyCloseHandle(HANDLE h) 
{
	auto const b = CloseHandle(h);
	assert(b);
	return b;
}

BOOL UtilsT::GetPID(const wchar_t * lpwstrProcessName, DWORD* pid)
{
	PROCESSENTRY32W proc;
	proc.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	*pid = -1;

	if (!IsHandleValid(hSnap))
		return false;

	if (Process32FirstW(hSnap, &proc)) {
		do {
			if (wcscmp(lpwstrProcessName, proc.szExeFile) == 0)
			{
				ProperlyCloseHandle(hSnap);
				*pid = proc.th32ProcessID;
				return true;
			}
		} while (Process32NextW(hSnap, &proc));
	}

	ProperlyCloseHandle(hSnap);
	return false;
}

DWORD UtilsT::EnumRegions(HANDLE hProcess, DWORD ADR_CHARACTERPOINTER, DWORD falseBase)
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
				if (ADR_Char)
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