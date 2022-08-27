#ifdef _DEBUG
#error "KAMEHAMEHA HAS TO BE DONE IN RELEASE MODE"
#endif

#pragma comment( lib, "../Release/InjectStreamModule.lib" )

#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <wininet.h>
#pragma comment(lib, "wininet")
#include <cpr/cpr.h>
#include "xor.h"
#include "resource.h"
#include "DllData.h"

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

HMODULE RemoteLoadStreamLibraryW( ULONG, PBYTE, LPCWSTR ), RemoteLoadStreamLibraryA( ULONG, PBYTE, LPCSTR );
FARPROC GetRemoteStreamExport( ULONG, HMODULE, LPCSTR );

/*
//Credits NcSoft( reversed from aion packet handler )
VOID myEncode( PBYTE _Byte, INT _Size, std::string _ClientKey, std::string _ServerKey )
{
	_Byte[ 2 ] ^= _ClientKey[ 0 ];

	BYTE _Previous = _Byte[ 2 ];

	for( INT i = 3; i < _Size; i++ )
	{
		_Byte[ i ] ^= ( BYTE ) ( _ServerKey[ ( i - 2 ) & ( _ServerKey.size( ) - 1 ) ] ^ _ClientKey[ ( i - 2 ) & ( _ClientKey.size( ) - 1 ) ] ^ _Previous );
		_Previous = _Byte[ i ];
	}
}
*/
//Credits NcSoft( reversed from aion packet handler )
/*
VOID myDecode( PBYTE _Byte, INT _Size, std::string _ClientKey, std::string _ServerKey )
{
	BYTE _Previous = _Byte[ 2 ];

	_Byte[ 2 ] ^= _ClientKey[ 0 ];

	for( INT i = 3; i < _Size; i++ )
	{
		BYTE _Current = _Byte[ i ];
		_Byte[ i ] ^= ( BYTE )( _ServerKey[ ( i - 2 ) & ( _ServerKey.size( ) - 1 ) ] ^ _ClientKey[ ( i - 2 ) & ( _ClientKey.size( ) - 1 ) ] ^ _Previous );
		_Previous = _Current;
	}
}*/


BOOL CheckKey(char * zKey)
{
	try {
		if (strlen(zKey) < 10)
			return false;

		HW_PROFILE_INFO hwProfileInfo;
		if (GetCurrentHwProfile(&hwProfileInfo) != NULL)
		{
			char buff[MAX_PATH];
			sprintf_s(buff, /*http://pbvipcit.ramleague.net/api/getKey?key=%s&hwid=%s*/XorStr<0xED, 56, 0x28932775>("\x85\x9A\x9B\x80\xCB\xDD\xDC\x84\x97\x80\x9E\x88\x9A\x93\x8F\xD2\x8F\x9F\x92\x6C\x64\x63\x64\x71\x60\x28\x69\x6D\x7D\x25\x6A\x7C\x64\x21\x68\x75\x65\x59\x76\x6D\x2A\x7D\x72\x61\x24\x3F\x68\x3A\x75\x69\x76\x44\x1C\x07\x50" + 0x28932775).s, zKey, hwProfileInfo.szHwProfileGuid);
			auto getUser = cpr::Get(cpr::Url{ buff });

			if (strlen(getUser.text.c_str()) < 10)
				return false;

			if (strcmp(getUser.text.c_str(), hwProfileInfo.szHwProfileGuid) == 0)
				return true;
		}
		return false;
	}
	catch (...){
		return false;
	}
	return false;
}

