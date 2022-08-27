// dxtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cpr/cpr.h>

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		SetConsoleTitle(/*PointBlank PH Cheat Updated - www.ramleague.net*/XorStr<0x62, 48, 0x99CA3988>("\x32\x0C\x0D\x0B\x12\x25\x04\x08\x04\x00\x4C\x3D\x26\x4F\x33\x19\x17\x12\x00\x55\x23\x07\x1C\x18\x0E\x1E\x18\x5D\x53\x5F\xF7\xF6\xF5\xAD\xF6\xE4\xEB\xEB\xED\xE8\xED\xFE\xE9\xA3\xE0\xEA\xE4" + 0x99CA3988).s);
		printf("Waiting for pointblank.exe...\n");
		while (!Utils->Attach(/*PointBlank.exe*/ XorStr<0xA4, 15, 0xF3555841>("\xF4\xCA\xCF\xC9\xDC\xEB\xC6\xCA\xC2\xC6\x80\xCA\xC8\xD4" + 0xF3555841).s, PROCESS_ALL_ACCESS)) {
			Sleep(100);
		}
		Utils->GetClientModule();
		printf("Hack Initiated.\n");
		printf("Do not close this window!\n");
		while (true)
		{
			Overlay->RefreshOverlay();
			Function->CallMemory();
		}
	}
	catch(...){
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

