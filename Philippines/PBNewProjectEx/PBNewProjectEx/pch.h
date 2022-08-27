// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <iostream>
#include <fstream>
#include <process.h>
#include <thread>
#include <io.h> 
#include <string>
#include <tlhelp32.h>
#include <sstream>
#include <direct.h>
#include <wininet.h>
#pragma comment(lib, "wininet")

#include "Xor.h"

#pragma comment( lib, "InjectStreamModule.lib" )

#include <cpr/cpr.h>


HMODULE RemoteLoadStreamLibraryW(ULONG, PBYTE, LPCWSTR),
RemoteLoadStreamLibraryA(ULONG, PBYTE, LPCSTR);

FARPROC GetRemoteStreamExport(ULONG, HMODULE, LPCSTR);

// TODO: add headers that you want to pre-compile here

#endif //PCH_H
