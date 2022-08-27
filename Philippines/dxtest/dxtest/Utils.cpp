#include "stdafx.h"

UtilsT* Utils = new UtilsT();

bool UtilsT::Attach(const char* pName, DWORD rights)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);

	do
		if (!strcmp(entry.szExeFile, pName)) {
			pID = entry.th32ProcessID;
			CloseHandle(handle);
			_process = OpenProcess(rights, false, pID);
			return true;
		}
	while (Process32Next(handle, &entry));
	return false;
}

PModule UtilsT::GetModule(const char* moduleName) {
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
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

PModule UtilsT::GetBaseAddress()
{
	PModule mod = { (DWORD)false,(DWORD)false };;
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	uintptr_t address = 0;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	while (address < reinterpret_cast<uintptr_t>(si.lpMaximumApplicationAddress))
	{
		SIZE_T size = VirtualQueryEx(_process, reinterpret_cast<LPVOID>(address), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (!size)
			address += si.dwPageSize;

		if (mbi.Protect == PAGE_EXECUTE_READWRITE && mbi.RegionSize >= 10000000)
		{
			mod = { (DWORD)mbi.BaseAddress,(DWORD)mbi.RegionSize };
		}
		address += mbi.RegionSize;
	}
	return mod;
}

PModule* UtilsT::GetClientModule() {
	if (modBase.dwBase == 0 && modBase.dwSize == 0)
	{
		modBase = GetBaseAddress();
	}
	if (modi3SceneDx.dwBase == 0 && modi3SceneDx.dwSize == 0) {
		modi3SceneDx = GetModule("i3SceneDx.dll");
	}
	if (modi3GfxDx.dwBase == 0 && modi3GfxDx.dwSize == 0){
		modi3GfxDx = GetModule("i3GfxDx.dll");
	}
	return &modBase;
}