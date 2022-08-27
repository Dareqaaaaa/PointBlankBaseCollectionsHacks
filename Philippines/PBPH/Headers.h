/*********************************************************/
/* CA Base D3D Menu Selection V5
/* Creditos:
/*	Solify's	-> CA Base D3D Menu Selection.
/*  WE11ington  -> Disponibilizou Para Combat Arms Brasil.
/*  luizimloko  -> Menu Selection V5.
/*********************************************************/
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <process.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <string>
#include <iostream>
#include <tchar.h>
#include <urlmon.h>
#include <time.h>
#include <cstdio>
#include<wininet.h>
#include <tlhelp32.h>
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "urlmon.lib")

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

void GetD3D( HMODULE hModule );

extern DWORD dwSPresent;