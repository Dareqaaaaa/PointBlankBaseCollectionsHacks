#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include "Xor.h"
#include "Header.h"
#include "HijackBase.h"


static void SafeCloseHandle(HANDLE processHandle)
{
	__try {
		if (processHandle)
			CloseHandle(processHandle);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
}


static HMODULE hNtdll = nullptr;
static lpNtQuerySystemInformation NtQuerySystemInformation = nullptr;
static lpNtDuplicateObject NtDuplicateObject = nullptr;

HandleHijack::CHandleHijack::CHandleHijack()
{
	hNtdll = LoadLibraryA(/*ntdll*/XorStr<0x96, 6, 0x7A53BD40>("\xF8\xE3\xFC\xF5\xF6" + 0x7A53BD40).s);

	NtQuerySystemInformation = (lpNtQuerySystemInformation)GetProcAddress(hNtdll, /*NtQuerySystemInformation*/XorStr<0x00, 25, 0x398E423A>("\x4E\x75\x53\x76\x61\x77\x7F\x54\x71\x7A\x7E\x6E\x61\x44\x60\x69\x7F\x63\x7F\x72\x60\x7C\x79\x79" + 0x398E423A).s);
	NtDuplicateObject = (lpNtDuplicateObject)GetProcAddress(hNtdll, /*NtDuplicateObject*/XorStr<0xE7, 18, 0x57092D38>("\xA9\x9C\xAD\x9F\x9B\x80\x84\x8D\x8E\x84\x94\xBD\x91\x9E\x90\x95\x83" + 0x57092D38).s);
}

int HandleHijack::CHandleHijack::FindHandle(DWORD dwTargetProcessId, LPDWORD pLastErr, LPHANDLE phHandle)
{
	HANDLE hProcess = nullptr;
	NTSTATUS status = 0;
	ULONG handleInfoSize = 0x10000;
	PSYSTEM_HANDLE_INFORMATION handleInfo = 0;
	HANDLE processHandle = nullptr;


	handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);
	ZeroMemory(handleInfo, handleInfoSize);

	while ((status = NtQuerySystemInformation(SystemHandleInformation, handleInfo, handleInfoSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH)
	{
		handleInfoSize *= 2;
		handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize);
	}

	if (!NT_SUCCESS(status)) {
		free(handleInfo);
		*pLastErr = GetLastError();
		return -1;
	}

	for (ULONG i = 0; i < handleInfo->HandleCount; i++)
	{
		auto handle = handleInfo->Handles[i];
		HANDLE dupHandle = NULL;

		if (handle.ObjectTypeNumber != 0x5 && handle.ObjectTypeNumber != 0x7) /* Just process handles */
			continue;


		SafeCloseHandle(processHandle);

		processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, handle.ProcessId);
		if (!processHandle || processHandle == INVALID_HANDLE_VALUE)
			continue;


		status = NtDuplicateObject(processHandle, (HANDLE)handle.Handle, NtCurrentProcess, &dupHandle, PROCESS_ALL_ACCESS, 0, 0);
		if (!NT_SUCCESS(status))
		{
			*pLastErr = GetLastError();
			continue;
		}


		if (GetProcessId(dupHandle) != dwTargetProcessId) {
			SafeCloseHandle(dupHandle);
			continue;
		}


		hProcess = dupHandle;
		break;
	}

	free(handleInfo);
	SafeCloseHandle(processHandle);

	if (!hProcess)
		return -2;

	SetLastError(ERROR_SUCCESS);
	*phHandle = hProcess;

	return 0;
}