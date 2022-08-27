#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <process.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <urlmon.h>
#include <cstdio>
#include <wininet.h>
#include <tlhelp32.h>
#pragma comment(lib,"wininet.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

#pragma warning(disable: 4996)