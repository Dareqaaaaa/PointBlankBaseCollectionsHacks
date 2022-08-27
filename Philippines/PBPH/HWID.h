DWORD FindProcessId(char* processName)
{
    char* p = strrchr(processName, '\\');
    if(p) processName = p+1;
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);
    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if ( processesSnapshot == INVALID_HANDLE_VALUE ) return 0;
    Process32First(processesSnapshot, &processInfo);
    if ( !strcmp(processName, processInfo.szExeFile) ){CloseHandle(processesSnapshot); return processInfo.th32ProcessID; }
    while ( Process32Next(processesSnapshot, &processInfo) )  { if ( !strcmp(processName, processInfo.szExeFile) ) { CloseHandle(processesSnapshot);return processInfo.th32ProcessID;}}
    CloseHandle(processesSnapshot);
    return 0;
}

int __cdecl GetHWID(LPCSTR lpszUrl, LPCSTR lpszAgent)
{
  HINTERNET v3, v4; 
  int result;
  DWORD dwNumberOfBytesRead;
  char Buffer[15000];
  v3 = InternetOpenA(lpszAgent, 0, 0, 0, 0);
  v4 = InternetOpenUrlA(v3, lpszUrl, 0, 0, 0x80000000u, 0);
  dwNumberOfBytesRead = 15;
  InternetReadFile(v4, Buffer, 0xFu, &dwNumberOfBytesRead);
  Buffer[dwNumberOfBytesRead] = 0;
  std::string myString = Buffer;
  result = atoi(myString.c_str());
  return result;
}

UCHAR szFileSys[255], szVolNameBuff[255];
DWORD dwMFL, dwSysFlags, dwSerial;
bool CheckValidHardwareID(int HWIDUser1, int HWIDUser2 , int HWIDUser3)
{
	GetVolumeInformation("C:\\",(LPTSTR)szVolNameBuff,255,&dwSerial, &dwMFL,&dwSysFlags,(LPTSTR)szFileSys,255);
	if (dwSerial == HWIDUser1 || dwSerial == HWIDUser2 || dwSerial == HWIDUser3)
	{
		return true;
	}else{
		return false;
	}
}
