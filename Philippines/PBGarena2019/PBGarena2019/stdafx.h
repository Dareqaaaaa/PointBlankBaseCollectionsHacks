// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <fstream>
#include <tlhelp32.h>
#include <iostream>
#include <list>
#include <process.h>
#include <stdint.h>
#include <string>
#include <detours.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "Xor.h"
#include "Address.h"
#include "Utils.h"
#include "Menu.h"
#include "Function.h"
#include "PBGarena2019.h"


// reference additional headers your program requires here