LOGFONT		lf;
HFONT		hFont;
HDC			hDC;
void SetFont(HWND &hDlg, LOGFONT &lf, HFONT &hFont, HDC &hDC, int nIDDlgItem, int nPoint, const char *cchFontName, bool isBold) {
	hDC = GetDC(NULL);
	lf.lfHeight = MulDiv(nPoint, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	lf.lfWeight = (isBold) ? FW_BOLD : FW_NORMAL;
	ReleaseDC(NULL, hDC);
	lstrcpy(lf.lfFaceName, cchFontName);
	hFont = CreateFontIndirect(&lf);
	SendDlgItemMessage(hDlg, nIDDlgItem, WM_SETFONT, (WPARAM)hFont, 0);
}

DWORD GetProcID(const char* ProcName)
{
	PROCESSENTRY32   pe32;
	HANDLE hSnapshot = NULL;
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

DWORD PID = NULL;
HANDLE WindowHandle = NULL;
HINSTANCE _Hinstance = NULL;
BOOL bIsReadyToInject = FALSE;
INT TIMER_INJECTED_COUNT = 0;
enum {
	TIMER_PROCESS_DETECTED = 10000,
};

typedef void(_cdecl* func)();
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lPara)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFont(hwnd, lf, hFont, hDC, ID_WAITING, 15, "Arial", true);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			char szInput[MAX_PATH];
			GetDlgItemText(hwnd, IDC_EDIT1, szInput, MAX_PATH);

			if (CheckKey(szInput))
			{
				ShowWindow(GetDlgItem(hwnd, ID_WAITING), SW_SHOW);
				ShowWindow(GetDlgItem(hwnd, IDOK), SW_HIDE);
				ShowWindow(GetDlgItem(hwnd, IDC_EDIT1), SW_HIDE);
				MessageBox(0, /*Success*/XorStr<0xA5, 8, 0x7925773E>("\xF6\xD3\xC4\xCB\xCC\xD9\xD8" + 0x7925773E).s, /*Notice*/XorStr<0x76, 7, 0xE198C726>("\x38\x18\x0C\x10\x19\x1E" + 0xE198C726).s, 0);
				bIsReadyToInject = true;
				SetTimer(hwnd, TIMER_PROCESS_DETECTED, 4000, 0);
			}
			else {
				MessageBox(0, /*Invalid Key or expired key*/XorStr<0x9B, 27, 0xF7D4BCA1>("\xD2\xF2\xEB\xFF\xF3\xC9\xC5\x82\xE8\xC1\xDC\x86\xC8\xDA\x89\xCF\xD3\xDC\xC4\xDC\xCA\xD4\x91\xD9\xD6\xCD" + 0xF7D4BCA1).s,  /*Notice*/XorStr<0x76, 7, 0xE198C726>("\x38\x18\x0C\x10\x19\x1E" + 0xE198C726).s, 0);
				EndDialog(hwnd, 0);
				return FALSE;
				break;
			}
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			return FALSE;
			break;
		}
		break;
	case WM_TIMER:
		switch (LOWORD(wParam))
		{
		case TIMER_PROCESS_DETECTED:
			if (bIsReadyToInject)
			{
				PID = GetProcID(/*PointBlank.exe*/XorStr<0x29, 15, 0xD52EF2FA>("\x79\x45\x42\x42\x59\x6C\x43\x51\x5F\x59\x1D\x51\x4D\x53" + 0xD52EF2FA).s);
				if (PID)
				{
					SetWindowText(GetDlgItem(hwnd, ID_WAITING), /*Injecting...*/XorStr<0x52, 13, 0xF7DE533E>("\x1B\x3D\x3E\x30\x35\x23\x31\x37\x3D\x75\x72\x73" + 0xF7DE533E).s);
					char _Directory[MAX_SIZE_SECURITY_ID] = { NULL };

					if (GetModuleFileNameA(_Hinstance, _Directory, MAX_SIZE_SECURITY_ID) == NULL)
						return EXIT_SUCCESS;

					std::string _Local(_Directory);

					_Local = _Local.substr(NULL, _Local.find_last_of("\\") + 1);

					std::string _DummyFile = _Local + "Library.dll";

					if (GetFileAttributesA(_DummyFile.c_str()) == INVALID_FILE_ATTRIBUTES)
						return EXIT_SUCCESS;

					HMODULE _Real = RemoteLoadStreamLibraryA(PID, DllData, _DummyFile.c_str());

					if (_Real) {
						//ShellExecute(NULL, "open", /*http://www.ramleague.net/*/XorStr<0xD2, 26, 0x8B52397A>("\xBA\xA7\xA0\xA5\xEC\xF8\xF7\xAE\xAD\xAC\xF2\xAF\xBF\xB2\x8C\x84\x83\x84\x91\x80\xC8\x89\x8D\x9D\xC5" + 0x8B52397A).s, NULL, NULL, SW_SHOWNORMAL);
						KillTimer(hwnd, TIMER_PROCESS_DETECTED);
						EndDialog(hwnd, 0);
					}
					else
					{
						TIMER_INJECTED_COUNT++;
						if (TIMER_INJECTED_COUNT >= 5)
						{
							KillTimer(hwnd, TIMER_PROCESS_DETECTED);
							MessageBox(NULL, /*INJECTION FAILED*/XorStr<0x18, 17, 0x44B88817>("\x51\x57\x50\x5E\x5F\x49\x57\x50\x6E\x01\x64\x62\x6D\x69\x63\x63" + 0x44B88817).s, NULL, MB_OK);
							EndDialog(hwnd, 0);
						}
					}
					return FALSE;
				}
			}
			return FALSE;
			break;
		}
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return FALSE;
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

INT __stdcall WinMain( HINSTANCE _hinstance, HINSTANCE _prev, LPSTR _command, INT _cmdshow ) 
{
	_Hinstance = _hinstance;
	DialogBoxParam(_hinstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DlgProc), 0);
	return EXIT_SUCCESS;
}