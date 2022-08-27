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
		status = NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)16/*SystemHandleInformation*/, buffer, bufferSize, &bufferSize);
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

void print_handle_information()
{
	enumerate_handles([](PSYSTEM_HANDLE_TABLE_ENTRY_INFO handle) {

		if (GetCurrentProcessId() != handle->UniqueProcessId) return STATUS_UNSUCCESSFUL;

		printf("Handle Object:  0x%p\n", handle->Object);
		printf("Handle Value:   0x%04X\n", handle->HandleValue);
		printf("Granted Access: 0x%08X\n", handle->GrantedAccess);

		//
		// Print name information
		// 
		PVOID       buffer = NULL;
		ULONG       bufferSize = 0x100;
		NTSTATUS    status;

		do {
			buffer = VirtualAlloc(NULL, bufferSize, MEM_COMMIT, PAGE_READWRITE);
			status = NtQueryObject((HANDLE)handle->HandleValue, (OBJECT_INFORMATION_CLASS)1/*ObjectNameInformation*/, buffer, bufferSize, &bufferSize);
			if (NT_SUCCESS(status)) break;
			if (buffer != NULL)
				VirtualFree(buffer, 0, MEM_RELEASE);
		} while (status == STATUS_INFO_LENGTH_MISMATCH);

		if (!NT_SUCCESS(status))
			goto EXIT;

		printf("Name:           %ws\n", ((POBJECT_NAME_INFORMATION)buffer)->Name.Buffer);

		VirtualFree(buffer, 0, MEM_RELEASE);

		do {
			buffer = VirtualAlloc(NULL, bufferSize, MEM_COMMIT, PAGE_READWRITE);
			status = NtQueryObject((HANDLE)handle->HandleValue, ObjectTypeInformation, buffer, bufferSize, &bufferSize);
			if (NT_SUCCESS(status)) break;
			if (buffer != NULL)
				VirtualFree(buffer, 0, MEM_RELEASE);
		} while (status == STATUS_INFO_LENGTH_MISMATCH);

		if (!NT_SUCCESS(status))
			goto EXIT;

		printf("Type:           %ws\n", ((POBJECT_TYPE_INFORMATION)buffer)->TypeName.Buffer);

		//
		// 7 is the process type index on my system. It's possible that this is different value on your system.
		// You can compare the TypeName to "Process" instead of doing it like this
		//
		if (handle->ObjectTypeIndex == 7) {
			WCHAR processPath[MAX_PATH];
			//
			// The handle needs to have PROCESS_QUERY_INFORMATION and PROCESS_VM_READ
			// access, otherwise this call fails
			// 
			if (GetModuleFileNameExW((HANDLE)handle->HandleValue, NULL, processPath, MAX_PATH))
				printf("Process:        %ws\n", PathFindFileNameW(processPath));
		}
		printf("-------------------------------------------------\n");

	EXIT:
		if (buffer != NULL)
			VirtualFree(buffer, 0, MEM_RELEASE);

		return STATUS_UNSUCCESSFUL;
	});
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

		//
		// 7 is the process type index. It's possible that this is different value on your system. 
		// Check the output print_handle_information for more info. You can compare the TypeName to
		// "Process" instead of doing it like this
		//
		if (handle->ObjectTypeIndex == 7) {
			WCHAR processPath[MAX_PATH] = {};
			//
			// The handle needs to have PROCESS_QUERY_INFORMATION and PROCESS_VM_READ
			// access, otherwise this call fails
			// 
			if (GetModuleFileNameExW((HANDLE)handle->HandleValue, NULL, processPath, MAX_PATH)) {
				LPWSTR filename = PathFindFileNameW(processPath);
				if (!wcscmp(filename, process)) {
					found = TRUE;
					hProcess = (HANDLE)handle->HandleValue;
				}
			}
		}

		//
		// STATUS_SUCCESS stops the enumeration
		//
		if (found)
			return STATUS_SUCCESS;

		return STATUS_UNSUCCESSFUL;
	});

	return hProcess;
}