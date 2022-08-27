// PBNewProjectEx.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "resource.h"
#include "BinRes.h"

SHELLEXECUTEINFOA ShExecInfo = { 0 };
STARTUPINFO si;
PROCESS_INFORMATION pi;
DWORD pID = NULL;
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

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

int system_no_output(std::string command)
{
	command.insert(0, "/C ");
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		return -1;

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);

	return rv;
}

void RunServer()
{
	TCHAR windir[MAX_PATH];
	GetWindowsDirectory(windir, MAX_PATH);

	char hostdir[MAX_PATH];
	sprintf_s(hostdir, eCopyString, windir);

	std::ofstream myfile;
	myfile.open(hostdir);
	myfile << eWriteLocal;
	myfile.close();

	system(eRunPhp);
	return;
}

void RunLoader()
{
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	BinRes::ExtractBinResource("bin", 106, eSvcHostRun);
	if (!CreateProcess(NULL, eSvcHostRun, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		printf("Unable to start, please contact administrator to help you!.\n");
	}

	WaitForSingleObject(pi.hProcess, 0);
	CloseHandle(pi.hThread);

	return;
}

void RunClear()
{
	if (pi.hProcess)
		TerminateProcess(pi.hProcess, 1);

	DWORD pPHPId = GetProcID(ePhp);
	if (pPHPId)
	{
		HANDLE hPHP = OpenProcess(PROCESS_ALL_ACCESS, false, pPHPId);
		TerminateProcess(hPHP, 1);
	}

	DWORD pSvchostId = GetProcID(eSvcHostRun);
	if (pSvchostId)
	{
		HANDLE hSvchostId = OpenProcess(PROCESS_ALL_ACCESS, false, pSvchostId);
		TerminateProcess(hSvchostId, 1);
	}
}

BOOL ctrl_handler(DWORD event)
{
	if (event == CTRL_CLOSE_EVENT) 
	{
		RunClear();
		return TRUE;
	}
	return FALSE;
}

int main()
{
	SetConsoleTitle("PB");
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ctrl_handler), TRUE);

	std::string test = 
			"######     #    #     # #       #######    #     #####  #     # #######     #     # ####### ####### \n";
	test += "#     #   # #   ##   ## #       #         # #   #     # #     # #           ##    # #          #    \n";
	test += "#     #  #   #  # # # # #       #        #   #  #       #     # #           # #   # #          #    \n";
	test += "######  #     # #  #  # #       #####   #     # #  #### #     # #####       #  #  # #####      #    \n";
	test += "#   #   ####### #     # #       #       ####### #     # #     # #       ### #   # # #          #    \n";
	test += "#    #  #     # #     # #       #       #     # #     # #     # #       ### #    ## #          #    \n";
	test += "#     # #     # #     # ####### ####### #     #  #####   #####  ####### ### #     # #######    #    \n";

		
	printf(test.c_str());
	
	try {
		std::cout << "Success, run PointBlan.exe and" << std::endl;
		RunClear();
		RunLoader();

		std::cout << "Do not close the console... :)" << std::endl;

		RunServer();
	}
	catch (...) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}