class Memory
{
public:

	template <typename Type, typename Base, typename Offset>
	static inline Type Ptr(Base base, Offset offset)
	{
		static_assert(std::is_pointer<Type>::value || std::is_integral<Type>::value, "Type must be a pointer or address");
		static_assert(std::is_pointer<Base>::value || std::is_integral<Base>::value, "Base must be a pointer or address");
		static_assert(std::is_pointer<Offset>::value || std::is_integral<Offset>::value, "Offset must be a pointer or address");

		return base ? reinterpret_cast<Type>((reinterpret_cast<uint64_t>(base) + static_cast<uint64_t>(offset))) : nullptr;
	}

	template <typename Type>
	static bool IsValidPtr(Type* ptr)
	{
		return (ptr && sizeof(ptr)) ? true : false;
	}

	static bool IsValidPtr(void* ptr)
	{
		return (ptr && sizeof(ptr)) ? true : false;
	}

	static class CAllocate
	{
	public:
		static void* Alloc(HANDLE hProcess, size_t Size)
		{
			return VirtualAllocEx(hProcess, NULL, Size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		}

		static void* Commit(HANDLE hProcess, void* Data, size_t Size)
		{
			void* AllocatedPointer = Alloc(hProcess, Size);
			if (AllocatedPointer)
			{
				if (WriteProcessMemory(hProcess, AllocatedPointer, Data, Size, NULL) == TRUE)
				{
					return AllocatedPointer;
				}
				Free(hProcess, AllocatedPointer, Size);
			}
			return NULL;
		}

		static void Free(HANDLE hProcess, void* Data, size_t Size)
		{
			VirtualFreeEx(hProcess, Data, Size, MEM_RELEASE);
		}
	}Allocate;

	static int GetHealth(DWORD ASM_GetHealth, DWORD Ptr)
	{
		void* pMemory = VirtualAllocEx(hProcess, 0, 4, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (!pMemory)
		{
			return 0;
		}

		HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)ASM_GetHealth, (void*)(Ptr), 0, 0);
		if (!hThread)
		{
			printf("Failed to create thread.\n");
			return 0;
		}
		WaitForSingleObject(hThread, INFINITE);
		DWORD dwExit = 0;
		GetExitCodeThread(hThread, &dwExit);
		return dwExit;
	}

	template<typename T>
	static T ReadMem(SIZE_T address)
	{
		T buffer;
		ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}
	static std::string ReadStr(SIZE_T address, int Size)
	{
		std::string buffer;
		ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, Size, NULL);
		return buffer;
	}

	template <class cData>
	static void Write(DWORD dwAddress, cData Value)
	{
		WriteProcessMemory(hProcess, (LPVOID)dwAddress, &Value, sizeof(cData), NULL);
	}

	template <class cData>
	static void Write(DWORD dwAddress, char *Offset, cData Value)
	{
		Write<cData>(Read<cData>(dwAddress, Offset, false), Value);
	}
}Mem;

DWORD GetProcID(char* ProcName)//Get ProcessId By Name
{
	PROCESSENTRY32   pe32;
	HANDLE         hSnapshot = NULL;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(hSnapshot, &pe32))
	{
		do {
			if (strcmp(pe32.szExeFile, ProcName) == 0)
			{
				return pe32.th32ProcessID;
			}
		} while (Process32Next(hSnapshot, &pe32));
	}

	if (hSnapshot != INVALID_HANDLE_VALUE)
		CloseHandle(hSnapshot);
	return 0;

}

DWORD dwGetModuleBaseAddress(DWORD dwProcessIdentifier, TCHAR *lpszModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessIdentifier);
	DWORD dwModuleBaseAddress = 0;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (strcmp(ModuleEntry32.szModule, lpszModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}






/*
#include <Windows.h>
#include <Psapi.h>
#include <ntstatus.h>
#include <cstdint>
#include <functional>
#include <Shlwapi.h>
#include <winternl.h>

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "Shlwapi.lib")

typedef struct _OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccessMask;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	ULONG PoolType;
	ULONG DefaultPagedPoolCharge;
	ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

NTSTATUS NTAPI NtQueryObject(
	_In_opt_   HANDLE Handle,
	_In_       OBJECT_INFORMATION_CLASS ObjectInformationClass,
	_Out_opt_  PVOID ObjectInformation,
	_In_       ULONG ObjectInformationLength,
	_Out_opt_  PULONG ReturnLength
);

NTSTATUS WINAPI NtQuerySystemInformation(
	_In_       SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_    PVOID SystemInformation,
	_In_       ULONG SystemInformationLength,
	_Out_opt_  PULONG ReturnLength
);

typedef std::function<NTSTATUS(PSYSTEM_HANDLE_TABLE_ENTRY_INFO)> ENUM_HANDLE_CALLBACK;

NTSTATUS enumerate_handles(ENUM_HANDLE_CALLBACK callback)
{
	NTSTATUS                    status = STATUS_UNSUCCESSFUL;
	PVOID                       buffer = NULL;
	ULONG                       bufferSize = 0;

	do {
		status = NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)16, buffer, bufferSize, &bufferSize);
		if (!NT_SUCCESS(status)) {
			if (status == STATUS_INFO_LENGTH_MISMATCH) {
				if (buffer != NULL)
					VirtualFree(buffer, 0, MEM_RELEASE);
				buffer = VirtualAlloc(NULL, bufferSize, MEM_COMMIT, PAGE_READWRITE);
				continue;
			}
			break;
		}
		else {
			PSYSTEM_HANDLE_INFORMATION handleInfo = (PSYSTEM_HANDLE_INFORMATION)buffer;
			for (ULONG i = 0; i < handleInfo->NumberOfHandles; i++) {
				auto handle = &handleInfo->Handles[i];
				status = callback(handle);
				if (NT_SUCCESS(status))
					break;
			}
			break;
		}
	} while (true);
	if (buffer != NULL)
		VirtualFree(buffer, 0, MEM_RELEASE);
	return status;
}

HANDLE get_handle_to_process(LPWSTR process)
{
	HANDLE hProcess = NULL;

	enumerate_handles([&](PSYSTEM_HANDLE_TABLE_ENTRY_INFO handle) {

		if (GetCurrentProcessId() != handle->UniqueProcessId) return STATUS_UNSUCCESSFUL;

		BOOL        found = FALSE;
		PVOID       buffer = NULL;
		ULONG       bufferSize = 0x100;
		NTSTATUS    status;

		if (handle->ObjectTypeIndex == 7) {
			WCHAR processPath[MAX_PATH] = {};
			if (GetModuleFileNameExW((HANDLE)handle->HandleValue, NULL, processPath, MAX_PATH)) {
				LPWSTR filename = PathFindFileNameW(processPath);
				if (!wcscmp(filename, process)) {
					found = TRUE;
					hProcess = (HANDLE)handle->HandleValue;
				}
			}
		}
		if (found)
			return STATUS_SUCCESS;

		return STATUS_UNSUCCESSFUL;
	});

	return hProcess;
}*/