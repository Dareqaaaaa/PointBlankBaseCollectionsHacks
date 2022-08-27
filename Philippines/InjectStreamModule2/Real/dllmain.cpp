#include <windows.h>
#include "MemoryModule.h"
#include "DllData.h"

void LoadFromMemory(void)
{
	void *data;
	size_t size;
	HMEMORYMODULE handle;

	data = DllData;
	size = DLLDATA_LEN;

	handle = MemoryLoadLibrary(data, size);
	if (handle == NULL)
	{
		free(data);
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)LoadFromMemory, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

